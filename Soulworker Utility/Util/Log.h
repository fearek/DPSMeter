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
    bool WriteLog(std::string data, ...);
    bool WriteLog(char* data, ...);
    bool WriteLogNoDate(LPTSTR data, ...);
    void Enable();
};
extern Log LogInstance;
