#include<stdio.h>
#include<stdlib.h>
#include "sudoku_struct.h"
int _sudoku_solve = 0;

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
            if(fscanf(file, "%d", &tmp) !=1) return 1;
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
            else check[s->sudoku[i][j]] = 1;
        }
    }
    // check column
    for(int j = 0; j < 9; j++){
        char check[10] = {0};
        for(int i = 0; i < 9; i++){
            if(s->sudoku[i][j] == 0) continue;
            if(check[s->sudoku[i][j]]) return 0;
            else check[s->sudoku[i][j]] = 1;
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

int check_one(Sudoku * s, int i, int j, int num){
    int flag = 1;
    for(int _i = 0; _i < 9; _i++)
        if(s->sudoku[_i][j] == num) flag = 0;
    for(int _j = 0; _j < 9; _j++)
        if(s->sudoku[i][_j] == num) flag = 0;
    int block_i = i / 3 * 3, block_j = j / 3 * 3;
    for(int _i = block_i; _i < block_i + 3; _i++)
        for(int _j = block_j; _j < block_j + 3; _j++)
            if(s->sudoku[_i][_j] == num) flag = 0;
    return flag;
}

int max_fill(Sudoku * s, int x[], int y[]){
    int fill_cnt = 0;
    int flag = 0;
    while(s->filled < 81){
        //fill line
        flag = 0;
        for(int i = 0; i < 9; i++){
            int sum = 0, cnt = 0, emp_pos;
            for(int j = 0; j < 9; j++){
                if(s->sudoku[i][j]){
                    sum += s->sudoku[i][j];
                    cnt ++;
                }
                else emp_pos = j;
            }
            if(cnt == 8){
                int to_fill = 45 - sum;
                if(!check_one(s, i, emp_pos, to_fill)) return -fill_cnt;
                s->sudoku[i][emp_pos] = to_fill;
                flag = 1;
                x[fill_cnt] = i;
                y[fill_cnt] = emp_pos;
                fill_cnt++;
                s->filled++;
            }
        }
        if(flag) break;
        for(int j = 0; j < 9; j++){
            int sum = 0, cnt = 0, emp_pos;
            for(int i = 0; i < 9; i++){
                if(s->sudoku[i][j]){
                    sum += s->sudoku[i][j];
                    cnt ++;
                }
                else emp_pos = i;
            }
            if(cnt == 8){
                int to_fill=  45 - sum;
                if(!check_one(s, emp_pos, j, to_fill)) return -fill_cnt; 
                s->sudoku[emp_pos][j] = to_fill;
                flag = 1;
                x[fill_cnt] = emp_pos;
                y[fill_cnt] = j;
                fill_cnt++;
                s->filled++;
            }
        }
        if(flag) break;
        for(int block_i = 0; block_i < 3; block_i++) for(int block_j = 0; block_j < 3; block_j++){
            int sum = 0, cnt = 0, emp_pos_x, emp_pos_y;
            for(int i = block_i*3; i < block_i*3 +3; i++) for(int j = block_j*3;j < block_j*3 + 3; j++){
                if(s->sudoku[i][j]){
                    sum += s->sudoku[i][j];
                    cnt++;
                }
                else{
                    emp_pos_x = i;
                    emp_pos_y = j;
                }
            }
            if(cnt == 8){
                int to_fill = 45 - sum;
                if(!check_one(s, emp_pos_x, emp_pos_y, to_fill)) return -fill_cnt;
                s->sudoku[emp_pos_x][emp_pos_y] = to_fill;
                flag = 1;
                x[fill_cnt] = emp_pos_x;
                y[fill_cnt] = emp_pos_y;
                fill_cnt++;
                s->filled++;
            }
        }
        if(!flag) break;
    }
    return fill_cnt;
}

void print_sudoku(Sudoku * s){
    for(int i = 0; i < 9; i ++){
        for(int j = 0; j < 9; j++)
            printf(j == 8 ? "%d\n" : "%d ", s->sudoku[i][j]);
    }
}

void _find_empty(Sudoku * s, int * i, int * j){
    for(*i = 0; *i < 9; (*i)++) for(*j = 0; *j < 9; (*j)++)
        if(s->sudoku[*i][*j] == 0) return;
}

int error = 0;
void solve_traceback(Sudoku * s){
    if(_sudoku_solve) return;
    int _cnt = 0;
    for(int i = 0; i < 9; i++) for(int j = 0; j < 9; j++)
        if(s->sudoku[i][j]) _cnt ++;
    if(_cnt != s->filled) error=1;
    if(s->filled == 81){
        _sudoku_solve = 1;
        print_sudoku(s);
        return;
    }
    //print_sudoku(s);
    //printf("solve: %d\n", s->filled);
    //putchar('\n');
    //int fill_x[30], fill_y[30];
    //int fill_num = max_fill(s, fill_x, fill_y);
    //if(fill_num < 0){
    //    //traceback
    //    s->filled += fill_num;
    //    for(int i = 0; i < fill_num; i++)
    //        s->sudoku[fill_x[i]][fill_y[i]] = 0;
    //    return;
    //}
    //s->filled += fill_num;
    //print_sudoku(s);
    //printf("solve: %d\n", s->filled);
    //putchar('\n');
    if(s->filled == 81){
        _sudoku_solve = 1;
        return;
    }
    //find the empty point
    int i, j = 0;
    _find_empty(s, &i, &j);
    s->filled++;
    for(int num = 1; num < 10; num++){
        int flag = check_one(s, i, j, num);
        if(flag){
            s->sudoku[i][j] = num;
            solve_traceback(s);
        }
    }
    //traceback
    s->filled--;
    //s->filled -= fill_num;
    s->sudoku[i][j] = 0;
    //for(i = 0; i < fill_num; i++)
    //    s->sudoku[fill_x[i]][fill_y[i]] = 0;
}
