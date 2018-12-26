# sudoku
A basic suduko program implement by C
## usage
### create n sudoku final layout
`./sudoku -c n`

the created layouts is in sudoku.txt in the current directory
### solve the given problem
`./sudoku -s problem.txt`

the problem.txt should like this:
```
0 0 9 0 0 8 0 4 0
6 0 0 0 0 0 0 1 7
0 1 0 0 4 0 0 0 0
0 0 0 0 0 0 0 0 4
4 8 0 6 0 3 0 2 1
3 0 0 0 0 0 0 0 0
0 0 0 0 9 0 0 8 0
2 4 0 0 0 0 0 0 6
0 5 0 7 0 0 1 0 0
```
and the output will be:
```
7 2 9 1 6 8 5 4 3
6 3 4 9 2 5 8 1 7
8 1 5 3 4 7 2 6 9
5 6 2 8 1 9 3 7 4
4 8 7 6 5 3 9 2 1
3 9 1 4 7 2 6 5 8
1 7 3 2 9 6 4 8 5
2 4 8 5 3 1 7 9 6
9 5 6 7 8 4 1 3 2
```
## Performance
* generate 1000000 final layouts
    * `12.81s user 0.35s system 99% cpu 13.183 total`
* generate 1 final layouts
    * `0.00s user 0.08s system 97% cpu 0.079 total`
* solve the example problem
    * `0.24s user 0.00s system 99% cpu 0.240 total` 