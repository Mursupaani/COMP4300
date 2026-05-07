#include "Clock.hpp"

#include <chrono>

Clock::Clock(void) {
	m_start = std::chrono::steady_clock::now();
}

const std::chrono::steady_clock::time_point &Clock::getStartTime(void) const {
	return (m_start);
}

void Clock::reset(void) {
	m_start = std::chrono::steady_clock::now();
}
