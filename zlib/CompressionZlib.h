#pragma once
#include "include/zlib.h"
#include "zlib/include/zconf.h"
#include <string>

class CompressionZlib
{
public:
	static long ZipString(std::string, char*);
	static long Zip(const char*, char*, unsigned int);
	static long UnZip(const char*, char*, unsigned int);
};

