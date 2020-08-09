#include "LevelManager.h"

#include <fstream>
#include <sstream>
#include <iostream>

LevelManager::LevelManager(const char* levelList)
{
	currentLevel = 0;
	std::string levelListStr = levelList;
	std::string directory = levelListStr.substr(0, levelListStr.find_last_of("/"));
	// Read contents of file into lines vector
	std::ifstream inFile;
	inFile.open(levelList, std::ios_base::in);
	if (!inFile.is_open())
	{
		std::string error = "Could not open file: ";
		error.append(levelList);
		throw std::exception(error.c_str());
	}

	std::vector<std::string> lines;
	while (inFile.good() && inFile.peek() != EOF)
	{
		std::string line;
		std::getline(inFile, line);
		if (!line.empty())
		{
			std::string::iterator end_pos = std::remove(line.begin(), line.end(), ' ');
			line.erase(end_pos, line.end());
			lines.push_back(line);
		}
	}
	inFile.close();

	// Phasrse Level Data
	for (unsigned int i = 0; i < lines.size(); i++)
	{
		std::stringstream lineStream(lines[i]);
		std::vector<std::string> lineComp;
		std::string lineToken;
		while (std::getline(lineStream, lineToken, ','))
			if (!lineToken.empty())
				lineComp.push_back(lineToken);

 		levels.push_back(Level((directory + "/" + lineComp[1]).c_str(), lineComp[0]));
	}
}

void LevelManager::setLevel(std::string levelName)
{
#ifdef _DEBUG
	std::cout << "Moving to Level: " << levelName << std::endl;
#endif // _DEBUG

	for (unsigned int i = 0; i < levels.size(); i++)
		if (levels[i].getName() == levelName)
			currentLevel = i;
}

Level& LevelManager::getLevel()
{
	if (levels.empty())
		throw std::exception("Level Manager Not Initalized");
	return levels[currentLevel];
}
