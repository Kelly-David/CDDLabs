/*
 * File: SafeBuffer.cpp
 * Project: CDD Labs
 * File Created: Monday, 27th November 2017 9:24:58 am
 * Author: David Kelly (c00193216@itcarlow.ie)
 * -----
 * Last Modified: Thursday, 10th May 2018 8:48:29 pm
 * Modified By: David Kelly
 * -----
 * License GPL-3.0
 * -----
 * Description: Safe buffer
 */

#include "SafeBuffer.h"

/*! \fn Constructor
    \brief Buffer size is set to max or 0
*/
SafeBuffer::SafeBuffer(int max=0){

  lock = std::make_shared<Semaphore>(1);
  items = std::make_shared<Semaphore>(0);
  spaces = std::make_shared<Semaphore>(max);
}

/*! \fn void Producer()
    \brief This function will be called from a thread. 
    \details Adds item to the buffer
*/
void SafeBuffer::Producer(char c)
{
    spaces->Wait();
    lock->Wait();
    sharedBuffer.push(c);
    lock->Signal();
    items->Signal();
}

/*! \fn void Consumer()
    \brief This function will be called from a thread.
    \details Returns first item in the buffer
*/
char SafeBuffer::Consumer()
{
    char c;
    items->Wait();
    lock->Wait();
    c = sharedBuffer.front();
    sharedBuffer.pop();
    lock->Signal();
    spaces->Signal();
    return c;
}
