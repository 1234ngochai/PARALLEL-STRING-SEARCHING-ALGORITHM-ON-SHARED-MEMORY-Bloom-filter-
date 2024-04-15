# Parallel String Searching using Bloom Filter

## Project Overview
This personal project focuses on implementing and optimizing a parallel string searching algorithm using a Bloom Filter on shared memory architecture. The objective is to improve the efficiency of string matching processes, specifically targeting large datasets by utilizing parallel computing techniques with C or C++ and POSIX/OpenMP.

## Background
String searching algorithms are integral in applications such as text editing, bioinformatics, and data retrieval. Traditional serial implementations of these algorithms can be inefficient with large data volumes. This project explores the use of Bloom Filters—a probabilistic data structure that efficiently handles large amounts of data with an acceptable rate of false positives.

## Bloom Filter
The Bloom filter is chosen for its complexity yet sequential nature, making it ideal for parallelization. Key components of the Bloom filter such as hash value calculation, data cleaning, and lookup operations are independently parallelizable, significantly enhancing the overall algorithm efficiency.

## Project Objectives
- **Parallelization:** To adapt the Bloom filter for parallel execution on shared memory systems, targeting various stages of the algorithm that contribute up to 80% of its operational time.
- **Performance Evaluation:** To compare the parallel algorithm's performance against its serial counterpart, utilizing a realistic and sufficiently large dataset.
- **Documentation and Reporting:** Develop comprehensive documentation and reports that detail the design, implementation, and performance analysis.

## Implementation

### Dataset
The word list combines texts from "Moby Dick", "Little Women", and Shakespeare’s works, approximating real-world scenarios with a dataset size of about 1.4 million words. The query list, provided by the Monash FIT 3143 Team, contains 91,636 words, aiding in testing the algorithm's efficiency and false positive rates.

### System Specifications
- **CPU:** AMD Epyc (1 CPU per task)
- **GPU:** NVIDIA RTX
- **Memory:** 16GB allocated

### Design of Parallel Bloom Filter
- **Unique Word Handling:** Parallelizes the removal of duplicates, reducing the dataset size before processing to enhance efficiency.
- **Hash Function:** Parallelizes the hashing process, assigning each thread a subset of words to hash independently, thereby avoiding race conditions.
- **Query Operations:** Parallel processing of queries, where each thread manages a subset of words, ensuring efficient lookups.

### Theoretical Speedup
Based on the analysis, the parallel portion of the code is approximately 98.30%, suggesting a theoretical speedup of around 15.29x on a 16-thread system.

## Results
The parallel Bloom filter demonstrates substantial performance improvements, especially in insertion and lookup times, which are critical for handling large datasets.

## Usage Instructions
Details on compiling and running the project are provided in the code files, with specific instructions for different datasets to assess performance across various scenarios.

## Contributing
This project is open for contributions. Suggestions and improvements are welcome, particularly in extending the application scope and refining the parallelization techniques.

## Contact and Additional Resources
For more detailed information, including pseudocode and deeper performance analysis, refer to the full project report and code repository.
