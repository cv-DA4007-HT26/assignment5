#include <stdlib.h>
#include <string>
#include <fstream>
#include <exception>
#include <stdio.h>
#include <vector>
#include <random>

#include "gram_builder.h"
#include "text_generator.h"

struct slm_args
{
    double Pseudocount;
    size_t GramSz;
    const char *TrainingFileName;
    size_t CharOutputCount;
};

inline double ExtractPseudocount(char **Args, int &ArgIdx)
{	
    string A(Args[ArgIdx++]);

    if(A != "-a")
	throw runtime_error("Invalid pseudocount flag");

    double Pseudocount = stod(Args[ArgIdx++]);

    if(Pseudocount < 0)
	throw runtime_error("Negative pseudocount");

    return Pseudocount;
}

slm_args ExtractArgs(int ArgCount, char **Args)
{
    slm_args A{};
    
    if(!((ArgCount >= 4) && (ArgCount <= 6)))
	throw runtime_error("Invalid argument count");

    int ArgIdx = 1;
    
    if(ArgCount == 6)
    {
	try
	{
	    A.Pseudocount = ExtractPseudocount(Args, ArgIdx);
	}
	catch(const invalid_argument &E)
	{
	    throw invalid_argument("No conversion could be performed");
	}
	catch(const out_of_range &E)
	{
	    throw out_of_range("Pseudocount is larger than a double");
	}
    }

    A.GramSz = atoi(Args[ArgIdx++]);
    if(A.GramSz < 0)
	throw runtime_error("Invalid gram size");
	
    A.TrainingFileName = Args[ArgIdx++];

    A.CharOutputCount = atoi(Args[ArgIdx++]);
    
    if((A.CharOutputCount < 0) ||
       (A.CharOutputCount < A.GramSz))
    {
	throw runtime_error("Too few characters to output");
    }

    return A;
}

int main(int ArgCount, char **Args_)
{
    try
    {
	slm_args Args = ExtractArgs(ArgCount, Args_);
    
	gram_builder Builder;
	Builder.Build(Args.TrainingFileName,
		      Args.GramSz,
		      Args.Pseudocount);
		
	text_generator Generator(Builder);
	Generator.Generate(Args.CharOutputCount, Args.Pseudocount);
    }
    catch(const exception &E)
    {
	fprintf(stderr, "%s\n", E.what());
	return -1;	    
    }
    catch(...)
    {
	fprintf(stderr, "Unknown program error\n");
	return -1;
    }
}
