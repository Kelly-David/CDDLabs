/*
 * File: Barrier.cpp
 * Project: CDD Labs
 * File Created: Thursday, 9th November 2017 11:30:49 am
 * Author: David Kelly (c00193216@itcarlow.ie)
 * -----
 * Last Modified: Thursday, 10th May 2018 1:32:33 pm
 * Modified By: David Kelly
 * -----
 * License GPL-3.0
 * -----
 * Description: Reusable barrier class
 */

/*! \file Barrier.cpp
    \brief A implementation of a resuable barrier class
*/
#include "Barrier.h"
 
/*! \fn void Phase1()
    \brief This function will be called from a thread
    \details Indicates that the threads have reached the rendevous point.
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