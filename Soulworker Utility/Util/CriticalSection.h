#pragma once

class CCriticalSection
{
public:
    CCriticalSection(void)
    {
        InitializeCriticalSection(&mSync);
    }

    virtual ~CCriticalSection(void)
    {
        DeleteCriticalSection(&mSync);
    }

    inline void Enter(void)
    {
        EnterCriticalSection(&mSync);
    }

    inline void Leave(void)
    {
        LeaveCriticalSection(&mSync);
    }

private:
    CRITICAL_SECTION mSync;
};
