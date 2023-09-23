#ifndef METADATA_H
#define METADATA_H

#include "SDL.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

// this class stores the meta data about the game
class MetaData
{
public:
    // constructor fetches the platform and sets the private variable accordingly
    MetaData()
    {
        std::cout << "Fetching MetaData...!" << std::endl;
    }
    ~MetaData() {
        // Clean up resources or perform other cleanup tasks here.
    }

    const std::string recordFile{"../high_score.txt"};

    int getHighScore();
    void setHighScore(int highScore);
};


#endif