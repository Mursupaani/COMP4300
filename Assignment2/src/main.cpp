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

// NOTE: Run game like this!
// int main(void) {
// 	Game game("config.txt");
// 	game.run();
// }

// void run(Engine &e) {
// 	while (e.window.isOpen()) {
// 		while (const std::optional event = e.window.pollEvent()) {
// 			if (event->is<sf::Event::Closed>())
// 				e.window.close();
// 			if (const auto *keyPressed =
// 					event->getIf<sf::Event::KeyPressed>()) {
// 				if (keyPressed->code == sf::Keyboard::Key::Escape)
// 					e.window.close();
// 			}
// 		}
// 		if (!e.window.isOpen()) {
// 			break;
// 		}
// 		e.window.clear();
// 		e.drawObjects();
// 		e.window.display();
// 	}
// }
//
// int main(int ac, char **av) {
// 	if (ac != 2) {
// 		std::cerr << "Please input config file\n";
// 		return (1);
// 	}
// 	try {
// 		Engine e(av[1]);
// 		run(e);
// 	} catch (std::exception &e) {
// 		std::cerr << e.what() << std::endl;
// 		return (1);
// 	}
// }
