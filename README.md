# IP List Compressor

This program is designed to retrieve a list of IPv4 records, including:

- Individual addresses (e.g., 12.11.22.11);
- Ranges (e.g., 10.10.10.10-10.10.100.10);
- Subnets (e.g., 10.10.10.10/24).

Once the data is retrieved, the program performs the following actions:

- <b>Validates</b> the records, rejecting any invalid entries.
- Decomposes ranges into subnets and individual hosts.
- <b>Merges</b> single hosts into the largest possible subnets.
- Combines smaller subnets into larger ones, when feasible.
- Removes duplicates and overlaps.
- Corrects subnets to a standardized form (e.g., input 10.10.10.10/24 becomes output 10.10.10.0/24).
- Returns the processed data, either to a file or standard output.

The primary objective of this program is to merge multiple IPv4 feeds into a single, consolidated feed while minimizing its size.

## Simple usage
```
./ListCompressor -i /path/to/input/data -o /path/to/output --suffix="\n,"
```
converts
```
10.10.10.1
100.100.100.
10.10.10.10-10.10.10.100
10.10.10.100/28
10.10.10.44/24
12.33.33.33
```
into
```
10.10.10.0/24,
12.33.33.33,
```

## Program arguments
Argument  | Short form | Example | Effect
------------- | ------------- | ------------- | -------------
--help  | -h | ./ListCompressor -h | Shows help message. 
--inputFilePath  | -i | -i /path/file1 -i /path/file2 | Program will read input from these files instead of std input.
--outputFilePath | -o | -o /path/output | Output will be saved there instead of printed to std output.
--inputDelimiter | -d | -d "/t," | Records in input files will be distinguished based on specified delimiter.
--hostPrefix | none | --hostPrefix="host: " | Appends the provided prefix in front of each individual host. For example, "1.1.1.1" will be transformed into "host: 1.1.1.1".
--subnetPrefix | none | --subnetPrefix="subnet: " | Like above. For subnets.
--suffix | -s | -s "\n," | Appends this suffix after each record in an output file.

## Dependencies
- BS_thread_pool v3.5.0 by Barak Shoshany https://github.com/bshoshany/thread-pool
- Boost C++ https://www.boost.org/
