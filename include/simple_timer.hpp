#pragma once

#include <iostream>
#include <chrono>

class SimpleTimer {
public:
	SimpleTimer() 
		: start_{ std::chrono::high_resolution_clock::now() }
		, end_{}
		, elapsed_mcs_{}
		, is_time_{ true } {}
	SimpleTimer(const SimpleTimer&) = delete;
	SimpleTimer& operator=(const SimpleTimer&) = delete;
	SimpleTimer(SimpleTimer&&) = delete;
	SimpleTimer& operator=(SimpleTimer&&) = delete;

	~SimpleTimer();

	void Start();
	void End();
	void Print();
private:
	std::chrono::high_resolution_clock::time_point start_;
	std::chrono::high_resolution_clock::time_point end_;

	std::chrono::microseconds elapsed_mcs_;

	bool is_time_;
};
