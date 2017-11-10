/*
 * @Author: david.kelly 
 * @Date: 2017-11-09 11:45:39 
 * @Last Modified by: david.kelly
 * @Last Modified time: 2017-11-09 13:16:06
 */

/*! @file prodCon.cpp
    @brief Producer Consumer Example.
*/
#include "SafeBuffer.h"
#include <stdlib.h>  
#include <iostream>
#include <thread>
#include <vector>


/*! @global int globalCount
    @brief This is a global variable to count threads that reached the barrier
*/ 
int sharedBuffer = 0;
bool go = true;
int tally [26] = {0};

/*! @fn void produce(std::shared_ptr<Semaphore> buffer, std::shared_ptr<Semaphore> items)
    @brief This function will be called from a thread
    
*/ 
void produce(int randNum, std::shared_ptr<SafeBuffer> buffer) {
	for(int i = 0; i < randNum; ++i) {
		int n = rand() % 26;
		char c = (char)(n + 97);
		buffer->Producer(c);
	}
}

/*! @fn void consume(std::shared_ptr<Semaphore> buffer, std::shared_ptr<Semaphore> items)
    @brief This function will be called from a thread
    
*/ 
void consume(std::shared_ptr<SafeBuffer> buffer) {
	while (go) {
		char c = buffer->Consumer();
		if (c == 'X') { 
			go = false;
		}
		else {
			tally[(int(c))-97]++;
		}
	}
}

/*! @fn void createThreads()
    @brief This function will be called from main
    @param barrier the shared barrier object
    @param n the number of threads
    
    creates vector of type thread
    forks two threads: one producer; one consumer
    joins the vector of threads
*/ 
void createThreads(int randNum, std::shared_ptr<SafeBuffer> buffer) {

	std::vector<std::thread> threads;

	/*! @brief fork two threads */
	threads.push_back(std::thread(produce, randNum, buffer));
	threads.push_back(std::thread(consume, randNum, buffer));
	

	/*! @brief loop will parse each thread element inside threads vector */
	for(auto& thread : threads) {
		thread.join();
	}
}

 /*! @fn int main()
    @brief The main function
    
    Creates two shared semaphore objects
    Calls void function
*/

int main(void){
	
	int randNum = rand() % 60 + 30;

	std::shared_ptr<SafeBuffer> buffer(new SafeBuffer(randNum));	

	createThreads(randNum, buffer);

	// Print the tally of letters
	for (int i = 0; i < 26; ++i) {
		std::cout << tally[i] << "\n";
	}	
	
	std::cout << "Complete \n";

	return 0;
}
