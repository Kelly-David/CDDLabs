/*
 * File: signal.cpp
 * Project: CDD Labs
 * File Created: Wednesday, 3rd October 2017 5:05:47 pm
 * Author: David Kelly (c00193216@itcarlow.ie)
 * -----
 * Last Modified: Wednesday, 9th May 2018 5:24:15 pm
 * Modified By: David Kelly
 * -----
 * License GPL-3.0
 * -----
 * Description: Simple signal using semaphores
 */

#include "Semaphore.h"
#include <iostream>
#include <thread>

/*! \fn void taskOne(std::shared_ptr<Semaphore> theSemaphore)
    \brief This function will be called from a thread. Will always run first. Then semaphore signals other to run.
    \param theSemaphore the the shared semaphore object
*/ 
void taskOne(std::shared_ptr<Semaphore> theSemaphore){
  std::cout <<"I ";
  std::cout << "must ";
  std::cout << "print ";
  std::cout << "first"<<std::endl;
  /*! Signal others to run */
  theSemaphore->Signal();
}

/*! \fn void taskTwo(std::shared_ptr<Semaphore> theSemaphore)
    \brief This function will be called from a thread. Initially blocked. Waits for signal.
    \param theSemaphore the the shared semaphore object
*/ 
void taskTwo(std::shared_ptr<Semaphore> theSemaphore){
  /*! Hold the thread for a signal */
  theSemaphore->Wait();
  std::cout <<"This ";
  std::cout << "will ";
  std::cout << "appear ";
  std::cout << "second"<<std::endl;
}

 /*! \fn int main()
    \brief Forks two threads and a shared semaphore. Assigns a task to each thread. Then joins both threads with the main thread
*/
int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem( new Semaphore);
  /*! Launch the threads  */
  threadOne=std::thread(taskTwo,sem);
  threadTwo=std::thread(taskOne,sem);
  std::cout << "Launched from main\n";
  threadOne.join();
  threadTwo.join();
  return 0;
}
