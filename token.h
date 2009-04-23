#define LIMIT  200
#define MAX 8
#define TOKEN_LIMIT 400

typedef struct {
	char tokenType [100];
	char instance [100];
	int lineNum;

} Token;


typedef struct{
Token* tokens;
int token_counter;
} TokenStream;

int getTokenStream(FILE *filePtr, TokenStream tk_stream);
int parseStream();


