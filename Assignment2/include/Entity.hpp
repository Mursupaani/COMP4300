#pragma once
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>

#include "Components.hpp"

class Entity {
	private:
		const size_t	  m_id = 0;
		const std::string m_tag = "Default";
		bool			  m_alive = true;

	public:
		CTransform *cTransform;
		CName	   *cName;
		CShape	   *cShape;
		CBBox	   *cBBox;

		Entity(void) = delete;
		Entity(const std::string &tag, const size_t id);
		Entity(const Entity &other) = delete;
		Entity &operator=(const Entity &other) = delete;
		~Entity(void);

		std::string tag(void) const;
		bool		isAlive(void) const;
		size_t		id(void) const;

		void destroy(void);
};

std::ostream &operator<<(std::ostream &stream, const Entity &vec);
