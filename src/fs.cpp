// Copyright (c) 2017 The Bitcoin Core developers
// Copyright (c) 2017 The Raven Core developers
// Copyright (c) 2018 The Rito Core developers
// Copyright (c) 2019 The Liquidcash Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include "fs.h"

namespace fsbridge {

FILE *fopen(const fs::path& p, const char *mode)
{
    return ::fopen(p.string().c_str(), mode);
}

FILE *freopen(const fs::path& p, const char *mode, FILE *stream)
{
    return ::freopen(p.string().c_str(), mode, stream);
}

} // fsbridge
