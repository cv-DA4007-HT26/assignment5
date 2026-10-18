## Description
This project features a language model that generates a text based on an input text file

## Compilation
Call "make"

NOTE: Makefile compiles for a Unix environment by default

## Usage
(From the build directory)

### Standard usage:

`.\slm [k value] [text file] [output character limit]`, where the "k value" is the size of the gram

### With pseudocount:
`.\slm -a [pseudocount] [k value] [text file] [output character limit]`