/*! @author David Kelly
    @date:  10/10/2017
    @updated: 23/10/2017
*/

/*! @file barrierExample.cpp
    @brief A reusable barrier example (with Barrier Class).
*/
#include "Barrier.h"
#include <iostream>
#include <thread>
#include <vector>


/*! @global int globalCount
    @brief This is a global variable to count threads that reached the barrier
*/ 
int globalCount = 0;

/*! @fn void taskOne(std::shared_ptr<Semaphore> mutexLock, std::shared_ptr<Semaphore> barrierA, std::shared_ptr<Semaphore> barrierB, int n)
    @brief This function will be called from a thread
    @param mutexLock the shared semaphore object
    @param barrierA a shared semaphore object
    @param barrierB a shared semaphore object
    @param n the number of threads
    
    N number of threads will waith at barrierA, then proceed and wait at barrierB
*/ 
void task (std::shared_ptr<Barrier> barrier) {

	barrier->Phase1();
	std::cout <<"A thread called barrier->Phase1();" << "\n" ;
	barrier->Phase2();
	std::cout <<"A thread called barrier->Phase2();" << "\n" ;

}
/*void taskOne(std::shared_ptr<Semaphore> mutexLock, std::shared_ptr<Semaphore> barrierA, std::shared_ptr<Semaphore> barrierB, int n){

	mutexLock->Wait();
	globalCount++;
	std::cout <<"Thread: " << globalCount << " acquired mutexLock" << "\n" ;

	if (globalCount == n) {
		std::cout <<"******************************" << "\n" ;
		std::cout <<"All threads have reached barrier" << "\n" ;
		std::cout <<"******************************" << "\n" ;
		barrierB->Wait();
		barrierA->Signal();
	}

	mutexLock->Signal();
	std::cout <<"Thread: " << globalCount << " released mutexLock" << "\n" ;

	barrierA->Wait(); //barrier - all threads must wait here
	std::cout <<"A thread called barrier.wait" << "\n" ;

	barrierA->Signal();
	std::cout <<"A thread called barrier.signal" << "\n" ;

	mutexLock->Wait();
	std::cout <<"mutexLock Wait" << "\n" ;

	globalCount--;
	if(globalCount == 0) { 
		std::cout <<"All threads completed" << "\n" ;
		barrierA->Wait();
		barrierB->Signal();
	}
	mutexLock->Signal();
	barrierB->Wait();
	barrierB->Signal();
}*/

/*! @fn void creatThreads(int n, std::shared_ptr<Semaphore> mutexLock, std::shared_ptr<Semaphore> barrierA, std::shared_ptr<Semaphore> barrierB)
    @brief This function will be called from main
    @param mutexLock the shared semaphore object
    @param barrier the shared semaphore object
    @param n the number of threads
    
    creates vector of type thread
    forks n thread pushed to vector threads
    joins the vector of threads
*/ 
void createThreads(int n, std::shared_ptr<Barrier> barrier) {

	std::vector<std::thread> threads;

	/*! @brief fork n threads */
	for (int i = 0; i < n; i++) {
		threads.push_back(std::thread(task, barrier));
	}

	/*! @brief loop will parse each thread element inside threads vector */
	for(auto& thread : threads) {
		thread.join();
	}
}

 /*! @fn int main()
    @brief The main function
    
    Creates three shared semaphore objects
    Calls void function
*/

int main(void){
	int nThreads = 5;

	// std::shared_ptr<Semaphore> mutexLock( new Semaphore(1));
	// std::shared_ptr<Semaphore> barrierA( new Semaphore(0));
	// std::shared_ptr<Semaphore> barrierB( new Semaphore(1));

	std::shared_ptr<Barrier> barrier(new Barrier(nThreads));

	/**< Launch the threads  */
	std::cout << "Launched from the main\n";
	createThreads(nThreads, barrier);

	std::cout << "Complete \n";

	return 0;
}
