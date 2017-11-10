/*
 * @Author: david.kelly 
 * @Date: 2017-11-09 11:45:59 
 * @Last Modified by: david.kelly
 * @Last Modified time: 2017-11-09 11:47:51
 */

/*! \file Barrier.cpp
    \brief A implemnetation of a resuable barrier class
*/
#include "Barrier.h"
/*! \class Barrier
    \brief A Reusable Barrier Implementation

   Uses C++11 features such as mutex and condition variables to implement a reusable barrier

*/
//std::shared_ptr<Semaphore> mutexLock( new Semaphore(1)); /*!< Mutex Lock */
//std::shared_ptr<Semaphore> turnstileA( new Semaphore(0)); /*!< First turnstile - rendevous point */
//std::shared_ptr<Semaphore> turnstileB( new Semaphore(1)); /*!< Second turnstile - final barrier */ 

/*! \fn void Phase1()
    \brief This function will be called from a thread
*/
void Barrier::Phase1()
{
  mutexLock->Wait();
  m_count++;
  if (m_count == m_threads) {
    turnstileB->Wait();
    turnstileA->Signal();
  }
  mutexLock->Signal();
  turnstileA->Wait();
  turnstileA->Signal();
     
}

/*! \fn void Phase2()
    \brief This function will be called from a thread
*/
void Barrier::Phase2()
{
  mutexLock->Wait();
  m_count--;
  if (m_count == 0) {
    turnstileA->Wait();
    turnstileB->Signal();
  }
  mutexLock->Signal();
  turnstileB->Wait();
  turnstileB->Signal();
}

/*! \fn void wait()
    \brief This function will be called from a thread
*/
void Barrier::Wait()
{
  Phase1();
  Phase2();
}

Barrier::Barrier(int threads=0) : m_threads(threads), m_count(0) {
  mutexLock = std::make_shared<Semaphore>(1);
  turnstileA = std::make_shared<Semaphore>(0);
  turnstileB = std::make_shared<Semaphore>(1);
}