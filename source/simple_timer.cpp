#include "simple_timer.hpp"

SimpleTimer::~SimpleTimer() {
	if (is_time_) {
		End();
	}
}

void SimpleTimer::Start() {
	if (!is_time_) {
		start_ = std::chrono::high_resolution_clock::now();
		is_time_ = true;
	}
	else {
		std::cout << "Timer Already Started" << std::endl;
	}
}

void SimpleTimer::End() {
	if (is_time_) {
		end_ = std::chrono::high_resolution_clock::now();
		elapsed_mcs_ = std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_);
		is_time_ = false;
	}
	else {
		std::cout << "Timer Not Started" << std::endl;
	}
}

void SimpleTimer::Print() {
	if (!is_time_) {
		std::cout << "Elapsed time is " << elapsed_mcs_.count() << " us" << std::endl;
	}
	else {
		std::cout << "Not data!!!" << std::endl;
	}
}
