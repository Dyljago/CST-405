#include "optimizer.h"
#include <stdbool.h>
#include <ctype.h>

void optimizeTAC(TAC** head) {
    constantFolding(head);
    /*
    constantPropagation(head);
    copyPropagation(head);
    deadCodeElimination(head);
    */
}

/**
 * Check if a string represents an integer constant.
 * 
 * @param str The string to check.
 * @return true if the string is an integer constant, false otherwise.
 * 
 * 
 * Functionality:
The function first checks if the input is 'NULL' or an empty string, 
returning 'false' in these cases as they don't represent a valid constant.

If your language supports negative numbers as constants, the function optionally checks 
for a leading - character, skipping it for the subsequent numeric check.

The main part of the function iterates over each character of the string using a while loop. 
For each character, it uses isdigit() to check if it's a numeric digit.

If any character is not a digit, the function immediately returns 'false'.

If the end of the string is reached without encountering any non-digit characters, 
the function returns 'true', indicating the string is a numeric constant.
 */
bool isConstant(const char* str) {
   

    return true; // All characters were digits
}


/**
 * Checks if a string represents a valid variable name according to a simple naming convention.
 * 
 * @param str The string to check.
 * @return true if the string is a valid variable name, false otherwise.
 
Functionality:
-------------
Initially, the function checks if the input is 'NULL' or an empty string, 
returning false in either case since these don't represent valid variable names.

It then checks if the first character is either a letter or an underscore, 
as per the common naming convention that variable names must start with 
an alphabetic character or underscore.

For the rest of the string, the function checks each character to ensure 
it is either a letter, a digit, or an underscore. This loop starts from the second character, 
as the first character's check was already performed.

If any character does not meet these criteria, the function returns 'false'.

If the string passes all checks, it is considered a valid variable name, and the function returns 'true'.
 */
bool isVariable(const char* str) {
    

    return true; // String meets the criteria for a variable name
}



// A simplified constant folding example that only handles addition of integer constants. 
void constantFolding(TAC** head) {
    TAC* current = *head; // Current TAC instruction

    // Apply constant folding optimization
   
}

// A simplified constant propagation example that only handles assignment of integer constants to variables.
void constantPropagation(TAC** head) {
    /*
    This function performs constant propagation on the provided TAC list.
    It iterates through the list and looks for assignments of integer constants to variables.
    When such an assignment is found, it propagates the constant value to all uses of the variable.
    */
    TAC* current = *head;
    
}

// A simplified copy propagation example that only handles assignment of variables to variables.
// This function replaces all uses of a variable with the value of the variable being assigned.
// For example, if the TAC contains "assign x, y", it will replace all uses of "y" with "x".

void copyPropagation(TAC** head) {
    TAC* current = *head;
    
}

// A simplified dead code elimination example that only handles removal of unused assignments.
// This function removes assignments that are not used in any subsequent TAC instructions.
// For example, if the TAC contains "assign x, 5" and "assign y, x", and "x" is not used after that, 
// it will remove the "assign x, 5" instruction.

void deadCodeElimination(TAC** head) {
    TAC* current = *head; // Current TAC instruction
    TAC* prev = NULL;     // Previous TAC instruction

    
}

// Print the optimized TAC list to a file
void printOptimizedTAC(const char* filename, TAC* head) {
    FILE* outputFile = fopen(filename, "w");
  
    printf("Optimized TAC written to %s\n", filename);
    fclose(outputFile);
}

// Print current TAC instruction
void printCurrentOptimizedTAC(TAC* current) {
    
}
