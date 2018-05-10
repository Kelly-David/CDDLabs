/*
 * File: prodCon.cpp
 * Project: CDD Labs
 * File Created: Monday, 27th November 2017 9:18:04 am
 * Author: David Kelly (c00193216@itcarlow.ie)
 * -----
 * Last Modified: Thursday, 10th May 2018 8:56:40 pm
 * Modified By: David Kelly
 * -----
 * License GPL-3.0
 * -----
 * Description: Producer - consumer example
 */

#include "SafeBuffer.h"
#include <stdlib.h>  
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

/*! \global int tally[]
    \brief This is an array to tally the char consumed from the safe buffer
*/ 
int tally [26] = {0};

/*! \fn void produce(int randNum, std::shared_ptr<SafeBuffer> buffer)
    \brief Description of void produce function
	\param randNum : the number od items to be produced
	\param buffer : the shared buffer
	\details This function will produce items to a shared  buffer
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

/*! \fn void consume(std::shared_ptr<SafeBuffer> buffer)
    \brief Description of void consume function
	\param buffer : the shared buffer
	\details This function consume items from a shared buffer
*/ 
void consume(std::shared_ptr<SafeBuffer> buffer) {
	char c;
	do {
		c = buffer->Consumer();
		std::cout << "Consumed: " << c << std::endl;
    	std::this_thread::sleep_for(std::chrono::milliseconds(std::rand()%1000));
		tally[(int(c))-97]++;
	} while ( c != 'X');
}

/*! \fn void createThreads()
    \brief This function will be called from main
    \param randNum : total items to be produced - passed to producer thread
    \param buffer : the shared buffer
    \details Creates vector of type thread. Forks two threads: one producer; one consumer. Joins the vector of threads
*/ 
void createThreads(int randNum, std::shared_ptr<SafeBuffer> buffer) {

	std::vector<std::thread> threads;

	/*! \brief fork two threads */
	threads.push_back(std::thread(produce, randNum, buffer));
	threads.push_back(std::thread(consume, buffer));

	/*! \brief loop will parse each thread element inside threads vector */
	for(auto& thread : threads) {
		thread.join();
	}
}

void printTally() {
	std::cout << "TOTAL CHARACTER COUNT\n";
	for ( char i = 97; i < 123; ++i ) {
		std::cout << i << " : " << tally[i-97] << "\n";
		
	}

}

 /*! \fn int main()
    \brief The main function
	\details Generate random number. Creates shared buffer.
*/

int main(void){
	
	int randNum = rand() % 60 + 30;

	std::shared_ptr<SafeBuffer> buffer(new SafeBuffer(randNum));

	createThreads(randNum, buffer);

	// Print the tally of letters
	printTally();	
	
	std::cout << "Complete \n";

	return 0;
}
