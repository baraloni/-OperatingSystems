
//#define NDEBUG
#include <csignal>
#include "scheduler.h"

/*------------- CONSTRUCTORS ------------*/
scheduler::scheduler(): _running(MAIN_THREAD_ID) {}

/*------------- PRIVATE -------------*/
void scheduler::_replaceRunning() {
    assert(!_ready.empty());
    _running = _ready.front();
    _ready.pop_front();
}

void scheduler::_handleBlockOrTermination(int tid) {
    if(tid == _running){
        _replaceRunning();
    }
    else{
        // If tid is in _ready, remove it from there:
        _ready.remove(tid);
    }
}

/*------------- PUBLIC -------------*/
int scheduler::getRunning() {
    return _running;
}

int scheduler::whosNextBlock(int tid) {
    _handleBlockOrTermination(tid);
    return _running;
}

int scheduler::whosNextTimeout() {
    _ready.push_back(_running);
    _replaceRunning();
    return _running;
}

int scheduler::whosNextTermination(int tid) {
    _handleBlockOrTermination(tid);
    return _running;
}

int scheduler::whosNextSleep() {
    _replaceRunning();
    return _running;
}


void scheduler::addThread(int tid) {

    // If tid is not already in _ready or _running, add it to the end of _ready:
    auto findIter = std::find(_ready.begin(), _ready.end(), tid);
    if((tid != _running) && (findIter ==_ready.end())){
        _ready.push_back(tid);
    }

}

void scheduler::printReady() {
    for(auto & iter : _ready){
        std::cout << iter << "; ";
    }
    std::cout << std::endl;
}
