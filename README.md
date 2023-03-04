# Zonemap Implementation


## About

This is an implemenation of Zonemaps. I used TemplateZonemaps repository for this project.

## Generating Workloads
You will be asked to generate workloads of a specific size, and generate specific number of point and
range queries. An incomplete workload generator is provided as part of the API that performs the
required functionality (**not that you are required to implement the range query generator for specfic
selectivity**).  Compile the workload generator using the "make" command, and execute using
```c
./workloadgenerator --help
```
You can get
```c
  ./workloadgenerator {OPTIONS}

    Zonemap_Workload_Parser.

  OPTIONS:

      Workload parameters:
        -N[N], --num-points=[N]           The number of total elements [def:
                                          1000000]
        --UB=[UB],
        --upper-bound-of-the-max-element=[UB]
                                          The upper bound of the largest
                                          positive element [def: 3000000]
        -P[P], --num-point-queries=[P]    The number of total point queries
                                          [def: 10000] (duplicates may exist in
                                          the input data, there might be more
                                          than one matching records)
        -R[R], --num-range-queries=[R]    The number of total range queries
                                          [def: 1000]
        -s[s],
        --selectivity-of-range-queries=[s]
                                          The selectivity for each range queries
                                          (0 <= s <= 1), [def: 0.5]
        --sort                            sort the input workload
```
For example, to generate a workload of 1 Million integers in file `workload.dat`, 10000 point queries in
file`point_queries`.txt, and an empty file `range_queries.txt` (you can define the format of range
queries by yourself).
```
./workloadgenerator
```
or 
```
./workload -N 1000000 -P 10000
```
## Zone Map Header
The zonemaps.h header file is a template that defines the basic components of a zone map data structure.
It is required to implement the data structure using this template in a separate file named
"zonemaps.cpp". You are free to modify certain components of the template to improve performance of the
data structure, however the core functionality should remain the same. In your implementation, it is
important to comment your code to highlight various design decisions and logic. 

## Testing 
The main.cpp file provides a foundational testing framework expected for this project. You are required
to generate the workloads, read the data, build the zone map, and benchmark point queries and range
queries. We have already provided a simple logic to benchmark the point query. You are required to
implement parsing the range queries from`range_queries.txt` and benchmarking the range query
performance. The execution times are to be written either into a log file or displayed onto the terminal
 along with other relevant details about the workload, such as: the input workload size, the number of
queries, the selectivity of range queries etc. 

Compile all files using the "make" command.
There are currently 4 test cases pre-configured in main.cpp, as per the assignment request.
Once the implementation of zone maps is complete, you will be required to fill in the appropriate test
call in the main.cpp file for the point/range queries. 
