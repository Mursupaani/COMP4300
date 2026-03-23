#pragma once
#include <iostream>
#include <ostream>
#include <string>

class Entity {
	private:
	public:
		Entity(void);
		Entity(const Entity &other);
		Entity &operator=(const Entity &other);
		~Entity(void);
};

std::ostream &operator<<(std::ostream &stream, const Entity &vec);
