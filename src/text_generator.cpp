#include <string>

#include "gram_builder.h"
#include "util.h"

#include "text_generator.h"

char
text_generator::GetRandomChar(map<char, size_t> &Entries)
{
    if(Entries.empty())
	throw runtime_error("Attempted fetch from empty map");
    
    vec<double> Weights(Entries.size());

    size_t EntryIdx = 0;
    for(const auto &[C, Frequency] : Entries)
    {
	Weights[EntryIdx++] = Frequency;
    }
    
    discrete_distribution<size_t> D(Weights.begin(), Weights.end());

    size_t Index = D(RNG);

    size_t SearchIdx = 0;
    char DesiredChar = 0;
    for(const auto &[C, Frequency] : Entries)
    {
	if(SearchIdx++ == Index)
	{
	    DesiredChar = C;
	    break;
	}
    }
    
    return DesiredChar;
}

void
text_generator::GetRandomGram(gram &G, string &Word)
{
    if(Grams.empty())
	throw runtime_error("No grams to generate text from");

    vec<string> Words;
    vec<double> Weights;

    for(const auto &[W, G] : Grams)
    {
	Words.push_back(W);
	Weights.push_back(G.Frequency);
    }

    discrete_distribution<size_t> D(Weights.begin(), Weights.end());

    size_t Index = D(RNG);
    
    Word = Words[Index];
    G = Grams[Word];    
}

inline bool
text_generator::UpdateGram(gram &ToUpdate, string Word)
{
    auto It = Grams.find(Word);
    
    if(It == Grams.end()) // NOTE: Not in map
	return false;

    ToUpdate = It->second;

    return true;
}

void
text_generator::Generate(size_t CharCountLimit, double Pseudocount)
{
    gram G{};
    string Word{};
    GetRandomGram(G, Word);
    
    fprintf(stdout, "%s", Word.c_str());
    
    size_t CharCount = Word.size();
    while(CharCount < CharCountLimit)
    {    
	char NextChar = GetRandomChar(G.NextChars);

	fprintf(stdout, "%c", NextChar);    
	++CharCount;
    
	string NewWord = Word + NextChar;
	NewWord.erase(NewWord.begin());
	
	if(!UpdateGram(G, NewWord))
	{
	    break;
	}

	Word = NewWord;
    }

    fprintf(stdout, "\n");    
}
