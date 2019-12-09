# Copyright (c) 2018 The Bitcoin Core developers
# Copyright (c) 2017 The Raven Core developers
# Copyright (c) 2018 The Liquidcash Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
#Shows data from the first 1000 blocks

import random
import os
import subprocess
import json


#Set this to your liquidcash-cli program
cli = "liquidcash-cli"

#mode = "-testnet"
mode = ""
rpc_port = 8501
#Set this information in your liquidcash.conf file (in datadir, not testnet3)
rpc_user = 'rpcuser'
rpc_pass = 'rpcpass555'


def rpc_call(params):
    process = subprocess.Popen([cli, mode, params], stdout=subprocess.PIPE)
    out, err = process.communicate()
    return(out)

def get_blockinfo(num):
    rpc_connection = get_rpc_connection()
    hash = rpc_connection.getblockhash(num)
    blockinfo = rpc_connection.getblock(hash)
    return(blockinfo)

def get_rpc_connection():
    from bitcoinrpc.authproxy import AuthServiceProxy, JSONRPCException
    connection = "http://%s:%s@127.0.0.1:%s"%(rpc_user, rpc_pass, rpc_port)
    #print("Connection: " + connection)
    rpc_connection = AuthServiceProxy(connection)
    return(rpc_connection)

for i in range(1,1000):
    dta = get_blockinfo(i)
    print("Block #" + str(i))
    print(dta.get('hash'))
    print(dta.get('difficulty'))
    print(dta.get('time'))
    print("")

