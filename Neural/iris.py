

import os
import csv
import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
from sklearn.model_selection import StratifiedShuffleSplit, train_test_split
from sklearn.preprocessing import OneHotEncoder
from sklearn.metrics import classification_report, confusion_matrix
from neuralnet import NeuralNet, StepLRScheduler

# --- 0. Config ---
PREDICTION_DIR = "prediction_outputs"
os.makedirs(PREDICTION_DIR, exist_ok=True)

# --- 1. Load and preprocess iris data ---
iris = load_iris()
X = iris.data.astype(np.float32)  # Use raw features
y = iris.target.reshape(-1, 1)

# One-hot encoding the labels
encoder = OneHotEncoder(sparse_output=False)
y_onehot = encoder.fit_transform(y)

# Stratified split: labeled and unlabeled
sss = StratifiedShuffleSplit(n_splits=1, test_size=0.5, random_state=42)
for train_idx, unlabeled_idx in sss.split(X, y):
    X_labeled, X_unlabeled = X[train_idx], X[unlabeled_idx]
    y_labeled, y_unlabeled = y_onehot[train_idx], y_onehot[unlabeled_idx]

# Validation split from labeled data
X_train, X_val, y_train, y_val = train_test_split(
    X_labeled, y_labeled, test_size=0.1, random_state=42, stratify=np.argmax(y_labeled, axis=1)
)

# --- 2. Initialize neural network ---
net = NeuralNet(
    layers=[4, 32, 3],  # Iris has 4 features, 3 classes
    activation="relu",
    optimizer="sgdmomentum",
    learning_rate=0.01,  # Adjusted learning rate
    loss="crossentropy",
    momentum=0.9,
    lr_scheduler=StepLRScheduler(step_size=20, gamma=0.5)
)

# --- 3. Train on labeled data ---
print("Initial training on labeled data...")
train_losses, val_losses = [], []
best_val_loss = float('inf')

for epoch in range(20):
    net.train(X_train.tolist(), y_train.tolist(), epochs=1, batch_size=32)

    # Calculate training loss
    train_out = [net.forward(x) for x in X_train]
    train_loss = np.mean([
        -np.sum(y_true * np.log(np.clip(np.array(out), 1e-8, 1.0)))
        for out, y_true in zip(train_out, y_train)
    ])

    # Calculate validation loss
    val_out = [net.forward(x) for x in X_val]
    val_loss = np.mean([
        -np.sum(y_true * np.log(np.clip(np.array(out), 1e-8, 1.0)))
        for out, y_true in zip(val_out, y_val)
    ])

    train_losses.append(train_loss)
    val_losses.append(val_loss)

    print(f"Epoch {epoch+1}/20 - Train Loss: {train_loss:.4f} - Val Loss: {val_loss:.4f}")

    if val_loss < best_val_loss:
        best_val_loss = val_loss
        # Save best model if needed

# --- 4. Predict on unlabeled data and save outputs ---
unlabeled_outputs = np.array(net.batch_forward(X_unlabeled.tolist()))
np.save(os.path.join(PREDICTION_DIR, "pseudo_probs.npy"), unlabeled_outputs)

with open(os.path.join(PREDICTION_DIR, "pseudo_probs.csv"), "w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(["index", "pred_label", "confidence"] + [f"class_{i}" for i in range(3)])
    for i, probs in enumerate(unlabeled_outputs):
        pred = int(np.argmax(probs))
        conf = float(np.max(probs))
        writer.writerow([i, pred, conf] + list(np.round(probs, 6)))

# --- 5. Select confident pseudo-labels using entropy ---
entropy = -np.sum(np.clip(unlabeled_outputs, 1e-8, 1.0) * np.log(np.clip(unlabeled_outputs, 1e-8, 1.0)), axis=1)
confident_idx = np.where(entropy < 0.5)[0]
print(f"Confident pseudo-labels: {len(confident_idx)}")

pseudo_X = X_unlabeled[confident_idx]
pseudo_y = np.argmax(unlabeled_outputs[confident_idx], axis=1)
pseudo_y_onehot = np.zeros((len(pseudo_y), 3))  # 3 classes
pseudo_y_onehot[np.arange(len(pseudo_y)), pseudo_y] = 1.0

# --- 6. Combine labeled + pseudo-labeled data and retrain ---
X_aug = np.concatenate([X_labeled, pseudo_X], axis=0)
y_aug = np.concatenate([y_labeled, pseudo_y_onehot], axis=0)

print("Retraining model with pseudo-labeled data...")
self_train_losses = []

for epoch in range(10):
    net.train(X_aug.tolist(), y_aug.tolist(), epochs=1, batch_size=32)
    outputs = [net.forward(x) for x in X_aug]
    loss = np.mean([
        -np.sum(y_true * np.log(np.clip(np.array(out), 1e-8, 1.0)))
        for out, y_true in zip(outputs, y_aug)
    ])
    self_train_losses.append(loss)
    print(f"Self-Train Epoch {epoch+1}/10 - Train Loss: {loss:.4f}")

# --- 7. Final test evaluation ---
X_test, _, y_test, _ = train_test_split(
    X_unlabeled, y_unlabeled, test_size=0.2, random_state=42
)

test_outputs = [net.forward(x) for x in X_test.tolist()]
preds = np.argmax(test_outputs, axis=1)
truths = np.argmax(y_test, axis=1)
accuracy = (preds == truths).mean() * 100

test_loss = np.mean([
    -np.sum(y_true * np.log(np.clip(np.array(out), 1e-8, 1.0)))
    for out, y_true in zip(test_outputs, y_test)
])

print(f"After self-training -> Test Loss: {test_loss:.4f} - Test Accuracy: {accuracy:.2f}%")

# --- 8. Plot learning curve ---
plt.figure(figsize=(14, 5))
plt.plot(train_losses, label="Train Loss")
plt.plot(val_losses, label="Val Loss")
plt.plot(range(len(train_losses), len(train_losses) + len(self_train_losses)), self_train_losses, label="Self-Train Loss")
plt.xlabel("Epoch")
plt.ylabel("Loss")
plt.title("Training Loss Curve")
plt.legend()
plt.tight_layout()
plt.show()

# --- 9. Visualize predictions ---
correct_idx = np.where(preds == truths)[0]
wrong_idx = np.where(preds != truths)[0]
n_show = 8

plt.figure(figsize=(16, 4))
for i in range(min(n_show, len(correct_idx))):
    idx = correct_idx[i]
    plt.subplot(2, n_show, i + 1)
    plt.imshow(X_test[idx].reshape(4, 1), cmap='gray')
    plt.title(f"T:{truths[idx]} P:{preds[idx]}")
    plt.axis('off')

for i in range(min(n_show, len(wrong_idx))):
    idx = wrong_idx[i]
    plt.subplot(2, n_show, n_show + i + 1)
    plt.imshow(X_test[idx].reshape(4, 1), cmap='gray')
    plt.title(f"T:{truths[idx]} P:{preds[idx]}")
    plt.axis('off')

plt.suptitle("Correct (Top) and Wrong (Bottom) Predictions")
plt.tight_layout()
plt.show()

# --- 10. Print wrong predictions ---
print("\nSample Wrong Predictions:")
for i, idx in enumerate(wrong_idx[:10]):
    print(f"Sample {idx}: True={truths[idx]} | Predicted={preds[idx]} | Probabilities={np.round(test_outputs[idx], 3)}")

# --- 11. Classification report ---
print("\nClassification Report:")
print(classification_report(truths, preds, zero_division=1))

