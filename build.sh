#!/bin/sh

DATE=$(date +"%Y-%m-%d")

export CC="x86_64-w64-mingw32-clang"
export CXX="x86_64-w64-mingw32-clang++"
export PATH="/mingw64/bin:$PATH"
export PATH="$PWD/dhewm3-libs/x86_64-w64-mingw32:/mingw64/bin:$PATH"
export PKG_CONFIG="pkg-config --static"
export PKG_CONFIG_LIBDIR="$PWD/dhewm3-libs/x86_64-w64-mingw32/lib/pkgconfig"

git clone --depth 1 https://github.com/dhewm/dhewm3-libs.git

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
  apack dhewm3_${DATE}.7z -a *.dll
  apack dhewm3_${DATE}.7z -af *.exe  || exit
  gh release create -t "${DATE}" -n "${DATE}" ${DATE} dhewm3_${DATE}.7z
cd ..

rm -rf dhewm3-libs
