#include <string>

#include "util.h"

#include "gram_builder.h"

void
gram_builder::MergeGrams(gram &Dest, gram &Src)
{
    ++Dest.Frequency;
    
    if(Src.NextChars.empty())
	return;

    next_char NCSrc = Src.NextChars.back(); // NOTE: NextChars size will be 1 (Dest gram consumes all similar grams in the array)

    bool FoundDup = false;
    for(next_char &NC : Dest.NextChars)
    {	
	if(NC.C == NCSrc.C)
	{
	    ++NC.Frequency;
	    
	    FoundDup = true;	    
	    break;
	}
    }

    if(!FoundDup)
    {
	Dest.NextChars.push_back(NCSrc);
    }

    ++Dest.TotalNextChars;
}

void
gram_builder::MergeDuplicates()
{
    for(size_t GramIdx = 0;
	GramIdx < Grams.size();
	++GramIdx)
    {
	gram &G = Grams[GramIdx];
	
	for(size_t GramIdx_ = GramIdx + 1;
	    GramIdx_ < Grams.size();
	    )
	{ 
	    gram G_ = Grams[GramIdx_];
	    
	    if(G.Word == G_.Word)
	    {
		MergeGrams(G, G_);
		
		Grams.erase(Grams.begin() + GramIdx_);
	    }
	    else
	    {
		++GramIdx_;
	    }
	}
    }
}

void
gram_builder::ComputeNextCharProbs()
{
    for(gram &G : Grams)
    {
	for(next_char &NC : G.NextChars)
	{
	    // TODO: Add pseudocount
	    NC.Probability = (double)NC.Frequency / (double)G.TotalNextChars;
	}
    }
}

const vec<gram> &
gram_builder::GetGrams() const
{
    return Grams;
}

void
gram_builder::Build(const char *TrainingFileName, size_t GramSz)
{
    vec<char> FileContents = ReadFile(TrainingFileName);

    // NOTE: Read k-grams
    size_t GramCount = (FileContents.size() - GramSz) + 1;
    Grams.resize(GramCount);
    
    char *Mem = FileContents.data();
    char *End = Mem + FileContents.size();
    
    for(gram &G : Grams)
    {
	string Str;

	for(size_t CharIdx = 0;
	    CharIdx < GramSz;
	    ++CharIdx)
	{
	    Str += *(Mem + CharIdx);
	}

	G.Word = Str;
	
	if((Mem + GramSz) >= End) // NOTE: No next char
	    break;

	next_char NC = {*(Mem + GramSz)};
	
	G.NextChars.push_back(NC);
	++G.TotalNextChars;
	
	++Mem;
    }

    MergeDuplicates();

    ComputeNextCharProbs();    
}
