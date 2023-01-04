# UndefinedDebugging

This projects contains puzzles (broken C codes) that you have to solve using your debugger.

The original puzzles are borrowed from [Advent-Of-Code 2021](https://adventofcode.com/2021). The puzzles are from Day-01 to Day 10 with broken solution, your goal is to fix them.

> Note: Day-01 to Day-04 and Day-09 have both Part-1 and Part-2, rest have only Part-1. Because in some days, the difference between both parts's solution were only one or two lines, so for them, we skipped Part-2.

This is provided free and open-source, and for purpose of learning and getting fimiliar with debuggers.

## Single rule
1. You can't use any flags other than `-DPART1`

## How to play

1. Go to the directory of level you want to play
```bash
cd 01
```

2. Then compile the program (if you want to do part-1 than flag `-DPART1`):
```bash
gcc -DPART1 main.c
```

3. Fire-up your debugger, for lldb:
```bash
# Open lldb and load the executable
lldb ./a.out
...
# Re-direct input file 'input'/'example' to executable
(lldb) settings set target.input-path input
# Set break-points, watch-points, etc
...
(lldb) run
```
For gdb:
```bash
# TODO
```

4. Find out what wrong with solutions and fix the C code.

5. Cross-check your output with one in `output` file. Output file will as:
```
<some-number> (example, part-1)
<some-number> (example, part-2)
<some-number> (input, part-1)
<some-number> (input, part-2)
```