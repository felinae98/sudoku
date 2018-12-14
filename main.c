#include<stdio.h>
#include "sudoku.h"
#include<string.h>
#include<stdlib.h>
#include<time.h>

int main(int argc, char* argv[]){
    srand(time(NULL));
    if(argc == 1){
        //GG
        printf("usage:");
    }
    else if(argc == 3 && !strcmp("-c", argv[1])){
        //generate
        char * endptr;
        int to_gen = strtol(argv[2], &endptr, 0);
        if(*endptr != 0){
            puts("input number format error");
            return 1;
        }
        if(to_gen < 1 || to_gen > 1000000){
            puts("input number range error");
            return 1;
        }
        FILE* file = fopen("sudoku.txt", "w");
        for(int i = 0; i < to_gen; i++){
            Sudoku s = generate_sudoku();
            output_to_file(file, s);
            if(i != to_gen - 1)
            fprintf(file, "\n");
        }
    }
    else if(argc == 3 && !strcmp("-s", argv[1])){
        //solve
    }
    return 0;
}
