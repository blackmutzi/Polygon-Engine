#!/bin/sh

#################################################
#  Auto Project Generation ./autogen.sh         #
#                by Mutzi                       #
#################################################

# Do not change this.
RPATH="-rpath '$"
RPATH+="(libdir)'"
# -------------------

clean_lists()
{
   [ -f source.list ] && rm -rf source.list
   [ -f headers.list ] && rm -rf headers.list  
}

add_source_directory()
{

data=$(find $1 -type f)

for entry in ${data}
do
echo ${entry} >> source.list
done 

}

add_header_directory()
{

data=$(cd $1 && find . -type f)
		
for entry in ${data}
do
echo ${entry} >> headers.list
done 

}

touch AUTHORS NEWS README ChangeLog

#project configuration
project_name="Polygon-Engine"
project_version=1.0.0
project_header_installdir="polygon-engine"

INCLUDE_LIBS="-llz4 -lglfw -lGL -lglut -lGLU -lXxf86vm -lXext -lX11 -lfreetype -lfreeimage -lboost_system -lboost_thread-mt "
INCLUDE_LIBS+="-lpolycomponent"

INCLUDE_PATH="  -I ../include/"
INCLUDE_PATH+=" -I ../include/Editor/Addons/"
INCLUDE_PATH+=" -I ../include/Editor/"
INCLUDE_PATH+=" -I ../include/Container/"
INCLUDE_PATH+=" -I ../include/Component/"
INCLUDE_PATH+=" -I ../include/Manager/"
INCLUDE_PATH+=" -I ../include/Material/"
INCLUDE_PATH+=" -I ../include/FileLoader/"
INCLUDE_PATH+=" -I ../include/GPU/"
INCLUDE_PATH+=" -I ../include/Render/"
INCLUDE_PATH+=" -I ../include/Interface/"
INCLUDE_PATH+=" -I ../include/Render/Modul/"

# Extern Headers from Libs 
INCLUDE_PATH+=" -I /usr/include/OIS/"
INCLUDE_PATH+=" -I /usr/include/freetype2/"
INCLUDE_PATH+=" -I /usr/include/polygon-component/"


# --prefix=/usr/
prefix="/usr"

#compiler Options
CFLAGS="-pipe -g -Wall -W -fPIC"
CXXFLAGS="-std=c++11 -Wdeprecated-declarations"
LDFLAGS=" -shared -export-dynamic"

#project source list 
clean_lists

add_source_directory ./Component/
add_source_directory ./Container/
add_source_directory ./Engine/
add_source_directory ./Objects/

SOURCE_LIST=$(cat source.list)

LIB_NAME="libpolygon"
LIB_EXT_A="a"
LIB_EXT_SO="so"
LIB_EXT_LA="la"

LIB_DEST_A=$LIB_NAME"."$LIB_EXT_A
LIB_DEST_SO=$LIB_NAME"."$LIB_EXT_SO
LIB_DEST_LA=$LIB_NAME"."$LIB_EXT_LA

MSG_ERROR_LIB_POLYGON_COMPONENT="Couldn´t find -lpolycomponent.so"
MSG_ERROR_POLYGON_COMPONENT="Couldn´t find polygon-component/arch.h"
MSG_ERROR_LZ4="Couldn´t find lz4.h"
MSG_ERROR_GLM="Couldn´t find GLM"

#if configure.ac found then remove 
[ -f configure.ac ] && rm -rf configure.ac

#create configure.ac
# ----------------------------------------------------------------------
echo "create configure.ac"
echo "AC_PREREQ([2.69])" >> configure.ac

echo "AC_INIT([$LIB_NAME],[$project_version])" >> configure.ac
echo "AC_CONFIG_AUX_DIR([./aux])" >> configure.ac
echo "AC_CONFIG_HEADERS([config.h])" >> configure.ac
echo "AC_CONFIG_MACRO_DIRS([m4])" >> configure.ac
echo "AM_INIT_AUTOMAKE([subdir-objects])" >> configure.ac 
echo "LT_INIT([disable-static])" >> configure.ac

echo "# Checks for programs." >> configure.ac
echo "AC_PROG_CXX" >> configure.ac
echo "AC_PROG_CC" >> configure.ac

echo "# Checks for libraries." >> configure.ac

echo "AC_LANG_CPLUSPLUS" >> configure.ac
echo "AC_CHECK_LIB([polycomponent],[_ZN4Arch15DatabaseManager15getSingletonPtrEv],[],[ echo $MSG_ERROR_LIB_POLYGON_COMPONENT ; exit -1 ])" >> configure.ac

# Checks for header files 
echo "# Checks for header files." >> configure.ac
echo "AC_PATH_X" >> configure.ac
echo "AC_CHECK_HEADERS([limits.h stdlib.h string.h sys/time.h])" >> configure.ac
echo "AC_CHECK_HEADERS([X11/X.h X11/Xlib.h])" >> configure.ac
echo "AC_CHECK_HEADERS([GL/glx.h GL/glut.h])" >> configure.ac
#echo "AC_CHECK_HEADERS([boost/uuid/uuid.hpp])" >> configure.ac
echo "AC_CHECK_HEADERS([GLFW/glfw3.h])" >> configure.ac
echo "AC_CHECK_HEADERS([FreeImage.h])" >> configure.ac
#echo "AC_CHECK_HEADERS([glm/glm.hpp],[],[AC_MSG_ERROR([ $MSG_ERROR_GLM ])])" >> configure.ac
echo "AC_CHECK_HEADERS([lz4.h],[],[AC_MSG_ERROR([ $MSG_ERROR_LZ4 ])] )" >> configure.ac
#echo "AC_CHECK_HEADERS([polygon-component/arch.h],[],[AC_MSG_ERROR([ $MSG_ERROR_POLYGON_COMPONENT ])] )" >> configure.ac

# Checks for typedefs, structures, and compiler characteristics
echo "# Checks for typedefs, structures, and compiler characteristics." >> configure.ac
echo "AC_CHECK_HEADER_STDBOOL" >> configure.ac

echo "AC_ENABLE_SHARED" >> configure.ac 
echo "AC_DISABLE_STATIC" >> configure.ac
echo "AC_PROG_LIBTOOL(libtool)" >> configure.ac

# create Makefiles
echo "AM_EXTRA_RECURSIVE_TARGETS([install])" >> configure.ac
echo "AC_CONFIG_FILES([Makefile include/Makefile])" >> configure.ac
echo "AC_OUTPUT" >> configure.ac 

# create local Makefile.am 
# ----------------------------------------------------------------------
LOCAL_MAKEFILE="Makefile.am"
HEADERS_LOCAL="./singleton.temp"

#if Makefile.am found then remove 
[ -f $LOCAL_MAKEFILE ] && rm -rf $LOCAL_MAKEFILE 

echo "ACLOCAL_AMFLAGS= -I m4" >> $LOCAL_MAKEFILE
echo "SUBDIRS= include " >> $LOCAL_MAKEFILE
echo "CFLAGS="$CFLAGS >> $LOCAL_MAKEFILE
echo "CXXFLAGS="$CXXFLAGS >> $LOCAL_MAKEFILE
echo "LDFLAGS="$RPATH" "$LDFLAGS >> $LOCAL_MAKEFILE
echo "CPPFLAGS="$INCLUDE_PATH >> $LOCAL_MAKEFILE
echo "LIBS="$INCLUDE_LIBS >> $LOCAL_MAKEFILE
echo "TARGET_LIB="$LIB_NAME"."$LIB_EXT_SO >> $LOCAL_MAKEFILE
echo "includedir = ${prefix}/include/"$project_header_installdir >> $LOCAL_MAKEFILE
echo "nobase_include_HEADERS="$HEADERS_LOCAL >> $LOCAL_MAKEFILE

echo "lib_LTLIBRARIES="$LIB_DEST_LA >> $LOCAL_MAKEFILE
echo $LIB_NAME"_"$LIB_EXT_LA"_SOURCES="$SOURCE_LIST >> $LOCAL_MAKEFILE
echo $LIB_NAME"_"$LIB_EXT_LA"_LDFLAGS= -version-info 1:0:0 " >> $LOCAL_MAKEFILE

# create headers Makefile.am
# ---------------------------------------------------------------------
HEADER_MAKEFILE="./include/Makefile.am"

#if Makefile.am found then remove 
[ -f $HEADER_MAKEFILE ] && rm -rf $HEADER_MAKEFILE 

add_header_directory ./include/
HEADERS_LIST=$(cat headers.list)

echo "includedir = ${prefix}/include/"$project_header_installdir >> $HEADER_MAKEFILE
echo "nobase_include_HEADERS="$HEADERS_LIST >> $HEADER_MAKEFILE

#----------------------------------------------------------------------

libtoolize --force
aclocal
autoheader
automake --add-missing --copy --force-missing
autoconf

[ ! -d ./build ] && mkdir ./build 
cd build 
../configure --enable-shared --prefix=$prefix











