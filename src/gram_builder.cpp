#include <string>
#include <set>

#include "util.h"

#include "gram_builder.h"

const map<string, gram> &
gram_builder::GetGrams() const
{
    return Grams;
}

const set<char> &
gram_builder::GetAlphabet() const
{
    return Alphabet;
}

void
gram_builder::Build(const char *TrainingFileName, size_t GramSz, double Pseudocount)
{
    vec<char> FileContents = ReadFile(TrainingFileName);

    for(const char C : FileContents)
	Alphabet.insert(C);
    
    char *Mem = FileContents.data();
    char *End = Mem + FileContents.size();
    
    while((Mem + GramSz) <= End)
    {
	string Str;

	for(size_t CharIdx = 0;
	    CharIdx < GramSz;
	    ++CharIdx)
	{
	    Str += *(Mem + CharIdx);
	}

	gram &G = Grams[Str];
	++G.Frequency;

	if((Mem + GramSz) >= End) // NOTE: No next char
	    break;

	char C = *(Mem + GramSz);
	
	// NOTE: Increment frequency
	++G.NextChars[C];
	
	++G.TotalNextChars;

	++Mem;
    }
}
