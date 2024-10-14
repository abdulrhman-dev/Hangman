#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>
#include <array>
#include <string_view>

class Game {
public:
	Game(const std::string& rightWord);

	void playTurn();

	int getWrongGuessesNumber() const { return m_wrongGuessesNumber; }
	bool isGameFinished() const { return m_gameFinished; }
	bool getWonStatus() const { return m_won; };
	std::string_view getRightWord() const { return m_rightWord; };

private:
	std::string m_rightWord{};
	std::vector<char> m_guessedChars{};
	std::vector<char> m_displayChars{};
	std::vector<char> m_wrongChars{};
	int m_wrongGuessesNumber{};
	bool m_gameFinished{ false };
	bool m_won{ false };

	bool isCharacterFound(char guessedCharacter);
	bool addGuessCharacter(char guessedCharacter);
	bool checkWon();
	void printDisplayChars();
	void printWrongGuesses();
};

#endif