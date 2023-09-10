#include "pch.h"
Log LogInstance;

BOOL Log::WriteLog(char* data, ...)
{
    if (shouldLog) {
        if (!file) return FALSE;
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
        return FALSE;
    }
    return TRUE;

}
BOOL Log::WriteLogNoDate(LPTSTR data, ...)
{
    if (shouldLog) {
        if (!file) return FALSE;
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
        return FALSE;
    }
    return TRUE;
}
void Log::Enable()
{
    SYSTEMTIME SystemTime;
    GetLocalTime(&SystemTime);
    CHAR CurrentFileName[MAX_PATH] = { 0, };
    sprintf_s(CurrentFileName, MAX_PATH, "LOG_%d-%d-%d %d.log",
        SystemTime.wYear,
        SystemTime.wMonth,
        SystemTime.wDay,
        SystemTime.wHour);
    if (!file)
    {
        fopen_s(&file,CurrentFileName, "w");
        if (file == NULL)
        {
            shouldLog = false;
            return;
        }
    }
    shouldLog = true;
}