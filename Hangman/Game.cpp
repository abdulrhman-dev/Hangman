#include <iostream>

#include "Game.h"
#include "Settings.h"

bool isInvalidInput(char guessedCharacter) {
	bool failure{ !std::cin };

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return failure || !std::isalpha(guessedCharacter);
}

Game::Game(const std::string& rightWord)
	: m_rightWord{ rightWord }
{
	m_displayChars = std::vector<char>(rightWord.size(), '_');
	m_wrongChars.reserve(Settings::maxGuesses);
}


void Game::playTurn() {

	std::cout << '\n';
	std::cout << "The word: ";
	printDisplayChars();
	std::cout << "\tWrong guesses: ";
	printWrongGuesses();
	std::cout << '\n';

	bool isWon{ checkWon() };

	if (m_wrongGuessesNumber >= Settings::maxGuesses || isWon) {
		m_gameFinished = true;
		m_won = isWon;
		return;
	}

	std::cout << "Enter your next letter: ";
	char guessedCharacter{};
	std::cin >> guessedCharacter;

	guessedCharacter = std::tolower(guessedCharacter);

	if (isInvalidInput(guessedCharacter)) {
		std::cout << "That wasn't a valid input.  Try again.\n";
		return;
	}


	if (isCharacterFound(guessedCharacter)) {
		std::cout << "You already guessed that.  Try again.\n";
		return;
	}

	bool validGuess{ addGuessCharacter(guessedCharacter) };

	if (validGuess) {
		std::cout << "Yes, '" << guessedCharacter << "' is in the word!";
	}
	else {
		std::cout << "No, '" << guessedCharacter << "' is not in the word!";
		++m_wrongGuessesNumber;
		m_wrongChars.push_back(guessedCharacter);
	}
	std::cout << '\n';
}

bool Game::isCharacterFound(char guessedCharacter) {
	for (const auto& prevGuessedChar : m_guessedChars) {
		if (guessedCharacter == prevGuessedChar)
			return true;
	}

	return false;
}

bool Game::addGuessCharacter(char guessedCharacter) {
	m_guessedChars.push_back(guessedCharacter);

	bool found{ false };

	for (std::size_t i = 0; i < m_rightWord.size(); ++i) {
		if (guessedCharacter == m_rightWord[i]) {
			m_displayChars[i] = guessedCharacter;
			found = true;
		}
	}

	return found;
}

bool Game::checkWon() {
	for (const auto& displayChar : m_displayChars)
		if (displayChar == '_')
			return false;

	return true;
}

void Game::printDisplayChars() {
	for (const auto& displayChar : m_displayChars)
		std::cout << displayChar;
}

void Game::printWrongGuesses() {
	for (int i = 0; i < (Settings::maxGuesses - m_wrongGuessesNumber); ++i)
		std::cout << '#';

	for (const auto& wrongChar : m_wrongChars)
		std::cout << wrongChar;
}