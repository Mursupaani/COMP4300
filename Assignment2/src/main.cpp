#include <exception>

#include "Game.hpp"
#include "Vec2.hpp"

/* NOTE::
 * GameEngine
 *		Scene
 *			Systems
 *			EntityManager
 *				Entity
 *					Componnent
 */

int main(void) {
	try {
		Game game("config.txt");
		game.run();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}
