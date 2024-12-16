#include "pch.h"
Log LogInstance;

bool Log::WriteLog(char* data, ...)
{
    if (shouldLog) {
        if (!file) return false;
        SYSTEMTIME SystemTime;
        char CurrentDate[32] = { 0, };
        char buffer[4096] = { 0 };
        char CurrentFileName[MAX_PATH] = { 0, };
        va_list ap;
        va_start(ap, data);
        vsprintf_s(buffer, 4096, data, ap);
        va_end(ap);

        GetLocalTime(&SystemTime);
        sprintf_s(CurrentDate, 32, "%d-%d-%d %d:%d:%d",
            SystemTime.wYear,
            SystemTime.wMonth,
            SystemTime.wDay,
            SystemTime.wHour,
            SystemTime.wMinute,
            SystemTime.wSecond);

        sprintf_s(CurrentFileName, MAX_PATH, "LOG_%d-%d-%d %d.log",
            SystemTime.wYear,
            SystemTime.wMonth,
            SystemTime.wDay,
            SystemTime.wHour);

        fprintf(file, "[%s] %s\n", CurrentDate, buffer);
        fflush(file);
    }
    else
    {
        return false;
    }
    return true;

}
bool Log::WriteLog(std::string data, ...)
{
    if (shouldLog) {
        if (!file) return false;
        SYSTEMTIME SystemTime;
        char CurrentDate[32] = { 0, };
        char buffer[4096] = { 0 };
        char CurrentFileName[MAX_PATH] = { 0, };
        va_list ap;
        va_start(ap, data);
        vsprintf_s(buffer, 4096, data.c_str(), ap);
        va_end(ap);

        GetLocalTime(&SystemTime);
        sprintf_s(CurrentDate, 32, "%d-%d-%d %d:%d:%d",
            SystemTime.wYear,
            SystemTime.wMonth,
            SystemTime.wDay,
            SystemTime.wHour,
            SystemTime.wMinute,
            SystemTime.wSecond);

        sprintf_s(CurrentFileName, MAX_PATH, "LOG_%d-%d-%d %d.log",
            SystemTime.wYear,
            SystemTime.wMonth,
            SystemTime.wDay,
            SystemTime.wHour);

        fprintf(file, "[%s] %s\n", CurrentDate, buffer);
        fflush(file);
    }
    else
    {
        return false;
    }
    return true;

}
bool Log::WriteLogNoDate(const char * data, ...)
{
    if (shouldLog) {
        if (!file) return false;
        SYSTEMTIME SystemTime;
        char CurrentDate[32] = { 0, };
        char buffer[4096] = { 0 };
        char CurrentFileName[MAX_PATH] = { 0, };
        va_list ap;
        va_start(ap, data);
        vsprintf_s(buffer, 4096, data, ap);
        va_end(ap);
        GetLocalTime(&SystemTime);
        sprintf_s(CurrentFileName, MAX_PATH, "LOG_%d-%d-%d %d.log",
            SystemTime.wYear,
            SystemTime.wMonth,
            SystemTime.wDay,
            SystemTime.wHour);

        fprintf(file, "%s\n", buffer);
        fflush(file);
    }
    else
    {
        return false;
    }
    return true;
}
void Log::Enable()
{
    SYSTEMTIME SystemTime;
    GetLocalTime(&SystemTime);
    char CurrentFileName[MAX_PATH] = { 0, };
    sprintf_s(CurrentFileName, MAX_PATH, "LOG_%d-%d-%d %d.log",
        SystemTime.wYear,
        SystemTime.wMonth,
        SystemTime.wDay,
        SystemTime.wHour);
    if (!file)
    {
        fopen_s(&file, CurrentFileName, "w");
        if (file == NULL)
        {
            shouldLog = false;
            return;
        }
    }
    shouldLog = true;
}