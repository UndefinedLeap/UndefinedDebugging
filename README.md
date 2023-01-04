# UndefinedDebugging


## Single rule
1. You can't use any flags other than `-DPART1`

## How to play

1. Go to the directory of level you want to play
```
cd 01
```
2. Then compile the program (if you want to do part-1 than flag `-DPART1`):
```
gcc -DPART1 main.c
```
3. Fire-up your debugger, for lldb:
```
lldb ./a.out # Open lldb and load the executable
...
(lldb) settings set target.input-path input # Re-direct input file 'input'/'example' to executable
# set break-points, watch-points, etc
(lldb) run
```
For gdb: