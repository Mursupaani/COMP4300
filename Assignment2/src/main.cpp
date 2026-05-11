#include <exception>

#include "Game.hpp"

int main(void) {
	try {
		Game game("../config.txt");
		game.run();

	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}
