#pragma once

class Timer
{
	public:
		void start();
		void clear();
		void restart();
		int verifCount();

	private:
		int count;
};