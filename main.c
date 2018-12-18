#include<stdio.h>
#include "sudoku.h"
#include<string.h>
#include<stdlib.h>
#include<time.h>

extern int _sudoku_solve;

int main(int argc, char* argv[]){
    srand(time(0));
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
        FILE* file = fopen(argv[2], "r");
        if(!file){
            printf("can't open file %s", argv[2]);
            return 1;
        }
        Sudoku s;
        int res = load_from_file(file, &s);
        if(res){
            puts("sudoku format error");
            return 1;
        }
        _sudoku_solve = 0;
        solve_traceback(&s);
        //print_sudoku(&s);
    }
    return 0;
}
