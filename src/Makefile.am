
DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS) $(ERROR_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

LCASH_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

LCASH_INCLUDES += -I$(srcdir)/secp256k1/include
LCASH_INCLUDES += $(UNIVALUE_CFLAGS)

LIBLCASH_SERVER=libliquidcash_server.a
LIBLCASH_COMMON=libliquidcash_common.a
LIBLCASH_CONSENSUS=libliquidcash_consensus.a
LIBLCASH_CLI=libliquidcash_cli.a
LIBLCASH_UTIL=libliquidcash_util.a
LIBLCASH_CRYPTO=crypto/libliquidcash_crypto.a
LIBLCASHQT=qt/libliquidcashqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

if ENABLE_ZMQ
LIBLCASH_ZMQ=libliquidcash_zmq.a
endif
if BUILD_LCASH_LIBS
LIBLCASHCONSENSUS=libliquidcashconsensus.la
endif
if ENABLE_WALLET
LIBLCASH_WALLET=libliquidcash_wallet.a
endif

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBLCASH_CRYPTO) \
  $(LIBLCASH_UTIL) \
  $(LIBLCASH_COMMON) \
  $(LIBLCASH_CONSENSUS) \
  $(LIBLCASH_SERVER) \
  $(LIBLCASH_CLI) \
  $(LIBLCASH_WALLET) \
  $(LIBLCASH_ZMQ)

lib_LTLIBRARIES = $(LIBLCASHCONSENSUS)

bin_PROGRAMS =
noinst_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_LCASHD
  bin_PROGRAMS += liquidcashd
endif

if BUILD_LCASH_CLI
  bin_PROGRAMS += liquidcash-cli
endif

if BUILD_LCASH_TX
  bin_PROGRAMS += liquidcash-tx
endif

.PHONY: FORCE check-symbols check-security
# liquidcash core #
LCASH_CORE_H = \
  addrdb.h \
  addressindex.h \
  spentindex.h \
  timestampindex.h \
  addrman.h \
  assets/assets.h \
  assets/assetdb.h \
  assets/assettypes.h \
  base58.h \
  bloom.h \
  blockencodings.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/tx_verify.h \
  core_io.h \
  core_memusage.h \
  cuckoocache.h \
  fs.h \
  httprpc.h \
  httpserver.h \
  indirectmap.h \
  init.h \
  key.h \
  keystore.h \
  dbwrapper.h \
  limitedmap.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  net_processing.h \
  netaddress.h \
  netbase.h \
  netmessagemaker.h \
  noui.h \
  policy/feerate.h \
  policy/fees.h \
  policy/policy.h \
  policy/rbf.h \
  pow.h \
  protocol.h \
  random.h \
  reverse_iterator.h \
  reverselock.h \
  rpc/blockchain.h \
  rpc/client.h \
  rpc/mining.h \
  rpc/protocol.h \
  rpc/safemode.h \
  rpc/server.h \
  rpc/register.h \
  scheduler.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  script/ismine.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/events.h \
  support/lockedpool.h \
  sync.h \
  threadsafety.h \
  threadinterrupt.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utiltime.h \
  validation.h \
  validationinterface.h \
  versionbits.h \
  wallet/coincontrol.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/feebumper.h \
  wallet/fees.h \
  wallet/init.h \
  wallet/rpcwallet.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  warnings.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h \
  algo/sph_groestl.h \
  algo/sph_types.h \
  algo/sph_blake.h \
  algo/sph_bmw.h \
  algo/sph_jh.h \
  algo/sph_keccak.h \
  algo/sph_skein.h \
  algo/sph_luffa.h \
  algo/sph_cubehash.h \
  algo/sph_simd.h \
  algo/sph_echo.h \
  algo/sph_shavite.h \
  algo/sph_sha2.h \
  algo/sph_haval.h \
  algo/sph_tiger.h \
  algo/lyra2.h \
  algo/sponge.h \
  algo/gost_streebog.h \
  algo/hashx21s.h \
  algo/groestl.c \
  algo/blake.c \
  algo/bmw.c \
  algo/cubehash.c \
  algo/echo.c \
  algo/jh.c \
  algo/keccak.c \
  algo/luffa.c \
  algo/shavite.c \
  algo/simd.c \
  algo/skein.c \
  algo/hamsi.c \
  algo/whirlpool.c \
  algo/shabal.c \
  algo/fugue.c \
  algo/sha2.c \
  algo/extra.c \
  algo/extra.h \
  algo/sph_sha2big.c \
  algo/haval.c \
  algo/tiger.cpp \
  algo/lyra2.cpp \
  algo/sponge.cpp \
  algo/sph_sha2.c \
  algo/gost_streebog.c 

obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh "$(abs_top_builddir)/src/obj/build.h" \
	  "$(abs_top_srcdir)"
libliquidcash_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between liquidcashd and liquidcash-qt
libliquidcash_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(LCASH_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libliquidcash_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libliquidcash_server_a_SOURCES = \
  addrdb.cpp \
  addrman.cpp \
  bloom.cpp \
  blockencodings.cpp \
  chain.cpp \
  checkpoints.cpp \
  consensus/consensus.cpp \
  consensus/tx_verify.cpp \
  httprpc.cpp \
  httpserver.cpp \
  init.cpp \
  dbwrapper.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  net_processing.cpp \
  noui.cpp \
  assets/assets.cpp \
  assets/assetdb.cpp \
  assets/assettypes.cpp \
  policy/fees.cpp \
  policy/policy.cpp \
  policy/rbf.cpp \
  pow.cpp \
  rest.cpp \
  rpc/assets.cpp \
  rpc/blockchain.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/safemode.cpp \
  rpc/server.cpp \
  script/sigcache.cpp \
  script/ismine.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  ui_interface.cpp \
  validation.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  $(LCASH_CORE_H)

if ENABLE_ZMQ
libliquidcash_zmq_a_CPPFLAGS = $(LCASH_INCLUDES) $(ZMQ_CFLAGS)
libliquidcash_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libliquidcash_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp
endif


# wallet: shared between liquidcashd and liquidcash-qt, but only linked
# when wallet enabled
libliquidcash_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(LCASH_INCLUDES)
libliquidcash_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libliquidcash_wallet_a_SOURCES = \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/feebumper.cpp \
  wallet/fees.cpp \
  wallet/init.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  $(LCASH_CORE_H)

# crypto primitives library
crypto_libliquidcash_crypto_a_CPPFLAGS = $(AM_CPPFLAGS)
crypto_libliquidcash_crypto_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libliquidcash_crypto_a_SOURCES = \
  crypto/aes.cpp \
  crypto/aes.h \
  crypto/chacha20.cpp \
  crypto/chacha20.h \
  crypto/common.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h \
  crypto/sph_sha2.h \
  crypto/sph_types.h

if USE_ASM
crypto_libliquidcash_crypto_a_SOURCES += crypto/sha256_sse4.cpp
endif

# consensus: shared between all executables that validate any consensus rules.
libliquidcash_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(LCASH_INCLUDES)
libliquidcash_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libliquidcash_consensus_a_SOURCES = \
  amount.h \
  arith_uint256.cpp \
  arith_uint256.h \
  consensus/merkle.cpp \
  consensus/merkle.h \
  consensus/params.h \
  consensus/validation.h \
  hash.cpp \
  hash.h \
  algo/hashx21s.h \
  prevector.h \
  primitives/block.cpp \
  primitives/block.h \
  primitives/transaction.cpp \
  primitives/transaction.h \
  pubkey.cpp \
  pubkey.h \
  script/liquidcashconsensus.cpp \
  script/interpreter.cpp \
  script/interpreter.h \
  script/script.cpp \
  script/script.h \
  script/script_error.cpp \
  script/script_error.h \
  serialize.h \
  support/cleanse.h \
  support/cleanse.cpp \
  tinyformat.h \
  uint256.cpp \
  uint256.h \
  utilstrencodings.cpp \
  utilstrencodings.h \
  version.h \
  $(LCASH_CORE_H)

# common: shared between liquidcashd, and liquidcash-qt and non-server tools
libliquidcash_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(LCASH_INCLUDES)
libliquidcash_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libliquidcash_common_a_SOURCES = \
  base58.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  key.cpp \
  keystore.cpp \
  netaddress.cpp \
  netbase.cpp \
  policy/feerate.cpp \
  protocol.cpp \
  scheduler.cpp \
  script/sign.cpp \
  script/standard.cpp \
  warnings.cpp \
  $(LCASH_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libliquidcash_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(LCASH_INCLUDES)
libliquidcash_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libliquidcash_util_a_SOURCES = \
  support/lockedpool.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  fs.cpp \
  random.cpp \
  rpc/protocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  threadinterrupt.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(LCASH_CORE_H)

if GLIBC_BACK_COMPAT
libliquidcash_util_a_SOURCES += compat/glibc_compat.cpp
AM_LDFLAGS += $(COMPAT_LDFLAGS)
endif

# cli: shared between liquidcash-cli and liquidcash-qt
libliquidcash_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(LCASH_INCLUDES)
libliquidcash_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libliquidcash_cli_a_SOURCES = \
  rpc/client.cpp \
  $(LCASH_CORE_H)

nodist_libliquidcash_util_a_SOURCES = $(srcdir)/obj/build.h
#

# liquidcashd binary #
liquidcashd_SOURCES = liquidcashd.cpp
liquidcashd_CPPFLAGS = $(AM_CPPFLAGS) $(LCASH_INCLUDES)
liquidcashd_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
liquidcashd_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
liquidcashd_SOURCES += liquidcashd-res.rc
endif

liquidcashd_LDADD = \
  $(LIBLCASH_SERVER) \
  $(LIBLCASH_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBLCASH_UTIL) \
  $(LIBLCASH_WALLET) \
  $(LIBLCASH_ZMQ) \
  $(LIBLCASH_CONSENSUS) \
  $(LIBLCASH_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBLEVELDB_SSE42) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

liquidcashd_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS)

# liquidcash-cli binary #
liquidcash_cli_SOURCES = liquidcash-cli.cpp
liquidcash_cli_CPPFLAGS = $(AM_CPPFLAGS) $(LCASH_INCLUDES) $(EVENT_CFLAGS)
liquidcash_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
liquidcash_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
liquidcash_cli_SOURCES += liquidcash-cli-res.rc
endif

liquidcash_cli_LDADD = \
  $(LIBLCASH_CLI) \
  $(LIBUNIVALUE) \
  $(LIBLCASH_UTIL) \
  $(LIBLCASH_CRYPTO)

liquidcash_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)
#

# liquidcash-tx binary #
liquidcash_tx_SOURCES = liquidcash-tx.cpp
liquidcash_tx_CPPFLAGS = $(AM_CPPFLAGS) $(LCASH_INCLUDES)
liquidcash_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
liquidcash_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
liquidcash_tx_SOURCES += liquidcash-tx-res.rc
endif

liquidcash_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBLCASH_COMMON) \
  $(LIBLCASH_UTIL) \
  $(LIBLCASH_CONSENSUS) \
  $(LIBLCASH_CRYPTO) \
  $(LIBSECP256K1)

liquidcash_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# liquidcashconsensus library #
if BUILD_LCASH_LIBS
include_HEADERS = script/liquidcashconsensus.h
libliquidcashconsensus_la_SOURCES = $(crypto_libliquidcash_crypto_a_SOURCES) $(libliquidcash_consensus_a_SOURCES)

if GLIBC_BACK_COMPAT
  libliquidcashconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libliquidcashconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libliquidcashconsensus_la_LIBADD = $(LIBSECP256K1)
libliquidcashconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_LCASH_INTERNAL
libliquidcashconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = $(EXTRA_LIBRARIES)

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
CLEANFILES += obj/build.h

EXTRA_DIST = $(CTAES_DIST)


config/liquidcash-config.h: config/stamp-h1
	@$(MAKE) -C $(top_builddir) $(subdir)/$(@)
config/stamp-h1: $(top_srcdir)/$(subdir)/config/liquidcash-config.h.in $(top_builddir)/config.status
	$(AM_V_at)$(MAKE) -C $(top_builddir) $(subdir)/$(@)
$(top_srcdir)/$(subdir)/config/liquidcash-config.h.in:  $(am__configure_deps)
	$(AM_V_at)$(MAKE) -C $(top_srcdir) $(subdir)/config/liquidcash-config.h.in

clean-local:
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(top_srcdir)/contrib/devtools/symbol-check.py < $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(<D) $<

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
