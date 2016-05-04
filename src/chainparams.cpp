// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include <iostream>

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x70;
        pchMessageStart[1] = 0x35;
        pchMessageStart[2] = 0x42;
        pchMessageStart[3] = 0x05;
        vAlertPubKey = ParseHex("0486bce1bac0d543f104cbff2bd23680056a3b9ea05e1137d2ff90eeb5e08472eb500322593a2cb06fbf8297d7beb6cd30cb90f98153b5b7cce1493749e41e0284");
        nDefaultPort = 18114;
        nRPCPort = 19114;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        /*
        nNonce is: 61618576
        Hash is: 000001768b08da66b92dede0ea8e7dcb97424f93d7ac2ac59e7a6cf98f20615a
        Block is: CBlock(hash=000001768b08da66b92dede0ea8e7dcb97424f93d7ac2ac59e7a6cf98f20615a, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=2da7a0080141ea1b6e32f670af4461801b638ba867241d319c3d590d03d75614, nTime=1445353519, nBits=1e0fffff, nNonce=61618576, vtx=1, vchBlockSig=)
          Coinbase(hash=2da7a0080141ea1b6e32f670af4461801b638ba867241d319c3d590d03d75614, nTime=1445353519, ver=1, vin.size=1, vout.size=1, nLockTime=0)
            CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a2e3230204f63742032303135204120426c6f6f6d626572672052756e3f204472756d73204172652042656174696e67)
            CTxOut(empty)
          vMerkleTree:  2da7a0080141ea1b6e32f670af4461801b638ba867241d319c3d590d03d75614
        */
        const char* pszTimestamp = "20 Oct 2015 A Bloomberg Run? Drums Are Beating";
        const uint32_t genesisTimestamp = 1445353519;
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, genesisTimestamp, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = genesisTimestamp;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();

/*
        // "mine" the nonce
        for (genesis.nNonce = 0; genesis.nNonce < 0xffffffff; genesis.nNonce++) {
            if (genesis.nNonce % 1000000 == 0)
                std::cout << "tried " << genesis.nNonce << " nonces" << std::endl;
            hashGenesisBlock = genesis.GetHash();
            unsigned char *b = hashGenesisBlock.end() - 3;
            if (memcmp(b, "\x01\x00\x00", 3) == 0) {
                std::cout << "nNonce is: " << genesis.nNonce << std::endl;
                std::cout << "Hash is: " << genesis.GetHash().ToString() << std::endl;
                std::cout << "Block is: " << genesis.ToString() << std::endl;
                abort();
                break;
            }
        }
*/

        genesis.nNonce = 61618576;
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x000001768b08da66b92dede0ea8e7dcb97424f93d7ac2ac59e7a6cf98f20615a"));
        assert(genesis.hashMerkleRoot == uint256("0x2da7a0080141ea1b6e32f670af4461801b638ba867241d319c3d590d03d75614"));

        vSeeds.push_back(CDNSSeedData("seed1.clubcoin.io", "seed1.clubcoin.io"));
        vSeeds.push_back(CDNSSeedData("seed2.clubcoin.io", "seed2.clubcoin.io"));
        vSeeds.push_back(CDNSSeedData("seed3.clubcoin.io", "seed3.clubcoin.io"));
        vSeeds.push_back(CDNSSeedData("seed4.clubcoin.io", "seed4.clubcoin.io"));
        vSeeds.push_back(CDNSSeedData("seed5.clubcoin.io", "seed5.clubcoin.io"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,28); // appears as "C" in base58
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,85);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,153);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = LAST_POW_BLOCK;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xcd;
        pchMessageStart[1] = 0xf2;
        pchMessageStart[2] = 0x42;
        pchMessageStart[3] = 0xef;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("0471dc165db490094d35cde15b1f5d755fa6ad6f2b5ed0f340e3f17f57389c3c2af113a8cbcc885bde73305a553b5640c83021128008ddf882e856336269080496");
        nDefaultPort = 28114;
        nRPCPort = 29114;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();

/*
        // "mine" the nonce
        for (genesis.nNonce = 0; genesis.nNonce < 0xffffffff; genesis.nNonce++) {
            if (genesis.nNonce % 1000000 == 0)
                std::cout << "tried " << genesis.nNonce << " nonces" << std::endl;
            hashGenesisBlock = genesis.GetHash();
            unsigned char *b = hashGenesisBlock.end() - 2;
            if (memcmp(b, "\x00\x00", 2) == 0) {
                std::cout << "testnet nNonce is: " << genesis.nNonce << std::endl;
                std::cout << "Hash is: " << genesis.GetHash().ToString() << std::endl;
                std::cout << "Block is: " << genesis.ToString() << std::endl;
                abort();
                break;
            }
        }
*/

        genesis.nNonce = 96540;
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x0000fb7faf0608bb189df6bfde6c17b7d9bb337056bb8c97f7973f929b493a4e"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();;
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();;

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1411111111;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 2;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";

        /*
        std::cout << "Block is: " << genesis.ToString() << std::endl;
        */
        assert(hashGenesisBlock == uint256("0xb0dd3b9300bac6ebca952b64d8f8e70698c5b94a8bef14e94d564ee6a0d4e00c"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
