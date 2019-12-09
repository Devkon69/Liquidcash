// Copyright (c)  The Bitcoin Core developers
// Copyright (c) 2017 The Raven Core developers
// Copyright (c) 2018 The Liquidcash Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#define BOOST_TEST_MODULE Liquidcash Test Suite

#include "net.h"

#include <boost/test/unit_test.hpp>

std::unique_ptr<CConnman> g_connman;

[[noreturn]] void Shutdown(void *parg)
{
    std::exit(EXIT_SUCCESS);
}

[[noreturn]] void StartShutdown()
{
    std::exit(EXIT_SUCCESS);
}

bool ShutdownRequested()
{
    return false;
}
