#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SZ 50

//prototypes
void usage(char *);
void print_buff(char *, int);
int  setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int  count_words(char *, int, int);
//add additional prototypes here
void reverse_string(char *, int);
void word_print(char *, int);


int setup_buff(char *buff, char *user_str, int len){
   //TODO: #4:  Implement the setup buff as per the directions
	bool prevCharIsSpace = false;
	int i = 0; // Used to iterate through the user_str
	int j = 0; // Used to put char in buff
	// If starts with spaces or tab
	while (user_str[i] == ' ' || user_str[i] == '\t'){
        i++;
   }
	while(user_str[i] != '\0'){
		// If char is not a space or a tab place char into buff
		if(user_str[i] != ' ' && user_str[i] != '\t'){
			buff[j] = user_str[i];
			j++;
			prevCharIsSpace = false;
		}
		// If char is a space or tab 
		else if(!prevCharIsSpace){
			buff[j] = ' ';
			j++;
			prevCharIsSpace = true;
		}
		i++;
	}
	// For the error -1 = The user supplied string is too large
	if(j > len){
		return -1;
	}
	// If the buffer has a spaces or tab at the end
	while(buff[j-1] == ' ' || buff[j-1] == '\t'){
		j--;
   }
	// To fill the buff with dots
	while(j<len){
		buff[j] = '.';
		j++;
	}
	// returning the length
   return i;
}

void print_buff(char *buff, int len){
    printf("Buffer:  [");
    for (int i=0; i<len; i++){
        putchar(*(buff+i));
    }
	 printf("]");
    putchar('\n');
}

void usage(char *exename){
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);

}

int count_words(char *buff, int len, int str_len){
    //YOU MUST IMPLEMENT
	 int wc = 0;
	 bool word_start = false;

	// iterate through buff wc incrementing for each word
	 for(int i=0; i<str_len; i++){
	 	if(!word_start && buff[i] != ' ' && i <len){
			wc++;
			word_start = true;
		}
		if(buff[i] == ' '){
			word_start = false;
      }
	 }
    return wc;
}

//ADD OTHER HELPER FUNCTIONS HERE FOR OTHER REQUIRED PROGRAM OPTIONS
void  reverse_string(char *str, int len){
	int end_idx = len-1;        
	int start_idx = 0;
   char tmp_char;
	while(start_idx < end_idx){ // swap char in str[start_idx] and str[end_idx]
		tmp_char = str[start_idx];
		str[start_idx] =  str[end_idx];
		str[end_idx] = tmp_char;
		start_idx++;
		end_idx--;
	}
   return;
}

void  word_print(char *str, int len){
   int last_char_idx = len-1;  //index of last char - strlen(str)-1;
   int wc = 0;         //counts words
   int wlen = 0;       //length of current word
   bool word_start = false;    //am I at the start of a new word

	// iterate through str and printing out each character
	// according to the outputs needed
	for(int i=0; i<len; i++){
		char ch = str[i];
      if(!word_start && ch != ' '){
			wc++;
         word_start = true;
			printf("%d. ", wc);
			wlen = 0;
      }
		if(word_start){
			if(ch != ' '){
				putchar(ch);
				wlen++;
			}
			if(ch == ' ' || i == last_char_idx){
				printf("(%d)\n", wlen);
				word_start = false;
				wlen = 0;
			}
		}
	}
}

int main(int argc, char *argv[]){

    char *buff;             //placehoder for the internal buffer
    char *input_string;     //holds the string provided by the user on cmd line
    char opt;               //used to capture user option from cmd line
    int  rc;                //used for return codes
    int  user_str_len;      //length of user supplied string
	 int len = 0;

    //TODO:  #1. WHY IS THIS SAFE, aka what if arv[1] does not exist?
	 
	 // This is safe because even if argv[1] does not exist, argc indicating
	 // the amount of arguments in the command line would be less than 2 calling the usage 
	 // function and exit accordingly. Also, if the first argument indicates
	 // the program and the second argument does not contain a "-", it would also exit.
    if ((argc < 2) || (*argv[1] != '-')){
        usage(argv[0]);
        exit(1);
    }

    opt = (char)*(argv[1]+1);   //get the option flag

    //handle the help flag and then exit normally
    if (opt == 'h'){
        usage(argv[0]);
        exit(0);
    }

    //WE NOW WILL HANDLE THE REQUIRED OPERATIONS

    //TODO:  #2 Document the purpose of the if statement below

	 // The purpose of the if statement is to make sure the program received enough arguments, 
	 // equal to or greater than 3 otherwise the usage function would be called and the program exits.
    if (argc < 3){
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; //capture the user input string

    //TODO:  #3 Allocate space for the buffer using malloc and
    //          handle error if malloc fails by exiting with a 
    //          return code of 99
	 buff = (char*) malloc(sizeof(char) * BUFFER_SZ);
	 if (buff == NULL){
	 	exit(99);
	 }

    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);     //see todos
    if (user_str_len < 0){
        printf("Error setting up buffer, error = %d", user_str_len);
        exit(2);
    }
	 // len of buff without dots
	 for (int i=0; i<BUFFER_SZ; i++){
	 	if(buff[i] == '.'){
	 		break;
    	}
		len++;
	}

    switch (opt){
        case 'c':
            rc = count_words(buff, BUFFER_SZ, user_str_len);  //you need to implement
            if (rc < 0){
                printf("Error counting words, rc = %d", rc);
                exit(2);
            }
            printf("Word Count: %d\n", rc);
            break;

        //TODO:  #5 Implement the other cases for 'r' and 'w' by extending
        //       the case statement options
		  case 'r':
		      reverse_string(buff, len);
				break;
		  case 'w':
		  		printf("Word Print\n----------\n");
            word_print(buff, len);
            printf("\n");
            rc = count_words(buff, BUFFER_SZ,user_str_len);
            printf("Number of words returned: %d\n",rc);
		  		break;
		  case 'x':
		  		if(argc != 5){
					return -1;
				}
		  		printf("Not Implemented!");
				return -2; 
				exit(0);
        default:
            usage(argv[0]);
            exit(1);
    }

    //TODO:  #6 Dont forget to free your buffer before exiting
	 print_buff(buff,BUFFER_SZ);

	 free(buff);
	 buff = NULL;
    exit(0);
}

//TODO:  #7  Notice all of the helper functions provided in the 
//          starter take both the buffer as well as the length.  Why
//          do you think providing both the pointer and the length
//          is a good practice, after all we know from main() that 
//          the buff variable will have exactly 50 bytes?
//  
// 			I think providing both the pointer and the length for helper
//				functions is good practice because this allows for multiple
// 			different buffers to be used and tested, allowing to implement
// 			and change parts of the fucntions when needed. This also
// 			allows for errors to be fixed more easily because we can see 
// 			all the intenions in the code.
