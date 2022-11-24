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

Str* stopWords;//array for stop words
char* specialCharacters;//to save special characters

//fucntion to delete words from a list
void deleteWordFromList(Sqlist L, int posInArr) {
	for (int i = posInArr;i < L.length - 1;i++) {
		strcpy(L.data[i].word, L.data[i + 1].word);//replace with next words
		L.length--;//decrease number of words;
	}
}

/*for qsort() when ordering array alphabetically
more info on: https://iq.opengenus.org/qsort-in-c/
*/
int compare(const void *a, const void *b) {
	const Str* wordA = a;
	const Str* wordB = b;
	return strcmp(wordA->word, wordB->word);
}


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

	//get stop words
	stopWords = (Str*)malloc(1024 * sizeof(Str));
	FILE* stopWordsFile = fopen("stopwords.txt", "r");
	char str[100];//for scanf
	int stopWordsCount = 0;
	while (fscanf(stopWordsFile, "%s",str) == 1) {
		strcpy(stopWords[stopWordsCount++].word, str);//save stop words into stopWords array
	}
	fclose(stopWordsFile);
	//for testing that stop words got saved
	/*for (int i = 0;i < stopWordsCount;i++) {
		printf("%s\n", stopWords[i].word);
	}*/
	
	//get special characters
	specialCharacters = (char*)malloc(1000);
	FILE* specialCharFile = fopen("specialcharacters.txt", "r");
	char c;int spChCount = 0;
	while ((c = fgetc(specialCharFile)) != EOF) {
		specialCharacters[spChCount++] = c;
	}
	fclose(specialCharFile);
	//for testing that special characters got saved
	/*for (int i = 0;i < spChCount;i++) {
		printf("%c", specialCharacters[i]);
	}
	*/
	
	/*it is important to convert all characters in the words to lowercase if necessary.
	 This will be important when computing for freq. and weight.
	 It will also matter when checking for stop words
	 ex:
	 "You'll" and "you'll" should be considered the same word
	*/
	for (int i = 0;i < L.length;i++) {
		for (int j = 0;j < strlen(L.data[i].word);j++) {
			char c = L.data[i].word[j];
			if ((c >= 'A') && (c <= 'Z')) {
				//add 32 to ASCII value of character
				L.data[i].word[j] = (char)((int)c + 32);
			}
		}
	}
	
	//remove stop words
	for (int i = 0;i < L.length;i++) {
		int wordIsStopWrd = 0;
		for (int j = 0;j < stopWordsCount;j++) {
			if (strcmp(L.data[i].word, stopWords[j].word) == 0) {//check if word is a stop word
				wordIsStopWrd = 1;//change status of words in array to true
				break;
			}
		}
		if (wordIsStopWrd == 1) {
			deleteWordFromList(L, i);
		}
	}

	//alphabetize
	qsort(L.data, L.length, sizeof(*L.data), compare);

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
