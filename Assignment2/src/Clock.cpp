#include "Clock.hpp"

Clock::Clock(void) {}

Clock::Clock(const Clock &other) {
	(void)other;
}

Clock &Clock::operator=(const Clock &other) {
	if (this == &other)
		return (*this);
	return (*this);
}
Clock::~Clock(void) {}

std::ostream &operator<<(std::ostream &stream, const Clock &clock) {
	(void)clock;
	return (stream);
}
