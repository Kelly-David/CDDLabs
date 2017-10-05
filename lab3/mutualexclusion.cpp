/*! \file mutualexclusion.cpp
    \brief A Documented file.
*/
#include "Semaphore.h"
#include <iostream>
#include <thread>

/*! \global int globalCount
    \brief This is a global variable to demo mutual exclusion
*/ 
int globalCount = 1;

/*! \fn void taskOne(std::shared_ptr<Semaphore> theSemaphore)
    \brief This function will be called from a thread
    \param theSemaphore the the shared semaphore object
    
    theSemaphore calls wait()
    The function prints to the screen
    The function updates a global variable
    theSemaphore calls signal()
*/ 
void taskOne(std::shared_ptr<Semaphore> mutexLock ){
  mutexLock->Wait();
  std::cout <<"Thread1: Critical Stuff\n";
  globalCount = globalCount + 1;
  mutexLock->Signal();
}

/*! \fn void taskTwo(std::shared_ptr<Semaphore> theSemaphore)
    \brief This function will be called from a thread
    \param theSemaphore the the shared semaphore object
    
    theSemaphore calls wait()
    The function prints to the screen
    The function updates a global variable
    theSemaphote call signal()
*/ 
void taskTwo(std::shared_ptr<Semaphore> mutexLock){
  mutexLock->Wait();
  std::cout <<"Thread2: Critical stuff\n";
  globalCount = globalCount - 1;
  mutexLock->Signal();
}

 /*! \fn int main()
    \brief The eponymous main function
    
    Forks two threads and a shared semaphore
    Assigns a task to each thread
    Then joins both threads with the main thread
*/
int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> mutexLock( new Semaphore(1));
  /**< Launch the threads  */
  threadOne=std::thread(taskTwo,mutexLock);
  threadTwo=std::thread(taskOne,mutexLock);
  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();
  std::cout << "Global count should equal 1. Now is equal: ";
  std::cout << globalCount;
  std::cout << "\n";
  return 0;
}
