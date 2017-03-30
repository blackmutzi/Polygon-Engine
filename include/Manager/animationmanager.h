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
#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include "index.h"
#include "animation.h"
#include "mesh.h"
#include "nodeanimscene.h"

namespace Engine
{
    /* FLIP Position Coord: Y-Achse to Z-Achse & Z-Achse to Y-Achse  */
    static const int POS_FLIP_YZ   = 0x1;

    /* FLIP Rotation Coord: Y-Achse to Z-Achse & Z-Achse to Y-Achse  */
    static const int ROT_FLIP_YZ   = 0x2;

    /* Make absolute Coordinates  */
    static const int ABS_POSITIONS = 0x4;

   /*!
    * \brief The AnimationLoader is a interface class for custom Loader specifically for Animations
    */
    class AnimationLoader
    {
     public:

          friend class AnimationManager;

          AnimationLoader( const std::string & extension );
          virtual ~AnimationLoader(){}

          /*!
           * Read MotionFile and Save data into anim_scene
           * \brief ReadFile
           * \param motion_file
           * \param node_anim_scene
           */
          virtual void ReadFile( const std::string & motion_file , NodeAnimScene * node_anim_scene )=0;

     protected:

          unsigned int mFlags;     /*!< actually Loader flags */
          std::string  mExtension; /*!< actually Loader extension */
    };


    /*!
     * \brief The AnimationManager controlled Animations
     */
    class AnimationManager : public Arch::ITempDatabase<Animation>
    {
        public:

        /* Map of Animations with Component IDs */
        using AnimationMap   = std::map< uint , Animation * >;

        /* List of Animation Loaders */
        using AnimLoaderList = std::list< AnimationLoader * >;

        public:
            AnimationManager();
            ~AnimationManager() = default;

            void prepareVBO( Animation * anim , Mesh * mesh );

            void AddTransformations( Animation * anim , Mesh * mesh );

            /*!
             * Create a New Animation with
             *  Animation Name & Animation Motion file
             *
             * \brief createAnimation
             * \param animation_name
             * \param motion_file : (./resource/animation.bvh)
             * \return
             */
            Animation * createAnimation( const std::string & animation_name ,
                                         const std::string & motion_file ,
                                         Mesh * mesh ) throw( std::runtime_error );


            void CreateBones( Animation * animation , const std::string & motion_file );


            /*!
             * Return Animation by Component ID
             * \brief getAnimation
             * \param component_id
             * \return
             */
            Animation * getAnimation( uint component_id );

            /*!
             * Destroy Animation
             * \brief remove
             * \param component_id
             */
            void destroy( uint component_id );


            /* Animation Importer Include */

            /*!
             * Read Animation File
             * \brief ReadFile
             * \param motion_file
             * \param flags
             * \return NodeAnimScene
             */
            const NodeAnimScene * ReadFile( const std::string & motion_file , unsigned int flags );

            /*!
             * Is Extension Supported then return true otherwise is false
             * \brief IsExtensionSupported
             * \param extension : ".bvh"
             * \return
             */
            bool IsExtensionSupported( const std::string & extension );

            /*!
             * Register new AnimationLoader
             * \brief registerLoader
             * \param loader
             */
            void registerLoader( AnimationLoader * loader );

        protected:

            /*!
             * Add new Extension
             * \brief addExtensionSupport
             * \param extension
             */
             void addExtensionSupport( const std::string & extension );

            /*!
             * Create a Bone Index for the Animation Shader
             * \brief createBoneIndex
             * \param anim
             * \param mesh
             */
            void prepareAnimation( Animation * anim , Mesh * mesh );

        private:

           AnimationMap mAnimationMap;       /*!< Save Animations */

           /* Importer */
           Strings mExtensions;              /*!< Save Supported extensions*/
           AnimLoaderList mAnimationLoaders; /*!< Save AnimationLoaders */
           NodeAnimScene mNodeScene;         /*!< Save File Data */
    };


}
#endif // ANIMATIONMANAGER_H
