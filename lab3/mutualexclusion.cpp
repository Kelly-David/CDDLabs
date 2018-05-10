/*
 * File: mutualexclusion.cpp
 * Project: CDD Labs
 * File Created: Wednesday, 18th October 2017 8:51:09 am
 * Author: David Kelly (c00193216@itcarlow.ie)
 * -----
 * Last Modified: Thursday, 10th May 2018 1:00:46 pm
 * Modified By: David Kelly
 * -----
 * License GPL-3.0
 * -----
 * Description: Demonstration of mutual exclusion using semaphores. Two threads read and write to a shared resource.
 */

/*! \file mutualexclusion.cpp
    \brief A mutual exclusion example
*/
#include "Semaphore.h"
#include <iostream>
#include <thread>

/*! \global int globalCount
    \brief This is a global variable to demo mutual exclusion
*/ 
int globalCount = 1;

/*! \fn void taskOne(std::shared_ptr<Semaphore> mutexLock)
    \brief Description of void taskOne function
    \param mutexLock the shared semaphore object
    \details Thread takes exclusive access to the shared resource
*/ 
void taskOne(std::shared_ptr<Semaphore> mutexLock ){
  mutexLock->Wait();
  std::cout <<"Thread1 reads shared resource : ";
  std::cout << globalCount << "\n";
  std::cout <<"Thread1 updates shared resource...+1\n";
  globalCount = globalCount + 1;  
  std::cout <<"Thread1 reads it again : ";
  std::cout << globalCount << "\n";
  mutexLock->Signal();
}

/*! \fn void taskTwo(std::shared_ptr<Semaphore> mutexLock)
    \brief Description of void taksTwo function
    \param mutexLock the shared semaphore object
    \details Thread takes exclusive access to the shared resource
*/
void taskTwo(std::shared_ptr<Semaphore> mutexLock){
  mutexLock->Wait();
  std::cout <<"Thread2 reads shared resource : ";
  std::cout << globalCount << "\n";
  std::cout <<"Thread2 updates shared resource... -1\n";
  globalCount = globalCount - 1;  
  std::cout <<"Thread2 reads it again : ";
  std::cout << globalCount << "\n";
  mutexLock->Signal();
}

 /*! \fn int main()
    \brief The eponymous main function
    \details Forks two threads with a shared lock
*/
int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> mutexLock( new Semaphore(1));
  threadOne=std::thread(taskTwo,mutexLock);
  threadTwo=std::thread(taskOne,mutexLock);

  std::cout << "Launched from main...\n";

  threadOne.join();
  threadTwo.join();

  std::cout << "All threads joined!\n";
  
  return 0;
}
