#!/bin/sh

export PATH="$PWD/dhewm3-libs/x86_64-w64-mingw32:/mingw64/bin:$PATH"
export PKG_CONFIG="pkg-config --static"
export PKG_CONFIG_LIBDIR="$PWD/dhewm3-libs/x86_64-w64-mingw32/lib/pkgconfig"

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

ninja -C build || exit

cd build
  cp -v ../dhewm3-libs/x86_64-w64-mingw32/bin/OpenAL32.dll .
  cp -v ../dhewm3-libs/x86_64-w64-mingw32/bin/SDL2.dll .
  rm *.7z
  apack dhewm3_$1.7z -a *.dll
  apack dhewm3_$1.7z -af *.exe  || exit
  gh release create -t "$1" -n "$1" $1 dhewm3_$1.7z
cd ..
