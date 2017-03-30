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
#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include "index.h"

namespace Engine
{
    typedef void (*THREAD_FUNC)();

    class CustomThreadClass
    {
        public:
            CustomThreadClass(){}
            virtual ~CustomThreadClass(){}
    };

    /*!
     * FunctorWorker a Basis Class
     * \brief The FunctorWorker class
     */
    class FunctorWorker
    {
        public:

            FunctorWorker();
            ~FunctorWorker(){}

            //override me ..
            virtual void operator()();
    };

    /*!
     * Thread a Basis Class
     * \brief The Thread class
     */
    class Thread
    {
         public:

            Thread();
            virtual ~ Thread(){}

            /*!
             * Start Thread
             * \brief start
             */
            void start();

            /*!
             * Wait until this Process Thread is finish then
             * return to main process (Sync)
             * \brief join
             */
            void join();

            /*!
             * Thread Process
             * \brief process
             */
            virtual void process(void)=0;

            /*!
             * Remove the pointer from Memory only
             * - dont destroy the thread process
             * \brief removeThreadPtr
             */
            void removeThreadPtr(void);

         private:

            void _process(void);

            boost::thread * mBoostThread;
    };

    using ThreadList = std::list< Thread *>;

    class ThreadManager
    {
        private:
            ThreadManager();
            void operator=( ThreadManager & ){}

            static ThreadManager * ptrInstance;

        public:

            static ThreadManager * getSingletonPtr(void);

            boost::thread createWorkerFunc( THREAD_FUNC func_pointer );
            boost::thread createFunctorWorker( FunctorWorker worker );

            void _register  ( Thread *  thread );
            void _unregister( Thread *  thread );
            bool hasThread  ( Thread *  thread );

       private:

            ThreadList mThreadList;

    };

//Examples - ein kleiner Trick um den Inhalt von dem Thread Process immer zu ändern
//    void GameLoop()
//    {
//         //Create a Local Worker Thread
//         struct Worker : public Thread
//         {
//              virtual void process()
//              {
//                  // Make anything....
//              }
//         };

//         Worker worker;
//         worker->start();
//    }

}

#endif // THREADMANAGER_H
