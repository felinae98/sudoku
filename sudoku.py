import numpy as np
import random
import itertools

class Sudoku:

    __solved = False

    init_matrixs = np.array([
      [ [ 1, 2, 3, 4, 5, 6, 7, 8, 9 ],
        [ 4, 5, 6, 7, 8, 9, 1, 2, 3 ],
        [ 7, 8, 9, 1, 2, 3, 4, 5, 6 ],
        [ 2, 1, 4, 3, 6, 5, 8, 9, 7 ],
        [ 3, 6, 5, 8, 9, 7, 2, 1, 4 ],
        [ 8, 9, 7, 2, 1, 4, 3, 6, 5 ],
        [ 5, 3, 1, 6, 4, 2, 9, 7, 8 ],
        [ 6, 4, 2, 9, 7, 8, 5, 3, 1 ],
        [ 9, 7, 8, 5, 3, 1, 6, 4, 2 ] ],
      [ [ 3, 9, 4, 5, 1, 7, 6, 2, 8 ], 
        [ 5, 1, 7, 6, 2, 8, 3, 9, 4 ],
        [ 6, 2, 8, 3, 9, 4, 5, 1, 7 ],
        [ 9, 3, 5, 4, 7, 1, 2, 8, 6 ],
        [ 4, 7, 1, 2, 8, 6, 9, 3, 5 ],
        [ 2, 8, 6, 9, 3, 5, 4, 7, 1 ],
        [ 1, 4, 3, 7, 5, 9, 8, 6, 2 ],
        [ 7, 5, 9, 8, 6, 2, 1, 4, 3 ],
        [ 8, 6, 2, 1, 4, 3, 7, 5, 9 ] ],
      [ [ 7, 6, 1, 9, 8, 4, 2, 3, 5 ], 
        [ 9, 8, 4, 2, 3, 5, 7, 6, 1 ],
        [ 2, 3, 5, 7, 6, 1, 9, 8, 4 ],
        [ 6, 7, 9, 1, 4, 8, 3, 5, 2 ],
        [ 1, 4, 8, 3, 5, 2, 6, 7, 9 ],
        [ 3, 5, 2, 6, 7, 9, 1, 4, 8 ],
        [ 8, 1, 7, 4, 9, 6, 5, 2, 3 ],
        [ 4, 9, 6, 5, 2, 3, 8, 1, 7 ],
        [ 5, 2, 3, 8, 1, 7, 4, 9, 6 ] ],
      [ [ 7, 1, 5, 4, 3, 6, 2, 9, 8 ], 
        [ 4, 3, 6, 2, 9, 8, 7, 1, 5 ],
        [ 2, 9, 8, 7, 1, 5, 4, 3, 6 ],
        [ 1, 7, 4, 5, 6, 3, 9, 8, 2 ],
        [ 5, 6, 3, 9, 8, 2, 1, 7, 4 ],
        [ 9, 8, 2, 1, 7, 4, 5, 6, 3 ],
        [ 3, 5, 7, 6, 4, 1, 8, 2, 9 ],
        [ 6, 4, 1, 8, 2, 9, 3, 5, 7 ],
        [ 8, 2, 9, 3, 5, 7, 6, 4, 1 ] ] ], dtype=np.int8)

    def generate_random_sudoku(self):
        first_num = 3 #(2+4) % 9 + 1
        self.sudoku = self.init_matrixs[random.randrange(0,4)]
        for _ in range(20):
            # 行变换
            block_num = random.randrange(0,3)
            p, q = random.choices([i for i in range(block_num*3, block_num*3+3)], k=2)
            self.sudoku[[p,q],:] = self.sudoku[[q,p],:]
        for _ in range(20):
            # 行变换
            block_num = random.randrange(0,3)
            p, q = random.choices([i for i in range(block_num*3, block_num*3+3)], k=2)
            self.sudoku[:,[p,q]] = self.sudoku[:,[q,p]]
        if self.sudoku[0][0] == first_num:
            return
        cur_num = self.sudoku[0][0]
        for i, j in itertools.product(range(9), repeat=2):
            if self.sudoku[i][j] == cur_num:
                self.sudoku[i][j] = first_num
            elif self.sudoku[i][j] == first_num:
                self.sudoku[i][j] = cur_num

    def check(self):
        # row check
        for row in self.sudoku:
            _check = [False] * 10
            for num in row:
                if num == 0: continue
                if _check[num]: return False
                else: _check[num] = True
        # column check
        for column in self.sudoku.T:
            _check = [False] * 10
            for num in column:
                if num == 0: continue
                if _check[num]: return False
                else: _check[num] = True
        # 3*3 check
        for i,j in itertools.product((0,1,2), repeat=2):
            matrix_s = self.sudoku[i*3:i*3+3, j*3:j*3+3].reshape((9))
            _check = [False] * 10
            for num in matrix_s:
                if num == 0: continue
                if _check[num]: return False
                else: _check[num] = True
        return True

    def __init__(self, s=None):
        if not s:
            self.generate_random_sudoku()            
            assert self.check()
        elif isinstance(s, Sudoku):
            self.sudoku = s.sudoku.copy()
        elif isinstance(s, str):
            # self.import_check(str)
            s = s.strip()
            s = s.split('\n')
            self.sudoku = np.array([list(map(lambda x: int(x), i.split())) for i in s])
            #self.sudoku = np.array(list(map(lambda x: int(x),map(lambda x: x.split(), s))))
            # add check
        else:
            raise Exception
    
    def __str__(self):
        lines = []
        for l in self.sudoku:
            lines.append(' '.join(map(lambda x: str(x), l.tolist())))
        return '\n'.join(lines)

    def max_fill(self):
        while True:
            if np.count_nonzero(self.sudoku) == 81: 
                return
            flag = False
            # fill row
            for i in range(9):
                if np.count_nonzero(self.sudoku[i]) == 8:
                    flag = True
                    to_fill_num = 45 - self.sudoku[i].sum()
                    for j in range(9):
                        if self.sudoku[i][j] == 0:
                            self.sudoku[i][j] = to_fill_num
                            break
            # fill collomn
            for j in range(9):
                if np.count_nonzero(self.sudoku[:,j]) == 8:
                    flag = True
                    to_fill_num = 45 - self.sudoku[:,j].sum()
                    for i in range(9):
                        if self.sudoku[i][j] == 0:
                            self.sudoku[i][j] = to_fill_num
                            break
            # fill 3*3
            for i,j in itertools.product((0,1,2), repeat=2):
                if np.count_nonzero(self.sudoku[3*i:3*i+3, 3*j:3*j+3]) == 8:
                    flag = True
                    to_fill_num = 45 - self.sudoku[3*i:3*i+3, 3*j:3*j+3].sum()
                    for p, q in itertools.product(range(3*i, 3*i+3), range(3*j, 3*j+3)):
                        if self.sudoku[p][q] == 0:
                            self.sudoku[p][q] = to_fill_num
                            break
            if not flag: break 

    def solve(self):
        type(self).__solved = False
        self.__traceback()
        if not type(self).__solved:
            print("no solution")
        else:
            print(str(self))

    def __traceback(self):
        print(str(self))
        print('')
        if type(self).__solved:
            return
        if np.count_nonzero(self.sudoku) == 81:
            type(self).__solved = True
            return
        # search the unfill
        self.max_fill()
        for i,j in itertools.product([_ for _ in range(9)], repeat=2):
            if self.sudoku[i][j] != 0:
                break
        candidate = [True] * 10
        for _j in range(9):
            candidate[self.sudoku[i][_j]] = False
        for _i in range(9):
            candidate[self.sudoku[_i][j]] = False
        block_i = i // 3 * 3
        block_j = j // 3 * 3
        for _i, _j in itertools.product(range(block_i, block_i + 3), range(block_j, block_j + 3)):
            candidate[self.sudoku[_i][_j]] = False
        for _ in range(1, 10):
            if candidate[_]:
                next_suduku = Sudoku(self)
                next_suduku.sudoku[i][j] = _
                next_suduku.__traceback()
            if type(self).__solved:
                return
        
    def import_check(self, string):
        lines = string.splitlines(False)
        if len(lines) != 9:
            raise Exception("format error")
        for line in lines:
            nums = line.split()
            if len(nums) != 9:
                raise Exception("format error")
            for num in nums:
                if int(num) < 0 or int(num) > 9:
                    raise Exception("format error")

if __name__ == "__main__":
    with open('./sudoku.txt', 'r') as f:
        data = f.read()
    a = Sudoku(data)
    a.max_fill()
    print(a)