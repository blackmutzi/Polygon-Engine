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
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "index.h"

namespace Engine
{


/*!
 * MouseEvent - Store Mouse Data
 * \brief The MouseEvent - Event class
 */
class MouseEvent
{
    public:
        MouseEvent(void);
        ~MouseEvent(void){}

        int  getButton(void) const;

        bool isMousePressed(void) const;
        bool isMouseReleased(void) const;
        bool isShiftDown(void) const;
        bool isControlDown(void) const;
        bool isAltDown(void) const;
        bool isSuperDown(void) const;

        int getAction(void) const;
        int getMod(void) const;

        void setAction(int action);
        void setMod(int mod);
        void setButton(int button);
        void setPosition(const Vector2f &vector);

   private:
        int mButton, mMod, mAction; /*!< TODO */
        Vector2f mPosition;         /*!< TODO */
};


/*!
 * Keyboard Event - Store Keyboard Data
 * \brief The KeyEvent - Event class
 */
class KeyEvent
{
    public:
        KeyEvent(void);
        ~KeyEvent(void){}

        void setMod(int mod);
        void setAction(int action);
        DEPRECATED void setKey(int key);
        void setKeys( std::list< int > list );
        void setKeyCode(int keycode);

        DEPRECATED int getKeyValue(void) const;
        std::list< int > getKeys(void) const;


        int getKeyScanCode(void) const;
        bool isKeyPressed( int key) const;
        bool isKeyReleased( int key) const;
        bool isShiftDown(void) const;
        bool isControlDown(void) const;
        bool isAltDown(void) const;
        bool isSuperDown(void) const;

    private:
        int mMod , mAction , mKey , mKeyCode;  /*!< TODO */
        std::list< int > m_keys;

};

/*!
 * \brief The InputListener - Interface class
 */
class InputListener
{
    public:
        virtual ~InputListener(){}

    /*!
     * Catch a Keyboard Event
     * \brief onKeyEvent
     * \param event
     */
    virtual void onKeyEvent(const KeyEvent & event)=0;

    /*!
     * Catch a Mouse Event
     * \brief onMouseEvent
     * \param event
     */
    virtual void onMouseEvent(const MouseEvent & event)=0;
};


/* List of InputListener */
using IListenerList = std::list< InputListener * >;

/*!
 * Management of Input Devices
 *
 * - create Keyboard Event
 * - create Mouse Event
 *
 * \brief The InputManager controlled InputListener
 */
class InputManager
{

    private:

        static InputManager * ptrInstance; /*!< InputManager Instance*/
        InputManager( void );
        InputManager( const InputManager &){}
        void operator=(const InputManager &){}

        ~InputManager(void){}

    public:

        /*!
         * Return InputManager Instance
         * \brief getSingletonPtr
         * \return
         */
        static InputManager * getSingletonPtr(void);
        void PollEvents( GLFWwindow * window );


        /*!
         * Add Input Listener
         * \brief addInputListener
         * \param listener
         */
        void addInputListener( InputListener * listener);

        /*!
         * Remove Input Listener
         * \brief removeListener
         * \param listener
         */
        void removeListener(  InputListener * listener);

        /*!
         * Capture Mouse and Save x,y data
         * \brief capture
         * \param mouseX
         * \param mouseY
         */
        void capture( int mouseX , int mouseY);

        /*!
         * Create a Keyboard Event
         * \brief createKeyBoardEvent
         * \param key
         * \param scancode
         * \param action
         * \param mods
         */
        void createKeyBoardEvent( int key , int scancode , int action , int mods);
        void createKeyListEvent( std::list< int > keys );

        /*!
         * Create a Mouse Event
         * \brief createMouseEvent
         * \param button
         * \param action
         * \param mods
         */
        void createMouseEvent( int button , int action , int mods);

        /*!
         * Return Mouse Position
         * \brief getMousePosition
         * \return
         */
        Vector2f & getMousePosition(void);

        /*!
         * Return all Listener
         * \brief getListener
         * \return
         */
        IListenerList & getListener();

   private:
        Vector2f mMousePosition;   /*!< Mouse Positions */
        IListenerList mList;       /*!< List of Input Listener */

        //Last Values (MouseEvent)
        int mLastButton;
        int mLastAction;
        int mLastMods;

        timeval mStartTimer;       /*!< TODO */
        double timeSinceLastFrame; /*!< TODO */
        bool mTriggerFlag;         /*!< TODO */
};

}
#endif // INPUTMANAGER_H
