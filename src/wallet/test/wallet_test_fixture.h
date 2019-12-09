// Copyright (c) 2016-2018 The Bitcoin Core developers
// Copyright (c) 2017 The Raven Core developers
// Copyright (c) 2018 The Liquidcash Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef LCASH_WALLET_TEST_FIXTURE_H
#define LCASH_WALLET_TEST_FIXTURE_H

#include "test/test_liquidcash.h"

/** Testing setup and teardown for wallet.
 */
struct WalletTestingSetup : public TestingSetup
{
    explicit WalletTestingSetup(const std::string &chainName = CBaseChainParams::MAIN);

    ~WalletTestingSetup();
};

#endif

