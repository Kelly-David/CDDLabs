/*! @author David Kelly
    @date:  10/10/2017
    @updated: 10/10/2017
*/

/*! @file barrierExample.cpp
    @brief A Documented file.
*/
#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>


/*! @global int globalCount
    @brief This is a global variable to demo mutual exclusion
*/ 
int globalCount = 0;

/*! @fn void taskOne(std::shared_ptr<Semaphore> mutexLock, std::shared_ptr<Semaphore> barrier, int n)
    @brief This function will be called from a thread
    @param mutexLock the shared semaphore object
    @param barrier the shared semaphore object
    @param n the number of threads
    
    mutexLock calls wait()
    The function prints to the screen
    The function updates the globalCount
    If the count == the number of threads ? barrier.signal() : barrier.wait()
    mutexLock calls signal()
*/ 
void taskOne(std::shared_ptr<Semaphore> mutexLock, std::shared_ptr<Semaphore> barrier, int n){

	mutexLock->Wait();
	globalCount++;
	std::cout <<"Thread: " << globalCount << " acquired mutexLock" << "\n" ;

	if (globalCount == n) {
		std::cout <<"******************************" << "\n" ;
		std::cout <<"All threads have reached barrier" << "\n" ;
		std::cout <<"******************************" << "\n" ;
		barrier->Signal();}

	mutexLock->Signal();
	std::cout <<"Thread: " << globalCount << " released mutexLock" << "\n" ;

	barrier->Wait(); //barrier - all threads must wait here
	std::cout <<"A thread called barrier.wait" << "\n" ;

	barrier->Signal();
	std::cout <<"A thread called barrier.signal" << "\n" ;

}

/*! @fn void creatThreads(int n, std::shared_ptr<Semaphore> mutexLock, std::shared_ptr<Semaphore> barrier)
    @brief This function will be called from main
    @param mutexLock the shared semaphore object
    @param barrier the shared semaphore object
    @param n the number of threads
    
    creates vecotr of type thread
    forks n thread pushed to vector threads
    joins the vector of threads
*/ 
void createThreads(int n, std::shared_ptr<Semaphore> mutexLock, std::shared_ptr<Semaphore> barrier) {

	std::vector<std::thread> threads;

	/*! @brief fork n threads */
	for (int i = 0; i < n; i++) {
		threads.push_back(std::thread(taskOne, mutexLock, barrier, n));
	}

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
	int nThreads = 5;

	std::shared_ptr<Semaphore> mutexLock( new Semaphore(1));
	std::shared_ptr<Semaphore> barrier( new Semaphore(0));

	/**< Launch the threads  */
	std::cout << "Launched from the main\n";
	createThreads(nThreads, mutexLock, barrier);

	std::cout << "Complete \n";

	return 0;
}
