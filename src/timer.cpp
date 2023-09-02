#include "headers/timer.hpp"

void Timer::start()
{
	count++;
}

void Timer::clear()
{
	count = 0;
}

void Timer::restart()
{
	clear();
	start();
}

int Timer::verifCount()
{
	return count;
}