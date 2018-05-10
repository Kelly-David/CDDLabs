/*
 * File: SafeBuffer.h
 * Project: CDD Labs
 * File Created: Monday, 27th November 2017 9:23:12 am
 * Author: David Kelly (c00193216@itcarlow.ie)
 * -----
 * Last Modified: Thursday, 10th May 2018 8:43:35 pm
 * Modified By: David Kelly
 * -----
 * License GPL-3.0
 * -----
 * Description: A safe buffer class
 */

/*! \file SafeBuffer.h
*/
#pragma once
#include <mutex>
#include "Semaphore.h"
#include <queue>

/*! \class SafeBuffer
    \brief A Safe Buffer Implementation

   Uses C++11 features such as mutex and condition variables to implement the producer-consumer safe buffer

*/
class SafeBuffer
{
public:
    std::queue<char> sharedBuffer ; // Shared buffer
    std::shared_ptr<Semaphore> lock; 
    std::shared_ptr<Semaphore> items; 
    std::shared_ptr<Semaphore> spaces; 
    SafeBuffer(int);
    void Producer(char);
    char Consumer();
};
