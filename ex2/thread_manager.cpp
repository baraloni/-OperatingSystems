
#include <iostream>
#include "thread.h"
#include "thread_manager.h"

typedef unsigned long address_t;

//-----Private helpers-----------------------------------------------------------------------------

thread *thread_manager::findThread(const int tid)
{
    auto pairTidThread = _threads.find(tid);
    if (pairTidThread != _threads.end())
    {
        return pairTidThread->second;
    }
    return nullptr;
}

int thread_manager::getSmallestTid()
{
    if (!_usedIds.empty())
    {
        int smallestId = _usedIds.top();
        _usedIds.pop();
        return smallestId;
    }
    return ++_largestId;
}


//--- Constructor& Destructor--------------------------------------------------------------------------------

thread_manager::thread_manager(const int quantum_usecs, const int maxThreadNum,
                               const int stackSize):
                               _maxThreadNum(maxThreadNum),_stackSize(stackSize),
                               _quantumUsecs(quantum_usecs), _largestId(0), _usedIds(), _threads()
                               {}

thread_manager::~thread_manager()
{
    thread *threadWithTid = findThread(0);
    delete threadWithTid;
}

//----Class functionality--------------------------------------------------------------------------

int thread_manager::threadManagerSetup()
{
    //creates representation of main thread:
    thread *mainThread;
    try{
         mainThread = new thread();
    }
    catch (std::bad_alloc& e)
    {
        std::cerr << "system error: bad memory allocation when creating thread." << std::endl;
        return -2;
    }
    mainThread->updateQuants();
    if (_threads.insert({0, mainThread}).second) // if the insertion took place successfully
    {
        return 0;
    }
    std::cerr << "system error: couldn't insert new thread to threads list." << std::endl;
    return -2;

}

int thread_manager::createThread(void (*f)())
{
    if ((int)_threads.size() < _maxThreadNum)
    {
        int newTid = getSmallestTid();
        auto *newThread = new thread();
        if (!newThread->setupThread(f, _stackSize))
        {
            if (_threads.insert({newTid, newThread}).second) // if the insertion took place successfully
            {
                return newTid;
            }
            std::cerr << "system error: couldn't insert new thread to threads list." << std::endl;
        }
        return -2;
    }
    return -1;
}

int thread_manager::killThread(const int tid)
{
    thread *threadWithTid = findThread(tid);
    if (threadWithTid != nullptr)
    {
        delete threadWithTid;
        _threads.erase(tid);
        _usedIds.push(tid); //recycles this tid
        return 0;
    }
    return -1;
}

int thread_manager::blockThread(const int tid)
{
    thread *threadWithTid = findThread(tid);
    if (threadWithTid != nullptr)
    {
        threadWithTid->setBlocked(true);
        return 0;
    }
    return -1;
}

int thread_manager::unBlockThread(const int tid)
{
    thread *threadWithTid = findThread(tid);
    if (threadWithTid != nullptr)
    {
        threadWithTid->setBlocked(false);
        return 0;
    }
    return -1;
}

bool thread_manager::isThreadBlocked(const int tid)
{
    thread *threadWithTid = findThread(tid);
    if (threadWithTid != nullptr)
    {
        return threadWithTid->getBlocked();
    }
    return false;
}

void thread_manager::putThreadToSleep(const int tid)
{
    //no need to check for existence-
    // made only on the running (and therefore existing) thread.
    thread *threadWithTid = findThread(tid);
    threadWithTid->setSleep(true);
}

int thread_manager::wakeThread(const int tid)
{
    thread *threadWithTid = findThread(tid);
    if (threadWithTid != nullptr)
    {
        threadWithTid->setSleep(false);
        return 0;
    }
    return -1;
}

bool thread_manager::isThreadAsleep(const int tid)
{
    thread *threadWithTid = findThread(tid);
    if (threadWithTid != nullptr)
    {
        return threadWithTid->getSleep();
    }
    return false;
}

int thread_manager::getThreadQuants(const int tid){
    thread *threadWithTid = findThread(tid);
    if (threadWithTid != nullptr)
    {
        return threadWithTid->getQuants();
    }
    return -1;
}

void thread_manager::switchContext(int currTid, int nextTid)
{
    thread *currThread = thread_manager::findThread(currTid);
    thread *nextThread = thread_manager::findThread(nextTid);

    assert(nextThread != nullptr);

    _threads[nextTid]->updateQuants();

    if (currTid != nextTid)
    {
        if(currThread == nullptr) // currThread terminated itself, can't save it's context, just jmp to nextThread
        {
            siglongjmp(nextThread->_env, 1);
        }
        int retVal = sigsetjmp(currThread->_env, 1);
        if (retVal == 0)
        {
            siglongjmp(nextThread->_env, 1);
        }
    }
}