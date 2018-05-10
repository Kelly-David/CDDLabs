/*
 * File: reusableBarrier.cpp
 * Project: CDD Labs
 * File Created: Thursday, 9th November 2017 11:56:26 am
 * Author: David Kelly (c00193216@itcarlow.ie)
 * -----
 * Last Modified: Thursday, 10th May 2018 1:48:40 pm
 * Modified By: David Kelly
 * -----
 * License GPL-3.0
 * -----
 * Description: Demonstration of a reusable barrier
 */


/*! @file barrierExample.cpp
    @brief A reusable barrier example (with Barrier Class).
*/
#include "Barrier.h"
#include <iostream>
#include <thread>
#include <vector>

/*! \fn void task(std::shared_ptr<Barrier> barrier)
    \brief Description of void task function
	\param barrier a shared barrier object
	\details Threads will enter barrier, wait for all threads pass phase1, then proceed to phase2
*/ 
void task(std::shared_ptr<Barrier> barrier) {
	std::cout << "First phase" << std::endl;
	barrier->Phase1();
	std::cout << "Second phase" << std::endl;	
	barrier->Phase2();
}

/*! \fn void creatThreads(int n, std::shared_ptr<Barrier> barrier)
    \brief This function will be called from main
    \param barrier the shared barrier object
    \param n the number of threads
    \details Creates vector of type thread, forks n thread pushed to vector threads, joins the vector of threads
*/ 
void createThreads(int n, std::shared_ptr<Barrier> barrier) {

	std::vector<std::thread> threads;

	/*! \details fork n threads */
	for (int i = 0; i < n; i++) {
		threads.push_back(std::thread(task, barrier));
	}

	/*! \details loop will parse each thread element inside threads vector */
	for(auto& thread : threads) {
		thread.join();
	}
}

 /*! \fn int main()
	 \brief The main function
	 \details Creates a shared barrier object
*/

int main(void){
    /**< Number of threads */
    int nThreads = 5;

    /**< Create shared barrier object */
	std::shared_ptr<Barrier> barrier(new Barrier(nThreads));

	/**< Launch the threads  */
	std::cout << "Launched from the main\n";
	createThreads(nThreads, barrier);

	std::cout << "All Complete \n";

	return 0;
}
