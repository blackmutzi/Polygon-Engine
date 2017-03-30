# Polygon-Engine
OpenGL Tests - Linux - Library - Polygon Engine


### build & install 

```sh
# Download Polygon-Engine
git clone https://github.com/blackmutzi/Polygon-Engine/
cd ./Polygon-Engine

# Makefile Generation
./autogen.sh

# Build & Install
cd ./build
make && make install

# default lib directory: /usr/lib/libpolygon.so
# default include directory : /usr/include/polygon-engine/
```
### lib dependencies

* Polygon-Component 

### other library dependencies

* LZ4
* GLFW
* OpenGL (Mesa)
* FreeType
* FreeImage
* Boost
