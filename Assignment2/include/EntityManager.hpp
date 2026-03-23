#pragma once
#include <iostream>
#include <ostream>
#include <string>

class EntityManager {
	private:
	public:
		EntityManager(void);
		EntityManager(const EntityManager &other);
		EntityManager &operator=(const EntityManager &other);
		~EntityManager(void);
};

std::ostream &operator<<(std::ostream &stream, const EntityManager &vec);
