#pragma once

typedef enum {
	end = 0,
	run = 1,
	suspend = 2,
}TIMER_STATUS;

class Timer {
private:
	TIMER_STATUS _status;
	uint64_t _suspendTimePoint;
	uint64_t _suspendedTime;

public:
	uint64_t _startTimePoint;
	Timer();
	~Timer();

	VOID Run();
	VOID Suspend();
	VOID Stop();
	BOOL isRun();

	uint64_t GetTime();
};