#pragma once
#include <iostream>
#include <ostream>
#include <string>

class Game {
	private:
	public:
		Game(void);
		Game(const Game &other);
		Game &operator=(const Game &other);
		~Game(void);
};

std::ostream &operator<<(std::ostream &stream, const Game &vec);
