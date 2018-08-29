#ifndef FILE_H
#define FILE_H
#include <stdio.h>
#include <stdlib.h>
class File
{
public:
	File();
	~File();
	char* fileToBuffer(char* file);
};

#endif