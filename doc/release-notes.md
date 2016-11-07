1.3.0 Change Log
========================

Bug Fixes
------------------------

* Restore hex to getrawtransaction vout scriptPubkey. 

1.2.0 Change Log
========================

Dependencies & Software
------------------------

* Miniupnpc 2.0.
* Latest config.guess & config.sub.
* Univalue brought in from upstream.
* Secp256k1 brougt in from upstream.

LevelDB
------------------------

* The build system is now integrated with leveldb.
* LevelDB update to 1.18.

C++11
------------------------

Various changes have been made to bring the codebase up to C++11.
This means that you will need a compiler with C++11 support, namely
GCC 4.7 or higher, or Clang 3.3 or higher.

When cross-compiling for a target that doesn't have C++11 libraries, configure with
`./configure --enable-glibc-back-compat ... LDFLAGS=-static-libstdc++`.

Build System
------------------------

A lot has been modified in this release.
* Alternate fallback downloads.
* Fixed checksum checks.
* Host and build id for salting.
* Check for QRencode.
* Enable hardening.
* Various Makefile fixes.
* Removed old Qt Makefiles.
* Some m4 scripts updates.

Code Sync Effort
------------------------

* Random: section off to random.cpp, bring in support code for random. 
* Add main-specific node state 
* Base58 is closer to upstream.
* Add: support/pagelocker.
* Add: allocators/{secure.h,zeroafterfree.h} 
* Add: compat/sanity, init calls glib sanity check 
* CMedianFilter: Move to timedata.

GUI
------------------------

* Qt: Rework signals & slots, makefile.
* Qt: Add windows shutdown monitor. 

