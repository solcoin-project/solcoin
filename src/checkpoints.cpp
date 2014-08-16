// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

#include "config.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double fSigcheckVerificationFactor = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64 nTimeLastCheckpoint;
        int64 nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (     2, uint256("0x65f69a4591090928f98478622058f614e5f3db42a16f1d99885c8ecad2ecbc9f") )
        (   512, uint256("0x2c5ad2a937958da366409db37d08cf9b75fe8695d4897d403e54dc078bb30b61") )
        (  3141, uint256("0x85dc531ed9c6c955a27b004d613c7f810f3b9d9c2fac9c4e6f160e4a727fba47") )
        (  7368, uint256("0xec9b27bbdaf6abdc984cbc24f08519a31488e58f5ad90e791b4f0766b5418460") )
        ( 10000, uint256("0x25a8e9c4fc3baca9c6b4200f7b34754845e7e3a3d25226ad0c371ecdfd5f236a") )
        ( 17600, uint256("0x3a03d650a9b11dccdf38117652eeadbbecd016cb9895341c08456ddc885c7685") )
        ( 57023, uint256("0xb8ccbc4bb9765ca2d6e7eea5bb6c7ffe3768a24dd2fb49319d217c408a725031") )
        ( 98996, uint256("0xd1eeaa723bff270d1483424beace793a3487721e964697303562b24a25c69f4d") );

    static const CCheckpointData data = {
        &mapCheckpoints,
        1408219938, // * UNIX timestamp of last checkpoint block
        240955,     // * total number of transactions between genesis and last checkpoint
                    // (the tx=... number in the SetBestChain debug.log lines)
        800.0       // * estimated number of transactions per day after checkpoint
    };

    // Solcoin has no testnet
    static MapCheckpoints mapCheckpointsTestnet = 
        boost::assign::map_list_of
        (     0, uint256("0xf00000002a936ca763904c3c35fce2f3556c559c0214345d31b1bcebf76acb70") );

    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1389610463,
        2,
        1
    };

    const CCheckpointData &Checkpoints() {
        if (fTestNet)
            return dataTestnet;
        else
            return data;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints
        if (!GetBoolArg("-checkpoints", true))
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex) {
        if (pindex==NULL)
            return 0.0;

        int64 nNow = time(NULL);

        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0; // Testnet has no checkpoints
        if (!GetBoolArg("-checkpoints", true))
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL; // Testnet has no checkpoints
        if (!GetBoolArg("-checkpoints", true))
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
