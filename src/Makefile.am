DIST_SUBDIRS = 

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)
EXTRA_LIBRARIES =










CLUBCOIN_CONFIG_INCLUDES=-I$(builddir)/config
CLUBCOIN_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

LIBCLUBCOIN_SERVER=libclubcoin_server.a
LIBCLUBCOIN_WALLET=libclubcoin_wallet.a
LIBCLUBCOIN_COMMON=libclubcoin_common.a
LIBCLUBCOIN_CLI=libclubcoin_cli.a
LIBCLUBCOIN_UTIL=libclubcoin_util.a
LIBCLUBCOIN_CRYPTO=crypto/libclubcoin_crypto.a
LIBCLUBCOINQT=qt/libclubcoinqt.a


















# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBCLUBCOIN_CRYPTO) \
  $(LIBCLUBCOIN_UTIL) \
  $(LIBCLUBCOIN_COMMON) \
  $(LIBCLUBCOIN_SERVER) \
  $(LIBCLUBCOIN_CLI)

if ENABLE_WALLET
CLUBCOIN_INCLUDES += $(BDB_CPPFLAGS)
#EXTRA_LIBRARIES += libclubcoin_wallet.a
endif
if ENABLE_ZMQ
#EXTRA_LIBRARIES += libclubcoin_zmq.a
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

.PHONY: FORCE check-symbols check-security
# clubcoin core #
CLUBCOIN_CORE_H = \
  addrman.h \
  alert.h \
  allocators.h \
  arith_uint256.h \
  base58.h \
  bignum.h \
  chainparams.h \
  chainparamsseeds.h \
  checkpoints.h \
  clientversion.h \
  coincontrol.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  core.h \
  crypter.h \
  db.h \
  hash.h \
  init.h \
  kernel.h \
  key.h \
  keystore.h \
  main.h \
  miner.h \
  mruset.h \
  net.h \
  netbase.h \
  pbkdf2.h \
  protocol.h \
  random.h \
  rpcclient.h \
  rpcprotocol.h \
  rpcserver.h \
  script.h \
  scrypt.h \
  serialize.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/pagelocker.h \
  sync.h \
  threadsafety.h \
  timedata.h \
  tinyformat.h \
  txdb.h \
  txdb-leveldb.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  util.h \
  utilstrencodings.h \
  utiltime.h \
  version.h \
  wallet.h \
  walletdb.h \
  json/json_spirit_error_position.h \
  json/json_spirit.h \
  json/json_spirit_reader.cpp \
  json/json_spirit_reader.h \
  json/json_spirit_reader_template.h \
  json/json_spirit_stream_reader.h \
  json/json_spirit_utils.h \
  json/json_spirit_value.cpp \
  json/json_spirit_value.h \
  json/json_spirit_writer.cpp \
  json/json_spirit_writer.h \
  json/json_spirit_writer_template.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libclubcoin_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between clubcoind and clubcoin-qt
# For now we REQUIRE the wallet sources for building. XXX
libclubcoin_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(CLUBCOIN_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libclubcoin_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
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






if ENABLE_ZMQ
#clubcoind_LDADD += $(LIBCLUBCOIN_ZMQ) $(ZMQ_LIBS)
endif







# wallet: shared between clubcoind and clubcoin-qt, but only linked
# when wallet enabled
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
crypto_libclubcoin_crypto_a_SOURCES = \
  crypto/sha512.cpp \
  crypto/sha512.h

# common: shared between clubcoind, and clubcoin-qt and non-server tools
libclubcoin_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(CLUBCOIN_INCLUDES)
libclubcoin_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libclubcoin_common_a_SOURCES = \
  base58.cpp \
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
  support/pagelocker.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  random.cpp \
  rpcprotocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  util.cpp \
  utiltime.cpp \
  utilstrencodings.cpp \
  $(crypto_libclubcoin_crypto_a_SOURCES) \
  $(CLUBCOIN_CORE_H)

if GLIBC_BACK_COMPAT
#libclubcoin_util_a_SOURCES += compat/glibc_compat.cpp
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
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)
# retired LDADD
# LIBCLUBCOIN_CRYPTO


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
include_HEADERS =
libclubcoinconsensus_la_SOURCES = \
  hash.cpp \
  hash.h \
  script.cpp \
  script.h \
  scrypt.cpp \
  scrypt.h \
  utilstrencodings.cpp \
  utilstrencodings.h \
  version.h

if GLIBC_BACK_COMPAT
#  libclubcoinconsensus_la_SOURCES += compat/glibc_compat.cpp
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

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

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
