# Polygon-Engine
is a little Rendering-Engine writted in c++ for fun and opengl learning

### build & install 
```sh
# Download Polygon-Engine
git clone https://github.com/blackmutzi/polygon-engine.git
cd ./polygon-engine

# Makefile Generation
./autogen.sh

# Build & Install
cd ./build
make && make install

# default lib directory: /usr/lib/libpolygon.so
# default include directory : /usr/include/polygon-engine/
```
### doxygen docu and github.io site
[github.io Polygon-Website with Screenshots](https://blackmutzi.github.io/polygon-engine/index.html)

[doxygen here](https://blackmutzi.github.io/polygon-engine/doxygen/html/index.html)

### lib dependencies

    * polygon-component 
    * LZ4
    * GLFW
    * opengl ( mesa package )
    * libfreetype
    * libfreeimage
    * libboost
