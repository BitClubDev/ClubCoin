#!/bin/sh

nice make -j`nproc` -f makefile.unix BDB_LIB_PATH=/usr/local/BerkeleyDB.4.8/lib BDB_INCLUDE_PATH=/usr/local/BerkeleyDB.4.8/include STATIC=yes LDFLAGS=-static-libstdc++
