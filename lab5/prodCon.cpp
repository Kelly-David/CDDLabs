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
#include <chrono>


/*! @global int tally[]
    @brief This is an array to tally the char consumed from the safe buffer
*/ 
bool go = true;
int tally [26] = {0};

/*! @fn void produce(int randNum, std::shared_ptr<SafeBuffer> buffer)
    @brief This function will produce items to a shared  buffer
	@param randNum : the number od items to be produced
	@param buffer : the shared buffer
    
*/ 
void produce(int randNum, std::shared_ptr<SafeBuffer> buffer) {
	for(int i = 0; i < randNum; ++i) {
		int n = std::rand() % 26;
		char c = (char)(n + 97);
		buffer->Producer(c);
		std::cout << "Produced: " << c << std::endl;
	}
	buffer->Producer('X');
}

/*! @fn void consume(std::shared_ptr<SafeBuffer> buffer)
    @brief This function consume items from a shared buffer
	@param buffer : the shared buffer
    
*/ 
void consume(std::shared_ptr<SafeBuffer> buffer) {
	while (go) {
		char c = buffer->Consumer();
		std::cout << "Consumed: " << c << std::endl;
    	std::this_thread::sleep_for(std::chrono::milliseconds(std::rand()%1000));
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
    @param randNum : total items to be produced - passed to producer thread
    @param buffer : the shared buffer
    
    creates vector of type thread
    forks two threads: one producer; one consumer
    joins the vector of threads
*/ 
void createThreads(int randNum, std::shared_ptr<SafeBuffer> buffer) {

	std::vector<std::thread> threads;

	/*! @brief fork two threads */
	threads.push_back(std::thread(produce, randNum, buffer));
	threads.push_back(std::thread(consume, buffer));

	/*! @brief loop will parse each thread element inside threads vector */
	for(auto& thread : threads) {
		thread.join();
	}
}

 /*! @fn int main()
    @brief The main function
    
    Generate random number
	Create shared buffer
	Call void function
	Output result
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
