#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARRAYSIZE( array ) sizeof( array ) / sizeof( array[0] )

typedef struct Str
{
	char word[50];
}Str;
typedef struct
{
	Str* data;
	int listsize;
	int length;
}Sqlist;
int initSqlist(Sqlist* L, int maxsize)
{
	L->data = (Str*)malloc(maxsize * sizeof(Str));
	if (L->data == NULL) 
	{ printf("Space application failed!"); exit(0); }
	L->listsize = maxsize;
	L->length = 0;
	return 1;
}

//FILE* fp = NULL; 
Sqlist L;

void getWords( FILE* file );
void printWords();

int main()
{
	initSqlist(&L, 1000);     //Initialize str, the size is 1000, used to store the segmented words
	/*
	char f1[] = "d1.txt"; //file location (your d1-d4.txt file location 
	char f2[] = "d2.txt";
	char f3[] = "d3.txt"; 
	char f4[] = "d4.txt";
	*/

	FILE* d1 = fopen( "d1.txt", "r" );
	if( !d1 )
		perror( "couldnt open d1" );
	FILE* d2 = fopen( "d2.txt", "r" );
	if( !d2 )
		perror( "couldnt open d2" );
	FILE* d3 = fopen( "d3.txt", "r" );
	if( !d3 )
		perror( "couldnt open d3" );
	FILE* d4 = fopen( "d4.txt", "r" );
	if( !d4 )
		perror( "couldnt open d4" );

	getWords( d1 );
	getWords( d2 );
	getWords( d3 );
	getWords( d4 );
	printWords();
/*
	printwords(f1);
	printwords(f2);
	printwords(f3);
	printwords(f4);
*/	
	//test：
	for (int i = 0; i < L.length; i++)
	{
		printf("%s", L.data[i].word);
	}

	return 0;
}

void
getWords( FILE* file ){
	 
	char* word;
	char string[1024];
	char buffer[1024];
	char stopWord[1024];

	FILE* stopWordFile = fopen( "stopwords.txt", "r" );
	if( !stopWordFile ){
		fprintf( stderr, "Could not open stopwords.txt\n" );
	}

	if ( file == NULL){
		fprintf( stderr, "Could not read from file" );
	} else{
		while (fgets( buffer, ARRAYSIZE( buffer ) , file ) != NULL){
			strcpy( string, buffer ); 
			word = strtok( string, " " );								// its not a stop word 
			while( word != NULL ){											// Copy each word if
				if( strcmp( word, fgets( stopWord, ARRAYSIZE( stopWord ), stopWordFile ) ) != 0 ){	// into the array
						strcpy( L.data[L.length].word, word );
						L.length++;
				}
				word = strtok( NULL, " " );								// its not a stop word 
			}
		}
	}

	fclose( file );
}

void printWords(){
	for( int i = 0; i < L.length; i++ )
	{
		char* p = " `~1!2@3#4$5%6^7&8*9(0)-_=+[{]}\\|;:',<.>/?¦©・";  //collection of delimiters
		char buf[1024] = { 0 };
		strcpy( buf, L.data[i].word );    //Copy to the buf array and operate on the buf array
		char* ret = NULL;
		for (ret = strtok(buf, p); ret != NULL; ret = strtok(NULL, p))  //Use strtok for loop segmentation operation
		{
			//printf( "%s", ret );
			strcpy( L.data[i].word, ret );  //Store it in the str structure
		}
	}
}
