# CPSC457 Assignment 5


## Part 1: Worst-fit Dynamic Partition Simulator

You will write a worst-fit dynamic partition memory allocation simulator that approximates some of the functionality of malloc() and free() in the standard C library. The input to your simulator will be a page size (a positive integer) and list of allocation and deallocation requests. Your simulator will simulate processing all requests and then compute some statistics.

Throughout the simulation your program will maintain an ordered list of dynamic partitions. Some partitions will be marked as occupied, the rest will be marked as free. Occupied partitions will have a numeric tag attached to it. Each partition will also contain its size in bytes, and the starting address. The starting address of the first partition should be 0. Your simulator will manipulate this list of partitions as a result of processing requests. Allocation requests will be processed by finding the most appropriately sized partition and then allocating a memory from it. Deallocation requests will free up any relevant occupied partitions, and also merging any adjacent free partitions.

__Allocation request__ 

Each allocation request will have two parameters – a tag and a size. Your program will use worst-fit algorithm to find a free partition, by scanning the list of partitions from the start until the end of the list. If more than one partition qualifies, it will pick the first partition it finds (i.e. the one with the smallest address). If the partition is bigger than the requested size, the partition will be split in two – an occupied partition and a free partition. The tag specified with the allocation request will be stored in the occupied partition.

The simulation will start with an empty list of partitions, or, if you prefer, a list containing one free partition of size 0 bytes. When the simulator fails to find a suitably large free partition, it will simulate asking the OS for more memory. The amount of memory that can be requested from OS must be a multiple of page_size. The newly obtained memory will be appended at the end of your list of partitions, and if appropriate, merged with the last free partition. Your program must figure

__Deallocation request__

A deallocation request will have a single parameter – a tag. In the input list of requests, this will be denoted by a negative number, which you convert to a tag by using its absolute value.

Your simulator will find all allocated partitions with the given tag and mark them free. Any adjacent free partitions will be merged. If there are no partitions with the given tag, your simulator will ignore such deallocation request.

### sample results:
```
$ ./memsim 123 < test1.txt
pages requested:                58
largest free partition size:    129
largest free partition address: 221
elapsed time:                   0.001

$ ./memsim 321 < test2.txt
pages requested:                16
largest free partition size:    136
largest free partition address: 5000
elapsed time:                   0.000
```

## Part 2: FAT simulation

Write a function fat_check() that examines the contents of a file allocation table fat[]. The ends of block chains in the FAT will be represented by ‘-1’. Your function should find the longest possible chain terminating on each block containing ‘-1’ in the FAT, and report these lengths.

The FAT entries will be represented by N integers. Each number will be an integer in range [-1 .. N-1], where “-1” represents null pointer (or end of chain), and numbers ≥0 represent pointers to blocks. The i-th integer will represent the i-th entry in the FAT.

### sample results:

```
$ cat test1.txt
  6 12  7  7 -1 15  9 15  6 10
 14  0 -1 11 13  1 12 -1 11 18

$ ./fatsim < test1.txt
chain sizes: 1 1 5
elapsed time: 0.000s
```
```
$ cat test2.txt
1 2 3 4 5 6 7 -1
7 6 5 4 3 2 1 0
0 1 2 0 4 4 6 7
0 1 2 3 4 5 6 7

$ ./fatsim < test2.txt
chain sizes: 9
elapsed time: 0.000s
```

