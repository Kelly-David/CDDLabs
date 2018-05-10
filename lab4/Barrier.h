/*
 * File: Barrier.h
 * Project: CDD Labs
 * File Created: Thursday, 9th November 2017 11:30:49 am
 * Author: David Kelly (c00193216@itcarlow.ie)
 * -----
 * Last Modified: Thursday, 10th May 2018 1:31:35 pm
 * Modified By: David Kelly
 * -----
 * License GPL-3.0
 * -----
 * Description: A Reusable barrier class using semaphores
 */

/*! \file Barrier.h
    \brief An implementation of a resuable barrier class
*/
#include <mutex>
#include "Semaphore.h"

/*! \class Barrier
    \brief A Reusable Barrier Implementation (ie. rendevous point from more than two threads).
*/
class Barrier
{
public:
    int m_threads; /*!< Holds the number of threads */
    int m_count; /*!< Running count */
    std::shared_ptr<Semaphore> mutexLock; /*!< Mutex Lock */
    std::shared_ptr<Semaphore> turnstileA; /*!< First turnstile - rendevous point */
    std::shared_ptr<Semaphore> turnstileB; /*!< Second turnstile - final barrier */ 

    Barrier(int threads);
    void Phase1();
    void Phase2();
    void Wait();
};
