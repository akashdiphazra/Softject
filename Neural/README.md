Copyright (C) Neural - All Rights Reserved

Unauthorized copying of this software, via any medium is strictly prohibited Proprietary and confidential Written by Akashdip Hazra 

# NeuralNet C++/Python Example

This project demonstrates a minimal neural network framework in C++ with a Python interface via pybind11.  
It features:  
- Configurable layers (Dense, ReLU, Tanh, LeakyReLU, Softmax, Dropout)
- Loss functions (CrossEntropy, MSE)
- Optimizers (SGD, SGD+Momentum, Adam)
- Learning Rate Schedulers (StepLR)
- Model save/load
- Batch and single prediction (`forward`, `batch_forward`)
- Python integration for easy use with scikit-learn datasets

---

## Installation

1. **Install dependencies**
   - Eigen (header-only)
   - pybind11
   - CMake, a C++17 compiler
   - Python 3.x, numpy, matplotlib, scikit-learn

2. **Build the Python extension**
   ```bash
   mkdir build && cd build
   cmake ..
   make
   # This will produce neuralnet.cpython-<...>.so for Python import
   ```

---

## Example Usage

### 1. Basic Training with scikit-learn Digits

```python
import numpy as np
from sklearn.datasets import load_digits
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import OneHotEncoder
from neuralnet import NeuralNet, StepLRScheduler

# Load and preprocess data
digits = load_digits()
X = digits.data.astype(np.float32) / 16.0  # Normalize
y = digits.target.reshape(-1, 1)
encoder = OneHotEncoder(sparse_output=False)
y_onehot = encoder.fit_transform(y)
X_train, X_test, y_train, y_test = train_test_split(
    X, y_onehot, test_size=0.2, random_state=42, stratify=y
)
X_train_l, y_train_l = X_train.tolist(), y_train.tolist()
X_test_l, y_test_l = X_test.tolist(), y_test.tolist()

# Build model with all features
scheduler = StepLRScheduler(step_size=10, gamma=0.5)
net = NeuralNet(
    layers=[64, 32, 10],               # Architecture
    activation="relu",                 # Activation (relu, tanh, leakyrelu)
    optimizer="sgdmomentum",           # Optimizer (sgd, sgdmomentum, adam)
    learning_rate=0.1,                 # Initial learning rate
    loss="crossentropy",               # Loss (crossentropy, mse)
    momentum=0.9,                      # Momentum for SGD+Momentum
    lr_scheduler=scheduler             # Learning rate scheduler
)
net.print_summary()  # Print model, optimizer, and scheduler information

# Train (LR scheduler works only if epochs > 1 in a single call)
epochs = 30
batch_size = 32
net.train(X_train_l, y_train_l, epochs=epochs, batch_size=batch_size)

# Save/Load model
net.save("model.bin")
net.load("model.bin")

# Batch prediction
outputs = net.batch_forward(X_test_l)
preds = np.argmax(outputs, axis=1)
truths = np.argmax(y_test, axis=1)
accuracy = (preds == truths).mean() * 100
print(f"Test Accuracy: {accuracy:.2f}%")
```

---

### 2. Loss and Optimizer Options

- **Loss:** `"crossentropy"` or `"mse"`
- **Optimizer:** `"sgd"`, `"sgdmomentum"`, `"adam"`
- **Activation functions:** `"relu"`, `"tanh"`, `"leakyrelu"`

### 3. Learning Rate Scheduling

```python
from neuralnet import StepLRScheduler
scheduler = StepLRScheduler(step_size=10, gamma=0.5)  # Halve LR every 10 epochs
net = NeuralNet(..., lr_scheduler=scheduler)
```

### 4. Model Save/Load

```python
net.save("model.bin")
net.load("model.bin")
```

### 5. Batch and Single Prediction

```python
out = net.forward(X_test_l[0])             # Single input (as list)
batch_out = net.batch_forward(X_test_l)    # Batch input (list of lists)
```

### 6. Print Model Summary

```python
net.print_summary()
# Example output:
# Model Summary:
#  Layer 0: Dense (64 -> 32)
#  Layer 1: ReLU
#  Layer 2: Dense (32 -> 10)
#  Layer 3: Softmax
#  Loss: CrossEntropy
#  Optimizer: SGD+Momentum (LR=0.1) momentum=0.9
#  LR Scheduler: StepLR(step_size=10, gamma=0.500000)
```

### 7. Using Dropout or LeakyReLU

```python
net = NeuralNet(
    layers=[64, 32, 10],
    activation="leakyrelu",
    dropout_rate=0.2,   # Dropout after each hidden activation
    ...
)
```

---

## Full Example: Training and Plotting Learning Curves

```python
import matplotlib.pyplot as plt

# ... (build and train net as above, save losses/accuracies per epoch) ...

# Plot
plt.plot(accuracies, label="Test Accuracy")
plt.xlabel("Epoch")
plt.ylabel("Accuracy (%)")
plt.title("Test Accuracy per Epoch")
plt.legend()
plt.show()
```

---

## Advanced: Custom LR Scheduler (C++)

You may subclass LRScheduler in C++ and expose it via pybind11 if desired.

---

## Troubleshooting

- **Learning rate not changing with scheduler?**  
  Call `.train(..., epochs=N)` **once** for N>1, not N times with epochs=1.

- **Data shape errors?**  
  Always pass list-of-lists (not numpy arrays) to `.train()` and `.batch_forward()`.

---

