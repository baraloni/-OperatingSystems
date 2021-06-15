#include "uthreads.h"
#include <iostream>
#define SECOND 1000000
#include <unistd.h>
#include <cassert>

#define STACK_SIZE 4096
#include "thread_manager.h"
#include "thread.h"

// THE ULTIMATE TEST-----------------------------------------------------------------------------------------------------------------

//void g()
//{
//    //TIME 4:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    assert(uthread_get_total_quantums() == 4);
//    while (1)
//    {
//        //assert(uthread_get_quantums(uthread_get_tid()) == 1);
//    }
//}
//
//void f() {
//
//    //TIME 2:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    assert(uthread_get_total_quantums() == 2);
//    std::cerr << "created: T"<<uthread_spawn(g)<<std::endl;
//    while (uthread_get_total_quantums() != 5)
//    {}
//
//    //TIME 5:
//    std::cerr << "terminating T2" << std::endl;
//    uthread_terminate(2);
//    while (1) {
//        //assert(uthread_get_quantums(uthread_get_tid()) == 2);
//    }
//}
//
//
//
//int main()
//{
//    int ret = uthread_init(1);
//
//    //TIME 1:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    assert(uthread_get_total_quantums() == 1);
//    std::cerr << "created: T"<<uthread_spawn(f)<<std::endl;
//    while (uthread_get_total_quantums() != 3) {}
//
//    //TIME 3:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    assert(uthread_get_total_quantums()  == 3);
//    while (uthread_get_total_quantums() != 6){}
//
//    //TIME 6:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    uthread_terminate(1);
//    std::cerr <<"terminated: T1\n";
//    while (uthread_get_total_quantums() != 7) {}
//
//    //TIME 7:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    uthread_terminate(0);
//    return 0;
//}


// BLOCK TEST----------------------------------------------------------------------------------------------------------------

//void t1(void)
//{
//    //TIME 2/5:
//    while (1){}
//}
//
//int main()
//{
//    assert (uthread_init(1) == 0);
//
//    //TIME 1:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    std::cerr << "T" << uthread_get_tid()<< ": " << " created" << uthread_spawn(t1) << std::endl;
//
//    while (uthread_get_total_quantums() != 3){}
//
//    //TIME 3:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    uthread_block(1);
//    std::cerr << "blocking : T1" << std::endl;
//
//    while (uthread_get_total_quantums() != 4){}
//
//    //TIME 4:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    uthread_resume(1);
//    std::cerr << "resuming : T1" << std::endl;
//
//    while (uthread_get_total_quantums() != 6){}
//
//    //TIME 6:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    uthread_terminate(1);
//    std::cerr << "terminating T1" << std::endl;
//
//    std::cerr << "terminating T0" << std::endl;
//    uthread_terminate(0);
//
//    return 0;
//
//
//}




//Basic TEST------------------------------------------------------------------------------------------------------------------------

//void f0(void)
//{
//    //TIME 2/4:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    while (1)
//    {
//        std::cerr << "T1...";
//    }
//}
//
//int main()
//{
//    assert (uthread_init(1) == 0);
//
//    //TIME 1:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    uthread_spawn(f0);
//
//  //  uthread_spawn(f1);
//    while (uthread_get_total_quantums() != 3){}
//
//    //TIME 3:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    while (uthread_get_total_quantums() != 5){}
//
//    //TIME 5:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    std::cerr << "terminating T1" << std::endl;
//    uthread_terminate(1);
//    std::cerr << "terminating T0" << std::endl;
//    uthread_terminate(0);
//
//
//    return 0;
//}

//THREAD TEST-------------------------------------------------------------------------------------------------------



//thread t0 = thread();
//thread t1 = thread();
//
//
//void switchContext(thread& curr, thread& next)
//{
//    int retVal = sigsetjmp(curr._env, 1);
//    if (retVal == 0)
//    {
//        std::cerr << "switch" << std::endl;
//        siglongjmp(next._env, 1);
//    }
//}
//
//void f0(void)
//{
//    int i = 0;
//    while (1){
//        ++i;
//        std::cerr << "T0...";
//        if (i % 5)
//        {
//            switchContext(t0, t1);
//        }
//    }
//}
//
//void f1(void)
//{
//    int i = 0;
//    while (1){
//        std::cerr << "T1...";
//        ++i;
//        if (i % 10)
//        {
//         switchContext(t1, t0);
//        }
//    }
//}
//
//int main() {
//    t0.setupThread(f0, STACK_SIZE);
//    t1.setupThread(f1, STACK_SIZE);
//    switchContext(t1, t0);
//}


//DEMO TEST-----------------------------------------------------------------------------------------------------------------\

//
//thread t0 = thread();
//thread t1 = thread();
//
//
//
//void switchThreads(int currTid)
//
//{
//
//    if (currTid == 0)
//    {
//        int retVal = sigsetjmp(t0._env, 1);
//        if (retVal == 0)
//        {
//            siglongjmp(t1._env, 1);
//        }
//    } else{
//        int retVal = sigsetjmp(t1._env, 1);
//        if (retVal == 0)
//        {
//            siglongjmp(t0._env, 1);
//        }
//    }
//}
//void f(void)
//{
//    int i = 0;
//    while(1){
//        ++i;
//        std::cerr << "in f ("<<i<<")\n";
//        if (i % 3 == 0) {
//            std::cerr <<"f: switching\n";
//            switchThreads(0);
//        }
//        usleep(SECOND);
//    }
//}
//
//void g(void)
//{
//    int i = 0;
//    while(1){
//        ++i;
//        std::cerr << "in g ("<<i<<")\n";
//        if (i % 5 == 0) {
//            std::cerr <<"f: switching\n";
//            switchThreads(1);
//        }
//        usleep(SECOND);
//    }
//}
//
//
//int main(void)
//{
//    t0.setupThread(f, STACK_SIZE);
//    t1.setupThread(g, STACK_SIZE);
//    siglongjmp(t0._env, 1);
//}


// SIGNAL MASKING TEST
//
//void f0(void)
//{
//    //TIME 2:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    while (1)
//    {
//        std::cerr << "T1...";
//    }
//}
//
//
//int main(void){
//    assert (uthread_init(1) == 0);
//
//    //TIME 1:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    std::cerr << "T" << uthread_get_tid()<< ": " << "spawn thread: " << uthread_spawn(f0) << std::endl;
//
//    while (uthread_get_total_quantums() != 3){}
//
//    //TIME 3:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    uthread_terminate(1);
//    std::cerr << "terminating T1" << std::endl;
//
//    std::cerr << "terminating T0" << std::endl;
//    uthread_terminate(0);
//}
//

//// SLEEP TEST
//
//static int awake = 0;
//
//
//void f0(void)
//{
//    //TIME 2:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    std::cerr << "Sleep t1"  << std::endl;
//    uthread_sleep(10000);
//
//    //TIME ? :
//    awake = 1;
//    std::cerr << "terminated t1 "<< std::endl;
//    uthread_terminate(1);
//}
//
//
//int main(void){
//    assert (uthread_init(1) == 0);
//
//    //TIME 1:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    std::cerr << "T" << uthread_get_tid()<< ": " << "spawn thread: " << uthread_spawn(f0) << std::endl;
//
//    while (uthread_get_total_quantums() != 3){}
//
//    // TIME 3
//    while(!awake){
//        //std::cerr << "T0...";
//    }
//
//    //TIME ? + 1:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid())<<"\nTIME: " <<uthread_get_total_quantums()<< std::endl;
//    std:: cerr << "terminated : t0 " << std::endl;
//    uthread_terminate(0);
//
//    //TIME X:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    uthread_terminate(1);
//    std::cerr << "terminating T1" << std::endl;
//
//    std::cerr << "terminating T0" << std::endl;
//    uthread_terminate(0);
//}


////BASIC SLEEP TEST:
//
//
//static int awake = 0;
//
//
//void f0(void)
//{
//    //TIME 2:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    std::cerr << "Sleep t1"  << std::endl;
//    uthread_sleep(10000);
//
//    //TIME ? :
//
//    awake = 1;
//    while(1){
//        std::cerr << "T1...";
//    }
//}
//
//
//int main(void){
//    assert (uthread_init(1) == 0);
//
//    //TIME 1:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    std::cerr << "T" << uthread_get_tid()<< ": " << "spawn thread: " << uthread_spawn(f0) << std::endl;
//
//    while (uthread_get_total_quantums() != 3){}
//
//    // TIME 3
//    while(!awake){
//     }
//
//    //TIME ? + 1:
//    std::cerr << "terminated t1 "<< std::endl;
//    uthread_terminate(1);
//
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    std:: cerr << "terminated : t0 " << std::endl;
//    uthread_terminate(0);
//
//    //TIME X:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    uthread_terminate(1);
//    std::cerr << "terminating T1" << std::endl;
//
//    std::cerr << "terminating T0" << std::endl;
//    uthread_terminate(0);
//    }

////BLOCK->SLEEP TEST:


//static int awake = 0;
//
//
//void f0(void)
//{
//    //TIME 2:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    std::cerr << "T" << uthread_get_tid()<< ": block T 2" << std::endl;
//    uthread_block(2);
//    std::cerr << "T" << uthread_get_tid()<< ": Sleep t1"  << std::endl;
//    uthread_sleep(10000);
//
//    //TIME ? :
//    awake = 1;
//    std::cerr << "AWAKEN!\n";
//    while(1){}
//
//}
//
//void f1(void)
//{
//    //TIME 4:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    std::cerr << "T" << uthread_get_tid()<< ": " << "resume thread: 1" <<  std::endl;
//    uthread_resume(1);
//
//    while(1){}
//
//}
//
//int main(void){
//    assert (uthread_init(1) == 0);
//
//    //TIME 1:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    std::cerr << "T" << uthread_get_tid()<< ": " << "spawn thread: " << uthread_spawn(f0) << std::endl;
//    std::cerr << "T" << uthread_get_tid()<< ": " << "spawn thread: " << uthread_spawn(f1) << std::endl;
//
//    while (uthread_get_total_quantums() != 3){}
//
//    // TIME 3
//    std::cerr << "T" << uthread_get_tid()<< ": " << "block thread: 1" <<  std::endl;
//    uthread_block(1);
//    std::cerr << "T" << uthread_get_tid()<< ": " << "resume thread: 2" <<  std::endl;
//    uthread_resume(2);
//
//    while(!awake){}
//
//    // TIME (?+1) or (?+2):
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid())<< std::endl;
//    std:: cerr << "terminated : t2 " << std::endl;
//    uthread_terminate(2);
//    std::cerr << "terminating T1" << std::endl;
//    uthread_terminate(1);
//    std::cerr << "terminating T0" << std::endl;
//    uthread_terminate(0);
//}


////SLEEP->BLOCK TEST:
//
//static int awake = 0;
//
//
//void f0(void)
//{
//    //TIME 2:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    std::cerr << "T" << uthread_get_tid()<< ": Sleep t1"  << std::endl;
//    uthread_sleep(10000);
//
//    //TIME 12 :
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    awake = 1;
//    std::cerr << "AWAKEN!\n";
//    while(1){} // TIME
//
//}
//
//
//int main(void){
//    assert (uthread_init(1) == 0);
//
//    //TIME 1:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    std::cerr << "T" << uthread_get_tid()<< ": " << "spawn thread: " << uthread_spawn(f0) << std::endl;
//
//    while (uthread_get_total_quantums() != 3){}
//
//    // TIME 3
//    std::cerr << "T" << uthread_get_tid()<< ": " << "block thread: 1" <<  std::endl;
//    uthread_block(1);
//
//    //TIME 4-8:
//    while (uthread_get_total_quantums() != 9){}
//
//    //TIME 9,10:
//    int limitQuants = uthread_get_quantums(0) + 2;
//    while (uthread_get_quantums(0) != limitQuants);
//
//    // TIME (11)
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid())<< std::endl;
//    std::cerr << "T" << uthread_get_tid()<< ": " << "resume thread: 1" <<  std::endl;
//    uthread_resume(1);
//    while (!awake){};
//
//    // TIME (13):
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid())<< std::endl;
//    std::cerr << "terminating T1" << std::endl;
//    uthread_terminate(1);
//    std::cerr << "terminating T0" << std::endl;
//    uthread_terminate(0);
//}


//// SELF TERMINATION TEST

//void f1(void)
//{
//    while(1){
//
//    }
//}
//
//void f0(void)
//{
//    //TIME 2:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    std::cerr << "T" << uthread_get_tid()<< ": Terminates t2"  << std::endl;
//    std::cerr << "T" << uthread_terminate(2)<< std::endl;
//    std::cerr << "T" << uthread_get_tid()<< ": Terminates myself (t1)"  << std::endl;
//    std::cerr << "T" << uthread_terminate(1)<< std::endl;
//}
//
//int main(void){
//    uthread_init(1);
//
//    // TIME 1:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    std::cerr << "T" << uthread_get_tid()<< ": " << "spawn thread: " << uthread_spawn(f0) << std::endl;
//    std::cerr << "T" << uthread_get_tid()<< ": " << "spawn thread: " << uthread_spawn(f1) << std::endl;
//
//    while(uthread_get_total_quantums() != 3){
//
//    }
//
//    // TIME 3:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid())<< std::endl;
//    std::cerr << "terminating T0" << std::endl;
//    std::cerr << uthread_terminate(0) << std::endl;
//
//}


////SLEEPING AT THE "SAME" TIME TEST:
//
//int awake1 = 0, awake2 = 0;
//
//void f1(void)
//{
//    //TIME 3:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    std::cerr << "T" << uthread_get_tid()<< ": Sleep t2"  << std::endl;
//    uthread_sleep(10);
//
//    // AFTER WAKING:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    awake2 = 1;
//    std::cerr << "T2 awaken!" << std::endl;
//    while (1){}
//}
//
//void f0(void)
//{
//    //TIME 2:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    std::cerr << "T" << uthread_get_tid()<< ": Sleep t1"  << std::endl;
//    uthread_sleep(40);
//
//    // AFTER WAKING:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    awake1 = 1;
//    std::cerr << "T1 awaken!" << std::endl;
//    while (1){}
//}
//
//int main(void){
//    uthread_init(1);
//
//    // TIME 1:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid()) << std::endl;
//    std::cerr << "T" << uthread_get_tid()<< ": " << "spawn thread: " << uthread_spawn(f0) << std::endl;
//    std::cerr << "T" << uthread_get_tid()<< ": " << "spawn thread: " << uthread_spawn(f1) << std::endl;
//
//    while(uthread_get_total_quantums() != 4){
//
//    }
//
//    // TIME 4:
//    while (!awake1 || !awake2 ) {}
//
//    //TIME ?:
//    std::cerr << "T" << uthread_get_tid()<< ": " << uthread_get_quantums(uthread_get_tid())<< std::endl;
//    std::cerr << "terminating T1" << std::endl;
//    std::cerr << uthread_terminate(1) << std::endl;
//    std::cerr << "terminating T2" << std::endl;
//    std::cerr << uthread_terminate(2) << std::endl;
//    std::cerr << "terminating T0" << std::endl;
//    std::cerr << uthread_terminate(0) << std::endl;
//
//}

//// TEST 1 (From Group)
///*
// * test1.cpp
// *
// *	test suspends and resume
// *
// *  Created on: Apr 6, 2015
// *      Author: roigreenberg
// */
//
//#include <stdio.h>
//#include <setjmp.h>
//#include <signal.h>
//#include <unistd.h>
//#include <sys/time.h>
//#include <stdlib.h>
//#include <deque>
//#include <list>
//#include <assert.h>
//#include "uthreads.h"
////#include "libuthread.a"
//#include <iostream>
//
//using namespace std;
//
//
//void f (void)
//{
//    int i = 1;
//    int j = 0;
//    while(1)
//    {
//        if (i == uthread_get_quantums(uthread_get_tid()))
//        {
//            cout << "f" << "  q:  " << i << endl;
//            if (i == 3 && j == 0)
//            {
//                j++;
//                cout << "          f suspend by f" << endl;
//                uthread_block(uthread_get_tid());
//            }
//            if (i == 6 && j == 1)
//            {
//                j++;
//                cout << "          g resume by f" << endl;
//                uthread_resume(2);
//            }
//            if (i == 8 && j == 2)
//            {
//                j++;
//                cout << "          **f end**" << endl;
//                uthread_terminate(uthread_get_tid());
//                return;
//            }
//            i++;
//        }
//    }
//}
//
//void g (void)
//{
//    int i = 1;
//    int j = 0;
//    while(1)
//    {
//        if (i == uthread_get_quantums(uthread_get_tid()))
//        {
//            cout << "g" << "  q:  " << i << endl;
//            if (i == 11 && j == 0)
//            {
//                j++;
//                cout << "          **g end**" << endl;
//                uthread_terminate(uthread_get_tid());
//                return;
//            }
//            i++;
//        }
//    }
//}
//
//
//int main(void)
//{
//    if (uthread_init(100) == -1)
//    {
//        return 0;
//    }
//
//    int i = 1;
//    int j = 0;
//
//    while(1)
//    {
//        //int a = uthread_get_quantums(uthread_get_tid());
//        //cout<<"quantums of thread number " << uthread_get_tid()<<" is " <<a<<std::endl;
//        if (i == uthread_get_quantums(uthread_get_tid()))
//        {
//            cout << "m" << "  q:  " << i << endl;
//            if (i == 3 && j == 0)
//            {
//                j++;
//                cout << "          spawn f at (1) " << uthread_spawn(f) << endl;
//                cout << "          spawn g at (2) " << uthread_spawn(g) << endl;
//            }
//
//            if (i == 6 && j == 1)
//            {
//                j++;
//                cout << "          g suspend by main" << endl;
//                uthread_block(2);
//                cout << "          g suspend again by main" << endl;
//                uthread_block(2);
//            }
//            if (i == 9 && j == 2)
//            {
//                j++;
//                cout << "          f resume by main" << endl;
//                uthread_resume(1);
//                cout << "          f resume again by main" << endl;
//                uthread_resume(1);
//            }
//            if (i == 13 && j == 3)
//            {
//                j++;
//                cout << "          spawn f at (1) " << uthread_spawn(f) << endl;
//                cout << "          f suspend by main" << endl;
//                uthread_block(1);
//            }
//            if (i == 17 && j == 4)
//            {
//                j++;
//                cout << "          spawn g at (2) " << uthread_spawn(g) << endl;
//                cout << "          f terminate by main" << endl;
//                uthread_terminate(1);
//                cout << "          spawn f at (1) " << uthread_spawn(f) << endl;
//                cout << "          f suspend by main" << endl;
//                uthread_block(1);
//            }
//            if (i == 20 && j == 5)
//            {
//                j++;
//                //cout << "i: " << i << endl;
//                cout << "          ******end******" << endl;
//                cout << "total quantums:  " << uthread_get_total_quantums() << endl;
//                uthread_terminate(0);
//                return 0;
//            }
//            i++;
//        }
//    }
//    cout << "end" << endl;
//    return 0;
//}
//
//
//

//// TEST 2 (From group)
//*
// * test2.cpp
// *
// *  Created on: Apr 7, 2015
// *      Author: roigreenberg
// */
//
//#include <stdio.h>
//#include <setjmp.h>
//#include <signal.h>
//#include <unistd.h>
//#include <sys/time.h>
//#include <stdlib.h>
//#include <deque>
//#include <list>
//#include <assert.h>
//#include "uthreads.h"
////#include "libuthread.a"
//#include <iostream>
//
//using namespace std;
//
//void f (void)
//{
//    while(1);
//}
//
//int main(void)
//{
//    if (uthread_init(10000) == -1)
//    {
//        return 0;
//    }
//    for (int i = 1; i <= 101; i++)
//        cerr << uthread_spawn(f) << endl;
//
//    uthread_terminate(5);
//
//    cerr << uthread_spawn(f) << endl;
//    cerr << uthread_spawn(f) << endl;
//
//    uthread_terminate(15);
//    uthread_terminate(25);
//    uthread_terminate(35);
//    uthread_terminate(45);
//    uthread_terminate(55);
//    uthread_terminate(65);
//    uthread_terminate(75);
//    uthread_terminate(85);
//
//    cerr << uthread_spawn(f) << endl;
//    cerr << uthread_spawn(f) << endl;
//    cerr << uthread_spawn(f) << endl;
//    cerr << uthread_spawn(f) << endl;
//    cerr << uthread_spawn(f) << endl;
//    cerr << uthread_spawn(f) << endl;
//    cerr << uthread_spawn(f) << endl;
//    cerr << uthread_spawn(f) << endl;
//    cerr << uthread_spawn(f) << endl;
//
//    uthread_terminate(0);
//    return 0;
//}

//// TEST 3 (From group)
///*
// * test3.cpp
// *
// *  Created on: Apr 8, 2015
// *      Author: roigreenberg
// */
//
//#include <stdio.h>
//#include <setjmp.h>
//#include <signal.h>
//#include <unistd.h>
//#include <sys/time.h>
//#include <stdlib.h>
//#include <deque>
//#include <list>
//#include <assert.h>
//#include "uthreads.h"
////#include "libuthread.a"
//#include <iostream>
//
//using namespace std;
//
//void f(void){}
//
//int main(void)
//{
//    if (uthread_init(1000000000) == -1)
//    {
//        return 0;
//    }
//
//
//    uthread_terminate(-1);
//    uthread_block(-1);
//    uthread_resume(-1);
//    uthread_get_quantums(-1);
//
//    uthread_terminate(1);
//    uthread_block(1);
//    uthread_resume(1);
//    uthread_get_quantums(1);
//
//    uthread_block(0);
//
//    uthread_spawn(f);
//    uthread_terminate(1);
//
//    uthread_terminate(1);
//    uthread_block(1);
//    uthread_resume(1);
//    uthread_get_quantums(1);
//
//    uthread_init(0);
//    uthread_init(-5);
//
//
//    uthread_terminate(0);
//    return 0;
//}


////TEST 4 (From group)

///*
// * test4.cpp
// *
// *  Created on: Apr 8, 2015
// *      Author: roigreenberg
// */
//
//#include <stdio.h>
//#include <setjmp.h>
//#include <signal.h>
//#include <unistd.h>
//#include <sys/time.h>
//#include <stdlib.h>
//#include <deque>
//#include <list>
//#include <assert.h>
//#include "uthreads.h"
////#include "libuthread.a"
//#include <iostream>
//
//using namespace std;
//
//void f (void)
//{
//    while(1)
//    {
////		cout << "f" << endl;
//        uthread_block(1);
//    }
//}
//
//void g (void)
//{
//    while(1)
//    {
////		cout << "g" << endl;
//        uthread_block(2);
//    }
//}
//
//void h (void)
//{
//    while(1)
//    {
////		cout << "h" << endl;
//        uthread_block(3);
//    }
//}
//
//int main(void)
//{
//    if (uthread_init(100) == -1)
//    {
//        return 0;
//    }
//
//    uthread_spawn(f);
//    uthread_spawn(g);
//    uthread_spawn(h);
//
//    while(uthread_get_total_quantums() < 10)
//    {
//        uthread_resume(1);
//        uthread_resume(2);
//        uthread_resume(3);
//    }
//
//    cout << uthread_get_quantums(0) << " + " << endl;
//    cout << uthread_get_quantums(1) << " + " << endl;
//    cout << uthread_get_quantums(2) << " + " << endl;
//    cout << uthread_get_quantums(3) << endl;
//    cout << " = " << uthread_get_total_quantums() << endl;
//
//    uthread_block(2);
//
//    while(uthread_get_total_quantums() < 20)
//    {
//        uthread_resume(1);
//        uthread_resume(3);
//    }
//
//    cout << uthread_get_quantums(0) << " + " << endl;
//    cout << uthread_get_quantums(1) << " + " << endl;
//    cout << uthread_get_quantums(2) << " + " << endl;
//    cout << uthread_get_quantums(3) << endl;
//    cout << " = " << uthread_get_total_quantums() << endl;
//
//    uthread_resume(2);
//
//    while(uthread_get_total_quantums() < 30)
//    {
//        uthread_resume(1);
//        uthread_resume(2);
//        uthread_resume(3);
//    }
//
//    cout << uthread_get_quantums(0) << " + " << endl;
//    cout << uthread_get_quantums(1) << " + " << endl;
//    cout << uthread_get_quantums(2) << " + " << endl;
//    cout << uthread_get_quantums(3) << endl;
//    cout << " = " << uthread_get_total_quantums() << endl;
//
//
//    uthread_terminate(0);
//    return 0;
//}


/**********************************************
 * Test 1: correct threads ids (JONA)
 *
 **********************************************/
//
//#include <cstdio>
//#include <cstdlib>
//#include "uthreads.h"
//
//#define GRN "\e[32m"
//#define RED "\x1B[31m"
//#define RESET "\x1B[0m"
//
//void halt()
//{
//    while (true)
//    {}
//}
//
//void wait_next_quantum()
//{
//    int quantum = uthread_get_quantums(uthread_get_tid());
//    while (uthread_get_quantums(uthread_get_tid()) == quantum)
//    {}
//    return;
//}
//
//void thread1()
//{
//    uthread_block(uthread_get_tid());
//}
//
//void thread2()
//{
//    halt();
//}
//
//void error()
//{
//    printf(RED "ERROR - wrong id returned\n" RESET);
//    exit(1);
//}
//
//int main()
//{
//    printf(GRN "Test 1:    " RESET);
//    fflush(stdout);
//
//    uthread_init(10);
//    if (uthread_spawn(thread1) != 1)
//        error();
//    if (uthread_spawn(thread2) != 2)
//        error();
//    if (uthread_spawn(thread2) != 3)
//        error();
//    if (uthread_spawn(thread1) != 4)
//        error();
//    if (uthread_spawn(thread2) != 5)
//        error();
//    if (uthread_spawn(thread1) != 6)
//        error();
//
//    uthread_terminate(5);
//    if (uthread_spawn(thread1) != 5)
//        error();
//
//    wait_next_quantum();
//    wait_next_quantum();
//
//    uthread_terminate(5);
//    if (uthread_spawn(thread1) != 5)
//        error();
//
//    uthread_terminate(2);
//    if (uthread_spawn(thread2) != 2)
//        error();
//
//    uthread_terminate(3);
//    uthread_terminate(4);
//    if (uthread_spawn(thread2) != 3)
//        error();
//    if (uthread_spawn(thread1) != 4)
//        error();
//
//    printf(GRN "SUCCESS\n" RESET);
//    uthread_terminate(0);
//
//}


/**********************************************
 * Test 5: sync/block/resume (JONA)
 *
 **********************************************/

//#include <cstdio>
//#include "uthreads.h"
//
//#define GRN "\e[32m"
//#define RED "\x1B[31m"
//#define RESET "\x1B[0m"
//
//#define NUM_THREADS 4
//#define RUN 0
//#define DONE 1
//char thread_status[NUM_THREADS];
//
//
//void halt()
//{
//    while (true)
//    {}
//}
//
//int next_thread()
//{
//    return (uthread_get_tid() + 1) % NUM_THREADS;
//}
//
//void thread()
//{
//    //uthread_sync(next_thread());
//
//    //uthread_sync(next_thread());
//
//    uthread_block(uthread_get_tid());
//
//    for (int i = 0; i < 50; i++)
//    {
//        uthread_resume(next_thread());
//    }
//
//    thread_status[uthread_get_tid()] = DONE;
//
//    halt();
//}
//
//bool all_done()
//{
//    bool res = true;
//    for (int i = 1; i < NUM_THREADS; i++)
//    {
//        res = res && (thread_status[i] == DONE);
//    }
//    return res;
//}
//
//int main()
//{
//    printf(GRN "Test 5:    " RESET);
//    fflush(stdout);
//
//    uthread_init(100);
//    uthread_spawn(thread);
//    uthread_spawn(thread);
//    uthread_spawn(thread);
//
//    for (int i = 0; i < NUM_THREADS; i++)
//    {
//        thread_status[i] = RUN;
//    }
//
//    while (!all_done())
//    {
//        uthread_resume(1);
//    }
//
//    printf(GRN "SUCCESS\n" RESET);
//    uthread_terminate(0);
//
//}

/**********************************************
 * Test 42: each thread has its own unique stack (JONA)
 *
 **********************************************/
//
//#include <cstdio>
//#include <cstdlib>
//#include "uthreads.h"
//
//#define GRN "\e[32m"
//#define RED "\x1B[31m"
//#define RESET "\x1B[0m"
//
//#define NUM_THREADS 7
//#define RUN 0
//#define DONE 1
//
//char thread_status[NUM_THREADS];
//
//int next_thread()
//{
//    return (uthread_get_tid() + 1) % NUM_THREADS;
//}
//
//void wait_next_quantum()
//{
//    int quantum = uthread_get_quantums(uthread_get_tid());
//    while (uthread_get_quantums(uthread_get_tid()) == quantum)
//    {}
//    return;
//}
//
//void run_test()
//{
//    int tid = uthread_get_tid();
//    int arr[10];
//
//    for (int i = 0; i < 10; i++)
//    {
//        arr[i] = i * tid;
//    }
//
//    //uthread_sync(next_thread());
//
//    for (int i = 0; i < 10; i++)
//    {
//        if (arr[i] != i * tid)
//        {
//            printf(RED "ERROR - stack values changed\n" RESET);
//            exit(1);
//        }
//    }
//
//    int b1 = tid * 314, b2 = tid * 141;
//
//    // let switching be invoked by the timer
//    wait_next_quantum();
//
//
//    if ((b1 != tid * 314) || (b2 != tid * 141) || (tid != uthread_get_tid()))
//    {
//        printf(RED "ERROR - stack values changed\n" RESET);
//        exit(1);
//    }
//
//    thread_status[uthread_get_tid()] = DONE;
//    uthread_terminate(uthread_get_tid());
//}
//
//bool all_done()
//{
//    bool res = true;
//    for (int i = 1; i < NUM_THREADS; i++)
//    {
//        res = res && (thread_status[i] == DONE);
//    }
//    return res;
//}
//
//
//int main()
//{
//    printf(GRN "Test 42:   " RESET);
//    fflush(stdout);
//
//    uthread_init(10);
//    uthread_spawn(run_test);
//    uthread_spawn(run_test);
//    uthread_spawn(run_test);
//    uthread_spawn(run_test);
//    uthread_spawn(run_test);
//    uthread_spawn(run_test);
//
//    for (int i = 1; i < NUM_THREADS; i++)
//    {
//        thread_status[i] = RUN;
//    }
//
//
//    while (!all_done())
//    {}
//
//    printf(GRN "SUCCESS\n" RESET);
//    uthread_terminate(0);
//
//}

/**********************************************
 * Test 429: Compute the N'th catalan number using
 *           multiple threads.
 *           (+random calls to uthreads functions) (JONA)
 *
 **********************************************/
//
///*
// * recall that the n'th catalan number is
// *
// *              n
// *           _______
// *           |     |    n+k
// *  C_n  =   |     |   -----
// *           |     |     k
// *             k=2
// */
//
//
//#include <cstdio>
//#include <cstdlib>
//#include <time.h>
//#include "uthreads.h"
//
//
//#define GRN "\e[32m"
//#define RED "\x1B[31m"
//#define RESET "\x1B[0m"
//
//#define N 15
//#define CATALAN_N 9694845
//#define NUM_THREADS 6
//
//#define RUN 0
//#define DONE 1
//
//typedef unsigned long ulong;
//
//char thread_status[NUM_THREADS];
//
//ulong partial_calc[NUM_THREADS];
//
//
//void halt()
//{
//    while (true)
//    {}
//}
//
//int rand_tid()
//{
//    return rand() % NUM_THREADS;
//}
//
//// random and legal call to one or more of block/sync/resume
//void random_uthreads_call()
//{
//    int tid = rand_tid();
//    if (rand() % 2)
//    {
//        if (tid != 0)
//        {
//            uthread_block(tid);
//        }
//    }
//    else
//    {
////        if (tid != uthread_get_tid())
////        {
////            uthread_sync(tid);
////        }
//    }
//    uthread_resume(rand_tid());
//}
//
//ulong partial_numerator_calculator(ulong start, ulong step)
//{
//    int tid;
//    ulong res = 1;
//    for (ulong k = start; k <= N; k += step)
//    {
//        random_uthreads_call();
//
//        res *= (N + k);
//
//        random_uthreads_call();
//    }
//    return res;
//}
//
//ulong partial_denominator_calculator(ulong start, ulong step)
//{
//    int tid;
//    ulong res = 1;
//    for (ulong k = start; k <= N; k += step)
//    {
//        random_uthreads_call();
//
//        res *= k;
//
//        random_uthreads_call();
//    }
//    return res;
//}
//
//void summon_calculator(bool numerator, ulong start, ulong step)
//{
//    if (numerator)
//    {
//        partial_calc[uthread_get_tid()] = partial_numerator_calculator(start, step);
//    }
//    else
//    {
//        partial_calc[uthread_get_tid()] = partial_denominator_calculator(start, step);
//    }
//    thread_status[uthread_get_tid()] = DONE;
//    halt();
//}
//
//void thread1()
//{
//    summon_calculator(true, 2, 3);
//}
//
//void thread2()
//{
//    summon_calculator(true, 3, 3);
//}
//
//void thread3()
//{
//    summon_calculator(true, 4, 3);
//}
//
//void thread4()
//{
//    summon_calculator(false, 2, 2);
//}
//
//void thread5()
//{
//    summon_calculator(false, 3, 2);
//}
//
//
//bool all_done()
//{
//    bool res = true;
//    for (int i = 1; i < NUM_THREADS; i++)
//    {
//        res = res && (thread_status[i] == DONE);
//    }
//    return res;
//}
//
//
//int main()
//{
//    printf(GRN "Test 429:  " RESET);
//    fflush(stdout);
//
//    srand(time(NULL));
//
//    // threads 1,2,3 - numerator
//    // threads 4,5 - denominator
//
//    uthread_init(20);
//
//    uthread_spawn(thread1);
//    uthread_spawn(thread2);
//    uthread_spawn(thread3);
//    uthread_spawn(thread4);
//    uthread_spawn(thread5);
//
//    for (int i = 1; i < NUM_THREADS; i++)
//    {
//        thread_status[i] = RUN;
//    }
//
//    int tid = 0;
//    while (!all_done())
//    {
//        // sequentially resume all threads, as they are blocking each other like madmen
//        uthread_resume(tid);
//        tid = (tid + 1) % NUM_THREADS;
//    }
//
//    ulong res = (partial_calc[1] * partial_calc[2] * partial_calc[3]) /
//                (partial_calc[4] * partial_calc[5]);
//
//    if (res == CATALAN_N)
//    {
//        printf(GRN "SUCCESS\n" RESET);
//    }
//    else
//    {
//        printf(RED "ERROR - failed to correctly calculate catalan number\n" RESET);
//    }
//    uthread_terminate(0);
//
//}


/**********************************************
 * Test 1430: sort array using multiple threads (JONA)
 *
 **********************************************/
//
//
//
///*
// *          main              (merge N-size array)
// *         /    \
// *        /      \
// *       /        \
// *      t1        t2          (merge N/2-size array)
// *     / \        / \
// *    /   \      /   \
// *  t3    t4    t5    t6      (sort N/4-size array)
// *
// * DISCLAIMER:
// * This sorting application is very limited for this specific test,
// * and is not recommended to be used for real sorting purposes
// *
// */
//
//
//
//
//#include <cstdlib>
//#include <cstdio>
//#include <cstring>
//#include <time.h>
//#include "uthreads.h"
//
//#define GRN "\e[32m"
//#define RED "\x1B[31m"
//#define RESET "\x1B[0m"
//
//#define NUM_THREADS 7
//#define ARRAY_SIZE 8192
//#define N ARRAY_SIZE
//#define RUN 0
//#define DONE 1
//
//char thread_status[NUM_THREADS];
//int array[ARRAY_SIZE];
//
//int place_holder0[N], place_holder1[N / 2], place_holder2[N / 2];
//
//
//void printArray();
//
//
//int rand_tid()
//{
//    return rand() % NUM_THREADS;
//}
//
//void wait_next_quantum()
//{
//    int quantum = uthread_get_quantums(uthread_get_tid());
//    while (uthread_get_quantums(uthread_get_tid()) == quantum)
//    {}
//    return;
//}
//
//// sort array[start..end-1]
//void sort(int start, int end)
//{
//    wait_next_quantum();
//
//    for (int i = start; i < end; i++)
//    {
//        for (int j = i + 1; j < end; j++)
//        {
//            if (array[i] > array[j])
//            {
//                int temp = array[i];
//                array[i] = array[j];
//                array[j] = temp;
//            }
//        }
//        if (i == (end + start) / 2)
//        {
//            wait_next_quantum();
//        }
//    }
//
//}
//
//
///*
// * merges array[start..end/2-1] and array[end/2..end-1]
// */
//void merge(int start, int end, int* place_holder)
//{
//
//    int start1 = start, end1 = (end + start) / 2;
//    int start2 = end1, end2 = end;
//    int i = start1, j = start2;
//    int k = 0;
//
//    while (i < end1 && j < end2)
//    {
//        if (array[i] < array[j])
//        {
//            place_holder[k++] = array[i++];
//        }
//        else
//        {
//            place_holder[k++] = array[j++];
//        }
//    }
//
//    wait_next_quantum();
//
//    while (i < end1)
//    {
//        place_holder[k++] = array[i++];
//    }
//    while (j < end2)
//    {
//        place_holder[k++] = array[j++];
//    }
//
//    wait_next_quantum();
//
//    // copy from place_holder to original array
//    memcpy(array + start1, place_holder, sizeof(int) * (end2 - start1));
//
//}
//
//void sorting_thread(int start, int end)
//{
//    sort(start, end);
//    thread_status[uthread_get_tid()] = DONE;
//    uthread_terminate(uthread_get_tid());
//}
//
//void thread3()
//{
//    sorting_thread(0, N / 4);
//}
//
//void thread4()
//{
//    sorting_thread(N / 4, N / 2);
//}
//
//void thread5()
//{
//    sorting_thread(N / 2, 3 * N / 4);
//}
//
//void thread6()
//{
//    sorting_thread(3 * N / 4, N);
//}
//
//
//void thread1()
//{
//    int t3 = uthread_spawn(thread3);
//    int t4 = uthread_spawn(thread4);
//
//    if (t3 == -1 || t4 == -1)
//    {
//        printf(RED "ERROR - thread spawn failed\n" RESET);
//        uthread_terminate(0);
//    }
//
//    while (thread_status[t3] == RUN || thread_status[t4] == RUN)
//    {}
//
//    merge(0, N / 2, place_holder1);
//    thread_status[uthread_get_tid()] = DONE;
//    uthread_terminate(uthread_get_tid());
//}
//
//void thread2()
//{
//    int t5 = uthread_spawn(thread5);
//    int t6 = uthread_spawn(thread6);
//
//    if (t5 == -1 || t6 == -1)
//    {
//        printf(RED "ERROR - thread spawn failed\n" RESET);
//        uthread_terminate(0);
//    }
//
//    while (thread_status[t5] == RUN || thread_status[t6] == RUN)
//    {}
//
//    merge(N / 2, N, place_holder2);
//    thread_status[uthread_get_tid()] = DONE;
//    uthread_terminate(uthread_get_tid());
//}
//
//void printArray()
//{
//    for (int i = 0; i < N; i++)
//    {
//        printf("%d, ", array[i]);
//    }
//    printf("\n");
//}
//
//
//int main()
//{
//    printf(GRN "Test 1430: " RESET);
//    fflush(stdout);
//
//    srand(time(NULL));
//
//    for (int i = 0; i < ARRAY_SIZE; i++)
//    {
//        array[i] = rand() % 4862;
//    }
//
//
//    for (int i = 1; i < NUM_THREADS; i++)
//    {
//        thread_status[i] = RUN;
//    }
//
//    uthread_init(50);
//
//    int t1 = uthread_spawn(thread1);
//    int t2 = uthread_spawn(thread2);
//    if (t1 == -1 || t2 == -1)
//    {
//        printf(RED "ERROR - thread spawn failed\n" RESET);
//        uthread_terminate(0);
//    }
//
//    while (thread_status[t1] == RUN || thread_status[t2] == RUN)
//    {}
//
//    merge(0, N, place_holder0);
//
//    // check that array is sorted
//    for (int i = 0; i < N - 1; i++)
//    {
//        if (array[i] > array[i + 1])
//        {
//            printf(RED "ERROR - failed to sort the array\n" RESET);
//            uthread_terminate(0);
//        }
//    }
//
//    printf(GRN "SUCCESS\n" RESET);
//    uthread_terminate(0);
//
//}
//

/**********************************************
 * Test 132: thread's signal mask is saved between switches (not including VTALRM)
 *
 * steps:
 * create three global sets of different signals (not including VTALRM) - set1, set2, set3
 * spawn threads 1,2,3
 * each thread K blocks setK and infinitely checks that his sigmask is setK (JONA)
 *
 **********************************************/


//
//#include <signal.h>
//#include <cstdlib>
//#include <cstring>
//#include <cstdio>
//#include "uthreads.h"
//
//
//#define GRN "\e[32m"
//#define RED "\x1B[31m"
//#define RESET "\x1B[0m"
//
//
//#define NUM_THREADS 4
//
//#define RUN 0
//#define DONE 1
//
//sigset_t set1, set2, set3;
//
//char thread_status[NUM_THREADS];
//
//void halt()
//{
//    while (true)
//    {}
//}
//
//
//int next_thread()
//{
//    return (uthread_get_tid() + 1) % NUM_THREADS;
//}
//
//void check_sig_mask(const sigset_t& expected)
//{
//    for (unsigned int i = 0; i <= 20; i++)
//    {
//        sigset_t actual;
//        sigprocmask(0, NULL, &actual);
//        if (memcmp(&expected, &actual, sizeof(sigset_t)) != 0)
//        {
//            printf(RED "ERROR - sigmask changed\n" RESET);
//            exit(1);
//        }
//
//        // in the first 10 iterations let the thread stop because of block.
//        // in later iterations it will stop because of the timer
//
//        else if (i < 10)
//        {
//            uthread_block(uthread_get_tid());
//        }
//        else
//        {
//            int quantum = uthread_get_quantums(uthread_get_tid());
//            while (uthread_get_quantums(uthread_get_tid()) == quantum)
//            {}
//        }
//    }
//    thread_status[uthread_get_tid()] = DONE;
//    halt();
//}
//
//void thread1()
//{
//    sigprocmask(SIG_BLOCK, &set1, NULL);
//    check_sig_mask(set1);
//}
//
//void thread2()
//{
//    sigprocmask(SIG_BLOCK, &set2, NULL);
//    check_sig_mask(set2);
//}
//
//void thread3()
//{
//    sigprocmask(SIG_BLOCK, &set3, NULL);
//    check_sig_mask(set3);
//}
//
//bool all_done()
//{
//    bool res = true;
//    for (int i = 1; i < NUM_THREADS; i++)
//    {
//        res = res && (thread_status[i] == DONE);
//    }
//    return res;
//}
//
//int main()
//{
//    printf(GRN "Test 132:  " RESET);
//    fflush(stdout);
//
//    sigemptyset(&set1);
//    sigemptyset(&set2);
//    sigemptyset(&set3);
//
//    sigaddset(&set1, SIGBUS);
//    sigaddset(&set1, SIGTERM);
//    sigaddset(&set1, SIGRTMAX);
//    sigaddset(&set1, SIGABRT);
//
//    sigaddset(&set2, SIGUSR1);
//    sigaddset(&set2, SIGSEGV);
//    sigaddset(&set2, SIGUSR2);
//    sigaddset(&set2, SIGPIPE);
//
//    sigaddset(&set3, SIGTSTP);
//    sigaddset(&set3, SIGTTIN);
//    sigaddset(&set3, SIGTTOU);
//    sigaddset(&set3, SIGBUS);
//
//    uthread_init(50);
//
//    for (int i = 1; i < NUM_THREADS; i++)
//    {
//        thread_status[i] = RUN;
//    }
//
//    int t1 = uthread_spawn(thread1);
//    int t2 = uthread_spawn(thread2);
//    int t3 = uthread_spawn(thread3);
//
//    if (t1 == -1 || t2 == -1 || t3 == -1)
//    {
//        printf(RED "ERROR - threads spawning failed\n" RESET);
//        exit(1);
//    }
//
//
//    int tid = 0;
//    while (!all_done())
//    {
//        // resume all threads, as each one of them is blocking himself
//        uthread_resume(tid);
//        tid = (tid + 1) % NUM_THREADS;
//    }
//
//
//    printf(GRN "SUCCESS\n" RESET);
//    uthread_terminate(0);
//}


////Test 5 (GROUP)
///*
// * test1.cpp
// *
// *	test suspends and resume
// *
// *  Created on: Apr 6, 2015
// *      Author: roigreenberg
// */
//
//#include <stdio.h>
//#include <setjmp.h>
//#include <signal.h>
//#include <unistd.h>
//#include <sys/time.h>
//#include <stdlib.h>
//#include <deque>
//#include <list>
//#include <assert.h>
//#include "uthreads.h"
////#include "libuthread.a"
//#include <iostream>
//using namespace std;
//
//
//void f (void)
//{
//    int i = 1;
//    int j = 0;
//    while(1)
//    {
//        if (i == uthread_get_quantums(uthread_get_tid()))
//        {
//            cout << "f" << "  q:  " << i << endl;
//            if (i == 3 && j == 0)
//            {
//                j++;
//                //uthread_sleep(2);
//            }
//            if (i == 6 && j == 1)
//            {
//                j++;
//            }
//            if (i == 8 && j == 2)
//            {
//                j++;
//                cout << "          **f end**" << endl;
//                uthread_terminate(uthread_get_tid());
//                return;
//            }
//            i++;
//        }
//    }
//}
//
//void g (void)
//{
//    int i = 1;
//    int j = 0;
//    while(1)
//    {
//        if (i == uthread_get_quantums(uthread_get_tid()))
//        {
//            cout << "g" << "  q:  " << i << endl;
//            if (i == 11 && j == 0)
//            {
//                j++;
//                cout << "          **g end**" << endl;
//                uthread_terminate(uthread_get_tid());
//                return;
//            }
//            if (i == 3 && j == 0)
//            {
//
//                uthread_sleep(3);
//            }
//
//            i++;
//        }
//    }
//}
//
//
//int main(void)
//{
//    if (uthread_init(100) == -1)
//    {
//        return 0;
//    }
//
//    int i = 1;
//    int j = 0;
//
//    while(1)
//    {
//        //int a = uthread_get_quantums(uthread_get_tid());
//        //cout<<"quantums of thread number " << uthread_get_tid()<<" is " <<a<<std::endl;
//        if (i == uthread_get_quantums(uthread_get_tid()))
//        {
//            cout << "m" << "  q:  " << i << endl;
//            if (i == 3 && j == 0)
//            {
//                j++;
//                cout << "          spawn f at (1) " << uthread_spawn(f) << endl;
//                cout << "          spawn g at (2) " << uthread_spawn(g) << endl;
//            }
//
//            if (i == 6 && j == 1)
//            {
//                j++;
//            }
//            if (i == 9 && j == 2)
//            {
//                j++;
//            }
//            if (i == 13 && j == 3)
//            {
//                j++;
//            }
//            if (i == 17 && j == 4)
//            {
//                j++;
//            }
//            if (i == 20 && j == 5)
//            {
//                j++;
//                //cout << "i: " << i << endl;
//                cout << "          ******end******" << endl;
//                cout << "total quantums:  " << uthread_get_total_quantums() << endl;
//                uthread_terminate(0);
//                return 0;
//            }
//            i++;
//        }
//    }
//    cout << "end" << endl;
//    return 0;
//}


//// TEST 6(GROP)
///*
// * test1.cpp
// *
// *	test suspends and resume
// *
// *  Created on: Apr 6, 2015
// *      Author: roigreenberg
// */
//
//#include <stdio.h>
//#include <setjmp.h>
//#include <signal.h>
//#include <unistd.h>
//#include <sys/time.h>
//#include <stdlib.h>
//#include <deque>
//#include <list>
//#include <assert.h>
//#include "uthreads.h"
//#include <iostream>
//
//using namespace std;
//
//
//void f (void)
//{
//    int i = 1;
//    int j = 0;
//    while(1)
//    {
//        if (i == uthread_get_quantums(uthread_get_tid()))
//        {
//            cout << "f" << "  q:  " << i << endl;
//            if (i == 3 && j == 0)
//            {
//                j++;
//                cout << "          **f sleep**" << endl;
//                uthread_sleep(2);
//            }
//            if (i == 6 && j == 1)
//            {
//                j++;
//            }
//            if (i == 8 && j == 2)
//            {
//                j++;
//                cout << "          **f end**" << endl;
//                uthread_terminate(uthread_get_tid());
//                return;
//            }
//            i++;
//        }
//    }
//}
//
//void g (void)
//{
//    int i = 1;
//    int j = 0;
//    while(1)
//    {
//        if (i == uthread_get_quantums(uthread_get_tid()))
//        {
//            cout << "g" << "  q:  " << i << endl;
//            if (i == 11 && j == 0)
//            {
//                j++;
//                cout << "          **g end**" << endl;
//                uthread_terminate(uthread_get_tid());
//                return;
//            }
//            if (i == 3 && j == 0)
//            {
//                cout << "          **g sleep**" << endl;
//                uthread_sleep(3);
//            }
//
//            i++;
//        }
//    }
//}
//
//
//int main(void)
//{
//    if (uthread_init(100) == -1)
//    {
//        return 0;
//    }
//
//    int i = 1;
//    int j = 0;
//
//    while(1)
//    {
//        //int a = uthread_get_quantums(uthread_get_tid());
//        //cout<<"quantums of thread number " << uthread_get_tid()<<" is " <<a<<std::endl;
//        if (i == uthread_get_quantums(uthread_get_tid()))
//        {
//            uthread_sleep(3);
//            cout << "m" << "  q:  " << i << "   " << j << endl;
//            if (i == 3 && j == 0)
//            {
//                j++;
//                cout << "          spawn f at (1) " << uthread_spawn(f) << endl;
//                cout << "          spawn g at (2) " << uthread_spawn(g) << endl;
//            }
//
//            if (i == 6 && j == 1)
//            {
//                j++;
//            }
//            if (i == 9 && j == 2)
//            {
//                j++;
//            }
//            if (i == 13 && j == 3)
//            {
//                j++;
//            }
//            if (i == 17 && j == 4)
//            {
//                j++;
//            }
//            if (i == 20 && j == 5)
//            {
//                j++;
//                //cout << "i: " << i << endl;
//                cout << "          ******end******" << endl;
//                cout << "total quantums:  " << uthread_get_total_quantums() << endl;
//                uthread_terminate(0);
//                return 0;
//            }
//            i++;
//        }
//    }
//    cout << "end" << endl;
//    return 0;
//}



//// TEST 7(GROUP)  (NOT PASSING!!!)
//
//#include "uthreads.h"
//#include <stdio.h>
//#include <iostream>
//
//int gotit1 = 0;
//int gotit2 = 0;
//int gotit3 = 0;
//int gotit4 = 1;
//
//
//void f(void) {
//    while (1) {
//        if (gotit1) {
//            std::cout << "in f id: " <<  uthread_get_tid() << " " << uthread_get_quantums
//                    (uthread_get_tid()) << std::endl;
//            gotit1 = 0;
//            gotit2 = 1;
//            gotit3 = 1;
//            gotit4 = 1;
//            if((5<= uthread_get_total_quantums()) && (uthread_get_total_quantums()<=8))
//            {
//                std::cout<< " f sleep for 1 sec\n";
//                uthread_sleep(1000000);
//            }
//            if((30<= uthread_get_total_quantums()) && (uthread_get_total_quantums()<=35))
//            {
//                std::cout<< " f sleep for 1 sec again\n";
//                uthread_sleep(1000000);
//            }
//        }
//    }
//}
//
//void g(void) {
//    while (1) {
//        if (gotit2) {
//            std::cout << "in g id: "  << uthread_get_tid() << " " << uthread_get_quantums
//                    (uthread_get_tid()) << std::endl;
//            gotit2 = 0;
//            gotit1 = 1;
//            gotit3 = 1;
//            gotit4 = 1;
//            if((5<= uthread_get_total_quantums()) && (uthread_get_total_quantums()<=8))
//            {
//                std::cout << " g try to wake f:\n";
//                if(uthread_resume(1))
//                {
//                    std::cout << " cant wake f!\n";
//                }
//            }
//            if((10<= uthread_get_total_quantums()) && (uthread_get_total_quantums()<=12))
//            {
//                std::cout << " g go to sleep for 3 sec:\n";
//                uthread_sleep(3000000);
//            }
//        }
//    }
//}
//void z(void) {
//    while (1) {
//        if (gotit3)
//        {
//            std::cout << "in z id: " << uthread_get_tid() << " " << uthread_get_quantums
//                    (uthread_get_tid
//                             ()) << std::endl;
//            gotit3 = 0;
//            gotit1 = 1;
//            gotit2 = 1;
//            gotit4 = 1;
//            if((10<= uthread_get_total_quantums()) && (uthread_get_total_quantums()<=12))
//            {
//                std::cout << " z try to resume g but g is sleeping:\n";
//                uthread_resume(2);
//            }
//            if((16<= uthread_get_total_quantums()) && (uthread_get_total_quantums()<=19))
//            {
//                std::cout << " z block g:\n";
//                uthread_block(2);
//            }
//            if((45<= uthread_get_total_quantums()) && (uthread_get_total_quantums()<=50))
//            {
//                std::cout<< " z try to resume f\n";
//                if(uthread_resume(1))
//                {
//                    std::cout << " f doesnt exist\n";
//                }
//                std::cout << " z create new f's\n";
//                uthread_spawn(f);
//            }
//        }
//    }
//}
//
//
//int main() {
//    uthread_init(100000);
//    uthread_spawn(f);
//    uthread_spawn(g);
//    uthread_spawn(z);
//    for (;;) {
//        if (gotit4) {
//            std::cout << "in main id: " << uthread_get_tid() << " "  << uthread_get_quantums
//                    (uthread_get_tid()) << std::endl;
//            std::cout << "Prog q count " << uthread_get_total_quantums() << std::endl;
//            gotit4 = 0;
//            gotit1 = 1;
//            gotit2 = 1;
//            gotit3 = 1;
//            if((16<= uthread_get_total_quantums()) && (uthread_get_total_quantums()<=17))
//            {
//                std::cout << " main resume g but g is sleeping:\n";
//                uthread_resume(2);
//            }
//            if((34<= uthread_get_total_quantums()) && (uthread_get_total_quantums()<=35))
//            {
//                std::cout<< " main terminated f\n";
//                uthread_terminate(1);
//            }
//            if((50<= uthread_get_total_quantums()) && (uthread_get_total_quantums()<=53))
//            {
//                std::cout << " main resume g:\n";
//                uthread_resume(2);
//            }
//            if((60<= uthread_get_total_quantums()) && (uthread_get_total_quantums()<=62))
//            {
//                std::cout<< " main terminated f (1) \n";
//                uthread_terminate(1);
//            }
//            if((65<= uthread_get_total_quantums()) && (uthread_get_total_quantums()<=68))
//            {
//                std::cout<< " main terminated g (2) \n";
//                uthread_terminate(2);
//            }
//            if((71<= uthread_get_total_quantums()) && (uthread_get_total_quantums()<=75))
//            {
//                std::cout<< " main terminated the main (end of prog) \n";
//                uthread_terminate(0);
//            }
//        }
//    }
//}


//// TEST 8(GROUP)

#include "uthreads.h"
#include <stdio.h>
#include <iostream>

int gotit1 = 0;
int gotit2 = 0;
int gotit3 = 0;
int gotit4 = 1;

void f(void) {
    while (1) {
        if (gotit1) {
            std::cout << "in f id: " <<  uthread_get_tid() << " " << uthread_get_quantums
                    (uthread_get_tid()) << std::endl;
            gotit1 = 0;
            gotit2 = 1;
            gotit3 = 1;
            gotit4 = 1;
            if((5<= uthread_get_total_quantums()) && (uthread_get_total_quantums()<=7))
            {
                std::cout<< " f sleep for 100000 usec\n";
                uthread_sleep(100000);
            }
            if((20<= uthread_get_total_quantums()) && (uthread_get_total_quantums()<=21))
            {
                std::cout<< " f sleep for 1 sec\n";
                uthread_sleep(1000000);
            }
        }
    }
}

void g(void) {
    while (1) {
        if (gotit2) {
            std::cout << "in g id: "  << uthread_get_tid() << " " << uthread_get_quantums
                    (uthread_get_tid()) << std::endl;
            gotit2 = 0;
            gotit1 = 1;
            gotit3 = 1;
            gotit4 = 1;
            if((6<= uthread_get_total_quantums()) && (uthread_get_total_quantums()<=8))
            {
                std::cout<< " g terminate  f\n";
                uthread_terminate(1);
            }
            if((9<= uthread_get_total_quantums()) && (uthread_get_total_quantums()<=10))
            {
                std::cout<< " g spawn new f\n";
                uthread_spawn(f);
            }
            if((21<= uthread_get_total_quantums()) && (uthread_get_total_quantums()<=22))
            {
                std::cout<< " g sleep for 1 sec\n";
                uthread_sleep(1000000);
            }
        }
    }
}
void z(void) {
    while (1) {
        if (gotit3)
        {
            std::cout << "in z id: " << uthread_get_tid() << " " << uthread_get_quantums
                    (uthread_get_tid
                             ()) << std::endl;
            gotit3 = 0;
            gotit1 = 1;
            gotit2 = 1;
            gotit4 = 1;
            if((4<= uthread_get_total_quantums()) && (uthread_get_total_quantums()<=5))
            {
                std::cout<< " z sleep for 0 usec\n";
                uthread_sleep(0);
            }
            if((23<= uthread_get_total_quantums()) && (uthread_get_total_quantums()<=24))
            {
                std::cout<< " z sleep for 1 sec\n";
                uthread_sleep(1000000);
            }
        }
    }
}


int main() {
    uthread_init(100000);
    uthread_spawn(f);
    uthread_spawn(g);
    uthread_spawn(z);
    for (;;) {
        if (gotit4) {
            std::cout << "in main id: " << uthread_get_tid() << " "  << uthread_get_quantums
                    (uthread_get_tid()) << std::endl;
            std::cout << "Prog q count " << uthread_get_total_quantums() << std::endl;
            gotit4 = 0;
            gotit1 = 1;
            gotit2 = 1;
            gotit3 = 1;
        }
        if((52<= uthread_get_total_quantums()) && (uthread_get_total_quantums()<=53))
        {
            std::cout<< " end of the program\n";
            uthread_terminate(0);
        }

    }
}





