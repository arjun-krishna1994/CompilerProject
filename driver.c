// GROUP NUMBER =23
// TEAM 1
// SANCHAY DEWAN -2012A7PS082P
// ARJUN KRISHNA - 2012A7PS030P



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include <ctype.h>
int isExAcceptableChar(char c) {
	if ( c == '(' || c == ')' || c == ',' || c =='{' || c == '}' || c == ';' || c == '[' || c == ']' || "." \
	 || c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>' || c == '!') {

		return 1;
	} else 
		return 0;
}

int main(int argc, char *argv[]) {
	
	TokenStream tk_stream;
	int token_counter = 0;
	char c;
	int numLine = 1;

	int charCount = 0;
	char tempStr[MAX]; // ! Remember: C doesn't do array out-of-bound checking! 
	int i;

	int isValid = 1; // true 
    FILE *filePtr;

    switch (argc) {
        case 1: // No parameters, use stdin
                // printf("NO argument provided\n");
                filePtr = stdin;
                break;

        case 2: // One parameter, use .lan file supplied	
                if ( (filePtr = fopen(strcat(argv[1], ".txt"), "r")) == NULL ) {
                        printf("Cannot open input file.\n");
                        exit(1);
                }
                break;

        default:
                printf("Syntax: scanner [file] (.lan is implicit)\n");
                exit(0);
    }

	fseek(filePtr, 0, SEEK_END);
	if (ftell(filePtr) == 0) {
        printf("File is empty.\n");
        exit(1);
	} else {
        rewind(filePtr);
	}
	while ((c = fgetc(filePtr)) != EOF) {
        if (c == '\n')
                numLine++;

        // Exclude comment line starting with '//' and ending with new line
        if (c == '/') {
                if (fgetc(filePtr) == '/') {
                        while ((c = fgetc(filePtr)) != '\n') {}
                        numLine++;
                }			
        }

        if (isalnum(c)) {
                tempStr[charCount] = c; 
                charCount++;
                if (charCount > MAX) {
                        printf("Word '%s' on line number %d is too long. \n", tempStr, numLine);
                        exit(1);	
                }
        } else if (isspace(c) || isExAcceptableChar(c)) { 
                charCount = 0;
        } else {
                printf("Invalid character '%c' at line %d. \n", c, numLine);
                isValid = 0; // false
        }

	}

	if (isValid == 0) { 
        printf("Something wrong with the input file. \n");
        exit(1);
	}

	rewind(filePtr);
	//printf("%s\n", "Before Token Stream Call");
	token_counter = getTokenStream(filePtr, tk_stream);
	//printf("%s %d \n", "After Token Stream Call", token_counter);
	fclose(filePtr); 
	//i = parseStream();

	/*FILE* filePtr2 = fopen("output_lexer.txt", "w");
	for (i = 0; i < token_counter; i++)
	{
	fprintf(filePtr2, "%s ", tk_stream.tokens[i].tokenType );
	}
	//printf("%d\n", isOtherToken(')') );
	fclose(filePtr2);

	FILE* filePtr3;
	filePtr3 = fopen("output_sym_table.txt", "w");
	for (i = 0; i < token_counter; i++)
	{
		if (tk_stream.tokens[i].tokenType == "id" || tk_stream.tokens[i].tokenType == "vid" || tk_stream.tokens[i].tokenType == "funcid" ){
	fprintf(filePtr3, "< %s , %s,  %d > \n", tk_stream.tokens[i].tokenType, tk_stream.tokens[i].instance, tk_stream.tokens[i].lineNum );
}
	}
	//printf("%d\n", isOtherToken(')') );*/
	//fclose(filePtr3);
	return 0;	

	}
