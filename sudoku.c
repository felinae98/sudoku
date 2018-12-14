#include<stdio.h>
#include<stdlib.h>
#include "sudoku_struct.h"

int output_to_file(FILE* file, Sudoku s){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            fprintf(file, j == 8 ? "%d\n": "%d ", s.sudoku[i][j]);
        }
    }
    return 0;
}

int load_from_file(FILE* file, Sudoku * s){
    char tmp[20];
    int cnt = 0;
    for(int line = 0; line < 9; line++){
        for(int num = 0; num < 9; num++){
            int tmp;
            if(fscanf(file, "%d", &tmp) !=0) return 1;
            if(tmp > 9 || tmp < 0) return 1;
            if(tmp) cnt++;
            s->sudoku[line][num] = tmp;
        }
    }
    s->filled = cnt;
    return 0;
}
int check_sudoku(Sudoku* s){
    // check line
    for(int i = 0; i < 9; i++){
        char check[10] = {0};
        for(int j = 0; j < 9; j++){
            if(s->sudoku[i][j] == 0) continue;
            if(check[s->sudoku[i][j]]) return 0;
            else s->sudoku[i][j] = 1;
        }
    }
    // check column
    for(int j = 0; j < 9; j++){
        char check[10] = {0};
        for(int i = 0; i < 9; i++){
            if(s->sudoku[i][j] == 0) continue;
            if(check[s->sudoku[i][j]]) return 0;
            else s->sudoku[i][j] = 1;
        }
    }
    for(int block_i = 0; block_i < 3; block_i++) for(int block_j = 0; block_j < 3; block_j++){
        char check[9] = {0};
        for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++){
            if(s->sudoku[block_i*3 + i][block_j*3 + j] == 0) continue;
            if(check[s->sudoku[block_i*3+i][block_j*3+j]]) return 0;
            else check[s->sudoku[block_i*3+i][block_j*3+j]] = 1;
        }
    }
    return 1;
}

Sudoku generate_sudoku(){
    int first_num = 3; // (2+4) % 9 +1
    int init_matrix[][9][9]={
      { { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
        { 4, 5, 6, 7, 8, 9, 1, 2, 3 },
        { 7, 8, 9, 1, 2, 3, 4, 5, 6 },
        { 2, 1, 4, 3, 6, 5, 8, 9, 7 },
        { 3, 6, 5, 8, 9, 7, 2, 1, 4 },
        { 8, 9, 7, 2, 1, 4, 3, 6, 5 },
        { 5, 3, 1, 6, 4, 2, 9, 7, 8 },
        { 6, 4, 2, 9, 7, 8, 5, 3, 1 },
        { 9, 7, 8, 5, 3, 1, 6, 4, 2 } },
      { { 3, 9, 4, 5, 1, 7, 6, 2, 8 }, 
        { 5, 1, 7, 6, 2, 8, 3, 9, 4 },
        { 6, 2, 8, 3, 9, 4, 5, 1, 7 },
        { 9, 3, 5, 4, 7, 1, 2, 8, 6 },
        { 4, 7, 1, 2, 8, 6, 9, 3, 5 },
        { 2, 8, 6, 9, 3, 5, 4, 7, 1 },
        { 1, 4, 3, 7, 5, 9, 8, 6, 2 },
        { 7, 5, 9, 8, 6, 2, 1, 4, 3 },
        { 8, 6, 2, 1, 4, 3, 7, 5, 9 } },
      { { 7, 6, 1, 9, 8, 4, 2, 3, 5 }, 
        { 9, 8, 4, 2, 3, 5, 7, 6, 1 },
        { 2, 3, 5, 7, 6, 1, 9, 8, 4 },
        { 6, 7, 9, 1, 4, 8, 3, 5, 2 },
        { 1, 4, 8, 3, 5, 2, 6, 7, 9 },
        { 3, 5, 2, 6, 7, 9, 1, 4, 8 },
        { 8, 1, 7, 4, 9, 6, 5, 2, 3 },
        { 4, 9, 6, 5, 2, 3, 8, 1, 7 },
        { 5, 2, 3, 8, 1, 7, 4, 9, 6 } },
      { { 7, 1, 5, 4, 3, 6, 2, 9, 8 }, 
        { 4, 3, 6, 2, 9, 8, 7, 1, 5 },
        { 2, 9, 8, 7, 1, 5, 4, 3, 6 },
        { 1, 7, 4, 5, 6, 3, 9, 8, 2 },
        { 5, 6, 3, 9, 8, 2, 1, 7, 4 },
        { 9, 8, 2, 1, 7, 4, 5, 6, 3 },
        { 3, 5, 7, 6, 4, 1, 8, 2, 9 },
        { 6, 4, 1, 8, 2, 9, 3, 5, 7 },
        { 8, 2, 9, 3, 5, 7, 6, 4, 1 } } };
    int mat_num = rand() % 4;
    Sudoku rt;
    // init
    for(int i = 0; i < 9; i++) for(int j = 0; j < 9; j++)
        rt.sudoku[i][j] = init_matrix[mat_num][i][j];
    // shift line
    for(int i = 0; i < 20; i++){
        int block_num = rand() % 3;
        int first_shift = rand() % 3;
        int second_shift = rand() % 2;
        if(second_shift >= first_shift) second_shift ++;
        first_shift += block_num * 3;
        second_shift += block_num * 3;
        int tmp;
        for(int i = 0; i < 9; i++){
            tmp = rt.sudoku[first_shift][i];
            rt.sudoku[first_shift][i] = rt.sudoku[second_shift][i];
            rt.sudoku[second_shift][i] = tmp;
        }
    }
    //shift column
    for(int i = 0; i < 20; i++){
        int block_num = rand() % 3;
        int first_shift = rand() % 3;
        int second_shift = rand() % 2;
        if(second_shift >= first_shift) second_shift ++;
        first_shift += block_num * 3;
        second_shift += block_num * 3;
        int tmp;
        for(int i = 0; i < 9; i++){
            tmp = rt.sudoku[i][first_shift];
            rt.sudoku[i][first_shift] = rt.sudoku[i][second_shift];
            rt.sudoku[i][second_shift] = tmp;
        }
    }
    if(rt.sudoku[0][0] != first_num){
        int swap_1 = first_num, swap_2 = rt.sudoku[0][0];
        for(int i = 0; i < 9; i++) for(int j = 0; j < 9; j++){
            if(rt.sudoku[i][j] == swap_1) rt.sudoku[i][j] = swap_2;
            else if(rt.sudoku[i][j] == swap_2) rt.sudoku[i][j] = swap_1;
        }
    }
    if(check_sudoku(&rt)) puts("GG");
    return rt;
}

int check_one(Sudoku *s, int pt_i, int pt_j){
    char check[9] = {0};
    for(int j = 0; j < 9; j++){
        if(s->sudoku[pt_i][j] == 0) continue;
        if(check[s->sudoku[pt_i][j]]) return 0;
        else check[s->sudoku[pt_i][j]] = 1;
    }
    for(int i = 0; i < 9; i++) check[i] = 0;
    for(int i = 0; i < 9; i++){
        if(s->sudoku[i][pt_j] == 0) continue;
        if(check[s->sudoku[i][pt_j]]) return 0;
        else check[s->sudoku[i][pt_j]] = 1;
    }
    for(int i = 0; i < 9; i++) check[i] = 0;
    int block_i = pt_i / 3;
    int block_j = pt_j / 3;
    for(int i = block_i; i < block_i + 3; i++) for(int j = block_j; j < block_j + 3; j++){
        if(s->sudoku[i][j] == 0) continue;
        if(check[s->sudoku[i][j]]) return 0;
        else check[s->sudoku[i][j]] = 1;
    }
    return 1;
}

