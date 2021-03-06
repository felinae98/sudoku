#include "sudoku_struct.h"
#include<stdio.h>
int output_to_file(FILE* file, Sudoku s);
int load_from_file(FILE* file, Sudoku * s);
Sudoku generate_sudoku();
int check_sudoku(Sudoku* s);
int check_one(Sudoku *s, int pt_i, int pt_j);
int max_fill(Sudoku * s, int x[], int y[]);
void solve_traceback(Sudoku * s);
void print_sudoku(Sudoku * s);