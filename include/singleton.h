#ifndef SINGLETON_H
#define SINGLETON_H

#include "index.h"

namespace Engine
{

    /*!
     * \brief The Singleton - template class
     */
    template < class Manager >
    class DEPRECATED Singleton
    {
         private:

            static Manager * ptrInstance;

            Singleton();
            Singleton( const Singleton & ) = default;

        public:

            static Manager * getSingletonPtr(void);
    };


    #include "singleton.temp"
}

#endif // SINGLETON_H
