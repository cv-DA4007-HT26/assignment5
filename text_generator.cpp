#include <string>

#include "gram_builder.h"
#include "util.h"

#include "text_generator.h"

template<typename T>
T text_generator::GetRandomEntry(vec<T> &V)
{
    // TODO: Error handling for empty V
    
    vec<double> Weights(V.size());

    for(size_t EntryIdx = 0;
	EntryIdx < V.size();
	++EntryIdx)
    {
	Weights[EntryIdx] = V[EntryIdx].Frequency;
    }
    
    discrete_distribution<size_t> D(Weights.begin(), Weights.end());

    size_t Index = D(RNG);

    return V[Index];
}

inline bool
text_generator::UpdateGram(gram &ToUpdate, vec<gram> Grams, string Word)
{
    for(gram &G : Grams)
    {
	if(G.Word == Word)
	{
	    ToUpdate = G;
	    return true;
	}
    }

    return false;
}

void
text_generator::Generate(size_t CharCountLimit)
{
    gram G = GetRandomEntry<gram>(Grams);
    
    fprintf(stdout, "%s", G.Word.c_str());
    
    size_t CharCount = G.Word.size();
    while(CharCount < CharCountLimit)
    {    
	next_char NC = GetRandomEntry<next_char>(G.NextChars);

	fprintf(stdout, "%c", NC.C);    
	++CharCount;
    
	string NewWord = G.Word + NC.C;
	NewWord.erase(NewWord.begin());
	
	if(!UpdateGram(G, Grams, NewWord))
	{
	    break;
	}
    }

    fprintf(stdout, "\n");    
}
