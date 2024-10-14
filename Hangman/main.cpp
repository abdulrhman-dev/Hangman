#include <iostream>
#include <fstream>
#include "Random.h"
#include "Game.h"
#include "Settings.h"

int main() {
	std::cout << "Welcome to Hangman\n";
	std::cout << "To win: guess the word.  To lose: run out of (#).\n";

	int selectedLine{ Random::get(1, Settings::maxWords) };

	std::ifstream file("./words.txt");
	std::string word;
	int lineNumber{ 1 };

	if (!file.is_open()) {
		std::cerr << "Unable to open the file.\n";
		return 0;
	}

	while (std::getline(file, word)) {
		if (lineNumber == selectedLine)
			break;
		++lineNumber;
	}

	file.close();


	Game g(word);

	do {
		g.playTurn();
	} while (!g.isGameFinished());

	if (!g.getWonStatus()) {
		std::cout << "You lost!  The word was: " << g.getRightWord();
		return 0;
	}

	std::cout << "You won! Congrats!";
}
