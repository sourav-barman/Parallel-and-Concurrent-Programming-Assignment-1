# Parallel-and-Concurrent-Programming-Assignment-1
================================================================
  CS5300 – Parallel & Concurrent Programming | Assignment 1
  Identifying Self-Dividing Numbers: SAM vs DAM
  Author : SOURAV BARMAN
================================================================

----------------------------------------------------------------
OVERVIEW
----------------------------------------------------------------
This assignment implements two parallel strategies to identify
all self-dividing numbers in the range 1 to N (where N = 10^n):

  1. SAM – Static Allocation Method
     Numbers are pre-assigned to threads before execution begins.
     Each thread receives interleaved chunks based on its ID.

  2. DAM – Dynamic Allocation Method
     Threads pick up chunks of work on-the-fly using a shared
     atomic counter (fetch_add), balancing the workload at runtime.

----------------------------------------------------------------
FILES
----------------------------------------------------------------
  SAM.cpp   — Source code for Static Allocation
  DAM.cpp   — Source code for Dynamic Allocation
  inp-params.txt               — Input parameters file
  readme.txt                   — This file

----------------------------------------------------------------
INPUT FILE FORMAT  (inp-params.txt)
----------------------------------------------------------------
The input file must be in the same directory as the executables.
It must follow this exact format:

    n,m,c
    <value_of_n>,<value_of_m>,<value_of_c>

  Where:
    n  →  Exponent such that N = 10^n  (e.g., n=5 means N=100000)
    m  →  Number of threads to spawn
    c  →  Chunk size (numbers processed per thread per iteration)

  Example (inp-params.txt):
    n,m,c
    5,10,10

----------------------------------------------------------------
COMPILATION
----------------------------------------------------------------
Make sure you have g++ installed with C++11 or later support.

  Compile SAM:
    g++ -std=c++11 -pthread -O2 -o SAM SAM.cpp

  Compile DAM:
    g++ -std=c++11 -pthread -O2 -o DAM DAM.cpp

  (On some systems, use -lpthread instead of -pthread)

----------------------------------------------------------------
EXECUTION
----------------------------------------------------------------
Ensure inp-params.txt is present in the working directory, then:

  Run SAM:
    ./SAM

  Run DAM:
    ./DAM

Both programs read inp-params.txt automatically — no command-line
arguments are needed.

----------------------------------------------------------------
SAMPLE OUTPUT
----------------------------------------------------------------
****** Static Allocation Method ******

Range = 1 to 100000 | No of Threads = 10 | Chunk Size = 10

Numbers Allocation:

Thread1: 1 to 10, 101 to 110, ...
Thread2: 11 to 20, 111 to 120, ...
...

Thread-wise Self Dividing Numbers Identification:

Thread1: 1 2 3 4 5 6 7 8 9 ...
Thread2: 11 12 ...
...

All Self Dividing Numbers in the range 1 to 100000:
1 2 3 4 5 6 7 8 9 11 12 ...

SAM Time: <nanoseconds> ns

(DAM output follows the same structure with "Dynamic Allocation Method")

----------------------------------------------------------------
NOTES
----------------------------------------------------------------
  • Both programs output execution time in nanoseconds.
  • The order of self-dividing numbers in the final consolidated
    list follows thread order (Thread1 first, then Thread2, etc.).
  • In DAM, thread-to-chunk assignment is non-deterministic and
    may vary between runs due to scheduling; the final set of
    self-dividing numbers will always be correct and complete.
  • Tested on: Linux (Ubuntu 22.04), g++ 11.4, C++11 standard.

----------------------------------------------------------------
DEPENDENCIES
----------------------------------------------------------------
  • Standard C++ library (iostream, fstream, sstream, vector,
    string, cmath, chrono)
  • C++ threading library (thread, atomic)
  • No external libraries required.

================================================================
