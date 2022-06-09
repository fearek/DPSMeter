#pragma once

class Log
{
private:
    FILE* file;
    bool shouldLog = false;
public:
        ~Log()
        {
            if (file)
            {
                fclose(file);
            }
        }
        Log()
        {

        }
        BOOL WriteLog(char* data, ...);
        BOOL WriteLogA(char* data, ...);
        BOOL WriteLogNoDate(LPTSTR data, ...);
        VOID MyLog(const _TCHAR* data, ...);
        VOID MyLog(const char* data, ...);
        void Enable();
};
extern Log LogInstance;
