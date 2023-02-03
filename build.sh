#!/bin/sh

rm -rf -- dhewm3-libs
git clone --depth 1 https://github.com/dhewm/dhewm3-libs.git

export PATH="/mingw64/bin:$PATH"
export PKG_CONFIG="pkg-config --static"
export PKG_CONFIG_LIBDIR="/mingw64/mingw/lib/pkgconfig"

cmake -Hneo -Bbuild -G Ninja \
    -DASAN=OFF \
    -DBASE=ON \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_TOOLCHAIN_FILE="$PWD"/toolchain.cmake \
    -DCORE=ON \
    -DD3XP=ON \
    -DDEDICATED=ON \
    -DDHEWM3LIBS="$PWD"/dhewm3-libs/x86_64-w64-mingw32 \
    -DFORCE_COLORED_OUTPUT=ON \
    -DHARDLINK_GAME=OFF \
    -DLINUX_RELEASE_BINS=OFF \
    -DONATIVE=OFF \
    -DREPRODUCIBLE_BUILD=OFF \
    -DSDL2=ON \
    -DUBSAN=OFF

ninja -C build
