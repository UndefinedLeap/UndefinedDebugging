# UndefinedDebugging

This projects contains puzzles (broken C codes) that you have to solve using your debugger.

The original puzzles are borrowed from [Advent-Of-Code 2021](https://adventofcode.com/2021). The puzzles are from Day-01 to Day 10 and solutions are then broken, you must fix them and check if your output match the one in `output` file.

This is provided free and open-source, and for purpose of learning and getting fimiliar with debuggers.

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
```
TODO
```
4. Find out what wrong with solutions and fix the C code.
5. Cross-check your output with one in `output` file. Output file will as:
```
<some-number> (example, part-1)
<some-number> (example, part-2)
<some-number> (input, part-1)
<some-number> (input, part-2)
```