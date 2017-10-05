/*! \file mutualexclusion.cpp
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
void taskOne(std::shared_ptr<Semaphore> oneArrived,std::shared_ptr<Semaphore> twoArrived ){
  std::cout <<"Stuff before rendevous ";
  std::cout << "...waiting for T2 ";
  oneArrived->Signal(); //One has arrived at rendevous point
  twoArrived->Wait();
  std::cout <<"Stuff after rendevous ";
  std::cout << "...T1 finished! ";
}

/*! \fn void taskTwo(std::shared_ptr<Semaphore> theSemaphore)
    \brief This function will be called from a thread
    \param theSemaphore the the shared semaphore object
    
    theSemaphore calls wait()
    The function prints to the screen
*/ 
void taskTwo(std::shared_ptr<Semaphore> oneArrived,std::shared_ptr<Semaphore> twoArrived){
  std::cout <<"Stuff before rendevous ";
  std::cout << "...waiting for T1 ";
  twoArrived->Signal(); //Two has arrived at rendevous point
  oneArrived->Wait();
  std::cout <<"Stuff after rendevous ";
  std::cout << "...T2 finished! ";
}

 /*! \fn int main()
    \brief The eponymous main function
    
    Forks two threads and a shared semaphore
    Assigns a task to each thread
    Then joins both threads with the main thread
*/
int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> oneArrived( new Semaphore);
  std::shared_ptr<Semaphore> twoArrived( new Semaphore);
  /**< Launch the threads  */
  threadOne=std::thread(taskTwo,oneArrived, twoArrived);
  threadTwo=std::thread(taskOne,oneArrived, twoArrived);
  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();
  return 0;
}
