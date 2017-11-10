/*
 * @Author: david.kelly 
 * @Date: 2017-11-09 12:51:56 
 * @Last Modified by:   david.kelly 
 * @Last Modified time: 2017-11-09 12:51:56 
 */

 /*! \file SafeBuffer.cpp
    \brief A implemnetation of a resuable barrier class
*/
#include "SafeBuffer.h"
/*! \class SafeBuffer
    \brief A Safe Buffer Implementation

   Uses C++11 features such as mutex and condition variables to implement a reusable barrier

*/

/*! \fn void Consumer()
    \brief This function will be called from a thread
*/
char SafeBuffer::Consumer()
{
    itemsLock->Wait();
    bufferLock->Wait();
    char c = sharedBuffer.front();
    sharedBuffer.pop();
    bufferLock->Signal();
    freeSpaces->Signal();
    return c;

}

/*! \fn void Produce()
    \brief This function will be called from a thread
*/
void SafeBuffer::Producer(char c)
{
    freeSpaces->Wait();
    bufferLock->Wait();
    sharedBuffer.push(c);
    itemsLock->Signal();
    bufferLock->Signal();
}

SafeBuffer::SafeBuffer(int max=0){

  bufferLock = std::make_shared<Semaphore>(1);
  itemsLock = std::make_shared<Semaphore>(0);
  freeSpaces = std::make_shared<Semaphore>(max);
}
