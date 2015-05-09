// GROUP NUMBER =23
// TEAM 1
// SANCHAY DEWAN -2012A7PS082P
// ARJUN KRISHNA - 2012A7PS030P


#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>



struct entry_s {
    char *key;
    char *value;
    int declarations;
    int scope;
    char *type;
    char *return_type;
    char *string_of_params;
    int number_of_params;
    int register_count;
    struct entry_s *next;
};
 
typedef struct entry_s entry_t;
 
struct hashtable_s {
    int size;
    struct entry_s **table; 
};
 
typedef struct hashtable_s hashtable_t;
 
 int tot_count=0;

 int total_tk_count=2;

 char str1[1000][1000];

 int main_flag=0;
 
/* Create a new hashtable. */
hashtable_t *ht_create( int size ) {
 
    hashtable_t *hashtable = NULL;
    int i;
 
    if( size < 1 ) return NULL;
 
    /* Allocate the table itself. */
    if( ( hashtable = malloc( sizeof( hashtable_t ) ) ) == NULL ) {
        return NULL;
    }
 
    /* Allocate pointers to the head nodes. */
    if( ( hashtable->table = malloc( sizeof( entry_t * ) * size ) ) == NULL ) {
        return NULL;
    }
    for( i = 0; i < size; i++ ) {
        hashtable->table[i] = NULL;
    }
 
    hashtable->size = size;
 
    return hashtable;   
}
 
/* Hash a string for a particular hash table. */
int ht_hash( hashtable_t *hashtable, char *key) {
 
    unsigned long int hashval;
    int i = 0;
 
    /* Convert our string to an tk_int */
    while( hashval < ULONG_MAX && i < strlen( key ) ) {
        hashval = hashval << 8;
        hashval += key[ i ];
        i++;
    }
 
    return hashval % hashtable->size;
}
 
/* Create a key-value pair. */
entry_t *ht_newpair( char *key, char *value ,int declarations,int scope,char *type,char *return_type,char *string_of_params,int number_of_params,int register_count) {
    entry_t *newpair;
    newpair = malloc( sizeof( entry_t )) ;
    newpair->key =key;
    newpair->value=value;
    newpair->declarations=declarations;
    newpair->scope=scope;
    newpair->type=type;
    newpair->return_type=return_type;
    newpair->string_of_params=string_of_params;
    newpair->number_of_params=number_of_params;
    newpair->register_count=register_count;
 
 
    newpair->next = NULL;
 
    return newpair;
}
 
/* Insert a key-value pair into a hash table. */
void ht_set( hashtable_t *hashtable, char *key, char *value ,int declarations,int scope,char *type,char *return_type,char *string_of_params,int number_of_params,int register_count) {

//printf("I HAVE BEEN CALLED\n");

//printf("my key is %s with declaration %d and scope== %d\n",key,declarations,scope);

    int bin = 0;
    entry_t *newpair = NULL;
    entry_t *next = NULL;
    entry_t *last = NULL;
 
    bin = ht_hash( hashtable, key );
 
    next = hashtable->table[ bin ];
 
    while( next != NULL && next->key != NULL && strcmp( key, next->key ) > 0 ) {
        last = next;
        next = next->next;
    }
 
    /* There's already a pair.  Let's replace that string. */
    if( next != NULL && next->key != NULL && strcmp( key, next->key ) == 0) {
 
        //free( next->value );
        //next->value = strdup( value );
 
    /* Nope, could't find it.  Time to grow a pair. */
    } else {
        newpair = ht_newpair( key, value ,declarations,scope,type,return_type,string_of_params,number_of_params,register_count);
 
        /* We're at the start of the linked list in this bin. */
        if( next == hashtable->table[ bin ] ) {
            newpair->next = next;
            hashtable->table[ bin ] = newpair;
    
        /* We're at the end of the linked list in this bin. */
        } else if ( next == NULL ) {
            last->next = newpair;
    
        /* We're in the middle of the list. */
        } else  {
            newpair->next = next;
            last->next = newpair;
        }
    }
}


 
/* Retrieve a key-value pair from a hash table. */
entry_t *ht_get( hashtable_t *hashtable, char *key) {

//printf("I GET STUFF\n\n");

//printf("My KEY IS %s\n",key);

    int bin = 0;
    entry_t *pair;
 
    bin = ht_hash( hashtable, key );
 
    /* Step through the bin, looking for our value. */
    pair = hashtable->table[ bin ];
    while( pair != NULL && pair->key != NULL && strcmp( key, pair->key ) > 0 ) {
        pair = pair->next;
    }
 
    /* Did we actually find anything? */
    if( pair == NULL || pair->key == NULL || strcmp( key, pair->key ) != 0 ) {
        return NULL;
 
    } else {
        return pair;
    }
    
}
 
hashtable_t *hashtable;

//using namespace std;

typedef struct Node
{
    int value;
    int countofchildren;
    struct Node *parent;
    struct Node *child[7];
    struct Node *next;
    struct Node *prev;
    int scope;
    int declaration;
    int code_generated;
    char* key;
} Node;

typedef Node * node;


Node* AddChild(node old,int val,int childnumber)
{
    // printf()
    node x = (Node*)malloc(sizeof(Node));
    x->parent = old;
    old->countofchildren++;
    old->child[childnumber-1]=x;
    int i;
    for(i=0;i<7;i++){
        x->child[i] = NULL;
    }
    x->prev = NULL;
    x->next = NULL;
    
    //  strcpy(x->value, value);
    x->value=val;
    x->code_generated=0;
    old->child[childnumber-1] = (x);
    return (old->child[childnumber-1]);
}


typedef struct Entry
{
    int value;
    struct Entry *next;
} Entry;

typedef Entry* entry;

typedef struct Stack
{
    entry top;
    int length;
} Stack;

typedef Stack* stack;

Stack *Push(stack s, int value)
{
    entry k = (Entry *)malloc(sizeof(Entry));
    //strcpy(k->value, value);
    k->value=value;
    k->next = s->top;
    s->top = k;
    s->length++;
    return s;
}

Stack *Pop(stack s)
{
    entry temp = s->top;
    s->top = s->top->next;
    s->length--;
    free(temp);
    return s;
}

void upon_83(node a,node left_child);
char *upon_73(node a);
char *upon_75(node a);

int moved[15];

void preorder_for_code_generation(node p,FILE *fp);
void code_generation_93(node a,FILE *fp);
void code_generation_73(node a,FILE *fp);
void code_generation_71(node a,FILE *fp);
void code_generation_75(node a,FILE *fp);
void code_generation_83(node a,FILE *fp,node lc,node rc);
void code_generation_83_vector(node a,FILE *fp);
void code_generation_83_vectors(node a,FILE *fp);
void code_generation(node root,FILE *temp_files);


int label_count=1;
int register_count=0;
int while_flag=0;
int vcount=0;
node tempv1,tempv2,tempv3,tempv4,tempv5,tempv6;

void formsymboltable(){
int q;

hashtable = ht_create( 65536 );

//FILE *ptr_files;
FILE *ptr_files=fopen("symbol.txt","r");
int c;
            int i=0;

            int count=0;
             
             
            

    while ((c=fgetc(ptr_files))!=EOF){

                char buf[100];


                //int c=buf;
               // printf("%d\n",buf);
               // if(buf==ff){
               // }else{
//printf("%d\n",c);
                if(c!=44 && c!=15){
                        buf[i]=c;
                        //tokenn[count][i]=c;
                        i++;
                       // printf("%c\n",buf[i-1]);

                }
              //  else if(c==44){
                //    printf("ENTER\n");
                //}
                else{

                    tot_count++;
                           
                       //    printf("%s\n",buf);

                   // int e=70-i;
                    
                            strcpy(str1[count],buf);
                            
                            
                            
                            int k=0;
                            for(k=0;k<=100;k++){
                                    buf[k]=0;
                                }
                    i=0;
                    count++;
                 //   printf("count == %d\n",count);

                }
//                if((count)%4==0){

  //                   printf("YAY\n");

     //           }
          }

          

       fclose(ptr_files);

tot_count--;

//ht_set( hashtable, "key1", "inky" ,5,8);


for( q=1;q<tot_count;q=q+5){

//char tt=str1[q+2][0];
//printf("%c\n",tt);

if(strcmp(str1[q],"funcid")==0){

entry_t *a=ht_get(hashtable,str1[q+1]);
if(a==NULL){
   // printf("\nYOYO\n");
   // printf("%s\n",str1[q+1]);
    int kk=str1[q+4][0]-'0';
    ht_set(hashtable,str1[q+1],str1[q],NULL,NULL,NULL,str1[q+2],str1[q+3],kk,NULL);
}
else{
    printf("\n <<<<<<<<<<<<<      FUNCTION OVERLOADING NOT ALLOWED !!! >>>>>>>>>>>>>>\n");
}

//ht_set(str1[q+1],str1[q],NULL,NULL,NULL,str1[q+2]);

}
else{
int pp=str1[q+2][1]-'0';
//printf("pp == %d\n",pp);

int rr=str1[q+2][0]-'0';
//printf("%d\n",rr);
int declaration=0;
if(pp<0){
declaration=rr;
}
else{
   declaration=rr*10 +pp; 
}


pp=str1[q+3][1]-'0';
//printf("pp == %d\n",pp);

rr=str1[q+3][0]-'0';
//printf("%d\n",rr);
int scope=0;
if(pp<0){
scope=rr;
}
else{
   scope=rr*10 +pp; 
}

//int declaration= rr*10 + str1[q+2][1] -'0';
//printf("scope == %d\n",scope);

//if((strcmp(str1[q],"funcid"))!=0){

//printf("%s\n",str1[q+1]);
char str4[4];
sprintf(str4,"%d",scope);
//strcpy(str4,"XX");

strcat(str1[q+1],str4);




entry_t *a=ht_get(hashtable,str1[q+1]);
if(a==NULL){
   // printf("\nYOYO\n");
   // printf("%s\n",str1[q+1]);
    ht_set(hashtable,str1[q+1],str1[q],declaration,scope,str1[q+4],NULL,NULL,NULL,register_count);
    register_count++;
}
else{
    printf("\n <<<<<<<<<<<<<      SEMANTIC ERROR in line %d as %s has been already been declared before in line %d >>>>>>>>>>>>>>\n",declaration,a->key,a->declarations);
}

}

}


//printf("tot count== %d\n",tot_count);

//printf("count== %d\n",count);
//entry_t *aa=ht_get(hashtable,str1[14]);
 //printf("ggg gg gg  %d\n",aa->declarations);
//  ht_set( hashtable, "key1", "inky" ,5);
int l;
for(l=2;l<tot_count;l=l+5){
    entry_t *a=ht_get(hashtable,str1[l]);
    if((strcmp(a->value,"id")==0) || (strcmp(a->value,"vid")==0)){
    printf("my key is %s, I belong to token %s and I have been declared in %d with scope==%d and type==%s\n",a->key,a->value,a->declarations,a->scope,a->type);
 // printf("%d\n",ht_get(hashtable,str1[6]));
 }
 else if(strcmp(a->value,"funcid")==0){

printf("my key is %s, I belong to token %s , with return type %s , with string of params as %s and number of params as %d\n",a->key,a->value,a->return_type,a->string_of_params,a->number_of_params);

 }
}


}

//
//Node* AddNext( node curr,node next)
//{
//
////    node y = (Node*)malloc(sizeof(Node));
//    y->parent = NULL;
//    y->child = NULL;
//    y->prev = prev;
//    y->next = NULL;
//   // strcpy(y->value, value);
//    prev->next = (y);
//    return y;
//}
//

void preorder(node p);
void traversalForAST(node p);

char tokenss[70][70];

char register_name[4][4];

int main(int argc,char *argv[]){



    
    //string tokens[];
    // const char *tokenss[]
    // ={"tk_int","funcid","tk_lb","tk_int","id","tk_comma","tk_float","id","tk_rb","tk_lcb","tk_return","id","tk_semicolon","tk_rcb","tk_main","tk_lcb","tk_int","id","tk_comma","id","tk_semicolon","id","tk_equals","intliteral","tk_semicolon","id","tk_equals","floatliteral","tk_semicolon","tk_if","tk_lb","id","tk_compare","id","tk_rb","tk_lcb","id","tk_equals","funcid","tk_lb","id","tk_comma","id","tk_rb","tk_semicolon","tk_rcb","tk_else","tk_lcb","id","tk_equals","floatliteral","tk_semicolon","tk_rcb","tk_rcb","$"};
    
printf("   \n   SYMBOL TABLE :-  \n\n");


    formsymboltable();

    strcpy(register_name[0],"ax");
    strcpy(register_name[1],"bx");
    strcpy(register_name[2],"cx");
    strcpy(register_name[3],"dx");


    //printf("NO PROB\n");
    
    FILE *ptr_file;
            
//FILE *output_file=fopen("PARSERSS.txt","w");    

FILE *output_file;

output_file=fopen(argv[2],"w");


         //   char ff=NULL;
            int c;
            int iii=0;

            int count=0;
             
             if(argc<=2){
                printf("Filename not given , specify both input and output file names\n");
                return 1;

             }
else{
            ptr_file =fopen(argv[1],"r");

        }

           int iiz=0;

  //          int count=0;
             
             char str11[1000][1000];
            

    while ((c=fgetc(ptr_file))!=EOF){

                char buf[100];
            
               if(c!=44 && c!=15){
                        buf[iiz]=c;
                        //tokenn[count][i]=c;
                        iiz++;
                       // printf("%c\n",buf[i-1]);

                }
              else{
           strcpy(str11[count],buf);

          //printf("At count== %d string == %s\n",count,str11[count]);
                            int k=0;
                            for(k=0;k<=100;k++){
                                    buf[k]=0;
                                }
                    iiz=0;
                    count++;
                }
}
 

int bc=(count-1)/4;
int iee;
       for(iee=0;iee<bc;iee++){
        strcpy(tokenss[iee],str11[(4*iee)+1]);
       // printf("%s\n",str11[(4*iee)+1]);
       }
    strcpy(tokenss[bc],"$$");
         fclose(ptr_file);
    
    
    char tokens[50][50];
    
    strcpy(tokens[0],"tk_comma");
    strcpy(tokens[1],"tk_dot");
    strcpy(tokens[2],"tk_semicolon");
    strcpy(tokens[3],"tk_add");
    strcpy(tokens[4],"tk_sub");
    strcpy(tokens[5],"tk_mul");
    strcpy(tokens[6],"tk_div");
    strcpy(tokens[7],"tk_int");
    strcpy(tokens[8],"tk_float");
    strcpy(tokens[9],"tk_void");
    strcpy(tokens[10],"tk_vector");
    strcpy(tokens[11],"tk_expression");
    strcpy(tokens[12],"tk_main");
    strcpy(tokens[13],"tk_equals");
    strcpy(tokens[14],"tk_mod");
    strcpy(tokens[15],"tk_cross");
    strcpy(tokens[16],"tk_and");
    strcpy(tokens[17],"tk_or");
    strcpy(tokens[18],"tk_return");
    strcpy(tokens[19],"tk_sin");
    strcpy(tokens[20],"tk_log");
    strcpy(tokens[21],"tk_if");
    strcpy(tokens[22],"tk_else");
    strcpy(tokens[23],"tk_while");
    strcpy(tokens[24],"tk_input");
    strcpy(tokens[25],"tk_output");
    strcpy(tokens[26],"tk_not");
    strcpy(tokens[27],"tk_gt");
    strcpy(tokens[28],"tk_gte");
    strcpy(tokens[29],"tk_lt");
    strcpy(tokens[30],"tk_ne");
    strcpy(tokens[31],"tk_lte");
    strcpy(tokens[32],"tk_compare");
    strcpy(tokens[33],"tk_lb");
    strcpy(tokens[34],"tk_rb");
    strcpy(tokens[35],"tk_lsb");
    strcpy(tokens[36],"tk_rsb");
    strcpy(tokens[37],"tk_lcb");
    strcpy(tokens[38],"tk_rcb");
    strcpy(tokens[39],"id");
    strcpy(tokens[40],"vid");
    strcpy(tokens[41],"funcid");
    strcpy(tokens[42],"intliteral");
    strcpy(tokens[43],"floatliteral");
    strcpy(tokens[44],"stringliteral");
    strcpy(tokens[45],"vectorliteral");
    strcpy(tokens[46],"$$");
    
    
    
    const char *table[100][47];
    int state[120][7][47];    // 5 represents no of non-terminlas to the right hand side.
    
    int i,j,k;
    
    
    for(i=0;i<120;i++){
        for(j=0;j<7;j++){
            for(k=0;k<47;k++){
                state[i][j][k]=-1;
            }
        }
    }

    int ert;

    for(ert=0;ert<10;ert++){
        moved[ert]=0;
    }
    
    //  memset(state,-1,sizeof(state)); // so as to specify stopping condition i.e while state[i][j]! =-1
    
    table[0][7]="<program>--> <functions><mainfunction>"; // only useful when printing.
    table[0][8]="<program>--> <functions><mainfunction>";
    table[0][9]="<program>--> <functions><mainfunction>";
    table[0][10]="<program>--> <functions><mainfunction>";
    table[0][12]="<program>--> <functions><mainfunction>";
    
    table[1][7]="<functions>--> <function><functions>";
    table[1][8]="<functions>--> <function><functions>";
    table[1][9]="<functions>--> <function><functions>";
    table[1][10]="<functions>--> <function><functions>";
    table[1][12]="<functions>--> e";     // 2 OR MORE POSSIBILITIES....
    // table[2]="<function>--> <funsign><functionbody>";
    
    
    table[2][7]="<function>--> <funsign><functionbody>";
    table[2][8]="<function>--> <funsign><functionbody>";
    table[2][9]="<function>--> <funsign><functionbody>";
    table[2][10]="<function>--> <funsign><functionbody>";
    
    table[3][7]="<funsign>--> <ret_type>funcid tk_lb <params> tk_rb";
    table[3][8]="<funsign>--> <ret_type>funcid tk_lb <params> tk_rb";
    table[3][9]="<funsign>--> <ret_type>funcid tk_lb <params> tk_rb";
    table[3][10]="<funsign>--> <ret_type>funcid tk_lb <params> tk_rb";
    
    table[4][7]="<ret_type>--> tk_int";
    table[4][8]="<ret_type>--> tk_float";
    table[4][9]="<ret_type>--> tk_void";
    table[4][10]="<ret_type>--> tk_vector";
    
    table[5][7]="<params>--> <type>id<param2>";
    table[5][8]="<params>--> <type>id<param2>";
    table[5][10]="<params>--> tk_vector vid<param2>";
    table[5][11]="<params>--> <type>id<param2>";
    table[5][34]="<params>--> e";
    
    
    table[6][0]="<param2>--> tk_comma<param3>";
    table[6][34]="<param2>--> e";
    
    table[7][7]="<param3>--> <type>id<param2>";
    table[7][8]="<param3>--> <type>id<param2>";
    table[7][10]="<param3>--> tk_vector vid<param2>";
    table[7][11]="<param3>--> <type>id<param2>";
    
    
    table[8][7]="<type>--> tk_int";
    table[8][8]="<type>--> tk_float";
    table[8][11]="<type>--> tk_expression";
    
    table[9][12]="<mainfunction>--> tk_main<functionbody>";
    
    table[10][37]="<functionbody>--> tk_lcb <declarations><statements>tk_rcb";
    
    table[11][7]="<declarations>--> <type><idlist><declarations>";
    table[11][8]="<declarations>--> <type><idlist><declarations>";
    table[11][10]="<declarations>--> tk_vector<veclist><declarations>";
    table[11][11]="<declarations>--> <type><idlist><declarations>";
    table[11][18]="<declarations>--> e";
    table[11][21]="<declarations>--> e";
    table[11][23]="<declarations>--> e";
    table[11][24]="<declarations>--> e";
    table[11][25]="<declarations>--> e";
    table[11][38]="<declarations>--> e";
    table[11][39]="<declarations>--> e";
    table[11][40]="<declarations>--> e";
    table[11][41]="<declarations>--> e";
    
    table[12][39]="<idlist>--> id<idlist2>";
    
    table[13][0]="<idlist2>--> tk_comma id<idlist2>";
    table[13][2]="<idlist2>--> tk_semicolon";
    
    table[14][40]="<idlist>--> vid<idlist3>";
    
    table[15][0]="<idlist3>--> tk_comma vid<idlist3>";
    table[15][2]="<idlist3>--> tk_semicolon";
    
    table[16][18]="<statements>--> <statement><statements>";
    table[16][18]="<statements>--> <statement><statements>";
    table[16][21]="<statements>--> <statement><statements>";
    table[16][23]="<statements>--> <statement><statements>";
    table[16][24]="<statements>--> <statement><statements>";
    table[16][25]="<statements>--> <statement><statements>";
    table[16][38]="<statements>--> e";
    table[16][39]="<statements>--> <statement><statements>";
    table[16][40]="<statements>--> <statement><statements>";
    table[16][41]="<statements>--> <statement><statements>";
    
    table[17][18]="<statement>--> <returnstmt>";
    table[17][21]="<statement>--> <selection>";
    table[17][23]="<statement>--> <iteration>";
    table[17][24]="<statement>--> <iostmt>";
    table[17][25]="<statement>--> <iostmt>";
    table[17][39]="<statement>--> <assignment>";
    table[17][40]="<statement>--> <assignment>";
    table[17][41]="<statement>--> <ifunccall>";
    
    table[18][41]="<funccall>--> funcid<more> tk_semicolon";
    
    table[19][14]="<scalarexp>--> <scalarexp1>";
    table[19][19]="<scalarexp>--> tk_sin tk_lb<scalarexp1>tk_rb";
    table[19][20]="<scalarexp>--> tk_log tk_lb<scalarexp1>tk_rb";
    table[19][33]="<scalarexp>--> <scalarexp1>";
    table[19][39]="<scalarexp>--> <scalarexp1>";
    table[19][40]="<scalarexp>--> <scalarexp1>";
    table[19][42]="<scalarexp>--> <scalarexp1>";
    table[19][43]="<scalarexp>--> <scalarexp1>";
    table[19][45]="<scalarexp>--> <scalarexp1>";
    
    table[20][14]="<scalarexp1>--> tk_mod tk_lb<vectorexp>tk_rb";
    table[20][33]="<scalarexp1>--> <scalarexp2> <scalarexp10>";
    table[20][39]="<scalarexp1>--> <scalarexp2> <scalarexp10>";
    table[20][40]="<scalarexp1>--> <vectorexp>tk_dot <vectorexp>";
    table[20][42]="<scalarexp1>--> <scalarexp2> <scalarexp10>";
    table[20][43]="<scalarexp1>--> <scalarexp2> <scalarexp10>";
    table[20][45]="<vectorexp>tk_dot<vectorexp>";
    
    table[21][2]="<scalarexp10>--> e";
    table[21][3]="<scalarexp10>--> tk_add <scalarexp2>";
    table[21][14]="<scalarexp10>--> e";
    table[21][19]="<scalarexp10>--> e";
    table[21][20]="<scalarexp10>--> e";
    table[21][33]="<scalarexp10>--> e";
    table[21][34]="<scalarexp10>--> e";
    table[21][36]="<scalarexp10>--> e";
    table[21][39]="<scalarexp10>--> e";
    table[21][40]="<scalarexp10>--> e";
    table[21][42]="<scalarexp10>--> e";
    table[21][43]="<scalarexp10>--> e";
    table[21][45]="<scalarexp10>--> e";
    
    table[22][33]="<scalarexp2>--> <mulexp> <scalarexp3>";
    table[22][39]="<scalarexp2>--> <mulexp> <scalarexp3>";
    table[22][42]="<scalarexp2>--> <mulexp> <scalarexp3>";
    table[22][43]="<scalarexp2>--> <mulexp> <scalarexp3>";
    
    table[23][2]="<scalarexp3>--> e";
    table[23][3]="<scalarexp3>--> e";
    table[23][4]="<scalarexp3>--> tk_sub <scalarexp2>";
    table[23][14]="<scalarexp3>--> e";
    table[23][19]="<scalarexp3>--> e";
    table[23][20]="<scalarexp3>--> e";
    table[23][33]="<scalarexp3>--> e";
    table[23][34]="<scalarexp3>--> e";
    table[23][36]="<scalarexp3>--> e";
    table[23][39]="<scalarexp3>--> e";
    table[23][40]="<scalarexp3>--> e";
    table[23][42]="<scalarexp3>--> e";
    table[23][43]="<scalarexp3>--> e";
    table[23][45]="<scalarexp3>--> e";
    
    table[24][33]="<mulexp>--> <divexp> <mulexp2>";
    table[24][39]="<mulexp>--> <divexp> <mulexp2>";
    table[24][42]="<mulexp>--> <divexp> <mulexp2>";
    table[24][43]="<mulexp>--> <divexp> <mulexp2>";
    
    
    table[25][2]="<mulexp2>--> e";
    table[25][3]="<mulexp2>--> e";
    table[25][4]="<mulexp2>--> e";
    table[25][5]="<mulexp2>--> tk_mul<divexp>";
    table[25][14]="<mulexp2>--> e";
    table[25][19]="<mulexp2>--> e";
    table[25][20]="<mulexp2>--> e";
    table[25][33]="<mulexp2>--> e";
    table[25][34]="<mulexp2>--> e";
    table[25][36]="<mulexp2>--> e";
    table[25][39]="<mulexp2>--> e";
    table[25][40]="<mulexp2>--> e";
    table[25][42]="<mulexp2>--> e";
    table[25][43]="<mulexp2>--> e";
    table[25][45]="<mulexp2>--> e";
    
    
    table[26][33]="<divexp>--> <rootexp> <divexp2>";
    table[26][39]="<divexp>--> <rootexp> <divexp2>";
    table[26][42]="<divexp>--> <rootexp> <divexp2>";
    table[26][43]="<divexp>--> <rootexp> <divexp2>";
    
    table[27][2]="<divexp2>--> e";
    table[27][3]="<divexp2>--> e";
    table[27][4]="<divexp2>--> e";
    table[27][5]="<divexp2>--> e";
    table[27][6]="<divexp2>--> tk_div <rootexp>";
    table[27][14]="<divexp2>--> e";
    table[27][19]="<divexp2>--> e";
    table[27][20]="<divexp2>--> e";
    table[27][33]="<divexp2>--> e";
    table[27][34]="<divexp2>--> e";
    table[27][36]="<divexp2>--> e";
    table[27][39]="<divexp2>--> e";
    table[27][40]="<divexp2>--> e";
    table[27][42]="<divexp2>--> e";
    table[27][43]="<divexp2>--> e";
    table[27][45]="<divexp2>--> e";
    
    table[28][33]="<rootexp>--> tk_lb<scalarexp>tk_rb";
    table[28][39]="<rootexp>--> id";
    table[28][42]="<rootexp>--> intliteral";
    table[28][43]="<rootexp>--> floatliteral";
    
    table[29][40]="<vectorexp>--> <vectorexp2> <vectorexp10>";
    table[29][45]="<vectorexp>--> <vectorexp2> <vectorexp10>";
    
    table[30][1]="<vectorexp10>--> e";
    table[30][2]="<vectorexp10>--> e";
    table[30][14]="<vectorexp10>--> e";
    table[30][15]="<vectorexp10>--> tk_cross <vectorexp2>";
    table[30][19]="<vectorexp10>--> e";
    table[30][20]="<vectorexp10>--> e";
    table[30][33]="<vectorexp10>--> e";
    table[30][34]="<vectorexp10>--> e";
    table[30][36]="<vectorexp10>--> e";
    table[30][39]="<vectorexp10>--> e";
    table[30][40]="<vectorexp10>--> e";
    table[30][42]="<vectorexp10>--> e";
    table[30][43]="<vectorexp10>--> e";
    table[30][45]="<vectorexp10>--> e";
    
    table[31][40]="<vectorexp2>--> <vectorexp3> <vectorexp11>";
    table[31][45]="<vectorexp2>--> <vectorexp3> <vectorexp11>";
    
    table[32][1]="<vectorexp11>--> e";
    table[32][2]="<vectorexp11>--> e";
    table[32][3]="<vectorexp11>--> tk_add<vectorexp3>";
    table[32][14]="<vectorexp11>--> e";
    table[32][15]="<vectorexp11>--> e";
    table[32][19]="<vectorexp11>--> e";
    table[32][20]="<vectorexp11>--> e";
    table[32][33]="<vectorexp11>--> e";
    table[32][34]="<vectorexp11>--> e";
    table[32][36]="<vectorexp11>--> e";
    table[32][39]="<vectorexp11>--> e";
    table[32][40]="<vectorexp11>--> e";
    table[32][42]="<vectorexp11>--> e";
    table[32][43]="<vectorexp11>--> e";
    table[32][45]="<vectorexp11>--> e";
    
    table[33][40]="<vectorexp3>--> vid";
    table[33][45]="<vectorexp3>--> vectorliteral";
    
    table[34][39]="<assignment>--> <normalass>";
    table[34][40]="<assignment>--> <vectorass>";
    
    table[35][40]="<vectorass>--> vid tk_equal <vectorass2>";
    
    table[36][35]="<vectorass2>--> tk_lsb<etype> <etype> <etype>tk_rsb tk_semicolon";
    table[36][40]="<vectorass2>--> <vectorexp>tk_semi_colon";
    table[36][41]="<vectorass2>--> funcid<more>tk_semi_colon";
    table[36][45]="<vectorass2>--> <vectorexp>tk_semi_colon";
    
    table[37][14]="<etype>--> <scalarexp>";
    table[37][19]="<etype>--> <scalarexp>";
    table[37][20]="<etype>--> <scalarexp>";
    table[37][33]="<etype>--> <scalarexp>";
    table[37][39]="<etype>--> <scalarexp>";
    table[37][40]="<etype>--> <scalarexp>";
    table[37][42]="<etype>--> <scalarexp>";
    table[37][43]="<etype>--> <scalarexp>";
    table[37][45]="<etype>--> <scalarexp>";
    
    table[38][33]="<more>--> tk_lb <list>tk_rb";
    
    table[39][34]="<list>--> e";
    table[39][39]="<list>--> id<list2>";
    table[39][40]="<list>--> vid<list2>";
    
    table[40][0]="<list2>--> tk_comma <list10>";
    table[40][34]="<list2>--> e";
    
    table[41][39]="<list10>--> id<list2>";
    table[41][40]="<list10>--> vid<list2>";
    
    table[42][39]="<normalass>--> id tk_equal <normalass2>";
    
    table[43][14]="<normalass2>--> <scalarexp>tk_semi_colon";
    table[43][19]="<normalass2>--> <scalarexp>tk_semi_colon";
    table[43][20]="<normalass2>--> <scalarexp>tk_semi_colon";
    table[43][33]="<normalass2>--> <scalarexp>tk_semi_colon";
    table[43][39]="<normalass2>--> <scalarexp>tk_semi_colon";
    table[43][40]="<normalass2>--> <scalarexp>tk_semi_colon";
    table[43][41]="<normalass2>--> funcid<more>tk_semi_colon";
    table[43][42]="<normalass2>--> <scalarexp>tk_semi_colon";
    table[43][43]="<normalass2>--> <scalarexp>tk_semi_colon";
    table[43][45]="<normalass2>--> <scalarexp>tk_semi_colon";
    
    table[44][18]="<returnstmt>--> tk_return  <returnstmt2>";
    
    table[45][39]="<returnstmt2>--> id tk_semi_colon";
    table[45][40]="<returnstmt2>--> vid tk_semi_colon";
    
    table[46][24]="<iostmt>--> <instmt>";
    table[46][25]="<iostmt>--> <outstmt>";
    
    table[47][25]="<outstmt>--> tk_output tk_lb<displaylist>tk_rb tk_semi_colon";
    
    table[48][39]="<displaylist>--> id<dlist2>";
    table[48][40]="<displaylist>--> vid<dlist2>";
    table[48][44]="<displaylist>--> stringliteral<dlist2>";
    
    table[49][0]="<dlist2>--> tk_comma <dlist3>";
    
    table[50][34]="<dlist3>--> e";
    table[50][39]="<dlist3>--> id<dlist2>";
    table[50][40]="<dlist3>--> vid<dlist2>";
    table[50][44]="<dlist3>--> stringliteral<dlist2>";
    
    table[51][24]="<instmt>--> tk_input tk_lb <inlist>tk_rb tk_semi_colon";
    
    table[52][44]="<inlist>--> stringliteral tk_comma <inlist2>";
    
    table[53][39]="<inlist2>--> id";
    table[53][40]="<inlist2>--> vid";
    
    table[54][26]="<condexp>--> <unaryexp> <condexp2>";
    table[54][39]="<condexp>--> <unaryexp> <condexp2>";
    table[54][40]="<condexp>--> vid tk_compare vid";
    table[54][42]="<condexp>--> <unaryexp> <condexp2>";
    table[54][43]="<condexp>--> <unaryexp> <condexp2>";
    
    table[55][16]="<condexp2>--> <binaryop><unaryexp>";
    table[55][17]="<condexp2>--> <binaryop><unaryexp>";
    table[55][27]="<condexp2>--> <binaryop><unaryexp>";
    table[55][28]="<condexp2>--> <binaryop><unaryexp>";
    table[55][29]="<condexp2>--> <binaryop><unaryexp>";
    table[55][30]="<condexp2>--> <binaryop><unaryexp>";
    table[55][31]="<condexp2>--> <binaryop><unaryexp>";
    table[55][32]="<condexp2>--> <binaryop><unaryexp>";
    table[55][34]="<condexp2>--> e";
    table[55][38]="<condexp2>--> e";
    
    table[56][26]="<unaryexp>--> tk_not <unaryexp>";
    table[56][33]="<unaryexp>--> <primaryexp>";
    table[56][39]="<unaryexp>--> <primaryexp>";
    table[56][42]="<unaryexp>--> <primaryexp>";
    table[56][43]="<unaryexp>--> <primaryexp>";
    
    
    table[57][16]="<binaryop>--> tk_and";
    table[57][17]="<binaryop>--> tk_or";
    table[57][27]="<binaryop>--> <rel_op>";
    table[57][28]="<binaryop>--> <rel_op>";
    table[57][29]="<binaryop>--> <rel_op>";
    table[57][30]="<binaryop>--> <rel_op>";
    table[57][31]="<binaryop>--> <rel_op>";
    table[57][32]="<binaryop>--> <rel_op>";
    
    table[58][27]="<rel_op>--> tk_gt";
    table[58][28]="<rel_op>--> tk_gte";
    table[58][29]="<rel_op>--> tk_lt";
    table[58][30]="<rel_op>--> tk_ne";
    table[58][31]="<rel_op>--> tk_lte";
    table[58][32]="<rel_op>--> tk_compare";
    
    table[59][33]="<primaryexp>--> tk_lb <condexp> tk_rb";
    table[59][39]="<primaryexp>--> id";
    table[59][42]="<primaryexp>--> intliteral";
    table[59][43]="<primaryexp>--> floatliteral";
    
    table[60][21]="<selection>--> tk_if tk_lb <condexp> tk_rb <block> <selection2>";
    
    table[61][18]="<selection2>--> e";
    table[61][21]="<selection2>--> e";
    table[61][22]="<selection2>--> tk_else <block>";
    table[61][23]="<selection2>--> e";
    table[61][24]="<selection2>--> e";
    table[61][25]="<selection2>--> e";
    table[61][38]="<selection2>--> e";
    table[61][39]="<selection2>--> e";
    table[61][40]="<selection2>--> e";
    table[61][41]="<selection2>--> e";
    
    table[62][37]="<block>--> tk_lcb <statements> tk_rcb";
    
    table[63][23]="<iteration>--> tk_while tk_lb <condexp> tk_rb <block>";
    
    
    
    
    
    //  state[0][0][0]=0;
    state[0][1][7]=9;               //first push "mainfunction",defined in line 9 , then push "functions",defined in line 1.
    state[0][1][8]=9;               // tk_int,tk_float etc are all tokens under which we can extend....see parsing table..
    state[0][1][9]=9;
    state[0][1][10]=9;
    state[0][2][7]=1;
    state[0][2][8]=1;
    state[0][2][9]=1;
    state[0][2][10]=1;
    state[0][1][12]=9;
    state[0][2][12]=1;
    state[0][1][46]=67;  // 67 == ACCEPTANCE STATE..
    
    
    state[1][1][7]=1;
    state[1][2][7]=2;
    state[1][1][8]=1;
    state[1][2][8]=2;
    state[1][1][9]=1;
    state[1][2][9]=2;
    state[1][1][10]=1;
    state[1][2][10]=2;
    state[1][1][12]=69;      
    
    
    state[2][1][7]=10;
    state[2][2][7]=3;
    state[2][1][8]=10;
    state[2][2][8]=3;
    state[2][1][9]=10;
    state[2][2][9]=3;
    state[2][1][10]=10;
    state[2][2][10]=3;
    
    state[3][1][7]=104;  // tk_rb=70+34
    state[3][2][7]=5;     //params..
    state[3][3][7]=103;
    state[3][4][7]=111;
    state[3][5][7]=4;
    state[3][1][8]=104;  // tk_rb=70+34
    state[3][2][8]=5;     //params..
    state[3][3][8]=103;
    state[3][4][8]=111;
    state[3][5][8]=4;
    state[3][1][9]=104;  // tk_rb=70+34
    state[3][2][9]=5;     //params..
    state[3][3][9]=103;
    state[3][4][9]=111;
    state[3][5][9]=4;
    state[3][1][10]=104;  // tk_rb=70+34
    state[3][2][10]=5;     //params..
    state[3][3][10]=103;
    state[3][4][10]=111;
    state[3][5][10]=4;
    
    
    state[4][1][7]=77;
    state[4][1][8]=78;
    state[4][1][9]=79;
    state[4][1][10]=80;
    
    state[5][1][7]=6;
    state[5][2][7]=109;
    state[5][3][7]=8;
    state[5][1][8]=6;
    state[5][2][8]=109;
    state[5][3][8]=8;
    state[5][1][10]=6;
    state[5][2][10]=110;
    state[5][3][10]=80;
    state[5][1][11]=6;
    state[5][2][11]=109;
    state[5][3][11]=8;
    state[5][1][34]=69;
    
    state[6][1][0]=7;      // first 65==state no's for non-terminlas ...from 70 for terminlas
    state[6][2][0]=70;    // 70=state no. of tk_comma, 71=state no. of tk_dot...
   state[6][1][34]=69;     // EITHER THIS IS THERE OR STATE[7][1][34]....
    
    state[7][1][7]=6;
    state[7][2][7]=109;
    state[7][3][7]=8;
    state[7][1][8]=6;
    state[7][2][8]=109;
    state[7][3][8]=8;
    state[7][1][10]=6;
    state[7][2][10]=110;
    state[7][3][10]=80;
    state[7][1][11]=6;
    state[7][2][11]=109;
    state[7][3][11]=8;
    //state[7][1][34]=69;
    
    state[8][1][7]=77;
    state[8][1][8]=78;
    state[8][1][11]=81;
    
    state[9][1][12]=10;
    state[9][2][12]=82;
    
    state[10][1][37]=108;
    state[10][2][37]=16;
    state[10][3][37]=11;
    state[10][4][37]=107;
    
    state[11][1][7]=11;
    state[11][2][7]=12;
    state[11][3][7]=8;
    state[11][1][8]=11;
    state[11][2][8]=12;
    state[11][3][8]=8;
    state[11][1][10]=11;
    state[11][2][10]=14;
    state[11][3][10]=80;
    state[11][1][11]=11;
    state[11][2][11]=12;
    state[11][3][11]=8;
    state[11][1][18]=69;
    state[11][1][21]=69;
    state[11][1][23]=69;
    state[11][1][24]=69;
    state[11][1][25]=69;
    state[11][1][38]=69;
    state[11][1][39]=69;
    state[11][1][40]=69;
    state[11][1][41]=69;
    
    
    state[12][1][39]=13;
    state[12][2][39]=109;
    
    state[13][1][0]=13;
    state[13][2][0]=109;
    state[13][3][0]=70;
    state[13][1][2]=72;
    
    
    state[14][1][40]=15;
    state[14][2][40]=110;
    
    
    state[15][1][0]=15;
    state[15][2][0]=110;
    state[15][3][0]=70;
    state[15][1][2]=72;
    
    state[16][1][18]=16;
    state[16][2][18]=17;
    state[16][1][21]=16;
    state[16][2][21]=17;
    state[16][1][23]=16;
    state[16][2][23]=17;
    state[16][1][24]=16;
    state[16][2][24]=17;
    state[16][1][25]=16;
    state[16][2][25]=17;
    state[16][1][38]=69;
    state[16][1][39]=16;
    state[16][2][39]=17;
    state[16][1][40]=16;
    state[16][2][40]=17;
    state[16][1][41]=16;
    state[16][2][41]=17;
    
    
    state[17][1][18]=44;
    state[17][1][21]=60;
    state[17][1][23]=63;
    state[17][1][24]=46;
    state[17][1][25]=46;
    state[17][1][39]=34;
    state[17][1][40]=34;
    state[17][1][41]=18;
    
    state[18][1][41]=72;
    state[18][2][41]=38;
    state[18][3][41]=111;
    
    state[19][1][14]=20;
    state[19][1][19]=104;
    state[19][2][19]=20;
    state[19][3][19]=103;
    state[19][4][19]=89;
    state[19][1][20]=104;
    state[19][2][20]=20;
    state[19][3][20]=103;
    state[19][4][20]=90;
    state[19][1][33]=20;
    state[19][1][39]=20;
    state[19][1][40]=20;
    state[19][1][42]=20;
    state[19][1][43]=20;
    state[19][1][45]=20;
    
    state[20][1][14]=104;
    state[20][2][14]=29;   // vectorexp
    state[20][3][14]=103;
    state[20][4][14]=84;
    state[20][1][33]=21;
    state[20][2][33]=22;
    state[20][1][39]=21;
    state[20][2][39]=22;
    state[20][1][40]=29;
    state[20][2][40]=71;
    state[20][3][40]=29;
    state[20][1][42]=21;
    state[20][2][42]=22;
    state[20][1][43]=21;
    state[20][2][43]=22;
    state[20][1][45]=29;
    state[20][2][45]=71;
    state[20][3][45]=29;
    
    
    state[21][1][2]=69;   // 2=tk_;
    state[21][1][3]=22;
    state[21][2][3]=73;
    state[21][1][14]=69;
    state[21][1][19]=69;
    state[21][1][20]=69;
    state[21][1][33]=69;
    state[21][1][34]=69;
    state[21][1][36]=69;
    state[21][1][39]=69;
    state[21][1][40]=69;
    state[21][1][42]=69;
    state[21][1][43]=69;
    state[21][1][45]=69;
    
    
    state[22][1][33]=23;
    state[22][2][33]=24;
    state[22][1][39]=23;
    state[22][2][39]=24;
    state[22][1][42]=23;
    state[22][2][42]=24;
    state[22][1][43]=23;
    state[22][2][43]=24;
    
    
    state[23][1][2]=69;
    state[23][1][3]=69;
    state[23][1][4]=22;
    state[23][2][4]=74;
    state[23][1][14]=69;
    state[23][1][19]=69;
    state[23][1][20]=69;
    state[23][1][33]=69;
    state[23][1][34]=69;
    state[23][1][36]=69;
    state[23][1][39]=69;
    state[23][1][40]=69;
    state[23][1][42]=69;
    state[23][1][43]=69;
    state[23][1][45]=69;
    
    state[24][1][33]=25;
    state[24][2][33]=26;
    state[24][1][39]=25;
    state[24][2][39]=26;
    state[24][1][42]=25;
    state[24][2][42]=26;
    state[24][1][43]=25;
    state[24][2][43]=26;
    
    
    state[25][1][2]=69;
    state[25][1][3]=69;
    state[25][1][4]=69;
    state[25][1][5]=26;
    state[25][2][5]=75;
    state[25][1][14]=69;
    state[25][1][19]=69;
    state[25][1][20]=69;
    state[25][1][33]=69;
    state[25][1][34]=69;
    state[25][1][36]=69;
    state[25][1][39]=69;
    state[25][1][40]=69;
    state[25][1][42]=69;
    state[25][1][43]=69;
    state[25][1][45]=69;
    
    
    state[26][1][33]=27;
    state[26][2][33]=28;
    state[26][1][39]=27;
    state[26][2][39]=28;
    state[26][1][42]=27;
    state[26][2][42]=28;
    state[26][1][43]=27;
    state[26][2][43]=28;
    
    state[27][1][2]=69;
    state[27][1][3]=69;
    state[27][1][4]=69;
    state[27][1][5]=69;
    state[27][1][6]=28;
    state[27][2][6]=76;
    state[27][1][14]=69;
    state[27][1][19]=69;
    state[27][1][20]=69;
    state[27][1][33]=69;
    state[27][1][34]=69;
    state[27][1][36]=69;
    state[27][1][39]=69;
    state[27][1][40]=69;
    state[27][1][42]=69;
    state[27][1][43]=69;
    state[27][1][45]=69;
    
    
    state[28][1][33]=104;
    state[28][2][33]=19;
    state[28][3][33]=103;
    state[28][1][39]=109;
    state[28][1][42]=112;
    state[28][1][43]=113;
    
    
    state[29][1][40]=30;
    state[29][2][40]=31;
    state[29][1][45]=30;
    state[29][2][45]=31;
    
    
    state[30][1][1]=69;
    state[30][1][2]=69;
    state[30][1][14]=69;
    state[30][1][15]=31;
    state[30][2][15]=85;
    state[30][1][19]=69;
    state[30][1][20]=69;
    state[30][1][33]=69;
    state[30][1][34]=69;
    state[30][1][36]=69;
    state[30][1][39]=69;
    state[30][1][40]=69;
    state[30][1][42]=69;
    state[30][1][43]=69;
    state[30][1][45]=69;
    
    state[31][1][40]=32;
    state[31][2][40]=33;
    state[31][1][45]=32;
    state[31][2][45]=33;
    
    
    state[32][1][1]=69; // 69==e
    state[32][1][2]=69; // 69==e
    state[32][1][3]=33;
    state[32][2][3]=73;
    state[32][1][14]=69; // 69==e
    state[32][1][15]=69; // 69==e
    state[32][1][19]=69; // 69==e
    state[32][1][20]=69; // 69==e
    state[32][1][33]=69; // 69==e
    state[32][1][34]=69; // 69==e
    state[32][1][36]=69; // 69==e
    state[32][1][39]=69; // 69==e
    state[32][1][40]=69; // 69==e
    state[32][1][42]=69; // 69==e
    state[32][1][43]=69; // 69==e
    state[32][1][45]=69; // 69==e
    
    
    state[33][1][40]=110;
    state[33][1][45]=115;
    
    state[34][1][39]=42;
    state[34][1][40]=35;
    
    state[35][1][40]=36;
    state[35][2][40]=83;
    state[35][3][40]=110;
    
    state[36][1][35]=72;
    state[36][2][35]=106;
    state[36][3][35]=37;
    state[36][4][35]=37;
    state[36][5][35]=37;
    state[36][6][35]=105;
    state[36][1][40]=72;
    state[36][2][40]=29;
    state[36][1][41]=72;
    state[36][2][41]=38;
    state[36][3][41]=111;
    state[36][1][45]=72;
    state[36][2][45]=29;
    
    state[37][1][14]=19;
    state[37][1][19]=19;
    state[37][1][20]=19;
    state[37][1][33]=19;
    state[37][1][39]=19;
    state[37][1][40]=19;
    state[37][1][42]=19;
    state[37][1][43]=19;
    state[37][1][45]=19;
    
    
    state[38][1][33]=104;
    state[38][2][33]=39;
    state[38][3][33]=103;
    
    
    state[39][1][34]=69;
    state[39][1][39]=40;
    state[39][2][39]=109;
    state[39][1][40]=40;
    state[39][2][40]=110;
    
    state[40][1][0]=41;
    state[40][2][0]=70;
    state[40][1][34]=69;
    
    state[41][1][39]=40;
    state[41][2][39]=109;
    state[41][1][40]=40;
    state[41][2][40]=110;
    
    state[42][1][39]=43;
    state[42][2][39]=83;
    state[42][3][39]=109;
    
    state[43][1][14]=72;
    state[43][2][14]=19;
    state[43][1][19]=72;
    state[43][2][19]=19;
    state[43][1][20]=72;
    state[43][2][20]=19;
    state[43][1][33]=72;
    state[43][2][33]=19;
    state[43][1][39]=72;
    state[43][2][39]=19;
    state[43][1][40]=72;
    state[43][2][40]=19;
    state[43][1][41]=72;
    state[43][2][41]=38;
    state[43][3][41]=111;
    state[43][1][42]=72;
    state[43][2][42]=19;
    state[43][1][43]=72;
    state[43][2][43]=19;
    state[43][1][45]=72;
    state[43][2][45]=19;
    
    
    state[44][1][18]=45;
    state[44][2][18]=88;
    
    state[45][1][39]=72;
    state[45][2][39]=109;
    state[45][1][40]=72;
    state[45][2][40]=110;
    
    state[46][1][24]=51;
    state[46][1][25]=47;
    
    state[47][1][25]=72;
    state[47][2][25]=104;
    state[47][3][25]=48;
    state[47][4][25]=103;
    state[47][5][25]=95;
    
    state[48][1][39]=49;
    state[48][2][39]=109;
    state[48][1][40]=49;
    state[48][2][40]=110;
    state[48][1][44]=49;
    state[48][2][44]=114;
    
    state[49][1][0]=50;
    state[49][2][0]=70;
    
    
    state[50][1][34]=69;
    state[50][1][39]=49;
    state[50][2][39]=109;
    state[50][1][40]=49;
    state[50][2][40]=110;
    state[50][1][44]=49;
    state[50][2][44]=114;
    
    state[51][1][24]=72;
    state[51][2][24]=104;
    state[51][3][24]=52;
    state[51][4][24]=103;
    state[51][5][24]=94;
    
    state[52][1][44]=53;
    state[52][2][44]=70;
    state[52][3][44]=114;
    
    state[53][1][39]=109;
    state[53][1][40]=110;
    
    state[54][1][26]=55;
    state[54][2][26]=56;
    state[54][1][39]=55;
    state[54][2][39]=56;
    state[54][1][40]=110;
    state[54][2][40]=102;
    state[54][3][40]=110;
    state[54][1][42]=55;
    state[54][2][42]=56;
    state[54][1][43]=55;
    state[54][2][43]=56;
    
    state[55][1][16]=56;
    state[55][2][16]=57;
    state[55][1][17]=56;
    state[55][2][17]=57;
    state[55][1][27]=56;
    state[55][2][27]=57;
    state[55][1][28]=56;
    state[55][2][28]=57;
    state[55][1][29]=56;
    state[55][2][29]=57;
    state[55][1][30]=56;
    state[55][2][30]=57;
    state[55][1][31]=56;
    state[55][2][31]=57;
    state[55][1][32]=56;
    state[55][2][32]=57;
    state[55][1][34]=69;
    state[55][1][38]=69;
    
    state[56][1][26]=56;
    state[56][2][26]=96;
    state[56][1][33]=59;
    state[56][1][39]=59;
    state[56][1][42]=59;
    state[56][1][43]=59;
    
    state[57][1][16]=86;
    state[57][1][17]=87;
    state[57][1][27]=58;
    state[57][1][28]=58;
    state[57][1][29]=58;
    state[57][1][30]=58;
    state[57][1][31]=58;
    state[57][1][32]=58;
    
    state[58][1][27]=97;
    state[58][1][28]=98;
    state[58][1][29]=99;
    state[58][1][30]=100;
    state[58][1][31]=101;
    state[58][1][32]=102;
    
    state[59][1][33]=104;
    state[59][2][33]=54;
    state[59][3][33]=103;
    state[59][1][39]=109;
    state[59][1][42]=112;
    state[59][1][43]=113;
    
    
    state[60][1][21]=61;
    state[60][2][21]=62;
    state[60][3][21]=104;
    state[60][4][21]=54;
    state[60][5][21]=103;
    state[60][6][21]=91;
    
    state[61][1][18]=69;
    state[61][1][21]=69;
    state[61][1][22]=62;
    state[61][2][22]=92;
    state[61][1][23]=69;
    state[61][1][24]=69;
    state[61][1][25]=69;
    state[61][1][38]=69;
    state[61][1][39]=69;
    state[61][1][40]=69;
    state[61][1][41]=69;
    
    state[62][1][37]=108;
    state[62][2][37]=16;
    state[62][3][37]=107;
    
    state[63][1][23]=62;
    state[63][2][23]=104;
    state[63][3][23]=54;
    state[63][4][23]=103;
    state[63][5][23]=93;
    
    
int flag_push=0;

    node root=(Node*)malloc(sizeof(Node));
    
    int ii;
    
    for(ii=0;ii<7;ii++){
        root->child[ii]=NULL;
    }
    root->parent=NULL;
    root->next=NULL;
    root->value=0;
    
    node current=root;
    
    node prev_accessed=NULL;
    
    node n1;
    
    
    //   stack<int> staack;
    //  staack.push(0);
    //  staack.push(0);
    
    
    stack staack=(Stack*)malloc(sizeof(Stack));
    
    
    staack=Push(staack,0);
    staack=Push(staack,0);
    
    
    
    
    
    
    //  staack.push(9);
    // staack.push(1);
    //  map<string,int>::iterator it;
    //  int converted_token=0;
    //
    //    cout<<tokens[0];
    //    printf("\n");
    //
    //    for(it = convert.begin(); it != convert.end(); it++) {
    //                    if(it->first==tokens[0]){
    //                        converted_token=it->second;
    //                        break;
    //                    }
    //                }
    //    printf("%d\n",converted_token);
    //    printf("%d\n",state[0][1][converted_token]);
    int flag3=0; // ACCEPATNCE FLAG
    
    int ik;
    
    for(ik=0;ik<70;ik++){   // 70= NUMBER OF TOKENS.....could be changed accordingly
        
        //        for(it = convert.begin(); it != convert.end(); it++) {
        //            if(it->first==tokens[i]){
        //                converted_token=it->second;
        //                break;
        //            }
        //        }
        
        
        
        char inputoken[50];
        
        strcpy(inputoken,tokenss[ik]);
        
        
        int ret1 =strcmp(tokens[0],inputoken);
        int ret2=strcmp(tokens[1],inputoken);
        int ret3 =strcmp(tokens[2],inputoken);
        int ret4=strcmp(tokens[3],inputoken);
        int ret5 =strcmp(tokens[4],inputoken);
        int ret6=strcmp(tokens[5],inputoken);
        int ret7 =strcmp(tokens[6],inputoken);
        int ret8=strcmp(tokens[7],inputoken);
        int ret9 =strcmp(tokens[8],inputoken);
        int ret10=strcmp(tokens[9],inputoken);
        int ret11 =strcmp(tokens[10],inputoken);
        int ret12=strcmp(tokens[11],inputoken);
        int ret13 =strcmp(tokens[12],inputoken);
        int ret14=strcmp(tokens[13],inputoken);
        int ret15 =strcmp(tokens[14],inputoken);
        int ret16=strcmp(tokens[15],inputoken);
        int ret17 =strcmp(tokens[16],inputoken);
        int ret18=strcmp(tokens[17],inputoken);
        int ret19 =strcmp(tokens[18],inputoken);
        int ret20=strcmp(tokens[19],inputoken);
        int ret21 =strcmp(tokens[20],inputoken);
        int ret22=strcmp(tokens[21],inputoken);
        int ret23 =strcmp(tokens[22],inputoken);
        int ret24=strcmp(tokens[23],inputoken);
        int ret25 =strcmp(tokens[24],inputoken);
        int ret26=strcmp(tokens[25],inputoken);
        int ret27 =strcmp(tokens[26],inputoken);
        int ret28=strcmp(tokens[27],inputoken);
        int ret29 =strcmp(tokens[28],inputoken);
        int ret30=strcmp(tokens[29],inputoken);
        int ret31 =strcmp(tokens[30],inputoken);
        int ret32=strcmp(tokens[31],inputoken);
        int ret33 =strcmp(tokens[32],inputoken);
        int ret34=strcmp(tokens[33],inputoken);
        int ret35 =strcmp(tokens[34],inputoken);
        int ret36=strcmp(tokens[35],inputoken);
        int ret37 =strcmp(tokens[36],inputoken);
        int ret38=strcmp(tokens[37],inputoken);
        int ret39 =strcmp(tokens[38],inputoken);
        int ret40=strcmp(tokens[39],inputoken);
        int ret41=strcmp(tokens[40],inputoken);
        int ret42=strcmp(tokens[41],inputoken);
        int ret43=strcmp(tokens[42],inputoken);
        int ret44=strcmp(tokens[43],inputoken);
        int ret45=strcmp(tokens[44],inputoken);
        int ret46=strcmp(tokens[45],inputoken);
        int ret47=strcmp(tokens[46],inputoken);
        
        
        
        int converted_token=0;
        
        if(ret1==0){
            converted_token=0;
            //printf("yay");
        }
        if(ret2==0){
            converted_token=1;
        }
        
        if(ret3==0){
            converted_token=2;
        }
        
        if(ret4==0){
            converted_token=3;
        }
        
        if(ret5==0){
            converted_token=4;
        }
        
        if(ret6==0){
            converted_token=5;
        }
        
        if(ret7==0){
            converted_token=6;
        }
        
        if(ret8==0){
            converted_token=7;
        }
        
        if(ret9==0){
            converted_token=8;
        }
        
        if(ret10==0){
            converted_token=9;
        }
        
        if(ret11==0){
            converted_token=10;
        }
        
        if(ret12==0){
            converted_token=11;
        }
        
        if(ret13==0){
            converted_token=12;
        }
        
        if(ret14==0){
            converted_token=13;
        }
        
        if(ret15==0){
            converted_token=14;
        }
        
        if(ret16==0){
            converted_token=15;
        }
        
        if(ret17==0){
            converted_token=16;
        }
        
        if(ret18==0){
            converted_token=17;
        }
        
        if(ret19==0){
            converted_token=18;
        }
        
        if(ret20==0){
            converted_token=19;
        }
        
        if(ret21==0){
            converted_token=20;
        }
        
        if(ret22==0){
            converted_token=21;
        }
        
        if(ret23==0){
            converted_token=22;
        }
        
        if(ret24==0){
            converted_token=23;
        }
        
        if(ret25==0){
            converted_token=24;
        }
        
        if(ret26==0){
            converted_token=25;
        }
        
        if(ret27==0){
            converted_token=26;
        }
        
        if(ret28==0){
            converted_token=27;
        }
        
        if(ret29==0){
            converted_token=28;
        }
        
        if(ret30==0){
            converted_token=29;
        }
        
        if(ret31==0){
            converted_token=30;
        }
        
        if(ret32==0){
            converted_token=31;
        }
        
        if(ret33==0){
            converted_token=32;
        }
        
        if(ret34==0){
            converted_token=33;
        }
        
        if(ret35==0){
            converted_token=34;
        }
        
        if(ret36==0){
            converted_token=35;
        }
        
        if(ret37==0){
            converted_token=36;
        }
        
        if(ret38==0){
            converted_token=37;
        }
        
        if(ret39==0){
            converted_token=38;
        }
        
        if(ret40==0){
            converted_token=39;
        }
        
        if(ret41==0){
            converted_token=40;
        }
        
        if(ret42==0){
            converted_token=41;
        }
        
        if(ret43==0){
            converted_token=42;
        }
        
        if(ret44==0){
            converted_token=43;
        }
        
        if(ret45==0){
            converted_token=44;
        }
        
        if(ret46==0){
            converted_token=45;
        }
        
        if(ret47==0){
            converted_token=46;
        }
        
        
        
        int flag=1;
        int flag2=0;
        // string s3=tokens[i];
        
        // if(s3=="$"){
        //   printf("ACCEPT\n");
        // }
        
        // else{
        while(flag==1 && flag3==0){
            
            entry a=(Entry*)malloc(sizeof(Entry));
            
            a=staack->top;
            
            int y=a->value;
            
            
            //   int y=staack.top();  // here,,y either a terminal or non-terminal or e...
            if(y==0 && converted_token==46){
                printf("ACCEPTED\n");     // when the last symbol i.e '$' encountered..
                flag3=1;
                
            }else{
                staack=Pop(staack);
                
                
                //staack.pop();
                //   printf("state==%d\n",y);
                //  printf("token == %d\n",converted_token);
                if(y<69){          // y a non-terminal hence, break down further....
                    
                    int kk;
                    
                    for(kk=1;kk<7;kk++){
                        
                        if(state[y][kk][converted_token]==-1){
                            if(kk==1){
                                if(y==54){
                                    printf("ERROR BECAUSE CONDITIONAL EXPRESSION NOT FOUND INSIDE THE SELECTION/ITERATION STATEMENT\n");
                                    printf("TERMINATING..\n");
                                }
                                else if(main_flag==0){
                                    printf("ERROR AS MAIN FUNCTION HAS NOT BEEN DECLARED !\n");
                                    printf("TERMINATING..\n");   
                                }
                                else{
                                printf("ERROR BECAUSE NO CORRESPONDING ENTRY FOUND IN THE PARSE TABLE\n");          // no entry in parsing table....
                                printf("TERMINATING..\n");
                                }exit(1);
                            }
                            break;
                        }
                        else{
                            //    printf("k == %d\n",k);
                            //   printf("token == %d\n",converted_token);
                                   // printf("pushed %d\n",state[y][kk][converted_token]);

                                            if(state[y][kk][converted_token]==85){
                                                flag_push=1;
                                            }

                                            if(state[y][kk][converted_token]==90){
                                                flag_push=2;
                                            }

                            staack=Push(staack,state[y][kk][converted_token]);
                            //   staack.push(state[y][k][converted_token]);
                            
                            n1=AddChild(current,state[y][kk][converted_token],8-kk);
                            if(prev_accessed!=NULL){
                                prev_accessed->prev=n1;
                            }
                            //  Addnext(n1,prev_accessed);
                            n1->next=prev_accessed;
                            prev_accessed=n1;
                        }
                        
                    }
                    fprintf(output_file,"%s\n",table[y][converted_token]);
                    // cout<<table[y][converted_token];
                    //   printf("\n");
                    
                    prev_accessed=NULL;
                    n1->prev=NULL;
                    current=n1;
                    //  y=staack.top();
                    
                    a=staack->top;
                    
                    y=a->value;
                    
                    
                    if(y>=70){
                        flag2=1;
                    }
                }
                
                if(y==69){
                    //  printf("kk\n");
                    // cout<<table[y][converted_token];
                    // printf("\n");
                    //  staack.pop();            // simply remove the empty element and consider the next state in the stack....
                    
                    staack=Pop(staack);
                    
                    int io;
                    
                    for(io=0;io<7;io++){
                        current->child[io]=NULL;
                    }
                    
                    while(current->next==NULL){
                        current=current->parent;
                        if(current==root){
                            printf("PARSING DONE\n");
                        }
                    }
                    // if(current->parent==root){
                    //   printf("PARSE TREE COMPLETED\n");
                    //        }
                    //      else{
                    current=current->next;
                    //    }
                    
                    //  y=staack.top();
                    //  printf("%d\n",y);
                    // staack.pop();
                }
                
                if(y==82){
                    main_flag=1;
                }
                
                
                if(y>=70){           // that is x->terminal<non-terminal>
                    if(y-70==converted_token){
                        //    cout<<table[y][converted_token];
                        //   printf("\n");
                                   //  printf("elilminations se pehle     == %d\n",converted_token);
                        int r;


                            // if(y==111){




                            // }

                            if(y==109 || y==110 || y==111 || y==112 || y==113){


                                

                                current->key=str11[total_tk_count];
                                    total_tk_count++;
                                    

                                int pp=str11[total_tk_count][1]-'0';

                        int rr=str11[total_tk_count][0]-'0';
                        int declaration=0;
                        if(pp<0){
                        declaration=rr;
                        }
                        else{
                        declaration=rr*10 +pp; 
                        }

                                         current->declaration=declaration;
                                                        total_tk_count++;
                                                       

                    pp=str11[total_tk_count][1]-'0';

                    rr=str11[total_tk_count][0]-'0';
                    //printf("%d\n",rr);
                    int scope=0;
                    if(pp<0){
                                    scope=rr;
                                        }
                        else{
                           scope=rr*10 +pp; 
                                    }


                                    current->scope=scope;

                                   char str4[4];
                        sprintf(str4,"%d",scope);
                        if(y==109 || y==110){
                        strcat(current->key,str4);
                    }

                                    total_tk_count++;
                                    total_tk_count++;




                            }
                            else{
                                   // printf("\n \n Y == %d\n",y);
                                    total_tk_count+=4;
                            }
                        for(r=0;r<7;r++){
                            current->child[r]=NULL;
                        }
                        //   printf("curr value%d\n",current->value);
                        while(current->next==NULL){
                            
                            current=current->parent;
                            if(current==root){
                             //   printf("PARSING DONE\n");
                                break;
                            }
                        }
                        // if(current->parent==root){
                        //   printf("PARSE TREE COMPLETED\n");
                        //        }
                        //      else{
                        current=current->next;
                        //    }
                        if(flag2==1){
                            
                            staack=Pop(staack);
                            // staack.pop();
                            flag2=0;
                        }
                        //  staack.pop();
                        flag=0;               // get the next token......
                        break;
                    }
                    else{
                        if(flag_push==1){
                                    printf("SEMANTIC ERROR BECAUSE LHS OF CROSS assignment IS NOT VID\n");
                                    printf("TERMINATING..\n");
                        }else if(flag_push==2){
                            printf("SEMANTIC ERROR AS EXPRESSION INSIDE LOG NOT A SCALAR EXPRESSION\n");
                            printf("TERMINATING..\n");
                        }
                        else{
                        printf("ERROR BECAUSE EXPECTED TERMINAL SYMBOL NOT FOUND\n");         //terminal does not match
                        printf("TERMINATING..\n");
                        }
                        exit(1);
                    }
                }
                else{             // X gives only non-terminals
                    // flag remains 1...
                    
                }
            }
        }
    }

    // printf("pl  %d\n",root->child[6]->value);
    //printf("YIUIYIYI\n");
  //  preorder(root);
    fclose(output_file);

    printf("\n");
    
    printf("       CHECKING FOR TYPE CHECKING AND SEMATIC ANALYSIS......\n");
    printf("    \n     RESULTS :-   \n");

    traversalForAST(root);

    preorder(root);

     FILE *temp_files=fopen("gcc.asm","w");

    
     

     code_generation(root,temp_files);
   

}


void code_generation(node root,FILE *temp_files){

    printf("\n AST== \n \n");

 fprintf(temp_files,"%s\n",".model tiny");
     fprintf(temp_files,"%s\n",".data");

     fprintf(temp_files,"%s\n","a1  db  0");
     fprintf(temp_files,"%s\n","b1  db  0");
     fprintf(temp_files,"%s\n","c1  db  0");
     fprintf(temp_files,"%s\n","d1  db  0");
     
     fprintf(temp_files,"%s\n",".code");
     fprintf(temp_files,"%s\n",".startup");

    // fprintf(temp_files, "%s\n","mov ax,@data");
    // fprintf(temp_files, "%s\n","mov ds,ax");

 preorder_for_code_generation(root,temp_files);

    if(while_flag==1){
        fprintf(temp_files,"jmp Label1\n");
        fprintf(temp_files,"Label2 : \n");
    }

    fprintf(temp_files,"lea di,a1\n");
    fprintf(temp_files,"mov [di],ax\n");

    fprintf(temp_files,"lea di,b1\n");
    fprintf(temp_files,"mov [di],bx\n");

fprintf(temp_files,"lea di,c1\n");
    fprintf(temp_files,"mov [di],cx\n");

fprintf(temp_files,"lea di,d1\n");
    fprintf(temp_files,"mov [di],dx\n");



  //  fprintf(temp_files,"%s\n","mov ah,4CH");
    fprintf(temp_files, "%s\n",".exit");
    fprintf(temp_files,"%s\n","end");



}



//////////////////////////////////

void preorder(node p)
{
    int t;
    
    if(p==NULL)return;
    //  if(p->value>=0){
    //printf(" %d",p->value);

if(p->value==45){

//printf("while ka 5th child ==%d\n",p->child[5]->child[6]->value); // GIVES 99...

//printf("\n fgfg   == %d\n",p->child[5]->value);

    char *child_key=p->child[5]->key;

    entry_t *ch=ht_get(hashtable,child_key);
    entry_t *chh=ht_get(hashtable,"#proc");

    if(chh!=NULL){
    if(strcmp(ch->type,chh->return_type)!=0){
        printf("<<<<<\n SEMANTIC ERROR !! RETURN TYPE OF FUNCTION DOES NOT MATCH");
    }
}

}



 if(p->value==83){



char *keyy=p->child[5]->key;
entry_t *bb=ht_get(hashtable,keyy);

//printf("\nYAY in p==83 YAYAYAY\n");

//printf("CURRENT LINE NO.== %d\n",p->child[5]->declaration);
//printf("KEY == %s     DECLAREDD IN %d\n",bb->key,bb->declarations);

if(p->child[5]->declaration==bb->declarations){
    printf("\n <<<<<<<<< VARIABLE %c USED WITHOUT DECLARATION in LINE %d >>>>>>>>>>\n",keyy[0],bb->declarations);
}

//printf("\n %s\n",p->child[5]->value);

 if(p->child[5]->value==109){

 //printf("HUARRAY\n");
 upon_83(p->child[6],p->child[5]);
 //printf("YFYFYFYFYF\n");
 }

// printf("%d\n",p->child[5]->value);
// printf("%d\n",p->child[6]->value);


}
    for(t=0;t<7;t++){
        
        
        preorder(p->child[t]);
        
    }
    // if(p->next!=NULL){
    //   preorder(p->next);
    // }
    // preorder(p->child);
    
    
}
//
void traversalForAST(node p){
    
    
    if(p==NULL)return;
    


 if(p->value==72 || p->value==70 || p->value==103 || p->value==104 || p->value==105 || p->value==106 || p->value==107 || p->value==108 || p->value==69){
        
        while(p->parent->parent->countofchildren==1 && p->parent->countofchildren==1){
            
            p->parent->parent->child[6]=p;
            //p->parent->child[6]=NULL;
            p->parent=p->parent->parent;

            
        }
        //  printf(" vvv %d\n",p->parent->value);
        
        if(p->parent->countofchildren==1){
            p->parent->parent->countofchildren--;
            
            int i;
            
            for(i=0;i<7;i++){
                if(p->parent->parent->child[i]!=NULL){
                    if(p->parent->parent->child[i]->value==p->parent->value){
                        
                        p->parent->parent->child[i]=NULL;
                        break;
                    }
                }
            }
        }else{
            
            int zz;
            
            for(zz=0;zz<7;zz++){
                if(p->parent->child[zz]!=NULL){
                    if(p->parent->child[zz]->value==p->value){
                        
                        p->parent->child[zz]=NULL;
                        break;
                    }
                    
                }
            }
            
        }
    }

    


    else if(p->value==77 || p->value==109 || p->value==78 || p->value==80 || p->value==89 || p->value==84 || p->value==96 || p->value==110 || p->value==112 || p->value==113 || p->value==114 || p->value==115){
        
        //if(p->parent->next!=NULL){
        // printf("\n \n next ku val== %d\n",p->parent->next->value);
        //   }
        
        while(p->parent->parent->countofchildren==1 && p->parent->countofchildren==1){
            
            p->parent->parent->child[6]=p;
            p->parent=p->parent->parent;
            
        }
       
        if(p->parent->countofchildren==1){
            
            int r;
            
            for(r=0;r<7;r++){
                
                if(p->parent->parent->child[r]!=NULL){
                    if(p->parent->parent->child[r]->value==p->parent->value){
                        
                        p->parent->parent->child[r]=p;
                        p->parent->child[r]=NULL;
                       // p->parent=p->parent->parent;
                        break;
                    }
                }
            }
        }
    }
    
    
   
   ///////////////////////////////////////////////////////////////////////////////////


    else if(p->value==93){
        
        
        int r;
        
        for(r=0;r<7;r++){
            
            if(p->parent->child[r]!=NULL){
                
                //  printf("r == %d\n",r);
                
                p->child[5]=p->parent->child[r+2];
                // p->child[5]->parent=p;
                
                p->parent->child[r+2]=NULL;
                
                p->child[6]=p->parent->child[r+4];
                // p->child[6]->parent=p;
                
                
                p->parent->child[r+4]=NULL;
                
                break;
            }
            
        }
        
        int ir;
        
        for(ir=0;ir<7;ir++){
            
            if(p->parent->parent->child[ir]!=NULL){
                
                if(p->parent->parent->child[ir]->value==p->parent->value){
                    
                    p->parent->parent->child[ir]=p;
                    
                    p->parent=p->parent->parent;
                    break;
                    
                    
                }
            }
            
        }
        
        while(p->parent->countofchildren==1){
            
            
            int bb;
            
            for(bb=0;bb<7;bb++){
                
                if(p->parent->parent->child[bb]!=NULL){
                    
                    if(p->parent->parent->child[bb]->value==p->parent->value){
                        
                        p->parent->parent->child[bb]=p;
                        
                        p->parent=p->parent->parent;
                        
                        break;
                        
                        
                    }
                    
                }
                
            }
            
        }
        
    }
    
    
    

 ///////////////////////////////////////////////////////////////////////////////////



else if(p->value==91){     // FOR HANDLING SELECTION STATEMENTS 
    
                     
                     int rn;
                     
                     for(rn=0;rn<7;rn++){
                         
                         if(p->parent->child[rn]!=NULL){
                             
                             //  printf("r == %d\n",r);
                             
                             p->child[4]=p->parent->child[rn+2];
                             // p->child[4]->parent=p;
                             
                             p->parent->child[rn+2]=NULL;
                             
                             p->child[5]=p->parent->child[rn+4];
                            //  p->child[5]->parent=p;
                             
                             
                             p->parent->child[rn+4]=NULL;
                             
                             p->child[6]=p->parent->child[rn+5];
                            //  p->child[6]->parent=p;
                             
                             
                             p->parent->child[rn+5]=NULL;
                             
                             
                             break;
                         }
                     }

    
                         int irr;
                         
                         for(irr=0;irr<7;irr++){
                             
                             if(p->parent->parent->child[irr]!=NULL){
                                 
                                 if(p->parent->parent->child[irr]->value==p->parent->value){
                                     
                                     p->parent->parent->child[irr]=p;
                                     
                                     p->parent=p->parent->parent;
                                     break;
                                     
                                     
                                 }
                             }
                             
                         }
                         
                         while(p->parent->countofchildren==1){
                             
                             
                             int bbc;
                             
                             for(bbc=0;bbc<7;bbc++){
                                 
                                 if(p->parent->parent->child[bbc]!=NULL){
                                     
                                     if(p->parent->parent->child[bbc]->value==p->parent->value){
                                         
                                         p->parent->parent->child[bbc]=p;
                                         
                                         p->parent=p->parent->parent;
                                         
                                         break;
                                         
                                         
                                     }
                                     
                                 }
                                 
                             }
                             
                         }
                         
                     }
                     
                     
                         
  ///////////////////////////////////////////////////////////////////////////////////             ///////////////////////////////////////////////////////////////////////////////////            
                
        else if(p->value==90){

         //   printf("IDDJDJD\n");
            p->child[6]=p->parent->child[5];
           // printf("<<<<<< %d\n",p->child[6]->value);
             p->parent->child[5]=NULL;

            p->parent->parent->parent->child[6]=p;
            p->parent=p->parent->parent->parent;
           // printf("%d\n",p->parent->value);
           

        }
    
    
    

    ///////////////////////////////////////////////////////
                 else if(p->value==94){
                     
                     
                     int rx;
                     
                     for(rx=0;rx<7;rx++){
                         
                         if(p->parent->child[rx]!=NULL){
                             
                             //  printf("r == %d\n",r);
                             
                             p->child[6]=p->parent->child[rx+2];
                          //  p->child[6]->parent=p;
                             p->parent->child[rx+2]=NULL;
                             
                     //        p->child[5]=p->parent->child[rn+4];
                             
                             
                       //      p->parent->child[rn+4]=NULL;
                             
                           //  p->child[6]=p->parent->child[rn+5];
                         //
                             
                           //  p->parent->child[rn+5]=NULL;
                             
                             
                             break;
                         }
                     }
                     int iw;
                     
                     for(iw=0;iw<7;iw++){
                         
                         if(p->parent->parent->child[iw]!=NULL){
                             
                             if(p->parent->parent->child[iw]->value==p->parent->value){
                                 
                                 p->parent->parent->child[iw]=p;
                                 
                                 p->parent=p->parent->parent;
                                 break;
                                 
                                 
                             }
                         }
                         
                     }
                     
                     while(p->parent->countofchildren==1){
                         
                         
                         int bbb;
                         
                         for(bbb=0;bbb<7;bbb++){
                             
                             if(p->parent->parent->child[bbb]!=NULL){
                                 
                                 if(p->parent->parent->child[bbb]->value==p->parent->value){
                                     
                                     p->parent->parent->child[bbb]=p;
                                     
                                     p->parent=p->parent->parent;
                                     
                                     break;
                                     
                                     
                                 }
                                 
                             }
                             
                         }
                         
                     }
                     
                 }
    
    
    
    
    
    
     ///////////////////////////////////////////////////////////////////////////////////
    
    
                 else if(p->value==95){
                     
                     
                     int rnm;
                     
                     for(rnm=0;rnm<7;rnm++){
                         
                         if(p->parent->child[rnm]!=NULL){
                             
                             //  printf("r == %d\n",r);
                             
                            p->child[4]=p->parent->child[rnm+2];
                           // p->child[4]->parent=p;
                             
                             p->parent->child[rnm+2]=NULL;
                             
                         //    p->child[5]=p->parent->child[rn+4];
                             
                             
                    //         p->parent->child[rn+4]=NULL;
                             
                    //         p->child[6]=p->parent->child[rn+5];
                             
                             
                      //       p->parent->child[rn+5]=NULL;
                             
                             
                             break;
                         }
                     }
                     int irrz;
                     
                     for(irrz=0;irrz<7;irrz++){
                         
                         if(p->parent->parent->child[irrz]!=NULL){
                             
                             if(p->parent->parent->child[irrz]->value==p->parent->value){
                                 
                                 p->parent->parent->child[irrz]=p;
                                 
                                 p->parent=p->parent->parent;
                                 break;
                                 
                                 
                             }
                         }
                         
                     }
                     
                     while(p->parent->countofchildren==1){
                         
                         
                         int bbd;
                         
                         for(bbd=0;bbd<7;bbd++){
                             
                             if(p->parent->parent->child[bbd]!=NULL){
                                 
                                 if(p->parent->parent->child[bbd]->value==p->parent->value){
                                     
                                     p->parent->parent->child[bbd]=p;
                                     
                                     p->parent=p->parent->parent;
                                     
                                     break;
                                     
                                     
                                 }
                                 
                             }
                             
                         }
                         
                     }
                     
                 }
    
    



 ///////////////////////////////////////////////////////////////////////////////////




    
    else if(p->value==82){     // FOR HANDLING MAIN.....
        
        int e;
        
        for(e=0;e<7;e++){
            
            if(p->parent->child[e]!=NULL){
                if(p->parent->child[e]->value==p->value){
                    
                    p->child[6]=p->parent->child[e+1];
                   // p->child[6]->parent=p;
                    p->parent->child[e+1]=NULL;
                    
                    break;
                }
            }
        }
        
        int mm;
        
        for(mm=0;mm<7;mm++){
            
            if(p->parent->parent->child[mm]!=NULL){
                if(p->parent->parent->child[mm]->value==p->parent->value){
                    
                    p->parent->parent->child[mm]=p;
                    p->parent=p->parent->parent;
                    break;
                }
                
                
                
            }
        }
        
    }


 ///////////////////////////////////////////////////////////////////////////////////

    else if(p->value==73 ){


     //   printf("1 \n");
        //p->parent->child[6]->parent=NULL;

if(p->parent->child[6]!=NULL){
        p->child[6]=p->parent->child[6];

    //    printf("%d\n",p->child[6]->value);
    
        //p->child[6]->parent=p;
        //p->child[6]->parent=NULL;
        //p->child[6]->parent=p;
        p->parent->child[6]=NULL;
    }
        //p->parent->parent->child[5]->parent=NULL;
        if(p->parent->parent->child[5]!=NULL){
        p->child[5]=p->parent->parent->child[5];
    
//        printf("%d\n",p->parent->parent->child[5]->value);
   //     printf("%d\n",p->child[5]->value);


//p->child[5]->parent=NULL;
        //p->child[5]->parent=p;
        p->parent->parent->child[5]=NULL;
    }

//printf("\n 3 \n");
        
        p->parent->parent->parent->child[6]=p;
        p->parent=p->parent->parent->parent;
    }
    

 ///////////////////////////////////////////////////////////////////////////////////





else if(p->value==75){


p->child[6]=p->parent->child[6];
 //p->child[6]->parent=p;
p->parent->child[6]=NULL;

p->child[5]=p->parent->parent->child[5];
 //p->child[5]->parent=p;
p->parent->parent->child[5]=NULL;

p->parent->parent->parent->child[5]=p;
p->parent=p->parent->parent->parent;

}




 ///////////////////////////////////////////////////////////////////////////////////


else if(p->value==83){



p->child[6]=p->parent->child[6];

p->child[6]->parent=p;

p->parent->child[6]=NULL;

if(p->parent->child[4]!=NULL){
                    p->child[5]=p->parent->child[4];
                    p->child[5]->parent=p;
                    p->parent->child[4]=NULL;
                }
                else{
                   // printf("\nYAY\n");
                   // printf("%d\n",p->parent->parent->parent->parent->child[5]->value);
                    p->child[5]=p->parent->parent->parent->parent->child[5];
                    p->parent->parent->parent->parent->child[5]=NULL;
                     p->child[5]->parent=p;

                }


}






///////////////////////////////////////////////////////////////////////////////////

else if(p->value==102 || p->value==99 || p->value==97 || p->value==98 || p->value==100 || p->value==101){
 // LTE,LT,GTE,GT...

//printf("sscsc   %d\n",p->parent->parent->parent->child[6]->child[6]->value);
p->child[6]=p->parent->parent->parent->child[6]->child[6];
p->parent->parent->parent->child[6]->child[6]=NULL;


//printf("sscsc AAA  %d\n",p->parent->parent->parent->parent->child[5]->value);
p->child[5]=p->parent->parent->parent->parent->child[5];
p->parent->parent->parent->parent->child[5]=NULL;

p->parent->parent->parent->parent->child[6]=p;
p->parent->parent->parent->parent->child[5]=NULL;

p->parent=p->parent->parent->parent->parent;



}


/////////////////////////////////////////////////////////////////



else if(p->value==111){

    //printf("YO\n");

if(p->parent->value==43){

   // printf("IN\n");

p->child[6]=p->parent->child[5];
p->parent->child[5]=NULL;

p->parent->parent->child[6]=p;
p->parent=p->parent->parent;


}

}






///////////////////////////////////////////////////////////////////////////////////



else if(p->value==86 || p->value==87){ // AND,OR

//printf("gg %d\n",p->parent->parent->parent->child[5]->value);
p->child[5]=p->parent->parent->parent->child[5];
p->parent->parent->parent->child[5]->child[6]=NULL;

p->child[6]=p->parent->parent->child[6]->child[6];
p->parent->parent->child[6]->child[6]=NULL;

p->parent->parent->parent->child[5]=NULL;
p->parent->parent->parent->child[6]=p;

p->parent=p->parent->parent->parent;




}







///////////////////////////////////////////////////////////////////////////////////

    else if(p->value==71 || p->value==74 ||  p->value==76 || p->value==86 || p->value==87){
        
        int ee;
        
//printf("WELCOME\n");

        for(ee=0;ee<7;ee++){
            
            if(p->parent->child[ee]!=NULL){
                if(p->parent->child[ee]->value==p->value){
                 

                      // printf("\n\n yele %d\n",p->parent->parent->parent->parent->child[6]->value);   
                    p->child[6]=p->parent->child[ee+1];
                    //p->child[6]->parent=p;
                    
                 
                    
                    p->parent->child[ee+1]=NULL;
                    

                    if(p->parent->child[ee-1]!=NULL){
                    p->child[5]=p->parent->child[ee-1];
                    // p->child[5]->parent=p;
                    p->parent->child[ee-1]=NULL;
                }
                else{
                   // printf("\nYAY\n");
                   // printf("%d\n",p->parent->parent->parent->parent->child[5]->value);
                    p->child[5]=p->parent->parent->parent->parent->child[5];
                     p->child[5]->parent=p;
                    p->parent->parent->parent->parent->child[5]=NULL;


                }
                    
                    break;
                }
            }
        }
        
        
        //         else if(p->value==93){
        //
        //
        //             for(int r=0;r<7;r++){
        //
        //                 if(p->parent->child[r]!=NULL){
        //
        //                   //  printf("r == %d\n",r);
        //
        //                 //    p->child[5]=p->parent->child[r+2];
        //                  //   p->child[6]=p->parent->child[r+4];
        //
        //
        //
        //                 }
        //
        //             }
        //
        
        
        int qq;
        
        for(qq=0;qq<7;qq++){
            
            if(p->parent->parent->child[qq]!=NULL){
                if(p->parent->parent->child[qq]->value==p->parent->value){
                    
                    p->parent->parent->child[qq]=p;
                    p->parent=p->parent->parent;
                    break;
                }
                
                
            }
        }
        
        while(p->parent->parent->countofchildren==1 && p->parent->countofchildren==1){
            
            p->parent->parent->child[6]=p;
            p->parent=p->parent->parent;
            
        }
        if(p->parent->countofchildren==1){
            
            int xx;
            
            for(xx=0;xx<7;xx++){
                
                if(p->parent->parent->child[xx]!=NULL){
                    if(p->parent->parent->child[xx]->value==p->parent->value){
                        
                        p->parent->parent->child[xx]=p;
                        p->parent=p->parent->parent;
                        break;
                    }
                    
                    
                }
                
                
            }
            
        }
    }
    int tt;
    
    for(tt=0;tt<7;tt++){
        
        
        traversalForAST(p->child[tt]);
        
    }
    
}







// //this node a when passED FOR THE FIRST TIME SHOULD BE THE RIGHT CHILD OF 83 !!!
// // return 1 if TRUE, O if FALSE


void upon_83(node a,node left_child){

//printf("KIDDA|\n");
//printf("%d\n",a->value);

char *keyy=left_child->key;
int current_line_number=left_child->declaration;

entry_t *vv=ht_get(hashtable,keyy);

 int declared_in_line=vv->declarations;

// if(declared_in_line==current_line_number){
//     printf("NOT DECLARED BEFORE\n");
// }

// ////////////////////////////////////////////////////////
 if(a->value==73){
    
    //printf("\n ithe\n");
    char *bb;
    bb=upon_73(a);
    if(strcmp(bb,"tk_float")==0){

        char *cc;
        cc=vv->type;

        if(strcmp(cc,"tk_int")==0){
            printf("\n<<<<<<<<<<   TYPE CHECKING ERROR at line %d >>>>>>>>>>>>>\n",current_line_number);
        }
        else{
            printf("\n<<<<<<<<<<<<<<< CORRECT , NO TYPE CHECKING ERROR AT LINE NUMBER %d >>>>>>>>>>>>>>\n",current_line_number);
        }

    }
    else{
            printf("\n<<<<<<<<<<<<<<< CORRECT , NO TYPE CHECKING ERROR AT LINE NUMBER %d >>>>>>>>>>>>>>\n",current_line_number);
    }
 }


// ////////////////////////////////////////////////////////


 else if(a->value==75){

    char *bb;
    //printf("KIDAA\n");
    bb=upon_75(a);
    if(strcmp(bb,"tk_float")==0){

        char *cc;
        cc=vv->type;

        if(strcmp(cc,"tk_int")==0){
            printf("\n<<<<<<<<<<<   TYPE CHECKING ERROR at line %d >>>>>>>>>>> \n",current_line_number);
        }
        else{
            printf("\n<<<<<<<<<<<<<<< CORRECT , NO TYPE CHECKING ERROR AT LINE NUMBER %d >>>>>>>>>>>>>>\n",current_line_number);
        }
    }else{
            printf("\n<<<<<<<<<<<<<<< CORRECT , NO TYPE CHECKING ERROR AT LINE NUMBER %d  >>>>>>>>>>>>>>\n",current_line_number);
        }


 }
// ////////////////////////////////////////////////////////


 else if(a->value==111){
// // HERE, ALSO CHECK FOR NO. AND TYPES OF PARAMETER...


    char *funckey=a->key;

  //  printf("\n <<<<<<  funckey == %s >>>>>>>>\n",funckey);
     entry_t *ff=ht_get(hashtable,funckey);

    

//printf("%s\n",ff->string_of_params);
////////////////////////////


char arr[10][10];
int nn=0;
//char st[] ="Where there is will, there is a way.";
  char *ch;

  //clrscr();
  //printf("Split \"%s\"\n", ff->string_of_params);
  ch = strtok(ff->string_of_params, "~");
  while (ch != NULL) {
  //printf("%s\n", ch);
  strcpy(arr[nn],ch);
  nn++;
  ch = strtok(NULL, "~");
  }


//printf("type 1 ==%s\n",arr[0]);
//printf("type 2 ==%s\n",arr[1]);



nn=0;
///////////////////////////

char retturn[20];
strcpy(retturn,ff->return_type);

//printf("ret type== %s\n",retturn);

char *cc;
        cc=vv->type;

        if( (strcmp(cc,"tk_int")==0) && (strcmp(retturn,"tk_float")==0) ){
            printf("RETURN TYPE OF FUNCTION %s DOES NOT MATCH ID TYPE OF %s IN LINE NUMBER %d\n",ff->key,vv->key,current_line_number);
        }
        else{
            printf("RETURN TYPE OF FUNCTION %s MATCHES ID TYPE OF %s IN LINE NUMBER %d\n",ff->key,vv->key,current_line_number);
        }



  int paramater_in_func=ff->number_of_params;
  //printf("no of params==  %d\n",paramater_in_func);
     int countofparameter=0;

    if(a->child[6]->child[5]->child[6]!=NULL){

       // printf("KIDDA\n");

        countofparameter++;

        node temp=a->child[6]->child[5]->child[5];

        char *tt=temp->key;
        //printf("param=%s\n",tt);
        entry_t *ww=ht_get(hashtable,tt);

        tt=ww->type;
 
        if(strcmp(arr[nn],tt)!=0){

           // if(strcmp(tt,"float")==0){
                printf("<<<<<<<<<<<  SEMANTIC ERROR AS TYPE OF PARAMETER NUMBERED %d FOR FUNTION %s DO NOT MATCH\n ",nn+1,funckey);
                nn++;
           // }

        }else{
            nn++;
        }

    }

node current,temp;

 if(a->child[6]->child[5]->child[6]!=NULL){
     current=a->child[6]->child[5]->child[6];
    // printf("fjdgjdfjgnjdfgh %d\n",current->value);
     }
// // current here == 40...!!

//printf("%d\n",current->child[5]->value);
//printf("%d\n",current->child[6]->value);

    while(current->child[6]!=NULL){

 countofparameter++;

if(current->child[6]->child[5]!=NULL){
    //printf("haha\n");
 temp=current->child[6]->child[5];

char *tt=temp->key;
       // printf("param=%s\n",tt);
        entry_t *ww=ht_get(hashtable,tt);

        tt=ww->type;

        //printf(" 11== %s\n",tt);
       // printf("111  ==  %s\n",arr[nn] );


        if(strcmp(arr[nn],tt)!=0){

           // if(strcmp(tt,"float")==0){
                printf("<<<<<<<<<<<  SEMANTIC ERROR AS TYPE OF PARAMETER NUMBERED %d FOR FUNTION %s DO NOT MATCH >>>>>>>>>\n ",nn+1,funckey);
                nn++;
           // }

        }else{
            nn++;
        }


}
else{
    break;
}

if(current->child[6]->child[6]!=NULL){
 current=current->child[6]->child[6];
}else{
    break;
}
// // HENCE THIS LOOP KEEPS ON GOING....

     }

//printf("Finally count==%d\n",countofparameter);

if(countofparameter==paramater_in_func){
    printf(" <<<<<< NUMBER OF PARAMS FOR FUNCTION %s MATCH CORRECTLY!! >>>>>>>\n",funckey);
}else{
    printf("<<<<<<<<<<  SEMANTIC ERROR !! NO OF PARAMS FOR FUNCTION %s DO NOT MATCH >>>>>>> \n",funckey);
}

// //     return upon_111(a);
 }


// ////////////////////////////////////////////////////////
 else if(a->value==71){ // tk_dot

    if(strcmp(vv->type,"tk_float")==0){
        printf("\n<<<<<<<<<  CORRECT NO TYPE CHECKING ERROR AT LINE NUMBER %d >>>>>>>>>>> \n",current_line_number);
    }else{
         printf(" \n<<<<<<<<<<<<   TYPE CHECKING ERROR at line %d because LHS is not a float variable >>>>>>>>>> \n",current_line_number);
    }

}

// ////////////////////////////////////////////////////////


else if(a->value==109){

char *keya=a->key;
entry_t *vv=ht_get(hashtable,keya);

char *tyype=vv->type;

if(strcmp(tyype,"tk_float")==0){

if(strcmp(vv->type,"tk_float")==0){
        printf("\n<<<<<<<<<<<  CORRECT ,NO TYPE CHECKING ERROR AT LINE NUMBER %d >>>>>>>>>>\n",current_line_number);
    }else{
         printf("\n<<<<<<<<<<<<< TYPE CHECKING ERROR at line %d >>>>>>>>\n",current_line_number);
    }


}

}

else if(a->value==112){

printf("\n<<<<<<<<   CORRECT , NO TYPE CHECKING ERROR AT LINE NUMBER %d  >>>>>>>>>\n",current_line_number);

}


else if(a->value==113){ // i.e simple assignment statmt ,,, id = floatliteral

if(strcmp(vv->type,"tk_float")==0){
        printf("\n <<<<<<<<< CORRECT , NO TYPE CHECKING ERROR AT LINE NUMBER %d >>>>>>>>>>>\n",current_line_number);
    }else{
         printf("\n<<<<<<<<<<<<<<   TYPE CHECKING ERROR at line %d >>>>>>>>>>\n",current_line_number);
    }


}

// ////////////////////////////////////////////////////////

 else{ // SINCE NOTHING MATCHES ,,, KEEP ON GOING DOWN THE LEFT CHILD...


    if(a->child[4]!=NULL){
        return upon_83(a->child[4],left_child);
    }
else if(a->child[5]!=NULL){
        return upon_83(a->child[5],left_child);
}
else{
        return upon_83(a->child[6],left_child);
}

}

}//  upon_83 ends here/..

 char *upon_73(node a){




    if(a->child[5]->child[5]->child[5]->child[5]->value==109){
 char *key1=a->child[5]->child[5]->child[5]->child[5]->key;
 //printf("key1 == %s\n",key1);
  entry_t *a1=ht_get(hashtable,key1);
  char *type1=a1->type;
  if(strcmp(type1,"tk_float")==0){
    return "tk_float";
  }
}

else if(a->child[5]->child[5]->child[5]->child[5]->value==113){
return "tk_float";
}



    if(a->child[6]->child[5]->child[5]->child[5]->value==109){
 char *key2=a->child[6]->child[5]->child[5]->child[5]->key;
  //printf("key2 == %s\n",key2);
 entry_t *a2=ht_get(hashtable,key2);
 char *type2=a2->type;
if(strcmp(type2,"tk_float")==0){
    return "tk_float";
  }
}
else if(a->child[6]->child[5]->child[5]->child[5]->value==113){
return "tk_float";
}



 
    return "tk_int";
// }

}


char *upon_75(node a){


 //char *key1=a->child[5]->child[6]->key;
 //char *key2=a->child[6]->child[5]->key;

 



    if(a->child[5]->child[6]->value==109){
 char *key1=a->child[5]->child[6]->key;
 //printf("key1 == %s\n",key1);
  entry_t *a1=ht_get(hashtable,key1);
  char *type1=a1->type;
  if(strcmp(type1,"tk_float")==0){
    return "tk_float";
  }
}

else if(a->child[5]->child[6]->value==113){
return "tk_float";
}



    if(a->child[6]->child[5]->value==109){
 char *key2=a->child[6]->child[5]->key;
  //printf("key2 == %s\n",key2);
 entry_t *a2=ht_get(hashtable,key2);
 char *type2=a2->type;
if(strcmp(type2,"tk_float")==0){
    return "tk_float";
  }
}
else if(a->child[6]->child[5]->value==113){
return "tk_float";
}

 
    return "tk_int";

}






///////////

void preorder_for_code_generation(node p,FILE *fp)
{
    int t;

    //printf("AAAA");

    if(p==NULL)return;
    //  if(p->value>=0){
    printf(" %d",p->value);

    
    if(p->value==71){
        //printf("uiuiu\n");
        code_generation_71(p,fp);

    }

    else if(p->value==93){
        while_flag=1;
        code_generation_93(p,fp);
        label_count+=2;
    }
    else if(p->value==73){

        code_generation_73(p,fp);


    }
    else if(p->value==75){
        code_generation_75(p,fp);
    }
    else if(p->value==83){

        if(p->child[5]->value==110 && vcount==0){
                code_generation_83_vector(p,fp);
                vcount++;
        }
        else if(p->child[5]->value==110 && vcount==1){
                code_generation_83_vectors(p,fp);
        }
        else{
        if(p->child[6]->value!=90 && p->child[6]->child[5]->value!=71  ){
      // printf("\n1\n");
        node temp=p->child[6]->child[5]->child[6]->child[5]->child[5]->child[5]->child[5];
       //printf("2\n");
        node temp2=p->child[6]->child[5]->child[6];
       // printf("3\n");
        node temp3=p->child[6]->child[5]->child[6]->child[5]->child[5];
        if(temp!=NULL && temp2!=NULL && temp2->value!=73 && temp3!=NULL && temp3->value!=75){
        //printf("\n hererere %d\n",temp->value);
        code_generation_83(p,fp,p->child[5],temp);
}
}
}
    }
    for(t=0;t<7;t++){
        
        preorder_for_code_generation(p->child[t],fp);
        
    }
    
}



void code_generation_93(node a,FILE *fp){

//fprintf(fp,"Label%d : ",label_count);

///////////////////////////////////////////////////////////////////////////////

node temp1=a->child[5]->child[6]->child[5];
node temp2=a->child[5]->child[6]->child[6]->child[6];
entry_t *e1=ht_get(hashtable,temp1->key);
entry_t *e2=ht_get(hashtable,temp2->key);


if(temp1->value==109){

if(moved[e1->register_count]==0)
{
//fprintf(fp,"mov %s,%s\n",register_name[e1->register_count],temp1->key);
moved[e1->register_count]=1;
}
//if(a->child[5]->child[6])

// NO NEED TO PUT THE RHS IN A REGISTER AS ONE OPERAND CAN BE PRESENT IN MEMORY.....

fprintf(fp,"cmp %s,%s\n",register_name[e1->register_count],register_name[e2->register_count]);


}




///////////////////////////////////////////////////////////////////////////////


else{

// LEFT HAND SIDE IS INTLITERAL//FLOATLITERAL

    if(temp2->value==109){

if(moved[e2->register_count]==0){
        //fprintf(fp,"mov %s,%s\n",register_name[e2->register_count],temp2->key);
        moved[e2->register_count]=1;
    }

        fprintf(fp,"cmp %s,%s\n",temp1->key,register_name[e2->register_count]);

        
    }


    /////////////////////////

else{

    // BOTH LHS AND RHS ARE INTLITERAL/FLOATLITERAL,,,

    fprintf(fp,"cmp %s,%s\n",temp1->key,temp2->key);



}


}

///////////////////////////////////////////////////////////////////////////////

node temp=a->child[5]->child[6];  //   REL OP....
//printf("%d\n",temp->value);
char typeofjump[4];

if(temp->value==99){    
strcpy(typeofjump,"jge");
//printf("LL\n");
}
else if(temp->value==97){
    strcpy(typeofjump,"jle");
}
else if(temp->value==98){
    strcpy(typeofjump,"jl");
}
else if(temp->value==101){
    strcpy(typeofjump,"jg");
}
else if(temp->value==102){

}
else if(temp->value==100){

}

fprintf(fp,"%s Label%d\n",typeofjump,label_count+1);
fprintf(fp,"Label1:  ");

//printf("jmp [Label%d]\n",label_count);
}







void code_generation_73(node a,FILE *fp){

    //printf("LHS ++ %d\n",a->parent->parent->parent->child[5]->value);
// GET REGISTER_COUNT OF THE ABOVE MENTIONED LHS... 

//printf("REACHED\n");
   

    int flag1=0,flag2=0;
    node temp1=a->child[5]->child[5]->child[5]->child[5];
    node temp2=a->child[6]->child[5]->child[5]->child[5];
    node temp3=a->parent->parent->parent->child[5];

    if(temp3->value==109){


    entry_t *e1=ht_get(hashtable,temp1->key);
    entry_t *e2=ht_get(hashtable,temp2->key);
    entry_t *e3=ht_get(hashtable,temp3->key);

    if(moved[e3->register_count]==0){

        //fprintf(fp,"mov %s,%s\n",register_name[e3->register_count],temp3->key);
        moved[e3->register_count]=1;
    }


    if(temp1->value==109){

        if(moved[e1->register_count]==0){
       // fprintf(fp,"mov %s,%s\n",register_name[e1->register_count],temp1->key);

        moved[e1->register_count]=1;
        }
        flag1=1;


    }


   if(temp2->value==109){

    if(moved[e2->register_count]==0){
    //fprintf(fp,"mov %s,%s\n",register_name[e2->register_count],temp2->key);
    moved[e2->register_count]=1;
    }
    flag2=1;

   } 

if(flag1==0 && flag2==0){
    //fprintf(fp,"add R%d,%s,%s\n",e3->register_count,temp1->key,temp2->key);
    fprintf(fp,"mov %s,%s\n",register_name[e3->register_count],temp1->key);
    fprintf(fp,"add %s,%s\n",register_name[e3->register_count],temp2->key);

    //printf("add R%d,%s\n",e3->register_count,temp2->key);
}
else if(flag1==1 && flag2==0){
    //printf("\n IDHAR== %s\n",register_name[e3->register_count]);
    fprintf(fp,"mov %s,%s\n",register_name[e3->register_count],register_name[e1->register_count]);
    fprintf(fp,"add %s,%s\n",register_name[e3->register_count],temp2->key);
   // printf("1\n");

    
    //printf("2\n");
    //fprintf(fp,"add R%d,R%d,%s\n",e3->register_count,e1->register_count,temp2->key);
    //printf("add R%d,%s\n",e3->register_count,temp2->key);
}
else if(flag1==1 && flag2==1){
   


    fprintf(fp,"mov %s,%s\n",register_name[e3->register_count],register_name[e1->register_count]);
    fprintf(fp,"add %s,%s\n",register_name[e3->register_count],register_name[e2->register_count]);
    
    //printf("DONE\n");
    //printf("add R%d,R%d\n",e3->register_count,e2->register_count);
}
else{
 //fprintf(fp,"add R%d,%s,R%d\n",e3->register_count,temp1->key,e2->register_count);

fprintf(fp,"mov %s,%s\n",register_name[e3->register_count],register_name[e2->register_count]);
 fprintf(fp,"add %s,%s\n",register_name[e3->register_count],temp1->key);
 


// printf("add R%d,R%d\n",e3->register_count,e2->register_count);      
}


}}



//////////////////////////////////////////////////////////////////







void code_generation_75(node a,FILE *fp){


int flag1=0,flag2=0;
//printf("\n5757575575757557575\n");

//printf("%d\n",a->child[5]->child[5]->value);
//printf("%d\n",a->child[6]->child[5]->value);

node temp1=a->child[5]->child[5];
node temp2=a->child[6]->child[5];
node temp3=a->parent->parent->parent->parent->parent->child[5];

//printf("%d\n",temp3->value);

if(temp3->value==109){


    entry_t *e1=ht_get(hashtable,temp1->key);
    entry_t *e2=ht_get(hashtable,temp2->key);
    entry_t *e3=ht_get(hashtable,temp3->key);

    if(moved[e3->register_count]==0){

      //  fprintf(fp,"mov %s,%s\n",register_name[e3->register_count],temp3->key);
        moved[e3->register_count]=1;
    }


    if(temp1->value==109){

        if(moved[e1->register_count]==0){
       // fprintf(fp,"mov %s,%s\n",register_name[e1->register_count],temp1->key);

        moved[e1->register_count]=1;
        }
        flag1=1;


    }


   if(temp2->value==109){

    if(moved[e2->register_count]==0){
    //fprintf(fp,"mov %s,%s\n",register_name[e2->register_count],temp2->key);
    moved[e2->register_count]=1;
    }
    flag2=1;

   } 

if(flag1==0 && flag2==0){
    //fprintf(fp,"mul R%d,%s,%s\n",e3->register_count,temp1->key,temp2->key);

     fprintf(fp,"mov %s,%s\n",register_name[e3->register_count],temp1->key);
    fprintf(fp,"mul %s,%s\n",register_name[e3->register_count],temp2->key);


    //printf("add R%d,%s\n",e3->register_count,temp2->key);
}
else if(flag1==1 && flag2==0){
    //fprintf(fp,"mul R%d,R%d,%s\n",e3->register_count,e1->register_count,temp2->key);

    fprintf(fp,"mov %s,%s\n",register_name[e3->register_count],register_name[e1->register_count]);
    fprintf(fp,"mul %s,%s\n",register_name[e3->register_count],temp2->key);
    
    
    //printf("add R%d,%s\n",e3->register_count,temp2->key);
}
else if(flag1==1 && flag2==1){
   // fprintf(fp,"mul R%d,R%d,R%d\n",e3->register_count,e1->register_count,e2->register_count);
    //printf("add R%d,R%d\n",e3->register_count,e2->register_count);

    fprintf(fp,"mov %s,%s\n",register_name[e3->register_count],register_name[e1->register_count]);
    fprintf(fp,"mul %s,%s\n",register_name[e3->register_count],register_name[e2->register_count]);
    
   

}
else{
 //fprintf(fp,"mul R%d,%s,R%d\n",e3->register_count,temp1->key,e2->register_count);
// printf("add R%d,R%d\n",e3->register_count,e2->register_count);     

fprintf(fp,"mov %s,%s\n",register_name[e3->register_count],register_name[e2->register_count]);
 fprintf(fp,"mul %s,%s\n",register_name[e3->register_count],temp1->key);
 


}


}}




void code_generation_83(node a,FILE *fp,node lc,node rc){

//printf("\nVCVCVCVCV   %s\n",rc->key);

entry_t *tt=ht_get(hashtable,lc->key);

if(moved[tt->register_count]==0){

//fprintf(fp,"mov %s,%s\n",register_name[tt->register_count],tt->key);
moved[tt->register_count]=1;
}
fprintf(fp,"mov %s,%s\n",register_name[tt->register_count],rc->key);


}

void code_generation_83_vector(node a,FILE *fp){

tempv1=a->child[6]->child[2]->child[6]->child[6]->child[5]->child[5]->child[5]->child[5];
//printf("\n1\n");
//printf("fgf %s\n",temp1->key);
tempv2=a->child[6]->child[3]->child[6]->child[6]->child[5]->child[5]->child[5]->child[5];
//printf("2\n");
//printf("fgf %s\n",temp2->key);
tempv3=a->child[6]->child[4]->child[6]->child[6]->child[5]->child[5]->child[5]->child[5];
//printf("3\n");
//printf("\n yoy yyoyy %s\n",temp1->key);
//printf(" fgfgg %s\n",temp2->key);
//printf("xcxc   %s\n",temp3->key);


//printf("child == \n",a->child[6]->child[3]->child[6]->child[6]->child[5]->child[5]->child[5]->child[5]->value);

}
void code_generation_83_vectors(node a,FILE *fp){

tempv4=a->child[6]->child[2]->child[6]->child[6]->child[5]->child[5]->child[5]->child[5];
//printf("\n1\n");
//printf("fgf %s\n",tempv4->key);
tempv5=a->child[6]->child[3]->child[6]->child[6]->child[5]->child[5]->child[5]->child[5];
//printf("2\n");
//printf("fgf %s\n",tempv5->key);
tempv6=a->child[6]->child[4]->child[6]->child[6]->child[5]->child[5]->child[5]->child[5];
//printf("3\n");
//printf("\n yoy yyoyy %s\n",temp1->key);
//printf(" fgfgg %s\n",temp2->key);
//printf("xcxc   %s\n",tempv6->key);



//printf("child == \n",a->child[6]->child[3]->child[6]->child[6]->child[5]->child[5]->child[5]->child[5]->value);

}

void code_generation_71(node a,FILE *fp){


//printf("%s\n",tempv1->key);
fprintf(fp,"mov %s,%s\n","bx",tempv1->key);

fprintf(fp,"mov %s,%s\n","ax",tempv4->key);

fprintf(fp,"mul %s\n","bx");

fprintf(fp,"mov %s,%s\n","cx","ax");

////////////////////////

fprintf(fp,"mov %s,%s\n","bx",tempv2->key);

fprintf(fp,"mov %s,%s\n","ax",tempv5->key);

fprintf(fp,"mul %s\n","bx");

//fprintf(fp,"mul %s,%s\n",register_count+3,register_count+1,register_count);

fprintf(fp,"add %s,%s\n","cx","ax");

//////////////////////

fprintf(fp,"mov %s,%s\n","bx",tempv3->key);

fprintf(fp,"mov %s,%s\n","ax",tempv6->key);

fprintf(fp,"mul %s\n","bx");

//fprintf(fp,"mul %s,R%d,R%d\n",register_count+4,register_count+1,register_count);

fprintf(fp,"add %s,%s\n","cx","ax");

////////////////////

//printf("\n IDIDIDDID %d\n",a->parent->parent->child[5]->value);

node temp22=a->parent->parent->child[5];

entry_t *uu=ht_get(hashtable,temp22->key);

if(moved[uu->register_count]==0){
    //fprintf(fp,"mov %s,%s\n","ax",uu->key);
    moved[uu->register_count]=1;
}
fprintf(fp,"mov %s,%s\n","ax","cx");

}

