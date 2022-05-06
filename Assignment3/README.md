# CPSC457 Assignment 3

## Part 1: Calculating 𝛑

Improve the performance of an existing single-threaded calcpi program by converting it to a multi-threaded implementation.

The function uint64_t count_pi(int r, int N) takes two parameters – the radius and number of threads, and returns the number of pixels inside the circle or radius 𝑟 centered at (0,0) for every pixel (𝑥,𝑦) in squre −𝑟≤𝑥,𝑦≤𝑟. The current implementation is single threaded, so it ignores the N argument. Your job is to re-implement the function so that it uses N threads to speed up its execution, such that it runs N times faster with N threads on hardware where N threads can run concurrently. Please note that your assignment will be marked both for correctness and the speedup it achieves.

You need to find a way to parallelize the algorithm without using any synchronization mechanisms, such as mutexes, semaphores, atomic types, etc. You are only allowed to create and join threads.

### Calculates PI by summing the circle's area, as explained here:

https://en.wikipedia.org/wiki/Approximations_of_%CF%80#Summing_a_circle's_area

You need to re-implement `count_pi()` in calcpi.cpp to make it multi-threaded.

To compile the code:
```
make
```
To run it with r=1000 and n_threads=1:
```
./calcpi 1000 1
```

## Part 2: Detecting Primes

Convert a single-threaded program detectPrimes to a multi-threaded implementation.

If duplicate primes appear in the input, they will be duplicated in the output. detectPrimes accepts a single command line argument – a number of threads. This parameter is ignored in the current implementation because it is single threaded. Your job is to improve the execution time of detectPrimes by making it multi-threaded, and your implementation should use the number of threads given on the command line.

The function takes two parameters: the list of numbers to test, and the number of threads to use. The function is called by the driver (main.cpp) after parsing the standard input and command line. Your implementation should use n_threads number of threads. Ideally, if the original single-threaded program takes time 𝑇 to complete a test, then your multi-threaded implementation should finish that same test in 𝑇/𝑁 time when using 𝑁 threads. To achieve this goal, you will need to design your program so that:
- You give each thread the same amount of work;
- Your multi-threaded implementation does the same amount of work as the single-threaded version; and
- The synchronization mechanisms you utilize are efficient


### detects primes from a list of numbers on standard input

This is a skeleton code for an assignment in CPSC457.

The program takes a single argument - number of threads that should be used
to speed up the computation.

* reads in a positive integers in range (2 .. 2^63-1) from standard input
* for each number on input:
  * if the number is not prime, it is ignored
  * if the number is prime, it is printed to standard output


compile with:
```sh
$ make
```

To find all prime numbers betwee 1 and 1000:
```console
$ seq 1000 | ./detectPrimes 5
Using 5 threads.
Identified 168 primes:
  2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 101
  103 107 109 113 127 131 137 139 149 151 157 163 167 173 179 181 191 193 197
  199 211 223 227 229 233 239 241 251 257 263 269 271 277 281 283 293 307 311
  313 317 331 337 347 349 353 359 367 373 379 383 389 397 401 409 419 421 431
  433 439 443 449 457 461 463 467 479 487 491 499 503 509 521 523 541 547 557
  563 569 571 577 587 593 599 601 607 613 617 619 631 641 643 647 653 659 661
  673 677 683 691 701 709 719 727 733 739 743 751 757 761 769 773 787 797 809
  811 821 823 827 829 839 853 857 859 863 877 881 883 887 907 911 919 929 937
  941 947 953 967 971 977 983 991 997

Finished in 0.0000s
```
To test the numbers in file `easy.txt`:
```console
$ ./detectPrimes 1 < ./easy.txt
Using 1 thread.
Identified 7 primes:
  2 3 5 7 101 103 107

Finished in 0.0000s
```

