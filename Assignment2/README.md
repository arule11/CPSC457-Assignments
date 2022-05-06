# CPSC457 Assignment 2

For this assignment you need to write a function safecall with the signature: 
```
int safecall(int n);
```
The purpose of safecall() function is to call another function, unsafe(), and return the result of that call. If the unsafe function was well behaved, you could write safecall like this:
```
int safecall(int i) { 
   return unsafe(i); 
}
```
However, the unsafe() function can misbehave, and you need to address this in your implementation of safecall. The misbehavior of unsafe() is that it sometimes runs for too long, sometimes it runs forever, and other times it even crashes. You need to write safecall() in such a way that it calls unsafe() similar to the above code, but also detects if unsafe misbehaves. If you detect no misbehavior, you simply return the result unsafe(), but if you detect misbehavior, you return special values (-1 or -2) as follows:

- If unsafe(i) runs for longer than 1 second, you stop the execution of unsafe(), and return -1
- If unsafe(i) crashes, you return -2
- If unsafe(i) returns a result in under 1 second, you return the result.

In order to deal with unsafe()’s misbehavior, you need to create a child process (using fork system call) and run unsafe() in the child process. The parent will then monitor the child process for misbehavior. You will also need a mechanism for transferring the results obtained by calling unsafe() in the child process back to the parent process.


## Starter code for CPSC 457 Assignment 2 (Fall 2021)

You can compile the C++ code by running:

```
$ make
```

You can run the code:

```
$ ./safecall < test1.txt
Finished in 0s
Correct results, good job.
```

## command line options

By default, the `main.cpp` driver will only print out outputs with wrong results.

```
$ ./safecall < test4.txt
Only displaying outputs with errors
==================================================
      | Expected   | Observed
Index | Output     | Output
--------------------------------------------------
    1 | -1         | 1          ! wrong
    3 | -1         | 3          ! wrong
    5 | -1         | 5          ! wrong
    7 | -1         | 7          ! wrong
    8 | -1         | 8          ! wrong
   10 | -1         | 10         ! wrong
   11 | -1         | 11         ! wrong
   12 | -1         | 12         ! wrong
   13 | -1         | 13         ! wrong
   14 | -1         | 14         ! wrong
==================================================
Finished in 50.004s
Wrong results :(
```

If you want to see all outputs, including correct ones, specify the
word 'all' on the command line:

```
$ ./safecall all < test4.txt
Calling safecall(0)
   safecall(0) returned 1000 after 0s
Calling safecall(1)
   safecall(1) returned 1 after 5s
Calling safecall(2)
   safecall(2) returned 2000 after 0s
Calling safecall(3)
   safecall(3) returned 3 after 5s
Calling safecall(4)
   safecall(4) returned 3001 after 0s
Calling safecall(5)
   safecall(5) returned 5 after 5s
Calling safecall(6)
   safecall(6) returned 4000 after 0s
Calling safecall(7)
   safecall(7) returned 7 after 5s
Calling safecall(8)
   safecall(8) returned 8 after 5s
Calling safecall(9)
   safecall(9) returned 6000 after 0s
Calling safecall(10)
   safecall(10) returned 10 after 5s
Calling safecall(11)
   safecall(11) returned 11 after 5s
Calling safecall(12)
   safecall(12) returned 12 after 5s
Calling safecall(13)
   safecall(13) returned 13 after 5s
Calling safecall(14)
   safecall(14) returned 14 after 5s

Displaying all outputs
==================================================
      | Expected   | Observed
Index | Output     | Output
--------------------------------------------------
    0 | 1000       | 1000
    1 | -1         | 1          ! wrong
    2 | 2000       | 2000
    3 | -1         | 3          ! wrong
    4 | 3001       | 3001
    5 | -1         | 5          ! wrong
    6 | 4000       | 4000
    7 | -1         | 7          ! wrong
    8 | -1         | 8          ! wrong
    9 | 6000       | 6000
   10 | -1         | 10         ! wrong
   11 | -1         | 11         ! wrong
   12 | -1         | 12         ! wrong
   13 | -1         | 13         ! wrong
   14 | -1         | 14         ! wrong
==================================================
Finished in 50.002s
Wrong results :(
```

If you don't want to see any outputs, specify 'none' on the command
line:

```
$ ./safecall none < test4.txt
Finished in 50.004s
Wrong results :(
```
