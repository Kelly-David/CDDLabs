/*! \file semaphore.cpp
    \brief A Documented file.
*/
#include "Semaphore.h"
/*! \class Semaphore
    \brief A Semaphore Implementation

   Uses C++11 features such as mutex and condition variables to implement Semaphore

*/

/*! \fn void wait()
    \brief This function will be called from a thread
    
    This creates a lock, calls wait on m_condition and decrements m_uiCount
*/

void Semaphore::Wait()
{
      std::unique_lock< std::mutex > lock(m_mutex);
      m_condition.wait(lock,[&]()->bool{ return m_uiCount>0; });
      --m_uiCount;
}

/*! \fn void signal()
    \brief This function will be called from a thread
    
    This creates a lock, increments m_uiCount, calls notify() on m_condition
*/
void Semaphore::Signal()
{
      std::unique_lock< std::mutex > lock(m_mutex);
      ++m_uiCount;
      m_condition.notify_one();
}
