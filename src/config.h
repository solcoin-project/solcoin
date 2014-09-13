// Copyright (c) 2014- The Solcoin developers
//
// This file abstracts parts of the currency's specifics in order to make it easier to configure
// the client, as well as helping others fork the sources into their own cryptocurrency.
//
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef _COIN_CONFIG_H
#define _COIN_CONFIG_H 1

// Uncomment this define to mine a new genesis block if the hashes don't match - only for forking a new coin!
//#define MINE_GENESIS_BLOCK              1

// The genesis message can't be longer than 91 bytes (not characters), excluding the terminating null byte
#define COIN_GENESIS_MSG                "Söndag 5:e januari 2014 - MtGox registrerar för andra gången BTC på över $1000."
#define COIN_GENESIS_HASH               "0x579b9ba9d7e8de5fbcc9b76cc90324f4b5d2e95855eeb67ed23c85e73cc2e54d"
#define COIN_MERKLE_ROOT                "0x4b1087013c57fb7fe108a48663a607509fdf0e688b69d68d2f16c38211ad168a"
#define COIN_GENESIS_TIME               1388971085  // Monday 6 January 2014 01:18:05 UTC
#define COIN_GENESIS_NONCE              32216616
#define COIN_GENESIS_BITS               0x1d07ffff
#define COIN_DIFFICULTY_SHIFT           29          // Lowest network diff. is 0.12499
#define COIN_COINBASE_MATURITY          72

#define COIN_MAX_MONEY                  696342000   // Maximum amount of SOL that can be sent in a single tx
#define COIN_MINTXFEE                   20000       // Transaction- and relay fees, in Satoshis
#define COIN_MINRELAYTXFEE              20000
#define COIN_DUST_SOFT_LIMIT            10000       // 0.0001 SOL
#define COIN_DUST_HARD_LIMIT            100         // 0.000001 SOL

#define SOLCOIN_OLD_TARGET_TIMESPAN     11304       // Solcoin: For block 0-14999
#define COIN_BLOCK_TARGET_TIME          188         // 188 seconds (3.14 minutes) between blocks
#define COIN_BLOCKS_BETWEEN_RETARGET    60          // Defined just in case KGW would be removed in the future
#define COIN_KGW_MIN_PAST_BLOCKS        114
#define COIN_KGW_MAX_PAST_BLOCKS        1443

#define COIN_BASE58_VERSION_BYTE        18          // Solcoin addresses start with '8'
#define COIN_PCHMESSAGE_START           { 0xfe, 0xc1, 0xba, 0xdc }

#define COIN_RPC_PORT                   24360       // Port for RPC calls (mining, stats etc.)
#define COIN_P2P_PORT                   24361       // Port for block chain exchange
#define COIN_RPC_TESTNET_PORT           24362       // Solcoin has no testnet; defined anyway to avoid collisions
#define COIN_P2P_TESTNET_PORT           24363

#define COIN_MAINNET_DNS_SEEDS          {"stolendata.net", "solcoinseeds.stolendata.net"}, \
                                        {"z80.guru", "solcoinseeds.z80.guru"}, \
                                        {"tru.io", "solcoinseeds.tru.io"}
#define COIN_TESTNET_DNS_SEEDS          {"solcoin.testnet.seed", "doesnotexist"}
#define COIN_HARDCODED_NODES            { 0x26f6f3a2, 0xe89de2bc, 0xf385f050, 0x1886f3a2, 0x86133eb2, 0x8cd2c780, \
                                          0x5dfbd382 }

#endif

