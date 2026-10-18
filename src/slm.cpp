#include <string>
#include <exception>
#include <stdio.h>

#include "gram_builder.h"
#include "text_generator.h"

struct slm_args
{
    double Pseudocount;
    int GramSz;
    const char *TrainingFileName;
    int CharOutputCount;
};

inline double ExtractPseudocount(char **Args, int &ArgIdx);
slm_args ExtractArgs(int ArgCount, char **Args);

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

//
//
//

inline double ExtractPseudocount(char **Args, int &ArgIdx)
{	
    string A(Args[ArgIdx++]);

    if(A != "-a")
	throw runtime_error("Invalid pseudocount flag");

    double Pseudocount = StringToDouble(Args[ArgIdx++]);

    if(Pseudocount < 0)
	throw runtime_error("Negative pseudocount");

    return Pseudocount;
}

slm_args ExtractArgs(int ArgCount, char **Args)
{
    slm_args A{};
    
    if(!((ArgCount == 4) || (ArgCount == 6)))
	throw runtime_error("Invalid argument count");

    int ArgIdx = 1;
    
    if(ArgCount == 6)
    {
	A.Pseudocount = ExtractPseudocount(Args, ArgIdx);
    }

    A.GramSz = StringToInteger(Args[ArgIdx++]);
    if(A.GramSz < 0)
	throw runtime_error("Invalid gram size");
	
    A.TrainingFileName = Args[ArgIdx++];

    A.CharOutputCount = StringToInteger(Args[ArgIdx++]);
    
    if((A.CharOutputCount < 0) ||
       (A.CharOutputCount < A.GramSz))
    {
	throw runtime_error("Too few characters to output");
    }

    return A;
}
