## Floyd-Warshall Algorithm Parallelized

This is just a short piece of code for parallelizing the famous Floyd-Warshall algorithm which finds all pairs shortes paths in a graph! You can read about the complete description of the algorithm [here](http://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm)!

It's using OpneMP for parallelization and some manual loop-iteration-sharing mechanism for splitting the workload! 

Some of the performance measurements for the execution time of this algorithm, for both Wall-Clock (execution of the whole program including IO, data generation, kernel scheduler task switching, etc.) and CPU-time (time dedicated **ONLY** for the computation part of the algorithm) are shown in the tables below! Also included the times associated with teh sequential version of the algorithm so you can see the **speedup** and improvements!

```
CPU-Time For Sequential Version

  MatrixSize         CPU-Time
--------------|----------------
     50       |      0.000922
     100      |      0.007870
     200      |      0.060540
     300      |      0.200254
     400      |      0.484370
     500      |      0.959779
     600      |      1.619062
     700      |      2.564561
     800      |      3.824898
     900      |      5.481911
     1000     |      7.523257

CPU-Time For Parallel Version

  MatrixSize         CPU-Time
--------------|----------------
     50       |      0.001267
     100      |      0.005596
     200      |      0.034841
     300      |      0.112635
     400      |      0.262726
     500      |      0.512023
     600      |      0.873279
     700      |      1.391699
     800      |      2.070986
     900      |      2.936617
     1000     |      4.030670
     
Wall-Clock For Sequential Version

50   --> 4.19
100  --> 11.696
200  --> 67.479
300  --> 211.938
400  --> 503.97700000000003
500  --> 990.675
600  --> 1659.762
700  --> 2617.3129999999996
800  --> 3893.132
900  --> 5572.325
1000 --> 7635.053

Wall-Clock For Parallel Version

50   --> 42.97
100  --> 12.789
200  --> 48.62
300  --> 140.47799999999998
400  --> 313.649
500  --> 606.026
600  --> 1057.8300000000002
700  --> 1601.1660000000002
800  --> 2350.114
900  --> 3344.596
1000 --> 4524.646


Matrix Size 1000 and 100 times execution in the Parallel Version:
  Min time: 1258.582
  Max time: 7089.379
  Avg time: 4775.320840000001


Matrix Size 1000 and 100 times execution in the Sequential Version:
  Min time: 7691.772
  Max time: 9593.056
  Avg time: 7992.262260000001

```

*As you can see in some cases we have up to **7-8** times **speedup**!*

**Check out the Min Time in both Sequential and Parallel Version 
for matrix size 1000x1000 and 100 times execution**
