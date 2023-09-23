
#include "SDL.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "metadata.h"

int MetaData::getHighScore()
{
    int highScore = 0;
    std::string line;
    std::ifstream filestream(recordFile);
    if (filestream.is_open())
    {
        if (std::getline(filestream, line))
        {
            std::istringstream linestream(line);
            if (linestream >> highScore)
            {
            }
        }
        filestream.close();
        std::cout << "reading high score record file ..." << std::endl;
    }
    else
    {
        std::cout << "High score record file does not exist. Creating new." << std::endl;
        std::ofstream outfile(recordFile);
    }
    return highScore;
}

void MetaData::setHighScore(int highScore)
{
    std::ofstream dataFile;
    dataFile.open(recordFile, std::ofstream::out | std::ofstream::trunc);
    if (!dataFile.is_open())
    {
        std::cout << " unable to open record file" << std::endl;
    }
    else
    {
        dataFile<<highScore;
    }
}