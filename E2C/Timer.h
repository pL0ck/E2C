#pragma once

#include <chrono>
#include <utility>
#include <Windows.h>

class timer
{
public:

	using clock_t = std::chrono::high_resolution_clock;
	using sysclock_t = std::chrono::system_clock;

private:
	ULONGLONG start_time;

public:
	timer() : start_time(GetTickCount64()) {}
	double get_elapsed_time() const { return (static_cast<double>(GetTickCount64()) - start_time) / 1000; }
	void reset() { start_time = GetTickCount64(); }
	std::string CurrentDateTime()
	{
		std::time_t now = sysclock_t::to_time_t(sysclock_t::now());

		char buf[28] = { 0 };
#pragma warning(suppress : 4996)
		std::strftime(buf, sizeof(buf), "%Y%m%d-%H%M%S", std::localtime(&now));

		return std::string(buf);
	}
};
