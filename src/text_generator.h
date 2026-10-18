#pragma once

#include "util.h"
#include "gram_builder.h"
#include <random>
#include <exception>
#include <map>

class text_generator : public gram_builder
{
private:
    mt19937 RNG;

    char GetRandomChar(map<char, size_t> &Entries, double Pseudocount);
    void GetRandomGram(gram &G, string &Word);

    inline bool UpdateGram(gram &ToUpdate, string Word);    
    
public:
    text_generator()
    {
	random_device RD;
	RNG.seed(RD());
    }

    text_generator(gram_builder &G)
    {
	random_device RD;
	RNG.seed(RD());

	Grams = G.GetGrams();
	Alphabet = G.GetAlphabet();
    }

    void Generate(size_t CharCountLimit, double Pseudocount);
};
