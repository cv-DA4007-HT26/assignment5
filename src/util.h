#pragma once

using namespace std;

#include <stdexcept>
#include <stdio.h>
#include <vector>

template<typename T>
using vec = vector<T>;

inline size_t GetFileSize(FILE *F)
{
    fseek(F, 0, SEEK_END);
    size_t Sz = ftell(F);
    fseek(F, 0, SEEK_SET);

    return Sz;
}

inline vec<char> ReadFile(const char *FileName)
{
    FILE *F = fopen(FileName, "rb");

    if(!F) throw runtime_error("Unable to open file " + string(FileName));

    size_t Sz = GetFileSize(F);

    vec<char> FileContents(Sz);

    size_t BytesRead = fread(FileContents.data(), 1, Sz, F);

    if(BytesRead != Sz)
	throw runtime_error("Failed to read entire file");

    return FileContents;
}
