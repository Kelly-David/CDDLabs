/*
 * @Author: david.kelly 
 * @Date: 2017-11-09 12:40:56 
 * @Last Modified by: david.kelly
 * @Last Modified time: 2017-11-09 12:51:34
 */

/*! \file SafeBuffer.h
    \brief A implementation of a safe buffer
*/
#pragma once
#include "Semaphore.h"
#include <stdlib.h>  
#include <iostream>
#include <queue>

/*! \class SafeBuffer
    \brief A Safe Buffer Implementation

   Uses C++11 features such as mutex and condition variables to implement the producer-consumer safe buffer

*/
class SafeBuffer
{
public:
    int limit; // Buffer capacity
    int count = 0; 

    std::queue<char> sharedBuffer ; // Shared buffer

    std::shared_ptr<Semaphore> bufferLock; 
    std::shared_ptr<Semaphore> itemsLock; 
    std::shared_ptr<Semaphore> freeSpaces; 


    SafeBuffer(int);
    void Producer(char);
    char Consumer();
};
