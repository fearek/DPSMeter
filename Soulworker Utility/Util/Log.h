#pragma once

class Log
{
private:
    FILE* file;
    
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
    bool WriteLogNoDate(const char* data, ...);
    void Enable();
    bool shouldLog = false;
};
extern Log LogInstance;
