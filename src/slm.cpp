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
    double PseudoCount;
    size_t GramSz;
    const char *TrainingFileName;
    size_t CharOutputCount;
};

inline double ExtractPseudoCount(char **Args, int &ArgIdx)
{	
    string A(Args[ArgIdx++]);

    if(A != "-a")
	throw runtime_error("Invalid pseudocount flag");

    // TODO: This is bad handling. atof returns 0 if no conversion could be done
    double PseudoCount = atof(Args[ArgIdx++]);

    if(PseudoCount < 0)
	throw runtime_error("Negative pseudocount\n");

    return PseudoCount;
}

slm_args ExtractArgs(int ArgCount, char **Args)
{
    slm_args A{};
    
    if(!((ArgCount >= 4) && (ArgCount <= 6)))
	throw runtime_error("Invalid argument count\n");

    int ArgIdx = 1;

    double PseudoCount = 0;
    
    if(ArgCount == 6)
	A.PseudoCount = ExtractPseudoCount(Args, ArgIdx);

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
	Builder.Build(Args.TrainingFileName, Args.GramSz);
		
	text_generator Generator(Builder);
	Generator.Generate(Args.CharOutputCount);
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
