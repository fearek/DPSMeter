#pragma once
#include "pch.h"

#include <list>

#define UTILLWINDOW UtillWindow::getInstance()

class UtillWindow : public Singleton<UtillWindow> {
private:
	bool _isOpen = false;
	std::list<std::string> logList;

	CHAR CurrentDate[32] = { 0, };
public:
	VOID AddLog(std::string log);
	VOID OpenWindow();
	VOID Update();
	UtillWindow();
	~UtillWindow();

};