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

inline double StringToDouble(char *Str)
{
    try
    {
	double D = stod(Str);
	return D;
    }
    catch(const invalid_argument &E)
    {
	throw invalid_argument("No conversion could be performed");
    }
    catch(const out_of_range &E)
    {
	throw out_of_range("Pseudocount is larger than a double");
    }

    return 0;
}

inline int StringToInteger(char *Str)
{
    try
    {
	int I = stoi(Str);
	return I;
    }
    catch(const invalid_argument &E)
    {
	throw invalid_argument("No conversion could be performed");
    }
    catch(const out_of_range &E)
    {
	throw out_of_range("Pseudocount is larger than a double");
    }

    return 0;
}
