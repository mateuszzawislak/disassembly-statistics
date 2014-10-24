Disassembly Statistics
======================

Statistics of the input, assembly file for selected ranges of addresses.

Motivation
----------
Statistics about registers and constants are useful in the security analysis executable applications.

Description of the expected functionality and algorithm procedure
-------------------

Program parses the input file in the format described below for the selected address ranges to calculate statistics about analyzed code. Output files form will also be discussed below.
The algorothm is divided into two main parts. The first of them `parses` text input file (containing assembly code), resulting in a collection of elements of type *Instruction*. Then, on the basis of this collection, algorithm bilds output file containing statistics about analyzed code.

The file format of input and output
-----------------------------------

Input files for this program will be generated for the test executable programs in PE format using `dumpbin` (available in the VisualStudio environment).

Program will output `.txt` file containing statistics - relating to parsed assembly file - for:
* instruction length,
* instruction opcode,
* used registers,
* the length of constant values ​​(expressed in bytes) used in the instruction.

The data will be presented in the form shown below:

    INSTRUCTION LENGTH
    instructionLength1 : count1
    instructionLength2 : count2
    instructionLength3 : count3
    ...
    OPCODE INSTRUCTION
    opcodeInstruction1 : count1
    opcodeInstruction2 : count2
    opcodeInstruction3 : count3
    ...
    USED REGISTER
    usedRegister1 : count1
    usedRegister2 : count2
    usedRegister3 : count3
    ...
    CONST LENGTH
    constLength1 : count1
    constLength2 : count2
    constLength3 : count3
    ...
