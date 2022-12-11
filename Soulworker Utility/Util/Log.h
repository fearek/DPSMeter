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
    BOOL WriteLogNoDate(LPTSTR data, ...);
    void Enable();
};
extern Log LogInstance;
