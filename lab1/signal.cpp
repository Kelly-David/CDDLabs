/*! \file signal.cpp
    \brief A Documented file.
*/
#include "Semaphore.h"
#include <iostream>
#include <thread>

/*! \fn void taskOne(std::shared_ptr<Semaphore> theSemaphore)
    \brief This function will be called from a thread
    \param theSemaphore the the shared semaphore object
    
    The function prints to the screen
    theSemaphore calls signal()
*/ 
void taskOne(std::shared_ptr<Semaphore> theSemaphore){
  std::cout <<"I ";
  std::cout << "must ";
  std::cout << "print ";
  std::cout << "first"<<std::endl;
  theSemaphore->Signal();
}

/*! \fn void taskTwo(std::shared_ptr<Semaphore> theSemaphore)
    \brief This function will be called from a thread
    \param theSemaphore the the shared semaphore object
    
    theSemaphore calls wait()
    The function prints to the screen
*/ 
void taskTwo(std::shared_ptr<Semaphore> theSemaphore){
  theSemaphore->Wait();
  std::cout <<"This ";
  std::cout << "will ";
  std::cout << "appear ";
  std::cout << "second"<<std::endl;
}

 /*! \fn int main()
    \brief The eponymous main function
    
    Forks two threads and a shared semaphore
    Assigns a task to each thread
    Then joins both threads with the main thread
*/
int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem( new Semaphore);
  /**< Launch the threads  */
  threadOne=std::thread(taskTwo,sem);
  threadTwo=std::thread(taskOne,sem);
  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();
  return 0;
}
