#!/bin/sh

#./autogen.sh

export CPPFLAGS="-I/c/devel/deps/build/db-4.8.30.NC/build_unix \
-I/c/devel/deps/build/openssl-1.0.1l/include \
-I/c/devel/deps/build \
-I/c/devel/deps/build/protobuf-2.6.1/src \
-I/c/devel/deps/build/libpng-1.6.16 \
-I/c/devel/deps/build/boost_1_57_0 \
-I/c/devel/deps/build/qrencode-3.4.4" 

export LDFLAGS="-L/c/devel/deps/build/db-4.8.30.NC/build_unix \
-L/c/devel/deps/build/openssl-1.0.1l \
-L/c/devel/deps/build/miniupnpc \
-L/c/devel/deps/build/protobuf-2.6.1/src/.libs \
-L/c/devel/deps/build/libpng-1.6.16/.libs \
-L/c/devel/deps/build/boost_1_57_0/stage/lib \
-L/c/devel/deps/build/qrencode-3.4.4/.libs" 

export BOOST_ROOT=/c/devel/deps/build/boost_1_57_0 

#./configure \
#--disable-upnp-default \
#--disable-tests \
#--with-qt-incdir=/c/Qt/5.3.2/include \
#--with-qt-libdir=/c/Qt/5.3.2/lib \
#--with-qt-plugindir=/c/Qt/5.3.2/plugins \
#--with-qt-bindir=/c/Qt/5.3.2/bin \
#--with-protoc-bindir=/c/devel/deps/build/protobuf-2.6.1/src

export PATH=${PATH}:/c/devel/deps/build/qtbase-opensource-src-5.3.2/bin

qmake USE_UPNP=-

make

