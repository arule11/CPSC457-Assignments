# CPSC457 Assignment 4

## Part 1: Deadlock Detector

For this question you will write a C++ function that detects a deadlock in a system state with a single instance per resource type. The system state will be provided to this function as an ordered sequence of request- and assignment-edges. Your function will start by initializing an empty system state. Then, your function will process the edges one at a time. For each edge, your function will update the system state, and run a deadlock detection algorithm. If a deadlock is detected after processing an edge, your function will stop processing any more edges and return results immediately.

The parameter edges[] is an ordered list of strings, each representing an edge. The function returns an instance of Result containing two fields as described below.

Your function will start with an empty system state – by initializing an empty graph data structure. For each string in edges[] it will parse it to determine if it represents an assignment edge or request edge, and update the graph accordingly. After inserting each edge, the function will run an algorithm that will look for a deadlock (by detecting if a cycle is present in the graph). If deadlock is detected, your function will stop processing any more edges and immediately return Result:
- with edge_index set to the index of the edge in edges[] that caused the deadlock; and
- with dl_procs[] containing process names that are involved in a deadlock. Order is arbitrary.

If no deadlock is detected after processing all edges, your function will indicate this by returning Result with edge_index=-1 and an empty dl_procs[].

Your function will be given the edges as a vector of strings, where each edge will represent and edge. A request edge will have the format "(P) -> (R)", and assignment edge will be of the form "(P) <- (R)", where (P) and (R) are the names of the process and resource, respectively.

### deadlock detection - skeleton for Assignment 4

To compile all code, type:
```
$ make
```

To run the resulting code on file test1.txt:
```
$ ./deadlock < test1.txt
```

### Test files

These are the correct results for the test files included in this repo.

| filename   | correct `edge_index` | correct `dl_procs` | minimum timings     | good timings     |
| :---------- | :-------------: | :-----------: | :-----------------: | :--------------: |
| `test1.txt` | `-1`            | `[]`          | `0.0000s`           | `0.0000s`        |
| `test2.txt` | `5`             | `[5,7]`       | `0.0000s`           | `0.0000s`        |
| `test3.txt` | `3`             | `[p7,p3]`     | `0.0000s`           | `0.0000s`        |
| `test4.txt` | `3`             | `[12,7]`      | `0.0000s`           | `0.0000s`        |
| `test5.txt` | `6`             | `[2,77]`      | `0.0000s`           | `0.0000s`        |
| `test6.txt` | `9903`          | `[ab,cd,ef]`  |`8.9431s`            | `0.8771s`        |
| `test7.txt` | `29941`         | `[is,this,answer,the,correct]`  |`191.7872s`    | `8.0726s`        |

## Part 2: Scheduler simulation

For this question you will implement a round-robin CPU scheduling simulator for a set of processes and a time slice. Each process will be described by an id, arrival time and CPU burst. Your simulator will simulate RR scheduling on these processes and for each process it will calculate its start time and finish time. Your simulator will also compute a condensed execution sequence of all processes.

The parameter quantum will contain a positive integer describing the length of the time slice and max_seq_len will contain the maximum length of execution order to be reported. The array processes will contain the description of processes, where struct Process is defined in scheduler.h as: 
```
struct Process { 
  int id; 
  int64_t arrival_time, burst; 
  int64_t start_time, finish_time; 
};
```
You must populate the start_time and finish_time for each process with computed values. You must also report the condensed execution sequence of the processes via the output parameter seq[]. You need to make sure the reported order contains at most the first max_seq_len entries. The entries in seq[] will contain either process ids, or -1 to denote idle CPU.
A condensed execution sequence is similar to a regular execution sequence, except consecutive repeated numbers are condensed to a single value. For example, if a regular sequence was [-1,-1,-1,1,1,2,1,2,2,2], then the condensed equivalent would be [-1,1,2,1,2].

### RR simulator - skeleton for Assignment 4

To compile all code, type:
```
$ make
```

To run the resulting code on file test1.txt with quantum=3 and max. execution sequence length of 20:
```
$ ./scheduler 3 20 < test1.txt
```

### Test files

The repository includes several test files. Here are correct results for these test files.

```
$ ./scheduler 3 20 < slides.txt
seq = [0,1,2,3,0,4,1,3]
+---------------------------+----------------------+----------------------+----------------------+
| Id |              Arrival |                Burst |                Start |               Finish |
+---------------------------+----------------------+----------------------+----------------------+
|  0 |                    0 |                    6 |                    0 |                   15 |
|  1 |                    0 |                    6 |                    3 |                   20 |
|  2 |                    1 |                    3 |                    6 |                    9 |
|  3 |                    2 |                    8 |                    9 |                   25 |
|  4 |                    3 |                    2 |                   15 |                   17 |
+---------------------------+----------------------+----------------------+----------------------+

$ ./scheduler 3 20 < test1.txt 
seq = [-1,0,1,0,2,1,0]
+---------------------------+----------------------+----------------------+----------------------+
| Id |              Arrival |                Burst |                Start |               Finish |
+---------------------------+----------------------+----------------------+----------------------+
|  0 |                    1 |                   10 |                    1 |                   19 |
|  1 |                    3 |                    5 |                    4 |                   15 |
|  2 |                    5 |                    3 |                   10 |                   13 |
+---------------------------+----------------------+----------------------+----------------------+

$ ./scheduler 1 20 < test1.txt 
seq = [-1,0,1,0,1,2,0,1,2,0,1,2,0,1,0]
+---------------------------+----------------------+----------------------+----------------------+
| Id |              Arrival |                Burst |                Start |               Finish |
+---------------------------+----------------------+----------------------+----------------------+
|  0 |                    1 |                   10 |                    1 |                   19 |
|  1 |                    3 |                    5 |                    4 |                   16 |
|  2 |                    5 |                    3 |                    7 |                   14 |
+---------------------------+----------------------+----------------------+----------------------+

$ ./scheduler 1 5 < test1.txt 
seq = [-1,0,1,0,1]
+---------------------------+----------------------+----------------------+----------------------+
| Id |              Arrival |                Burst |                Start |               Finish |
+---------------------------+----------------------+----------------------+----------------------+
|  0 |                    1 |                   10 |                    1 |                   19 |
|  1 |                    3 |                    5 |                    4 |                   16 |
|  2 |                    5 |                    3 |                    7 |                   14 |
+---------------------------+----------------------+----------------------+----------------------+

$ ./scheduler 100 20 < test2.txt 
seq = []
+---------------------------+----------------------+----------------------+----------------------+
| Id |              Arrival |                Burst |                Start |               Finish |
+---------------------------+----------------------+----------------------+----------------------+
+---------------------------+----------------------+----------------------+----------------------+

$ ./scheduler 300000000000 40 < test3.txt 
seq = [-1,0,1,0,2,1,0]
+---------------------------+----------------------+----------------------+----------------------+
| Id |              Arrival |                Burst |                Start |               Finish |
+---------------------------+----------------------+----------------------+----------------------+
|  0 |         100000000000 |        1000000000000 |         100000000000 |        1900000000000 |
|  1 |         300000000000 |         500000000000 |         400000000000 |        1500000000000 |
|  2 |         500000000000 |         300000000000 |        1000000000000 |        1300000000000 |
+---------------------------+----------------------+----------------------+----------------------+

$ ./scheduler 30000000000 1000 < test3.txt 
seq = [-1,0,1,0,1,0,1,0,1,0,2,1,0,2,1,0,2,1,0,2,1,0,2,1,0,2,1,0,2,1,0,2,1,0,2,1,0,2,1,0,1,0,1,0,1,0]
+---------------------------+----------------------+----------------------+----------------------+
| Id |              Arrival |                Burst |                Start |               Finish |
+---------------------------+----------------------+----------------------+----------------------+
|  0 |         100000000000 |        1000000000000 |         100000000000 |        1900000000000 |
|  1 |         300000000000 |         500000000000 |         310000000000 |        1590000000000 |
|  2 |         500000000000 |         300000000000 |         550000000000 |        1390000000000 |
+---------------------------+----------------------+----------------------+----------------------+

$ ./scheduler 1 40 < test3.txt 
seq = [-1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0]
+---------------------------+----------------------+----------------------+----------------------+
| Id |              Arrival |                Burst |                Start |               Finish |
+---------------------------+----------------------+----------------------+----------------------+
|  0 |         100000000000 |        1000000000000 |         100000000000 |        1900000000000 |
|  1 |         300000000000 |         500000000000 |         300000000001 |        1600000000000 |
|  2 |         500000000000 |         300000000000 |         500000000002 |        1400000000000 |
+---------------------------+----------------------+----------------------+----------------------+

$ ./scheduler 1 40 < test4.txt 
seq = [-1,0,1,0,1,0,1,0,1,0,1,2,0,1,0,-1,3]
+---------------------------+----------------------+----------------------+----------------------+
| Id |              Arrival |                Burst |                Start |               Finish |
+---------------------------+----------------------+----------------------+----------------------+
|  0 |                    5 |                   10 |                    5 |                   22 |
|  1 |                    6 |                    6 |                    7 |                   19 |
|  2 |                   14 |                    1 |                   16 |                   17 |
|  3 |                   50 |                   17 |                   50 |                   67 |
+---------------------------+----------------------+----------------------+----------------------+

$ ./scheduler 3 40 < test4.txt 
seq = [-1,0,1,0,1,0,2,0,-1,3]
+---------------------------+----------------------+----------------------+----------------------+
| Id |              Arrival |                Burst |                Start |               Finish |
+---------------------------+----------------------+----------------------+----------------------+
|  0 |                    5 |                   10 |                    5 |                   22 |
|  1 |                    6 |                    6 |                    8 |                   17 |
|  2 |                   14 |                    1 |                   20 |                   21 |
|  3 |                   50 |                   17 |                   50 |                   67 |
+---------------------------+----------------------+----------------------+----------------------+

$ ./scheduler 157 140 < test5.txt 
seq = [-1,0,1,2,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,3,4,-1,5]
+---------------------------+----------------------+----------------------+----------------------+
| Id |              Arrival |                Burst |                Start |               Finish |
+---------------------------+----------------------+----------------------+----------------------+
|  0 |                   10 |                 1000 |                   10 |                 4464 |
|  1 |                   30 |                 1000 |                  167 |                 4522 |
|  2 |                  100 |                 1000 |                  324 |                 4580 |
|  3 |                  500 |                 1000 |                  952 |                 4952 |
|  4 |                  501 |                 1000 |                 1109 |                 5010 |
|  5 |              5000000 |                    1 |              5000000 |              5000001 |
+---------------------------+----------------------+----------------------+----------------------+

$ ./scheduler 1 200 < test6.txt
seq = [-1,0,1,-1,2,3,-1,4,5,4,5,4,5,4,5,4,5,4,5,4,5,4,-1,6]
+---------------------------+----------------------+----------------------+----------------------+
| Id |              Arrival |                Burst |                Start |               Finish |
+---------------------------+----------------------+----------------------+----------------------+
|  0 |                   20 |                    1 |                   20 |                   21 |
|  1 |                   20 |                   10 |                   21 |                   31 |
|  2 |                 1000 |                    1 |                 1000 |                 1001 |
|  3 |                 1000 |                   10 |                 1001 |                 1011 |
|  4 |                 2000 |                 2000 |                 2000 |                 4007 |
|  5 |                 2005 |                    7 |                 2006 |                 2019 |
|  6 |                 6000 |                    1 |                 6000 |                 6001 |
+---------------------------+----------------------+----------------------+----------------------+

$ ./scheduler 5 200 < test6.txt
seq = [-1,0,1,-1,2,3,-1,4,5,4,5,4,-1,6]
+---------------------------+----------------------+----------------------+----------------------+
| Id |              Arrival |                Burst |                Start |               Finish |
+---------------------------+----------------------+----------------------+----------------------+
|  0 |                   20 |                    1 |                   20 |                   21 |
|  1 |                   20 |                   10 |                   21 |                   31 |
|  2 |                 1000 |                    1 |                 1000 |                 1001 |
|  3 |                 1000 |                   10 |                 1001 |                 1011 |
|  4 |                 2000 |                 2000 |                 2000 |                 4007 |
|  5 |                 2005 |                    7 |                 2010 |                 2022 |
|  6 |                 6000 |                    1 |                 6000 |                 6001 |
+---------------------------+----------------------+----------------------+----------------------+

$ ./scheduler 5555 200 < test6.txt
seq = [-1,0,1,-1,2,3,-1,4,5,-1,6]
+---------------------------+----------------------+----------------------+----------------------+
| Id |              Arrival |                Burst |                Start |               Finish |
+---------------------------+----------------------+----------------------+----------------------+
|  0 |                   20 |                    1 |                   20 |                   21 |
|  1 |                   20 |                   10 |                   21 |                   31 |
|  2 |                 1000 |                    1 |                 1000 |                 1001 |
|  3 |                 1000 |                   10 |                 1001 |                 1011 |
|  4 |                 2000 |                 2000 |                 2000 |                 4000 |
|  5 |                 2005 |                    7 |                 4000 |                 4007 |
|  6 |                 6000 |                    1 |                 6000 |                 6001 |
+---------------------------+----------------------+----------------------+----------------------+

$ ./scheduler 1 50 < test7.txt
seq = [-1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0]
+---------------------------+----------------------+----------------------+----------------------+
| Id |              Arrival |                Burst |                Start |               Finish |
+---------------------------+----------------------+----------------------+----------------------+
|  0 |          10000000000 |         100000000000 |          10000000000 |         160000000150 |
|  1 |          11000000000 |          10000000010 |          11000000001 |          67300000057 |
|  2 |          12000000000 |          10000000020 |          12000000002 |          69800000108 |
|  3 |          13000000000 |          10000000030 |          13000000003 |          71133333482 |
|  4 |          14000000000 |          10000000040 |          14000000004 |          71883333513 |
|  5 |          15000000000 |          10000000050 |          15000000005 |          72283333534 |
+---------------------------+----------------------+----------------------+----------------------+
```






