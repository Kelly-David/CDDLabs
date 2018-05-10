/*
 * File: rendevous.cpp
 * Project: CDD Labs
 * File Created: Tuesday, 3rd October 2017 2:17:48 pm
 * Author: David Kelly (c00193216@itcarlow.ie)
 * -----
 * Last Modified: Thursday, 10th May 2018 10:16:48 am
 * Modified By: David Kelly
 * -----
 * License GPL-3.0
 * -----
 * Description: An implementation of the rendevous pattern using semaphores. Forks two threads sharing two semaphores. Each assigned a task and rendevous point. Both must wait for the other to arrivr at point before continuing. 
 */

/*! \file rendevous.cpp
    \brief A Documented file.
*/
#include "Semaphore.h"
#include <iostream>
#include <thread>

/*! \fn void taskOne(std::shared_ptr<Semaphore> oneArrived, std::shared_ptr<Semaphore> twoArrived, )
    \brief Description of void taskOne function
    \param oneArrived the the shared semaphore object
    \param twoArrived the the shared semaphore object
    \details Signals to other threads that has arrived at rendevous. 
*/ 
void taskOne(std::shared_ptr<Semaphore> oneArrived,std::shared_ptr<Semaphore> twoArrived ){
  std::cout <<"Stuff before rendevous\n";
  std::cout << "...waiting for T2\n";
  oneArrived->Signal(); // One has arrived at rendevous point
  twoArrived->Wait();
  std::cout <<"Stuff after rendevous\n";
  std::cout << "...T1 finished!\n";
}

/*! \fn void taskTwo(std::shared_ptr<Semaphore> oneArrived, std::shared_ptr<Semaphore> twoArrived, )
    \brief Description of void taskTwo function
    \param oneArrived the the shared semaphore object
    \param twoArrived the the shared semaphore object
    \details Signals to other threads that it has arrived at rendevous point. 
*/ 
void taskTwo(std::shared_ptr<Semaphore> oneArrived,std::shared_ptr<Semaphore> twoArrived){
  std::cout <<"Stuff before rendevous\n";
  std::cout << "...waiting for T1\n";
  twoArrived->Signal(); // Two has arrived at rendevous point
  oneArrived->Wait();
  std::cout <<"Stuff after rendevous\n";
  std::cout << "...T2 finished!\n";
}

/*! \fn int main()
    \brief Forks two threads and two shared semaphores. Assigns a task to each thread. Then joins both threads with the main thread
*/
int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> oneArrived( new Semaphore);
  std::shared_ptr<Semaphore> twoArrived( new Semaphore);
  threadOne=std::thread(taskTwo,oneArrived, twoArrived);
  threadTwo=std::thread(taskOne,oneArrived, twoArrived);

  std::cout << "Launched from main...\n";

  threadOne.join();
  threadTwo.join();

  std::cout << "All threads joined!\n";
  
  return 0;
}
