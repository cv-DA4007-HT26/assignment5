#pragma once

#include "util.h"

struct next_char
{
    char C;

    size_t Frequency = 1;
    
    double Probability;
};

struct gram
{
    string Word;

    vec<next_char> NextChars;
    size_t TotalNextChars = 0;

    size_t Frequency = 1;
};

class gram_builder
{
protected:
    vec<gram> Grams; // NOTE: Uniques

private:
    void MergeDuplicates();
    void MergeGrams(gram &Dest, gram &Src);
    void ComputeNextCharProbs();
    
public:
    const vec<gram> &GetGrams() const;
    void Build(const char *TrainingFileName, size_t k_);
};
