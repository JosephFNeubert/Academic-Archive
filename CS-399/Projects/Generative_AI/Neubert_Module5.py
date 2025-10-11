"""
File: Neubert_Module5
Author: Joseph Neubert
Purpose: To use the GloVe model to create a simple AI program to identify word outliers.

Sources Used: ChatGPT used for guidance in developing the code and answering questions concerning GloVe
"""

from wv import Model
from scipy.stats import zscore

# GloVe model selected due to its ease and intuitive nature for word-based AI
model = Model("models/glove_short.txt")

while True:
    words = input("Please enter a comma separated list of words: ").split(",")

    if len(words) < 3:
        print("You must input at least 3 words.")
        break

    vectors = []
    for word in words:
        vector = model.get_vector(word.strip())
        if vector is None:
            print(f"Vector representation not found for {word.strip()}.")
            break
        vectors.append(vector)

    if len(vectors) != len(words):
        continue

    zscores = zscore(vectors)
    filtered_words = [word for word, zscore in zip(words, zscores) if abs(zscore) < 2]

    print(
        f"With outliers removed, your list looks like this: {', '.join(filtered_words)}"
    )
