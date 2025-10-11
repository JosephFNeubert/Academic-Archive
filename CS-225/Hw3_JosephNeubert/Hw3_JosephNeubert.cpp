/****************************************************************************
 * File:      Hw3_JosephNeubert.cpp
 * Author:    Joseph Neubert
 * Purpose:   To create a hangman game
 * Version:   1.0 Sept 12, 2024
 * Resources: Assistance from W3 School for certain string methods
 *******************************************************************************/

#include <iostream>
#include <string>
using namespace std;

int main()
{
	string words[5] = {"elephant", "zebra", "tiger", "cheetah", "hamster"};
	int wordNum;
	cout << "Welcome to Hangman! Please enter a number between 1 to 5 to select a word and play: ";
	cin >> wordNum;
	while (!cin || wordNum < 1 || wordNum > 5)
	{
		cout << "Invalid entry, please try again: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> wordNum;
	}
	string word = words[wordNum - 1];

	int attempts = 0;
	int lettersGuessed = 0;
	char letter;
	bool correct;
	string censoredWord("");
	for (int i = 0; i < word.size(); i++)
	{
		censoredWord.append("*");
	}
	while (lettersGuessed != word.size())
	{
		correct = false;
		cout << "Guess a letter in the word: " << censoredWord << endl;
		cin >> letter;
		while (!cin)
		{
			cout << "Invalid guess. Please try again..." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> letter;
		}
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		for (int i = 0; i < word.size(); i++)
		{
			if (letter == word[i])
			{
				lettersGuessed++;
				censoredWord.replace(i, 1, string(1, letter));
				correct = true;
			}
		}
		attempts++;
		if (!correct)
		{
			cout << "Sorry, but " << letter << " is not in the word." << endl;
		}
	}
	cout << "Well done! You guessed the word " << censoredWord << " with " << attempts << " guesses!" << endl;
	return 0;
}