"""
File: Neubert_Module5.py
Author: Joseph Neubert
Description: A program that will open and read a text file (the novel "Treasure Planet") and output the most-occurring word as well as how many times the word captain appears.
"""
file_name = "treasure.txt"
plain_text = {}
plain_text_string = ""

try:
    with open(file_name, "r") as f:
        # Parse text file into usable plain text
        text = f.read()
        text = text.replace("-", " ")
        text = text.casefold()
        plain_text = text.split()
        count = -1
        for i in plain_text:
            count += 1
            for j in i:
                if j.isalpha():
                    plain_text_string += j
            plain_text[count] = plain_text_string
            plain_text_string = ""
            if i == "":
                plain_text.remove(i)

        print(plain_text)

        # Creates dictionary of words and occurrences as keys and values respectively
        plain_text_dictionary = {}
        for i in plain_text:
            if i not in plain_text_dictionary.keys():
                plain_text_dictionary.update({i: 1})
            else:
                plain_text_dictionary.update({i: plain_text_dictionary.get(i) + 1})

        # Outputs
        max_freq = 0
        max_word = ""
        word_captain = plain_text_dictionary.get("captain", 0)
        for key, value in plain_text_dictionary.items():
            if value > max_freq:
                max_freq = value
                max_word = key
        print(
            f"The most frequently appearing word is '{max_word}'. It appears {max_freq} times."
        )
        print(f"The word 'captain' appears {word_captain} timnes.")

except FileNotFoundError:
    print("File not found.")


"""
text = f.read()
        text = text.replace("-", " ")
        text = text.casefold()
        plain_text = text.split()
        count = -1
        for i in plain_text:
            count += 1
            for j in i:
                if j.isalpha():
                    plain_text_string += j
            plain_text[count] = plain_text_string
            plain_text_string = ""
            if i == "":
                plain_text.remove(i)

        print(plain_text)
"""
