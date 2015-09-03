#!/bin/bash
set -e
cd $HOME
# ---------------------------- MESA
tar -xvzf mesa-11.0.0-rc1.tar.gz
pushd mesa-11.0.0-rc1
autoreconf -fi
  
CC=clang CXX=clang ./configure \
    CXXFLAGS="-fPIC -O2 -g -DDEFAULT_SOFTWARE_DEPTH_BITS=31" \
    CFLAGS="-fPIC -O2 -g -DDEFAULT_SOFTWARE_DEPTH_BITS=31" \
    LDFLAGS="-lm -lstdc++" \
    --disable-xvmc \
    --disable-glx \
    --disable-dri \
    --enable-opengl \
    --disable-gles1 \
    --disable-gles2 \
    --disable-egl \
    --with-dri-drivers="" \
    --with-gallium-drivers="swrast" \
    --enable-texture-float \
    --enable-shared-glapi \
    --enable-gallium-osmesa \
    --enable-gallium-llvm=yes \
    --prefix=/opt/osmesa_llvmpipe

make -j6
make install
popd
# ---------------------------- GLU
tar -xvzf glu-9.0.0.tar.gz
pushd glu-9.0.0

CC=clang CXX=clang ./configure \
    PKG_CONFIG_PATH=/opt/osmesa_llvmpipe/lib/pkgconfig \
    CXXFLAGS="-fPIC -O2"\
    CFLAGS="-fPIC -O2" \
    LDFLAGS="-lm -lstdc++" \
    --enable-osmesa \
    --prefix=/opt/osmesa_llvmpipe
    
make -j6
make install
popd
