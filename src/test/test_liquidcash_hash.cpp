// Copyright (c)  The Bitcoin Core developers
// Copyright (c) 2017 The Raven Core developers
// Copyright (c) 2018 The Liquidcash Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <arith_uint256.h>
#include <algo/hashx21s.h>
#include <stdio.h>
#include <string.h>
#include <utilstrencodings.h>
#include <iostream>

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        std::vector<unsigned char> rawHeader = ParseHex(argv[1]);

        std::vector<unsigned char> rawHashPrevBlock(rawHeader.begin() + 4, rawHeader.begin() + 36);
        uint256 hashPrevBlock(rawHashPrevBlock);

        std::cout << HashX21S(rawHeader.data(), rawHeader.data() + 80, hashPrevBlock).GetHex();
    } else
    {
        std::cerr << "Usage: test_liquidcash_hash blockHex" << std::endl;
        return 1;
    }

    return 0;
}
