#!/bin/sh

# install and configure bdb 4.8 manually, from http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz

qmake "BDB_LIB_PATH=/usr/local/BerkeleyDB.4.8/lib" "BDB_INCLUDE_PATH=/usr/local/BerkeleyDB.4.8/include" "QMAKE_LFLAGS+=-static-libstdc++"
nice make -j`nproc` 

