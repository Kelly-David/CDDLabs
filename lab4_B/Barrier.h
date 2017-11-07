/*! @author David Kelly
    @date:  10/10/2017
    @updated: 23/10/2017
*/

/*! \file Barrier.h
    \brief A implemnetation of a resuable barrier class
*/
#include <mutex>
#include "Semaphore.h"

/*! \class Barrier
    \brief A Reusable Barrier Implementation

   Uses C++11 features such as mutex and condition variables to implement a reusable barrier

*/
class Barrier
{
public:
    int m_threads; /*!< Holds the number of threads */
    int m_count; /*!< Running count */
    std::shared_ptr<Semaphore> mutexLock; /*!< Mutex Lock */
    std::shared_ptr<Semaphore> turnstileA; /*!< First turnstile - rendevous point */
    std::shared_ptr<Semaphore> turnstileB; /*!< Second turnstile - final barrier */ 


    Barrier(int threads);
    void Phase1();
    void Phase2();
    void Wait();
};
