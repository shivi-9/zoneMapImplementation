## Average execution time for the following workloads:
1. W1 : 5M inserts with sorted data*, 10K point queries
    Query : ./workloadgenerator -N 5000000 --sort -P 10000 && ./main
    Result : Starting Point Queries
             Time taken to perform point queries from zonemap = 4.402101e+06 microseconds
             Starting Range Queries
             Time taken to perform range query from zonemap = 6.122208e+07 microseconds

2. W2 : 5M inserts with sorted data, 1K range queries, selectivity: 0.001
    Query : ./workloadgenerator -N 5000000 --sort -R 1000 -s 0.001 && ./main
    Result : Starting Point Queries
             Time taken to perform point queries from zonemap = 4.396344e+06 microseconds
             Starting Range Queries
             Time taken to perform range query from zonemap = 5.091673e+05 microseconds

3. W3 : 5M inserts with sorted data, 1K range queries, selectivity: 0.1
    Query : ./workloadgenerator -N 5000000 --sort -R 1000 -s 0.1 && ./main
    Result : Starting Point Queries
             Time taken to perform point queries from zonemap = 4.385175e+06 microseconds
             Starting Range Queries
             Time taken to perform range query from zonemap = 1.586014e+07 microseconds

4. W4 : W1 with unsorted data
    Query : ./workloadgenerator -N 5000000 -P 10000 && ./main
    Result : Starting Point Queries
             Time taken to perform point queries from zonemap = 4.434887e+06 microseconds
             Starting Range Queries
             Time taken to perform range query from zonemap = 6.222374e+07 microseconds

5. W5 : W2 with unsorted data
    Query : ./workloadgenerator -N 5000000 -R 1000 -s 0.001 && ./main
    Result : Starting Point Queries
             Time taken to perform point queries from zonemap = 4.382705e+06 microseconds
             Starting Range Queries
             Time taken to perform range query from zonemap = 5.106047e+05 microseconds

6. W6: W3 with unsorted data
    Query : ./workloadgenerator -N 5000000 -R 1000 -s 0.1 && ./main
    Result : Starting Point Queries
             Time taken to perform point queries from zonemap = 4.379094e+06 microseconds
             Starting Range Queries
             Time taken to perform range query from zonemap = 1.588123e+07 microseconds

** Screenshot of the result also added to the repository (Result.png)

## Research Questions
1. What is the expected memory footprint (in bytes) to build the zone map? (assume: the number of elements is N and every zone has d entries) <br>

Solution : Memory to build a zone map depends on multiple factors such as the size of each element in the input data, the total number of elements in the input data, the total number of zones, and the total number of elements in that zone. 
Assuming, the total number of elements is N and every zone has d entries, then in this case, the memory footprint to build the zone map would be N * sizeOf(data type of each element) + d * sizeOf(data type of each element) * the total number of zones. Here, total number of zones will be approximately N/d

2. In practice, we may have raw data stored on disk, and the zone map is maintained in memory to reduce the number of required I/Os to answer queries. What should we do if we only have a limited memory budget to build the zone map(i.e., when the memory budget of M bytes is smaller than the expected memory footprint)? <br>

Solution : To build the zone map with budget memory, we should store the raw data on the disk and, we should also decrease the number of zones stored on the memory. For this, we should increase the size of the zones.