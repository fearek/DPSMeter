#pragma once

template <class T, int ALLOC_BLOCK_SIZE = 50>
class MemoryPool : public MultiThreadSync<T>
{
public:
    static void* operator new(std::size_t allocLength)
    {
        MultiThreadSync<T>::template ThreadSync Sync;

        if (!mFreePointer)
            allocBlock();

        unsigned char* ReturnPointer = mFreePointer;
        mFreePointer = *reinterpret_cast<unsigned char**>(ReturnPointer);

        return ReturnPointer;
    }

    static void operator delete(void* deletePointer)
    {
        MultiThreadSync<T>::template ThreadSync Sync;

        *reinterpret_cast<unsigned char**>(deletePointer) = mFreePointer;

        mFreePointer = static_cast<unsigned char*>(deletePointer);
    }

private:
    static void    allocBlock()
    {
        mFreePointer = new unsigned char[sizeof(T) * ALLOC_BLOCK_SIZE];

        unsigned char** Current = reinterpret_cast<unsigned char**>(mFreePointer);
        unsigned char* Next = mFreePointer;

        for (int i = 0; i < ALLOC_BLOCK_SIZE - 1; ++i)
        {
            Next += sizeof(T);
            *Current = Next;
            Current = reinterpret_cast<unsigned char**>(Next);
        }

        *Current = 0;
    }

private:
    static unsigned char* mFreePointer;

protected:
    virtual ~MemoryPool()
    {
    }
};

template <class T, int ALLOC_BLOCK_SIZE>
unsigned char* MemoryPool<T, ALLOC_BLOCK_SIZE>::mFreePointer;