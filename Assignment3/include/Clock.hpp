#pragma once
#include <chrono>

class Clock {
	public:
		Clock(void);
		Clock(const Clock &other) = delete;
		Clock &operator=(const Clock &other) = delete;
		~Clock(void) = default;

		const std::chrono::steady_clock::time_point &getStartTime(void) const;
		void										 reset(void);

	private:
		std::chrono::steady_clock::time_point m_start;
};
