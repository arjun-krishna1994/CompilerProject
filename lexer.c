// GROUP NUMBER =23
// TEAM 1
// SANCHAY DEWAN -2012A7PS082P
// ARJUN KRISHNA - 2012A7PS030P



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include <ctype.h>

typedef struct {
	char tokenType [100];
	char instance [100];
	int lineNum;
	int scope;

} SymEntry;

int scope  = 0;
int redundant = 0;
int keyword_index;
int other_token_index;

char *keywords[] = {"DOT", "int", "float", "void", "vector", "expression", "main()", "MOD", "CROSS", "return", "sin", "log", "if", "else", "while", "input", "output"};	

char* keywordsTokenType[] = { "tk_dot", "tk_int", "tk_float", "tk_void", "tk_vector","tk_expression", "tk_main\0", "tk_mod", "tk_cross", "tk_return", "tk_sin", "tk_log", "tk_if", "tk_else", "tk_while", "tk_input", "tk_output"};


char* relationalOperators[] = {"==", "<", ">", "!=", "=>", "=<", "!", "="};

char* relOpTokenType[] = {"tk_compare", "tk_lt", "tk_gt", "tk_ne", "tk_gte", "tk_lte", "tk_not", "tk_equals"};

char otherTokens[] = {',', ';', '+', '-', '*', '/', '(', ')', '[', ']'};

char* otherTokenType[] = {"tk_comma", "tk_semicolon", "tk_add", "tk_sub", "tk_mul", "tk_div", "tk_lb", "tk_rb", "tk_lsb", "tk_rsb"};


char words[LIMIT][MAX]; // include identifiers, and keywords
int wordi = 0, wordj = 0;
int wordLineNums[LIMIT];

char strins[LIMIT][MAX]; // to store strings
int strni = 0, strnj=0;
   


char nums[LIMIT][MAX];  // to store numbers
int numi = 0, numj = 0;
int numLineNums[LIMIT];

char logicalOps[LIMIT][3];
int logicalOpi = 0;


char scopingTok[LIMIT][2];
int scopingToi = 0;

char otherTokensInput[LIMIT][2]; // to store other operators
int otherToi = 0;

char relOps[LIMIT][MAX]; // to store keywords
int relOpi = 0, relOpj = 0;

SymEntry symTable[300];
int token_counter = 0;
int sym_counter = 0;
int func_counter = 0;
int func_counter2 = 0;
char funcs[200][30];
char funcs2[200][30];
int found = 0;

int isFunctionDefined2(char *name){
    int i;
    int res = -1;
    for(i = 0; i < func_counter2; i++){
        if (strcmp(funcs2[i], name) == 0){
            res = 0;
        }
    }
    return res;
}
void insertFuncDef2(char *name){
    strcpy(funcs2[func_counter2],name);
    func_counter2++;
}
int isFunctionDefined(char *name){
    int i;
    int res = -1;
    for(i = 0; i < func_counter; i++){
        if (strcmp(funcs[i], name) == 0){
            res = 0;
        }
    }
    return res;
}
void insertFuncDef(char *name){
    strcpy(funcs[func_counter],name);
    func_counter++;
}



int lookupSymTable(char *instance, int sc){
    int i;
    int res = -1;
    for(i = 0; i < sym_counter; i++){
    if (strcmp(symTable[i].instance, instance) == 0){
        //printf("%s\n", "present.");
        /*if(symTable[i].scope == sc || symTable[sym_counter].scope == 0 ){
            res = 0;
        }*/
        if(symTable[i].scope == sc){
            res = 0;
        }
        
    }
    }
    return res;
}

void insertSymTable(char *instance, int sc, int ln, char *tk_type){
    SymEntry se;
    strcpy(se.instance, instance);
    se.scope = sc;
    se.lineNum = ln;
    strcpy(se.tokenType, tk_type);
    symTable[sym_counter] = se;
    sym_counter++;
}

int isStartRelationalOperator(char c) {
	int result = -1; // false
	if (c == '=' || c == '<' || c == '>' || c == '!') {
		result = 1;
	}
	return result;	
}

int isOtherToken(char c) {
	 int i;
	 int result = -1; // false
	 for (i = 0; i < 10; i++) {
		if (otherTokens[i] == c) 
			result = i;
	 }
	 return result;
}



int isKeyword(char *str) {
	int i;
	int result = -1; // false
	for (i = 0; i < 17; i++) {
		if (!strcasecmp(keywords[i], str))
			result = i;
	}
	return result;
}

int isValidStringChar(char c){
	int result = -1;
	if (isalpha(c) || isdigit(c) || c == ' ' || c == '_'){
		result = 1;
	}
	return result;
}



int getTokenStream(FILE *filePtr, TokenStream tk_stream) {
	FILE* filePtr2 = fopen("output_lexer.txt", "w");
    FILE* filePtr3 = fopen("symbol.txt", "w");
    char strnde[10][100];
	int lineNum = 1;	
	char ch;
	char ch1, ch2;
	int i,j,param_count;
	tk_stream.tokens = malloc(400*sizeof(Token));
	fprintf(filePtr3, "%s", ",");
	//printf("%s\n", "INside TkS" );
	while ((ch = fgetc(filePtr)) != EOF) {
		//printf("%c\n", ch );
		if (ch == '\n') {
			lineNum++;
		}

		// Ignore comment starting with // to the end of line
		else if (ch == '/') {
			if (fgetc(filePtr) == '/') {
				while ((ch = fgetc(filePtr)) != '\n') {}
				lineNum++;
			} else
				fseek(filePtr, -1, SEEK_CUR);
		}
		//Detect Keywords, vid, funcid and id tk_stream.tokens.

		else if (isalpha(ch) || ch == '#') {
			
			words[wordi][wordj++] = ch;	
			while (isalpha(ch = fgetc(filePtr)) || isdigit(ch) || ch == '_') {
				words[wordi][wordj++] = ch;	
			}
			
			//words[wordi][wordj] = '\0';	
				
			if (strcmp(words[wordi], "main") == 0)
			{			
				ch1 = ch;
				ch2 = fgetc(filePtr);
				if (ch1 == '(' && ch2 == ')')
				{
					words[wordi][wordj++] = ch1;
					words[wordi][wordj++] = ch2;
					words[wordi][wordj++] = '\0';
					ch = fgetc(filePtr);
				}
			}
			else {
			words[wordi][wordj++] = '\0';
			}
			keyword_index = isKeyword(words[wordi]);
			if (keyword_index != -1)
			{
				tk_stream.tokens[token_counter].lineNum = lineNum;
				strcpy(tk_stream.tokens[token_counter].tokenType , keywordsTokenType[keyword_index]);
				//printf("%s\n", "Words present.");
				strcpy(tk_stream.tokens[token_counter].instance , words[wordi]);
				
				fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].tokenType );
				fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].instance );
				fprintf(filePtr2, ",%d", lineNum );
				fprintf(filePtr2, ",%d", scope);
				
                if (strcmp(tk_stream.tokens[token_counter].tokenType,"tk_main" ) == 0 ){
                    scope++;
                } 
                token_counter += 1;
				
			}
			else  {
					if (words[wordi][0] == 'V'){

								strcpy(tk_stream.tokens[token_counter].tokenType , "vid");
								strcpy(tk_stream.tokens[token_counter].instance , words[wordi]);
								tk_stream.tokens[token_counter].lineNum = lineNum;
								fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].tokenType );
								fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].instance );
								fprintf(filePtr2, ",%d", lineNum );
								fprintf(filePtr2, ",%d", scope);


								if ( lookupSymTable(words[wordi], scope) == -1){
								//printf("%s\n", "INside vid" );
                                fprintf(filePtr3, "%s", "vid,");
                                fprintf(filePtr3, "%s", words[wordi]);
                                fprintf(filePtr3, "%s", ",");
                                fprintf(filePtr3, "%d", lineNum); 
                                fprintf(filePtr3, "%s", ",");
                                fprintf(filePtr3, "%d,", scope);
                                fprintf(filePtr3, "%s,", "tk_vector");
                                insertSymTable(words[wordi], scope, lineNum, "vid");
                                }
								token_counter++;
								
					}
				else if (words[wordi][0] == '#'){
					strcpy(tk_stream.tokens[token_counter].tokenType ,"funcid");
					strcpy(tk_stream.tokens[token_counter].instance , words[wordi]);
					tk_stream.tokens[token_counter].lineNum = lineNum;
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].tokenType );
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].instance );
					fprintf(filePtr2, ",%d", lineNum );
					fprintf(filePtr2, ",%d", scope);
			
					token_counter++;
                    if ( isFunctionDefined2(tk_stream.tokens[i].instance) == -1){
                    	
                    insertFuncDef2(tk_stream.tokens[i].instance);
                    scope++;
                    }
                    else{
                    	//printf("%s\n", tk_stream.tokens[token_counter-1].tokenType);
                    	if(strcmp(tk_stream.tokens[token_counter-2].tokenType, "tk_int")==0 || strcmp(tk_stream.tokens[token_counter-2].tokenType, "tk_float")==0 || strcmp(tk_stream.tokens[token_counter-2].tokenType, "tk_vector")==0 )
                    	{
                    		printf("%s %s %s %d\n", "Error Function", tk_stream.tokens[token_counter-1].instance," overloading at line", lineNum);
                    	}
                    }

					
			
				}
				else
				{
					strcpy(tk_stream.tokens[token_counter].tokenType ,"id");
					strcpy(tk_stream.tokens[token_counter].instance , words[wordi]);
		
					tk_stream.tokens[token_counter].lineNum = lineNum;
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].tokenType );
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].instance );
					fprintf(filePtr2, ",%d", lineNum );
					fprintf(filePtr2, ",%d", scope);
					if (lookupSymTable(words[wordi], scope) == -1){
					j = token_counter;
					
					//printf("%s\n", "INside id" );
                    fprintf(filePtr3, "%s", "id,");
                    fprintf(filePtr3, "%s", words[wordi]);
                    fprintf(filePtr3, "%s", ",");
                    fprintf(filePtr3, "%d", lineNum); 
                    fprintf(filePtr3, "%s", ",");
                    fprintf(filePtr3, "%d,", scope);
                    found = 0;
                    while(strcmp(tk_stream.tokens[j].tokenType,"tk_semicolon") != 0) {
                        if (strcmp(tk_stream.tokens[j].tokenType,"tk_int") == 0 || strcmp(tk_stream.tokens[j].tokenType,"tk_float") == 0){
                            fprintf(filePtr3, "%s,", tk_stream.tokens[j].tokenType);
                            found = 1;
                            break;
                        }
                        j--;
					}
					if (found == 0){
					   //printf("Variable %s undeclared at %d line.", words[wordi], lineNum);
						fprintf(filePtr3, "%s,", "undeclared");
					}
                    
                    
                    insertSymTable(words[wordi], scope, lineNum, "id");
                    }
					token_counter++;
					
					
				}
			}
			wordi++; wordj = 0;
			fseek(filePtr, -1, SEEK_CUR);
		} 
		//detect intliterals, float literals 
		else if (isdigit(ch) || ch == '-') {
			//printf("%s\n", "Int or Float Literals present.");
			nums[numi][numj++] = ch;
			while (isdigit(ch = fgetc(filePtr))) {
				nums[numi][numj++] = ch;
			}
			//nums[numi][numj] = '\0';
			
			numLineNums[numi] = lineNum;
			if (ch == '.'){
				nums[numi][numj++] = ch;
			while(isdigit(ch = fgetc(filePtr))){
				nums[numi][numj++] = ch;
				
			}
			nums[numi][numj++] = '\0';
			strcpy(tk_stream.tokens[token_counter].tokenType , "floatliteral");
			strcpy(tk_stream.tokens[token_counter].instance , nums[numi]);
			tk_stream.tokens[token_counter].lineNum = lineNum;
			fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].tokenType );
			fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].instance );
			fprintf(filePtr2, ",%d", lineNum );
			fprintf(filePtr2, ",%d", scope);
			//printf("%s , %s , %d \n", tk_stream.tokens[token_counter].tokenType ,tk_stream.tokens[token_counter].instance, lineNum );
			token_counter++; 
			
			}
			else{
			nums[numi][numj++] = '\0';
			strcpy(tk_stream.tokens[token_counter].tokenType , "intliteral");
			strcpy(tk_stream.tokens[token_counter].instance , nums[numi]);
			tk_stream.tokens[token_counter].lineNum = lineNum;
			fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].tokenType );
			fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].instance );
			fprintf(filePtr2, ",%d", lineNum );
			fprintf(filePtr2, ",%d", scope);
			//printf("%s , %s , %d \n", tk_stream.tokens[token_counter].tokenType ,tk_stream.tokens[token_counter].instance, lineNum );
			token_counter++; 
			
			}
			//printf("%s \n", "Detecting numbers done." );
			numi++; numj = 0;
			fseek(filePtr, -1, SEEK_CUR);
		}
		//detect string literals
		else if(ch == '\"')
		{
			//printf("%s\n", "STring Present" );
			strins[strni][strnj++] = ch;
			ch = fgetc(filePtr);

			//FIXME while loop stops only the end of the file, throw errors.	
			while( isValidStringChar(ch) != -1)
			{
				//printf("%s \n", "String Present." );
				strins[strni][strnj++] = ch;
				ch = fgetc(filePtr);	
			}
			strins[strni][strnj++] = ch;
			strins[strni][strnj++] = '\0';
			strcpy(tk_stream.tokens[token_counter].tokenType ,"stringliteral");
			strcpy(tk_stream.tokens[token_counter].instance , strins[strni]);
			tk_stream.tokens[token_counter].lineNum = lineNum;
			fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].tokenType );
			fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].instance );
			fprintf(filePtr2, ",%d", lineNum );
			fprintf(filePtr2, ",%d", scope);
			//printf("%s , %s , %d \n", tk_stream.tokens[token_counter].tokenType ,tk_stream.tokens[token_counter].instance, lineNum );
			token_counter++;
			strni++; strnj=0;
			//fseek(filePtr, -1, SEEK_CUR);

			//ch = fgetc(filePtr);
			//printf("%s \n", "Detecting strings done." );
		}		
		//detect relational operators
		else if(isStartRelationalOperator(ch) != -1 ){
			relOps[relOpi][relOpj++] = ch;
			//printf("%s\n","Rel Operator Present" );
			if (ch == '='){
				//check if it is '=='
				if ((ch=fgetc(filePtr)) == '='){
					//printf("%s \n", "Detecting == done." );
					relOps[relOpi][relOpj++] = ch;
					strcpy(tk_stream.tokens[token_counter].tokenType , "tk_compare");
					strcpy(tk_stream.tokens[token_counter].instance , "==");
					tk_stream.tokens[token_counter].lineNum = lineNum;
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].tokenType );
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].instance );
					fprintf(filePtr2, ",%d", lineNum );
					fprintf(filePtr2, ",%d", scope);
					//printf("%s , %s , %d \n", tk_stream.tokens[token_counter].tokenType ,tk_stream.tokens[token_counter].instance, lineNum );
					token_counter++; 
				}
				else{
					fseek(filePtr, -1, SEEK_CUR);
					strcpy(tk_stream.tokens[token_counter].tokenType ,"tk_equals");
					strcpy(tk_stream.tokens[token_counter].instance , "=");
					tk_stream.tokens[token_counter].lineNum = lineNum;
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].tokenType );
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].instance );
					fprintf(filePtr2, ",%d", lineNum );
					fprintf(filePtr2, ",%d", scope);
					
					//printf("%s , %s , %d \n", tk_stream.tokens[token_counter].tokenType ,tk_stream.tokens[token_counter].instance, lineNum );
					token_counter++;
				}
			}
			else if (ch == '>'){
				//relOps[relOpi][relOpj++] = ch;
				ch = fgetc(filePtr);
				//check if it is '>='
				if (ch == '='){
					relOps[relOpi][relOpj++] = ch;
					strcpy(tk_stream.tokens[token_counter].tokenType , "tk_gte");
					strcpy(tk_stream.tokens[token_counter].instance , ">=");
					tk_stream.tokens[token_counter].lineNum = lineNum;
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].tokenType );
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].instance );
					fprintf(filePtr2, ",%d", lineNum );
					fprintf(filePtr2, ",%d", scope);
					//printf("%s , %s , %d \n", tk_stream.tokens[token_counter].tokenType ,tk_stream.tokens[token_counter].instance, lineNum );
					token_counter++;
				}
				//then it is '>'
				else{
					fseek(filePtr, -1, SEEK_CUR); 
					strcpy(tk_stream.tokens[token_counter].tokenType ,"tk_gt");
					strcpy(tk_stream.tokens[token_counter].instance , ">");
					tk_stream.tokens[token_counter].lineNum = lineNum;
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].tokenType );
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].instance );
					fprintf(filePtr2, ",%d", lineNum );
					fprintf(filePtr2, ",%d", scope);
					//printf("%s , %s , %d \n", tk_stream.tokens[token_counter].tokenType ,tk_stream.tokens[token_counter].instance, lineNum );
					token_counter++;
				}
			}
			//check if it is '<' or '<='
			else if (ch == '<'){
				//relOps[relOpi][relOpj++] = ch;
				ch = fgetc(filePtr);
				//check if it is '<='
				if (ch == '='){
					relOps[relOpi][relOpj++] = ch;
					strcpy(tk_stream.tokens[token_counter].tokenType , "tk_lte");
					strcpy(tk_stream.tokens[token_counter].instance , "<=");
					tk_stream.tokens[token_counter].lineNum = lineNum;
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].tokenType );
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].instance );
					fprintf(filePtr2, ",%d", lineNum );
					fprintf(filePtr2, ",%d", scope);
					//printf("%s , %s , %d \n", tk_stream.tokens[token_counter].tokenType ,tk_stream.tokens[token_counter].instance, lineNum );
					token_counter++;
				}
				//then it is '<'
				else{
					fseek(filePtr, -1, SEEK_CUR); 
					strcpy(tk_stream.tokens[token_counter].tokenType , "tk_lt");
					strcpy(tk_stream.tokens[token_counter].instance , "<");
					tk_stream.tokens[token_counter].lineNum = lineNum;
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].tokenType );
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].instance );
					fprintf(filePtr2, ",%d", lineNum );
					fprintf(filePtr2, ",%d", scope);
					//printf("%s , %s , %d \n", tk_stream.tokens[token_counter].tokenType ,tk_stream.tokens[token_counter].instance, lineNum );
					token_counter++;

				}
			}
			//check if it is '!' or '!='
			else if (ch == '!'){
				//relOps[relOpi][relOpj++] = ch;
				ch = fgetc(filePtr);
				//check if it is '!='
				if (ch == '='){
					relOps[relOpi][relOpj++] = ch;
					strcpy(tk_stream.tokens[token_counter].tokenType , "tk_ne");
					strcpy(tk_stream.tokens[token_counter].instance , "!=");
					tk_stream.tokens[token_counter].lineNum = lineNum;
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].tokenType );
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].instance );
					fprintf(filePtr2, ",%d", lineNum );
					fprintf(filePtr2, ",%d", scope);
					//printf("%s , %s , %d \n", tk_stream.tokens[token_counter].tokenType ,tk_stream.tokens[token_counter].instance, lineNum );
					token_counter++;
				}
				//then it is '!'
				else{
					fseek(filePtr, -1, SEEK_CUR); 
					strcpy(tk_stream.tokens[token_counter].tokenType , "tk_not");
					strcpy(tk_stream.tokens[token_counter].instance , "!");
					tk_stream.tokens[token_counter].lineNum = lineNum;
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].tokenType );
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].instance );
					fprintf(filePtr2, ",%d", lineNum );
					fprintf(filePtr2, ",%d", scope);
					//printf("%s , %s , %d \n", tk_stream.tokens[token_counter].tokenType ,tk_stream.tokens[token_counter].instance, lineNum );
					token_counter++;
					
				}
			}
			//printf("%s,%s\n", "Rel",relOps[relOpi] );
			relOpi++;
			relOpj = 0;
			//ch = fgetc(filePtr);
		}
		//Check for logical operators '&&' and '||'
		else if (ch == '&' || ch == '|'){
			//printf("%s\n","logical operators present" );
			logicalOps[logicalOpi][0] = ch;
			//Check for &&
			if (logicalOps[logicalOpi][0] == '&' && ((ch=fgetc(filePtr))=='&')){
					logicalOps[logicalOpi][1] = ch;
					strcpy(tk_stream.tokens[token_counter].tokenType , "tk_and");
					strcpy(tk_stream.tokens[token_counter].instance , "&&");
					tk_stream.tokens[token_counter].lineNum = lineNum;
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].tokenType );
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].instance );
					fprintf(filePtr2, ",%d", lineNum );
					fprintf(filePtr2, ",%d", scope);
					//printf("%s , %s , %d \n", tk_stream.tokens[token_counter].tokenType ,tk_stream.tokens[token_counter].instance, lineNum );
					token_counter++;
			}
			//Check for ||
			if (logicalOps[logicalOpi][0] == '|' && ((ch=fgetc(filePtr))=='|')){
					logicalOps[logicalOpi][1] = ch;
					strcpy(tk_stream.tokens[token_counter].tokenType , "tk_or");
					strcpy(tk_stream.tokens[token_counter].instance , "||");
					tk_stream.tokens[token_counter].lineNum = lineNum;
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].tokenType );
					fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].instance );
					fprintf(filePtr2, ",%d", lineNum );
					fprintf(filePtr2, ",%d", scope);
					//printf("%s , %s , %d \n", tk_stream.tokens[token_counter].tokenType ,tk_stream.tokens[token_counter].instance, lineNum );
					token_counter++;
			}
			//printf("%s%s\n","Logical Op", logicalOps[logicalOpi] );
			logicalOpi++;
			//advance ch
			//ch = fgetc(filePtr);
		}
		//Check for operators which can modify scope i.e '{' and '}'
		else if (ch == '{' || ch == '}'){
			//printf("%s\n", "Scoping token present");
			scopingTok[scopingToi][0] = ch;
			if (ch == '{'){
				strcpy(tk_stream.tokens[token_counter].tokenType , "tk_lcb");
				strcpy(tk_stream.tokens[token_counter].instance , "{");
				tk_stream.tokens[token_counter].lineNum = lineNum;
				fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].tokenType );
				fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].instance );
				fprintf(filePtr2, ",%d", lineNum );
				fprintf(filePtr2, ",%d", scope);
				//printf("%s , %s , %d \n", tk_stream.tokens[token_counter].tokenType ,tk_stream.tokens[token_counter].instance, lineNum );
				token_counter++;
				if ( (strcmp(tk_stream.tokens[token_counter -1].tokenType,"funcid") == 0) || (strcmp(tk_stream.tokens[token_counter - 1].tokenType,"tk_main")==0))				
                    {
                    scope++;
			        }
			}
			if (ch == '}'){
				strcpy(tk_stream.tokens[token_counter].tokenType , "tk_rcb");
				strcpy(tk_stream.tokens[token_counter].instance , "}");
				tk_stream.tokens[token_counter].lineNum = lineNum;
				fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].tokenType );
				fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].instance );
				fprintf(filePtr2, ",%d", lineNum );
				fprintf(filePtr2, ",%d", scope);
				//printf("%s , %s , %d \n", tk_stream.tokens[token_counter].tokenType ,tk_stream.tokens[token_counter].instance, lineNum );
				token_counter++;
			}
			scopingToi++;
			//ch = fgetc(filePtr);

		}

		//Now for all the remaining tk_stream.tokens which are of length 1 '(' , ')', '[', ']'
		//printf("%d \n", isOtherToken(ch));
		else if (isOtherToken(ch) != -1){
			//printf("%s \n","Other Token Present." );
			//printf("%d \n",isOtherToken(ch) );
			otherTokensInput[otherToi][0] = ch;
			otherTokensInput[otherToi][1] = '\0';
			strcpy(tk_stream.tokens[token_counter].tokenType , otherTokenType[isOtherToken(ch)]);
			strcpy(tk_stream.tokens[token_counter].instance , otherTokensInput[otherToi]);
			tk_stream.tokens[token_counter].lineNum  = lineNum;
			fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].tokenType );
			if (strcmp(tk_stream.tokens[token_counter].instance , ",") == 0){
                fprintf(filePtr2, ",%s", "comma" );
                }
            else{
            
			    fprintf(filePtr2, ",%s", tk_stream.tokens[token_counter].instance );
			    }
			fprintf(filePtr2, ",%d", lineNum );
			fprintf(filePtr2, ",%d", scope);
			//printf("%s , %s , %d \n", tk_stream.tokens[token_counter].tokenType ,tk_stream.tokens[token_counter].instance, lineNum );
			token_counter++;
			otherToi++;
		}
	} // end while
	fprintf(filePtr2,"%s", ",");
	//fprintf(filePtr2,"%s", "END");
	for(i=0; i<token_counter; i++)
	{
	    if(strcmp(tk_stream.tokens[i].tokenType,"funcid") == 0){
				    if ( isFunctionDefined(tk_stream.tokens[i].instance) == -1){
					
                    fprintf(filePtr3, "%s", "funcid,");
                    fprintf(filePtr3, "%s", tk_stream.tokens[i].instance);
                    fprintf(filePtr3, "%s", ",");
                    fprintf(filePtr3, "%s,", tk_stream.tokens[i-1].tokenType); 
                    	
                    insertFuncDef(tk_stream.tokens[i].instance);
                    j = i;  
                    param_count = 0;
                    while(strcmp(tk_stream.tokens[j].tokenType,"tk_rb") != 0){
                        if ( strcmp(tk_stream.tokens[j].tokenType,"id")==0 || strcmp(tk_stream.tokens[j].tokenType,"vid")==0){
                        fprintf(filePtr3, "%s", tk_stream.tokens[j-1].tokenType);
                        fprintf(filePtr3, "%s", "~");
                        param_count++;
                        }
                        j++;  
                    }
                    fprintf(filePtr3, ",%d,", param_count);		
                    }
        }
    }
	fclose(filePtr2);
    fclose(filePtr3);
	return token_counter;
}



