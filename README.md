# SUPRESIS - Trading Signals Parser

---

SupResis parses raw text files containing generated discord crypto trading signals. The parsed result is then formatted
as CSV and saved to a file.

I developed it as a contribution to my friend Emils who needed the formatted data to back-test a trading algorithm he
was developing.

## Build from source

Follow the [instructions](https://cmake.org/cmake/help/git-stage/guide/tutorial/Packaging%20Debug%20and%20Release.html)
to build for your desired CPU architecture.

## Run the binary

The binary takes two arguments, the input file, and an output file.

 ```shell
./supresis input.txt output.csv
```