#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <vector>
#include <string>

class IOManager
{
public:
	static bool readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer);
};

#endif