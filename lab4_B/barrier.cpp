/*! @author David Kelly
    @date:  10/10/2017
    @updated: 13/10/2017
*/

/*! \file Barrier.h
    \brief A implemnetation of a resuable barrier
*/
#include "Barrier.h"
/*! \class Barrier
    \brief A Barrier Implementation

   Uses C++11 features such as mutex and condition variables to implement Barrier

*/

/*! \fn void Count_Down_Wait()
    \brief This function will be called from a thread
    
    The calling thread decrements the m_uicount
*/

void Barrier::Wait()
{
      std::unique_lock< std::mutex > lock(m_mutex);
      m_condition.wait(lock,[&]()->bool{ return m_uiCount>0; });
      --m_uiCount;
}

/*! \fn void signal()
    \brief This function will be called from a thread
    
    This creates a lock, increments m_uiCount, calls notify() on m_condition
*/
void Barrier::Signal()
{
      std::unique_lock< std::mutex > lock(m_mutex);
      ++m_uiCount;
      m_condition.notify_one();
}
