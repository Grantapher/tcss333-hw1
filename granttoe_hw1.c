/*
 * Grant Toepfer - HW1
 * TCSS 333
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** split_str(char*, char);
void print_month(char*, int);
#define DEFAULT_STRING_SIZE 256

int main(void) {
    int count;
    scanf("%d\n", &count);

    char str[DEFAULT_STRING_SIZE];
    char current_month[8];
    int current_precip;

    
    printf("Monthly Totals\n");
    while(0 < count--) {
        //get the line
        scanf("%s\n", str);
       
        //get date and precip columns
        char** tokens = split_str(str, ',');    
        char* date = tokens[0];
        char* precip = tokens[19];

        //convert date into output format
        char** split_date = split_str(date, '-');
        char* month = split_date[1];
        char* year = split_date[0];
        char this_month[8];
        sprintf(this_month, "%s/%s", month, year);

        //store precips as integers multiplied by 100
        char** split_precip = split_str(precip, '.');
        char* new_precip_str = strcat(split_precip[0], split_precip[1]);
        int precip_times_100 = atoi(new_precip_str);
        
        //when the month changes, print out the previous month
        if (0 != strcmp(this_month, current_month)) {
            
            //if current_month is empty, then we just entered the loop
            //and have nothing to print
            if(0 != strlen(current_month)) {
                print_month(current_month, current_precip);
            }

            //re-initialize variables
            strcpy(current_month, this_month);
            current_precip = precip_times_100;
        } else {
            //if the month hasn't changed, just add the precip
            current_precip += precip_times_100;
        }

        //destruct the string splits
        free(tokens);
        free(split_date);
        free(split_precip);
    }
    
    //print the final month
    print_month(current_month, current_precip);

    return 0;
}

void print_month(char* month, int precip) {
    printf("%7s Precip = %2d.%d\n", month, precip / 100, precip % 100);
}

char** split_str(char* str, char delim) {
    //count the number of tokens (1 by default,
    //number or tokens is 1 + num of delimiters)
    int i, num_tokens = 1;
    for(i = 0; i < strlen(str); i++) {
        char c = str[i];
        if(delim == c) num_tokens++;
    }

    char** ret = (char**) malloc(sizeof(char*) * num_tokens);
    ret[0] = str; //first token starts at beginning of the string
    
    int array_index = 1;
    while(array_index < num_tokens) {
        char* currentChar;

        //find the next delimiter
        for(currentChar = ret[array_index - 1]; //start in the previous string 
                *currentChar != delim;          //until we find the delimiter
                currentChar += sizeof(char));   //move the pointer up one character

        *currentChar = '\0'; //null terminate the previous string
        
        //set the next token to start at the character after the delimiter
        ret[array_index++] = currentChar + sizeof(char);  
    }  

    //the final token will use the '\0' at the end of the original string
    return ret;
}
