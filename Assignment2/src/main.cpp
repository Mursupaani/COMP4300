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
	Game game("config.txt");
	game.run();
}
