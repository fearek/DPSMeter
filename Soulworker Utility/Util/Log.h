#pragma once

class Log
{
private:
    bool shouldLog = false;
public:
        BOOL WriteLog(LPTSTR data, ...);
        BOOL WriteLogA(char* data, ...);
        BOOL WriteLogNoDate(LPTSTR data, ...);
        VOID MyLog(const _TCHAR* data, ...);
        VOID MyLog(const char* data, ...);
        void Enable();
};
extern Log LogInstance;
