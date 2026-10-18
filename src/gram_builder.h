#pragma once

#include <map>
#include <set>

#include "util.h"

struct gram
{
    size_t Frequency = 0;
    map<char, size_t> NextChars;
    size_t TotalNextChars = 0;
};

class gram_builder
{
protected:
    map<string, gram> Grams;
    
public:
    const map<string, gram> &GetGrams() const;
    void Build(const char *TrainingFileName, size_t k_, double Pseudocount);
};
