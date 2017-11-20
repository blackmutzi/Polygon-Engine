/*
   Copyright (C) 2014 - 2016 Mutzii

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#include "threadmanager.h"

using namespace Engine;

ThreadManager * ThreadManager::ptrInstance = nullptr;

ThreadManager::ThreadManager(){}

ThreadManager * ThreadManager::getSingletonPtr(void)
{
    if( ptrInstance != nullptr)
    {
        ptrInstance = new ThreadManager();
    }

    return ptrInstance;
}

boost::thread ThreadManager::createWorkerFunc(THREAD_FUNC func_pointer)
{
    boost::thread workerThread( func_pointer );
    return workerThread;
}


boost::thread ThreadManager::createFunctorWorker(FunctorWorker worker)
{
    boost::thread workerThread( worker );
    return workerThread;
}

void ThreadManager::_register(Thread * thread )
{
    mThreadList.push_back( thread );
}

void ThreadManager::_unregister( Thread * thread )
{
    mThreadList.remove( thread );
}

bool ThreadManager::hasThread(Thread *thread)
{
    for( Thread * current : mThreadList )
    {
        if( current == thread )
               return true;
    }

    return false;
}

//+++++++++++++++++++++++++++ Functor Worker CLASS +++++++++++++++++++++++++

FunctorWorker::FunctorWorker(){}

void FunctorWorker::operator()(){}

//+++++++++++++++++++++++++++ THREAD CLASS +++++++++++++++++++++++++++++++++

Thread::Thread()
    : mBoostThread( NULL )
{
  //empty
}

void Thread::start()
{
    mBoostThread = new boost::thread
                   (
                       boost::bind
                       (
                            &Thread::_process,
                            boost::ref(*this)
                       )
                   );
}

void Thread::_process( void )
{
    process();
}

void Thread::join()
{
    mBoostThread->join();
}

void Thread::removeThreadPtr(void)
{
    if( mBoostThread != nullptr )
         delete mBoostThread;
}
