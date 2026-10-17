#pragma once

#include "util.h"
#include "gram_builder.h"
#include <random>
#include <exception>

class text_generator : public gram_builder
{
private:
    mt19937 RNG;
    
    template<typename T>
    T GetRandomEntry(vec<T> &V);

    inline bool UpdateGram(gram &ToUpdate, vec<gram> Grams, string Word);
    
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
    }

    void Generate(size_t CharCountLimit);
};
