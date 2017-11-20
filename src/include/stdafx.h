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
#ifndef POLYGON_STDAFX_H
#define POLYGON_STDAFX_H

#ifdef __GNUC__
#define DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define DEPRECATED __declspec(deprecated)
#endif

#define GLX_GLXEXT_LEGACY
#define GL_GLEXT_PROTOTYPES 1
#define GLX_GLXEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#define PI 3.1415926535897932384626433832795

//Standard Header
#include <fstream>
#include <iostream>
#include <ios>

#include <exception>
#include <vector>
#include <algorithm>
#include <time.h>
#include <typeinfo>
#include <math.h>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <stdlib.h>
#include <list>
#include <limits.h>
#include <string.h>
#include <sstream>
#include <mutex>

#ifdef  __linux__

#include <sys/time.h>
#include <dirent.h>

//X11
#include<X11/X.h>
#include<X11/Xlib.h>

//OpenGL
#include <GL/gl.h>
#include <GL/glu.h>

//GLX - GLUT
#include <GL/glx.h>
#include <GL/glut.h>

//OpenGL Extensions
#include <GL/glext.h>      // OpenGL v1.2
#include <GL/glxext.h>     // GLX 1.3 API
#include <GL/glcorearb.h>  // ARB Extensions

#elif _WIN32

//#include <tkPlatDecls.h>
#include "windows.h"

#ifndef _DEBUG
#define _DEBUG
#endif


//OpenGL
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GL/glcorearb.h>
#include <GL/wglext.h>

#pragma warning( disable : 4290 )
#pragma warning( disable : 4244 )

#else
//other OS
#endif

//Boost
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/array.hpp>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

//GLFW
#include <GLFW/glfw3.h>

//Freeimage
#include <FreeImage.h>

//FreeType
#include <ft2build.h>
#include FT_FREETYPE_H

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_MESSAGES
#define GLM_FORCE_RADIANS

//LZ4
#include "lz4.h"

//------------------
// Component-Arch (Polygon-Component)
//------------------
#include <polygon-component/arch.h>

//OpenPolygon
//#define MESH_LOADER_DEBUG
//#define ENTITY_MANAGER_DEBUG
//#define OPENGL_DEBUG


using namespace std;

#endif // STDAFX_H

