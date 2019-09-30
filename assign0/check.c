#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ARITHMETICOPERANDS '1'||'2'||'3'||'4'||'5'||'6'||'7'||'8'||'9'||'0'
#define LOGICALOPERANDS  "true" || "false"



//return string length
int strLen (char*str){
    int i = 0;

    while(str[i] != '\0'){
        i++;
    }

    return i;
}

//returns 0 if equal
bool stringEquals(char *s1, char *s2)
{
    char c1 = *s1++;
    char c2 = *s2++;

    while(c1 != '\0' && c2 != '\0') {
        if(c1 != c2) {
            return false;
        }

        c1 = *s1++;
        c2 = *s2++;
    }

    return c1 == '\0' && c2 == '\0';
}

bool isArithmetic(char** tokens) {
    return stringEquals(tokens[1],"-") || stringEquals(tokens[1],"*") 
        || stringEquals(tokens[1],"+") || stringEquals(tokens[1],"/");
}

bool isLogical(char** tokens) {
    return stringEquals(tokens[1], "AND") || stringEquals(tokens[1], "OR");
}



//////////////////////////////////////////////////////////\
//  return string array, from expression                  |
///////////////////////////////////////////////////////////
char** delimSpace(int* numTokens, char *in){

    //1st looop determines how many base indeces
    /*
    int baseIndex = 0;
    int prevSpace = 1;
    int longestToken = 0;
    int latestToken = 0;
    int counter1 = 0;
    while(in[counter1] != '\0'){
        if (in[counter1] != ' ' && prevSpace == 1){
            baseIndex++;
            prevSpace = 0;            
        }
        if (in[counter1] == ' '){
            prevSpace = 1;
            if (longestToken < latestToken){
                int temp = longestToken;
                longestToken = latestToken;
                latestToken = temp;
            }
            latestToken = -1;
        }
        latestToken++;   
        counter1++;
    }
    */

    char** tokens = NULL;
    int index = 0;
    *numTokens = 0;
    int tokenStart = 0;

    while(in[index] != '\0') {
        while(in[index] != ' ' && in[index] != '\0') {
            index++;
        }
        
        if(tokens == NULL) {
            tokens = malloc(sizeof(char*));
        } else {
            tokens = realloc(tokens, (*numTokens + 1) * sizeof(char*));
        }

        char* currToken = malloc((index - tokenStart + 1) * sizeof(char));
        int copyIndex = 0;

        while(copyIndex < index - tokenStart) {
            currToken[copyIndex] = in[tokenStart + copyIndex];
            copyIndex += 1;
        }
        
        if (in[index] == ' '){
            index++;
        }

        tokens[*numTokens] = currToken;
        tokenStart = index;
        (*numTokens)++;
    }

    return tokens;

    /*
    //  creates output
    char** strArr = malloc((baseIndex + 1) * sizeof(char));
    //  2nd loop
    int i = 0;
    bool reachedEndOfLine = false;

    while(!reachedEndOfLine) {
        strArr[baseIndex] = malloc(longestToken*sizeof(char));
        int hiCount = 0;

        while(in[i] != ' ' && in[i] != '\0') {
            strArr[baseIndex][hiCount] = in[i];
            hiCount++;
            i++;
        }
        if(in[i] == '\0') {
            reachedEndOfLine = true;
        }
        i++;
    }

    *numElements = baseIndex + 1;
    return strArr;
    */
}


//////////////////////////////////////////////////////////\
//  return char array (aka expression) and whether hit \0  |
///////////////////////////////////////////////////////////
char* delimSemicolon(int*expressionLen, char*in, int start){
    printf("%x -> %d\n", expressionLen, *expressionLen);
    int index = start;
    *expressionLen = 0;
    //1st loop determine how much space to malloc, continue as long as not ';' and not '\0'
    while(in[index] != ';' &&  in[index] !='\0'){
        (*expressionLen)++;
        index++;
    }

    //creates output, malloced space based off 1st loop
    char* charArr = malloc((*expressionLen+1)*sizeof(char));

    //2nd loop fillin output 
    index = start; 
    int counter = 0;
    while(counter != *expressionLen) {		
        charArr[counter] = in[index];
        counter++;
        index++;
    }

    if(in[index] == '\0'){
        (*expressionLen)--;
    }
    return charArr;

}


//////////////////////////////////////////////////////////\
//  MAIN FUNCTION  |
///////////////////////////////////////////////////////////

int main(int argc, char* argv[]){



    //  initialize variables
    int numElements = 0; // for freeing
    int expressionLen = 0; // length of expression
    int numArithmeticExps = 0;
    int numLogicalExps = 0;

    //  initialize var as input from command line
    char* s = argv[1]; //will hold remainder of original string

    //  loop through expression
    int counter = 0;

    while (s[counter] != '\0'){
        if(s[counter]== ' '){
            counter++;
        }
        char *expression = delimSemicolon(&expressionLen, s, counter);
        counter = counter+expressionLen+1;
        printf("%s\n", expression);
        char **tokens = delimSpace(&numElements, expression);

        if (isLogical(tokens)){
            numLogicalExps++;
        }
        if (isArithmetic(tokens)){
            numArithmeticExps++;
        }

    }

    printf("Found %i expressions, : %i logical and %i arithmetic.\nOK\n", 
            (numLogicalExps + numArithmeticExps), 
            numLogicalExps, 
            numArithmeticExps); 

    //  frees the dynamically allocated mem
    // int i = 0;
    // while(i < numElements) {
    //       free(*(tokens + i));
    //     i++;
    // }
    //	free(tokens);


    return 0;
}


