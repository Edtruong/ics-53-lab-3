#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>



#define MAXLINE 80
#define MAX_SIZE 400



char * p;
char delim[] = " \n";
int allocated_used;
int count = 1;
int block_id = 0;
int headers[50]; // array of pointers to headers


int eval(char *cmdline);
int get_int_arg(unsigned int *arg);
int get_char_arg(char *arg);
void allocate(unsigned int size);
void free_block(int block_num);
void writeheap(int block_num,char word, int copies);
void printheap(int block_num, int num_chars);
void blockList(char *p);
void assign_block ( int i, int size );

int main()
{
	int i;
	p = malloc(MAX_SIZE);
	char cmdline[MAXLINE]; //Command Line
	while(1)
{
		printf("\n> ");
		fgets(cmdline, MAXLINE, stdin);
		if (feof(stdin))
			exit(0);

		//Evaluate the line
		eval(cmdline);
	}
	free(p);
}


/*eval - evaluate a command line */
int eval(char *cmdline)
{	
	
	char *arg;
	char *cmd = strtok(cmdline, delim);
	if (strcmp(cmd, "allocate") == 0)
	{
			 unsigned int size;
			if(get_int_arg(&size) < 0) {
			return 0;
			}	
			 /* allocate function */ 
			
			allocate(size);
			
			
	}
	else if (strcmp(cmd, "free") == 0)
	{
			/*free function free a block of memory */
			unsigned int block_num;
			if(get_int_arg(&block_num) < 0 ){
				return 0;
			}
			free_block(block_num);
	}
	else if (strcmp(cmd, "blocklist") == 0)
	{	
			blockList(p);
			/*blocklist printing function prints in order ( Size Allocated Start End )*/
			
	}

	else if (strcmp(cmd, "writeheap") == 0)
	{
		unsigned int block_num; //first parameter
		char word;
		unsigned int copies;
		if(get_int_arg(&block_num) < 0 || get_char_arg(&word) < 0 || get_int_arg(&copies) < 0) {
			return 0;
		}
		writeheap(block_num, word, copies);
			/*writeheap function  writeheap 3 A 24 */
	}
	else if (strcmp(cmd, "printheap") == 0 )
	{
		unsigned int block_num; //1st parameter
		unsigned int num_chars; //2nd parameter
		if(get_int_arg(&block_num) < 0 || get_int_arg(&num_chars) < 0) {
			return 0;
		}
			/* printheap function printheap 3 10 (prints 10 characters in block 3) */
			printheap(block_num, num_chars);
	}
	else if (strcmp(cmd, "quit") == 0)
	{   /* exit/quit the program */
		free(p);
		exit(0);
	}
	else 
	{
		printf("Invalid command\n");
	}
	return;
}



int get_int_arg(unsigned int *arg) {
	char *tmp;
	if((tmp = strtok(NULL, delim)) == NULL) {
		printf("Not enough arguments!\n");
		return -1;
	}
	
	*arg = atoi(tmp);
	return 0;
}

int get_char_arg(char *arg) {
	char *tmp;
	if((tmp = strtok(NULL, delim)) == NULL) {
		printf("Not enough arguments!\n");
		return -1;
	}

	*arg = tmp[0];
	return 0;
}


void free_block(int block_num) {
	

}




void allocate(unsigned int size)
{   int allocated = 0;
	if ( allocated_used >= MAX_SIZE )  // heap is full
	{
		printf("HEAP IS FULL.\n");
		return;
	}
	if ( MAX_SIZE - allocated_used <= size + 1 )
	{
		printf("NOT ENOUGH SPACE\n");
		printf("Only %d free blocks\n", MAX_SIZE - allocated_used-2 );
		return;
	}
	
	int i = 0; //position in heap

	if ( p[i] == 0 )
		assign_block( i, size );

	else
	{ 
		while(allocated != 1){
		 if ( i + size + 1 > MAX_SIZE)
		{
			printf("SIZE EXCEEDS THE CAPACITY OF ANY FREE BLOCK.\n");
			return;
		}

		else if ( p[i] > 0){
			i += p[i]+1;
		}

		else if ( p[i] < 0 && -p[i+ p[i]] != -p[i])
		{
			i +=  1;
			/*if ( size < -p[i] ){

				assign_block (i, size);
				allocated = 1;
			}
			else{
				i -= p[i];
			} */
			
		}
		else if(p[i] < 0 && -p[i+ p[i]] == -p[i])
		{
			i += -p[i];
		}
		else if (p[i] == 0)
		{
			assign_block (i, size);
			allocated = 1;
		}

		else 
		{
			printf( "UNKNOWN ERROR OCCURED\n");
			return;
		}
	}
}
}

void assign_block ( int i, int size )
{ 	
	p[i] = size; // header indicating #of allocated blocks
	printf("block id =%d, value = %d\n", ++block_id, size);
	
	headers[block_id] = p[i]; // CHECK &p[i] compared to header[block_id]	
	

	
	if ( MAX_SIZE - allocated_used >= size + 1)
		p[size + 1 + i] = -size; //use later to keep track of freed cells
	
	allocated_used += size + 2; // tracks # of allocated blocks
	printf("used_blocked = %d ", allocated_used);
	printf("\n\n");
	for (i=0; i<allocated_used; i+=1){
    printf("%d ", p[i]); 
}
}

void writeheap(int block_num, char word, int copies){
	
}

void printheap(int block_num, int num_chars)
{


}

void blockList(char * p) {
	
}	

