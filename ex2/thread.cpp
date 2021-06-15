#include <iostream>
#include "thread.h"



//-------------------helpers--------------------------------------------------------------------------------------------
#ifdef __x86_64__
/* code for 64 bit Intel arch */

typedef unsigned long address_t;
#define JB_SP 6
#define JB_PC 7

/* A translation is required when using an address of a variable.
   Use this as a black box in your code. */
address_t thread::translateAddress(address_t addr)
{
    address_t ret;
    asm volatile("xor    %%fs:0x30,%0\n"
                 "rol    $0x11,%0\n"
    : "=g" (ret)
    : "0" (addr));
    return ret;
}

#else
/* code for 32 bit Intel arch */

typedef unsigned int address_t;
#define JB_SP 4
#define JB_PC 5

/* A translation is required when using an address of a variable.
   Use this as a black box in your code. */
address_t thread::translateAddress(address_t addr)
{
    address_t ret;
    asm volatile("xor    %%gs:0x18,%0\n"
		"rol    $0x9,%0\n"
                 : "=g" (ret)
                 : "0" (addr));
    return ret;
}

#endif

//-----------------Constructor & Destructor ----------------------------------------------------------------------------

thread::thread()
        :_quants(0), _isBlocked(false), _isSleeping(false) {}


thread::~thread()
{
    //will not be called foe the main thread so will not cause an error.
    delete _stack;
}

//----------------- general functionality-------------------------------------------------------------------------------

int thread::setupThread(void(*f)(), int stackSize)
{
    try{
        _stack = new char[stackSize];
    }
    catch (std::bad_alloc& e)
    {
        std::cerr << "system error: bad memory allocation when creating thread." << std::endl;
        return -2;
    }
    address_t sp = (address_t) _stack + stackSize - sizeof(address_t);
    auto pc = (address_t)f;
    auto translatedSp = translateAddress(sp);
    auto translatedPc = translateAddress(pc);
    sigsetjmp(_env, 1);
    (_env->__jmpbuf)[JB_SP] = translatedSp;
    (_env->__jmpbuf)[JB_PC] = translatedPc;
    if (sigemptyset(&_env->__saved_mask) == -1)
    {
        std::cerr << "system error: " << strerror(errno) << std::endl;
        return -2;
    }
    return 0;
}

void thread::setBlocked(bool isBlocked){
    _isBlocked = isBlocked;
}

bool thread::getBlocked(){
    return _isBlocked;
}

void thread::setSleep(bool isSleeping){
    _isSleeping = isSleeping;
}

bool thread::getSleep(){
    return _isSleeping;
}

void thread::updateQuants(){
    _quants++;
}

int thread::getQuants(){
    return _quants;
}

