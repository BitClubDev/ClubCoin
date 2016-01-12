DIST_SUBDIRS = 

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS) -DENABLE_WALLET

if EMBEDDED_LEVELDB
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/include
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/helpers/memenv
LIBLEVELDB += $(builddir)/leveldb/libleveldb.a
LIBMEMENV  += $(builddir)/leveldb/libmemenv.a

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
$(LIBLEVELDB): $(LIBMEMENV)

$(LIBLEVELDB) $(LIBMEMENV):
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
          OPT="$(AM_CXXFLAGS) $(PIE_FLAGS) $(CXXFLAGS) $(AM_CPPFLAGS) $(CPPFLAGS) -D__STDC_LIMIT_MACROS"
endif

CLUBCOIN_CONFIG_INCLUDES=-I$(builddir)/config
CLUBCOIN_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

LIBCLUBCOIN_SERVER=libclubcoin_server.a
LIBCLUBCOIN_WALLET=libclubcoin_wallet.a
LIBCLUBCOIN_COMMON=libclubcoin_common.a
LIBCLUBCOIN_CLI=libclubcoin_cli.a
LIBCLUBCOIN_UTIL=libclubcoin_util.a
LIBCLUBCOIN_CRYPTO=crypto/libclubcoin_crypto.a
LIBCLUBCOINQT=qt/libclubcoinqt.a

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES = \
  crypto/libclubcoin_crypto.a \
  libclubcoin_util.a \
  libclubcoin_common.a \
  libclubcoin_server.a \
  libclubcoin_cli.a
if ENABLE_WALLET
CLUBCOIN_INCLUDES += $(BDB_CPPFLAGS)
#EXTRA_LIBRARIES += libclubcoin_wallet.a
endif
if ENABLE_ZMQ
EXTRA_LIBRARIES += libclubcoin_zmq.a
endif

if BUILD_CLUBCOIN_LIBS
lib_LTLIBRARIES = libclubcoinconsensus.la
LIBCLUBCOIN_CONSENSUS=libclubcoinconsensus.la
else
LIBCLUBCOIN_CONSENSUS=
endif

bin_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_CLUBCOIND
  bin_PROGRAMS += clubcoind
endif

if BUILD_CLUBCOIN_UTILS
#  bin_PROGRAMS += clubcoin-cli clubcoin-tx
#   these don't exist yet
endif

.PHONY: FORCE
# clubcoin core #
CLUBCOIN_CORE_H = \
  addrman.h \
  alert.h \
  amount.h \
  arith_uint256.h \
  base58.h \
  bloom.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/merkle.h \
  consensus/params.h \
  consensus/validation.h \
  core_io.h \
  core_memusage.h \
  hash.h \
  httprpc.h \
  httpserver.h \
  init.h \
  key.h \
  keystore.h \
  dbwrapper.h \
  limitedmap.h \
  main.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  netbase.h \
  noui.h \
  policy/fees.h \
  policy/policy.h \
  pow.h \
  prevector.h \
  primitives/block.h \
  primitives/transaction.h \
  protocol.h \
  pubkey.h \
  random.h \
  reverselock.h \
  rpcclient.h \
  rpcprotocol.h \
  rpcserver.h \
  scheduler.h \
  script/interpreter.h \
  script/script.h \
  script/script_error.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  serialize.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/pagelocker.h \
  sync.h \
  threadsafety.h \
  timedata.h \
  tinyformat.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utilstrencodings.h \
  utiltime.h \
  validationinterface.h \
  version.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/wallet.h \
  wallet/wallet_ismine.h \
  wallet/walletdb.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libclubcoin_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between clubcoind and clubcoin-qt
# For now we REQUIRE the wallet sources for building. XXX
libclubcoin_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(CLUBCOIN_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libclubcoin_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) -I$(srcdir)/leveldb/helpers/
libclubcoin_server_a_SOURCES = \
  addrman.cpp \
  alert.cpp \
  checkpoints.cpp \
  crypter.cpp \
  db.cpp \
  init.cpp \
  kernel.cpp \
  main.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  pbkdf2.cpp \
  rpcblockchain.cpp \
  rpcclient.cpp \
  rpcdump.cpp \
  rpcmining.cpp \
  rpcmisc.cpp \
  rpcnet.cpp \
  rpcrawtransaction.cpp \
  rpcserver.cpp \
  rpcwallet.cpp \
  scrypt.cpp \
  timedata.cpp \
  txdb-leveldb.cpp \
  txmempool.cpp \
  wallet.cpp \
  walletdb.cpp \
  $(CLUBCOIN_CORE_H)


# wallet: shared between clubcoind and clubcoin-qt, but only linked
# when wallet enabled
# Including the leveldb helpers directly is definitely hacky, but it works for now.
libclubcoin_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(CLUBCOIN_INCLUDES)
libclubcoin_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS) -I$(srcdir)/leveldb/helpers/
libclubcoin_wallet_a_SOURCES = \
  crypter.cpp \
  db.cpp \
  rpcdump.cpp \
  walletdb.cpp \
  txdb-leveldb.cpp \
  rpcwallet.cpp \
  wallet.cpp \
  scrypt.cpp \
  $(CLUBCOIN_CORE_H)

# crypto primitives library
crypto_libclubcoin_crypto_a_CPPFLAGS = $(AM_CPPFLAGS) $(CLUBCOIN_CONFIG_INCLUDES)
crypto_libclubcoin_crypto_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libclubcoin_crypto_a_SOURCES = 

# common: shared between clubcoind, and clubcoin-qt and non-server tools
libclubcoin_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(CLUBCOIN_INCLUDES)
libclubcoin_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libclubcoin_common_a_SOURCES = \
  chainparams.cpp \
  core.cpp \
  hash.cpp \
  key.cpp \
  keystore.cpp \
  netbase.cpp \
  protocol.cpp \
  script.cpp \
  $(CLUBCOIN_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libclubcoin_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(CLUBCOIN_INCLUDES)
libclubcoin_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libclubcoin_util_a_SOURCES = \
  version.cpp \
  rpcprotocol.cpp \
  sync.cpp \
  util.cpp \
  $(CLUBCOIN_CORE_H)

if GLIBC_BACK_COMPAT
libclubcoin_util_a_SOURCES += compat/glibc_compat.cpp
endif

# cli: shared between clubcoin-cli and clubcoin-qt
libclubcoin_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(CLUBCOIN_INCLUDES)
libclubcoin_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libclubcoin_cli_a_SOURCES = \
  rpcclient.cpp \
  $(CLUBCOIN_CORE_H)

nodist_libclubcoin_util_a_SOURCES = $(srcdir)/obj/build.h
#

# clubcoind binary #
clubcoind_SOURCES = bitcoind.cpp
clubcoind_CPPFLAGS = $(AM_CPPFLAGS) $(CLUBCOIN_INCLUDES)
clubcoind_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
clubcoind_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
#clubcoind_SOURCES += clubcoind-res.rc
endif

clubcoind_LDADD = \
  $(LIBCLUBCOIN_SERVER) \
  $(LIBCLUBCOIN_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBCLUBCOIN_UTIL) \
  $(LIBCLUBCOIN_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

if ENABLE_ZMQ
clubcoind_LDADD += $(LIBCLUBCOIN_ZMQ) $(ZMQ_LIBS)
endif

if ENABLE_WALLET
#clubcoind_LDADD += libclubcoin_wallet.a
endif

clubcoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS)

# clubcoin-cli binary #
clubcoin_cli_SOURCES = clubcoin-cli.cpp
clubcoin_cli_CPPFLAGS = $(AM_CPPFLAGS) $(CLUBCOIN_INCLUDES) $(EVENT_CFLAGS)
clubcoin_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
clubcoin_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
clubcoin_cli_SOURCES += clubcoin-cli-res.rc
endif

clubcoin_cli_LDADD = \
  $(LIBCLUBCOIN_CLI) \
  $(LIBUNIVALUE) \
  $(LIBCLUBCOIN_UTIL)

clubcoin_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)
#

# clubcoin-tx binary #
clubcoin_tx_SOURCES = clubcoin-tx.cpp
clubcoin_tx_CPPFLAGS = $(AM_CPPFLAGS) $(CLUBCOIN_INCLUDES)
clubcoin_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
clubcoin_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
clubcoin_tx_SOURCES += clubcoin-tx-res.rc
endif

clubcoin_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBCLUBCOIN_COMMON) \
  $(LIBCLUBCOIN_UTIL) \
  $(LIBCLUBCOIN_CRYPTO) \
  $(LIBSECP256K1)

clubcoin_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# clubcoinconsensus library #
if BUILD_CLUBCOIN_LIBS
include_HEADERS = script/clubcoinconsensus.h
libclubcoinconsensus_la_SOURCES = \
  hash.cpp \
  script.cpp \
  scrypt.cpp

if GLIBC_BACK_COMPAT
  libclubcoinconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libclubcoinconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libclubcoinconsensus_la_LIBADD = $(LIBSECP256K1)
libclubcoinconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -DBUILD_CLUBCOIN_INTERNAL
libclubcoinconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a
CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb

clean-local:
	-$(MAKE) -C leveldb clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h

.rc.o:
	@test -f $(WINDRES)
	$(AM_V_GEN) $(WINDRES) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(AM_CXXFLAGS) $(PIE_FLAGS) $(CXXFLAGS) -c -o $@ $<

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

if ENABLE_TESTS
#include Makefile.test.include
endif

if ENABLE_BENCH
#include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
#include Makefile.qttest.include
endif

