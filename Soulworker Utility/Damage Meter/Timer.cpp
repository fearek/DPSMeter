#include "pch.h"
#include ".\Damage Meter\Timer.h"

Timer::Timer() {
	_status = TIMER_STATUS::end;
	_startTimePoint = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	_suspendTimePoint = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	_suspendedTime = 0.f;
}

Timer::~Timer() {

}

VOID Timer::Run() {
	
	if (_status == TIMER_STATUS::end) {
		_startTimePoint = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		_suspendedTime = 0.f;
		_status = TIMER_STATUS::run;
	}
	else if (_status == TIMER_STATUS::suspend) {
		uint64_t suspendedTime;
		suspendedTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - _suspendTimePoint;
		_suspendedTime += suspendedTime;
		_status = TIMER_STATUS::run;
	}
	else {

	}
}

VOID Timer::Suspend() {

	if (_status == TIMER_STATUS::run) {
		_suspendTimePoint = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		_status = TIMER_STATUS::suspend;
	}
	else {

	}
}

VOID Timer::Stop() {
	
	_status = TIMER_STATUS::end;
}

BOOL Timer::isRun() {
	if (_status == TIMER_STATUS::run)
		return TRUE;
	else
		return FALSE;
}

uint64_t Timer::GetTime() {

	uint64_t time;

	if (_status == TIMER_STATUS::run) {
		time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - _startTimePoint;
	}
	else if (_status == TIMER_STATUS::suspend) {
		time = _suspendTimePoint - _startTimePoint;
	}
	else {
		return 0;
	}

	return time - _suspendedTime;
}