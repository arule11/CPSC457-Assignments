# CPSC457 Assignment 1

Your job is to improve slow-pali.cpp by writing a new implementation called fast-pali.cpp. Your new implementation should be faster than slow-pali.cpp and at least as fast as palindrome.py for all possible inputs! Your new 
implementation must match the output of the slow implementation and the Python implementation. You may re-use any code from the slow-pali.cpp file.

## Valid input
Your program must be able to handle any text input of up to 2GiB in size. You may assume that no word will be longer
than 1024 bytes. The files may or may not include a new line at the end.

Small number of test files are available in the GitLab repository, but it is expected that you create your own test 
files to help you validate your solutions. Your TAs will grade your code on inputs that are not published to you.

## Requirements
- Your program must read input from standard input.
- You are only allowed to use the read() system call wrapper. You cannot use any other APIs, such as mmap(), fopen(), fread(), fgetc(), or C++’s streams.
- Do not store the entire input in memory. You need to write your code so that it can handle any input size, even if it is bigger than the available memory.


# Files for CPSC457 Assignment 1 - Fall 2021
You can compile the C++ code by running:

```
$ make
```

You can test the slow C++ palindrome finder:

```
$ ./slow-pali < t4.txt
Longest palindrome: redder
```
To run the Python version:
```
$ ./palindrome.py < t4.txt
Longest palindrome: redder
```

