#pragma once
#include <iostream>
#include <ostream>
#include <string>

class Clock {
	private:
	public:
		Clock(void);
		Clock(const Clock &other);
		Clock &operator=(const Clock &other);
		~Clock(void);
};

std::ostream &operator<<(std::ostream &stream, const Clock &vec);
