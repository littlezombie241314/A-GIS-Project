#pragma once

#include "CELLPlatform.hpp"


#if CELL_PLATFORM == CELL_PLATFORM_WIN32


namespace   CELL
{
    class   CELLMutex
    {
    protected:
        //! »¥³âÌå
        CRITICAL_SECTION    _cs;
    public:
        class   ScopeLock
        {
        public:
            ScopeLock(CELLMutex& mutex)
                :_mutex(mutex)
            {
                _mutex.lock();
            }
            ~ScopeLock()
            {
                _mutex.unLock();
            }
        protected:
            CELLMutex&  _mutex;
        private:
            ScopeLock(const ScopeLock&);
            void operator = (const ScopeLock&);
        };
    public:
        CELLMutex()
        {
            ::InitializeCriticalSection(&_cs);
        }
        ~CELLMutex()
        {
            ::DeleteCriticalSection(&_cs);
        }
        void    lock()
        {
            ::EnterCriticalSection(&_cs);
        }
        void    unLock()
        {
            ::LeaveCriticalSection(&_cs);
        }
        bool    tryLock()
        {
            return  TryEnterCriticalSection(&_cs) == TRUE;
        }
    };

}

#elif CELL_PLATFORM == CELL_PLATFORM_LINUX

#include "CELLObject.hpp"

namespace CELL
{
    class CELLMutex :public CELLObject
    {
    protected:
        pthread_mutex_t _mutex;
    public:
        class ScopeLock
        {
        protected:
            CELLMutex&  _mutex;
        public:
            ScopeLock(CELLMutex& mutex)
                :_mutex(mutex)
            {
                _mutex.lock();
            }
            ~ScopeLock()
            {
                _mutex.unLock();
            }
        private:
            ScopeLock(const ScopeLock&);
            void operator = (const ScopeLock&);
        };
    public:
        CELLMutex()
        {
            pthread_mutexattr_t attr;
            pthread_mutexattr_init(&attr);

            if (pthread_mutex_init(&_mutex, &attr))
            {
                pthread_mutexattr_destroy(&attr);
            }
            pthread_mutexattr_destroy(&attr);
        }
        virtual ~CELLMutex()
        {
            pthread_mutex_destroy(&_mutex);
        }
        void    lock()
        {
            int rc  =   pthread_mutex_lock(&_mutex);
            assert(rc == 0);
        }

        void    unLock()
        {
            int rc  =   pthread_mutex_unlock(&_mutex);
            assert(rc == 0);
        }

        bool    tryLock()
        {
            struct timespec abstime;
            struct timeval  tv;
            gettimeofday(&tv, NULL);
            abstime.tv_sec  =   tv.tv_sec;
            abstime.tv_nsec =   tv.tv_usec * 1000 + 10000;//( 10 micro second )
            if (abstime.tv_nsec >= 1000000000)
            {
                abstime.tv_nsec -= 1000000000;
                abstime.tv_sec++;
            }
            int rc = pthread_mutex_timedlock(&_mutex, &abstime);
            if (rc == 0)
            {
                return true;
            }
            else if (rc == ETIMEDOUT)
            {
                return false;
            }
            else
            {
                assert(rc == 0);
                return  false;
            }
        }

    };
}

#endif
