#pragma once
#ifndef TIMER_H
#define TIMER_H
#include <chrono>
#include <iostream>
#include <string>

/*
Based on the Timer by Youtuber TheCherno
*/
class Timer {
public:
	Timer() {
		startPoint = std::chrono::high_resolution_clock::now();
	}

	~Timer() {
		endPoint = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(startPoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endPoint).time_since_epoch().count();
		duration = (end - start) * 0.001;

		std::cout << "Pass took " << duration << "ms" <<std::endl;
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> startPoint;
	std::chrono::time_point<std::chrono::high_resolution_clock> endPoint;
	double duration;
};

#endif