from sudoku import Sudoku
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('-c', help="create final sudoku layouts of a given number", type=int)
parser.add_argument('-s', help="solve given sodoku", type=str)

args = parser.parse_args()
if args.c:
    if args.c < 1 or args.c > 1000000:
        print("number invalid")
        exit(0)
    final = []
    for _ in range(args.c):
        a = Sudoku()
        final.append(str(a))
    with open("sudoku.txt", "w") as f:
        f.write('\n\n'.join(final))
elif args.s:
    with open(args.s, 'r') as f:
        data = f.read()
    s = Sudoku(data)
    s.solve()
    