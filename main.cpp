#include <iostream>
#include "blockchain.h"

int main(int argc, char **argv)
{
    const int DIFICULTY = argc > 1 ? std::stoi(argv[1]) : 4; // Dificulty
    Blockchain bChain = Blockchain(DIFICULTY);               // Blockchain
    const int nBlocks = argc > 2 ? std::stoi(argv[2]) : 10;  // Number of blocks

    // Add blocks to the blockchain
    for (int i = 1; i <= nBlocks; i++)
    {
        std::cout << "Adding block " << i << "..." << std::endl;
        bChain.AddBlock(Block(i, "Block " + std::to_string(i))); // Add block
    }

    std::cout << "\n"
              << "-------Blockchain-------" << std::endl;
    bChain.PrintChain();
    std::cout << "------------------------" << std::endl;

    return 0;
}