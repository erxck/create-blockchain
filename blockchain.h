#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <ctime>
// #include <openssl/sha.h>

// std::string sha256(const std::string str)
// {
//     unsigned char hash[SHA256_DIGEST_LENGTH];

//     SHA256_CTX sha256;
//     SHA256_Init(&sha256);
//     SHA256_Update(&sha256, str.c_str(), str.size());
//     SHA256_Final(hash, &sha256);

//     std::stringstream ss;

//     for(int i = 0; i < SHA256_DIGEST_LENGTH;i++) {
//         ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
//     }

//     return ss.str();
// }

// Block class
class Block
{
public:
    std::string sPrevHash; // Previous hash
    // Constructor
    Block(uint32_t nIndexIn, const std::string &sDataIn) : _nIndex(nIndexIn), _sData(sDataIn)
    {
        _nNonce = 0;
        _tTime = time(nullptr); // Set the time
        _sHash = _CalculateHash();
    }

    // Get hash
    std::string GetHash() { return _sHash; }

    // function to mine the block
    void MineBlock(uint32_t nDifficulty)
    {
        char cstr[nDifficulty + 1]; // Create a string with nDifficulty * "0"

        // Set the first nDifficulty characters to '0'
        for (uint32_t i = 0; i < nDifficulty; ++i)
        {
            cstr[i] = '0';
        }
        cstr[nDifficulty] = '\0';

        // Convert cstr to string
        std::string str(cstr);
        // time_t initialTime = time(nullptr);

        // Keep changing the nonce until the hash has nDifficulty leading 0s
        while (_sHash.substr(0, nDifficulty) != str)
        {
            _nNonce++;
            _sHash = _CalculateHash();

            // time_t currentTime = time(nullptr);
            // time_t timeDiff = currentTime - initialTime / 1000;
            // if (timeDiff > 1)
            // {
            //     std::cout << "Time: " << timeDiff << "s" << std::endl;
            //     initialTime = time(nullptr);
            // }
        }

        std::cout << "Block mined: " << _sHash << std::endl;
    }

    // Print block
    void PrintBlock()
    {
        std::cout << "Block " << _nIndex << " [" << _sData << "]" << std::endl;
        std::cout << "Hash: " << _sHash << std::endl;
        std::cout << "Prev: " << sPrevHash << std::endl;
        std::cout << "Time: " << _tTime << std::endl;
        std::cout << "Nonce: " << _nNonce << std::endl;
    }

private:
    uint32_t _nIndex;
    int64_t _nNonce;
    std::string _sData;
    std::string _sHash;
    time_t _tTime;

    // Calculate hash
    std::string _CalculateHash() const
    {
        return std::to_string(_nIndex) + std::to_string(_nNonce) + _sData + sPrevHash + std::to_string(_tTime);
    }
};

// Blockchain class
class Blockchain
{
public:
    // Constructor
    Blockchain(uint32_t nDifficulty)
    {
        _nDifficulty = nDifficulty;
        _GenesisBlock(); // Create the first block
    }

    // Add block to the chain
    void AddBlock(Block bNew)
    {
        bNew.sPrevHash = _HashLastBlock(); // Set the previous hash
        // bNew.MineBlock(_nDifficulty);
        _vChain.push_back(bNew); // Add the block to the chain
    }

    // Print the chain
    void PrintChain()
    {
        for (uint32_t i = 0; i < _vChain.size(); i++)
        {
            _vChain[i].PrintBlock();
            std::cout << std::endl;
        }
    }

private:
    uint32_t _nDifficulty;
    std::vector<Block> _vChain; // Vector to store the chain

    // Get last block
    Block _GetLastBlock() const
    {
        return _vChain.back(); // Return the last block
    }

    // Genesis block
    void _GenesisBlock()
    {
        _vChain.push_back(Block(0, "Genesis Block")); // Create the first block
    }

    // Hash last block
    std::string _HashLastBlock()
    {
        return _GetLastBlock().GetHash();
    }
};