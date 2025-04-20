import nltk
nltk.download('movie_reviews')
from nltk.corpus import movie_reviews
import random
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay, accuracy_score

from sentiment_model import NaiveBayes  # assuming your module name is sentiment_model

# Prepare dataset
docs = [(list(movie_reviews.words(fileid)), category)
        for category in movie_reviews.categories()
        for fileid in movie_reviews.fileids(category)]
random.shuffle(docs)

texts = [" ".join(words) for words, _ in docs]
labels = [1 if cat == 'pos' else 0 for _, cat in docs]

# Train/test split
split = int(0.8 * len(texts))
train_texts, test_texts = texts[:split], texts[split:]
train_labels, test_labels = labels[:split], labels[split:]

# Train C++ model
model = NaiveBayes()
model.train(train_texts, train_labels)

# Predictions
predictions = [model.predict(text) for text in test_texts]
accuracy = accuracy_score(test_labels, predictions)

print(f"Accuracy: {accuracy * 100:.2f}%")

# Confusion matrix
cm = confusion_matrix(test_labels, predictions)
disp = ConfusionMatrixDisplay(confusion_matrix=cm, display_labels=['neg', 'pos'])
disp.plot(cmap=plt.cm.Blues)
plt.title(f"Confusion Matrix (Accuracy: {accuracy * 100:.2f}%)")
plt.show()

