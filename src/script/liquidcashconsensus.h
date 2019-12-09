// Copyright (c)  The Bitcoin Core developers
// Copyright (c) 2017 The Raven Core developers
// Copyright (c) 2018 The Liquidcash Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef LCASH_LCASHCONSENSUS_H
#define LCASH_LCASHCONSENSUS_H

#include <stdint.h>

#if defined(BUILD_LCASH_INTERNAL) && defined(HAVE_CONFIG_H)
#include "config/liquidcash-config.h"
  #if defined(_WIN32)
    #if defined(DLL_EXPORT)
      #if defined(HAVE_FUNC_ATTRIBUTE_DLLEXPORT)
        #define EXPORT_SYMBOL __declspec(dllexport)
      #else
        #define EXPORT_SYMBOL
      #endif
    #endif
  #elif defined(HAVE_FUNC_ATTRIBUTE_VISIBILITY)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBLCASHCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define LCASHCONSENSUS_API_VER 1

typedef enum liquidcashconsensus_error_t
{
    liquidcashconsensus_ERR_OK = 0,
    liquidcashconsensus_ERR_TX_INDEX,
    liquidcashconsensus_ERR_TX_SIZE_MISMATCH,
    liquidcashconsensus_ERR_TX_DESERIALIZE,
    liquidcashconsensus_ERR_AMOUNT_REQUIRED,
    liquidcashconsensus_ERR_INVALID_FLAGS,
} liquidcashconsensus_error;

/** Script verification flags */
enum
{
    liquidcashconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    liquidcashconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    liquidcashconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    liquidcashconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    liquidcashconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    liquidcashconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    liquidcashconsensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    liquidcashconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = liquidcashconsensus_SCRIPT_FLAGS_VERIFY_P2SH | liquidcashconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               liquidcashconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | liquidcashconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               liquidcashconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | liquidcashconsensus_SCRIPT_FLAGS_VERIFY_WITNESS
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not nullptr, err will contain an error/success code for the operation
EXPORT_SYMBOL int liquidcashconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, liquidcashconsensus_error* err);

EXPORT_SYMBOL int liquidcashconsensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, liquidcashconsensus_error* err);

EXPORT_SYMBOL unsigned int liquidcashconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // LCASH_LCASHCONSENSUS_H
