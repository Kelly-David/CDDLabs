/*! @author David Kelly
    @date:  10/10/2017
    @updated: 13/10/2017
*/

/*! \file Barrier.h
    \brief A implemnetation of a resuable barrier
*/
#include <mutex>
#include <condition_variable>
#include <chrono>
/*! \class Barrier
    \brief A Barruer Implementation

   Uses C++11 features such as mutex and condition variables to implement Barrier

*/w
class Barrier
{
private:
    unsigned int                m_uiCount; /*!< Holds the thread count */
    std::mutex                  m_mutex;
    std::condition_variable     m_condition;

public:
    Barrier(unsigned int uiCount=0) : m_uiCount(uiCount) { };
    void Wait();
    bool Wait(const std::chrono::duration<R,P>& crRelTime);
    void Signal();

};
