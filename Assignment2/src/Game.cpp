#include "Game.hpp"

Game::Game(void) {}

Game::Game(const Game &other) {
	(void)other;
}

Game &Game::operator=(const Game &other) {
	if (this == &other)
		return (*this);
	return (*this);
}
Game::~Game(void) {}

std::ostream &operator<<(std::ostream &stream, const Game &clock) {
	(void)clock;
	return (stream);
}
