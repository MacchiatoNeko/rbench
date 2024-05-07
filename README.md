# rbench - Router Benchmark Tool

## Overview
rbench is a command-line tool designed to test the performance of routers running OpenWRT firmware. It evaluates the processing speed of cryptographic hashing algorithms (MD5, SHA1, and SHA256) on the router's hardware.

## Features
- Benchmarking of MD5, SHA1, and SHA256 algorithms.
- Measures the total score based on the combined iterations of all algorithms.

## Installation
1. Clone the rbench repository from GitHub.
2. Make the program.
3. Run rbench located next to Makefile.

## Notes
- Ensure that OpenSSL development libraries are installed on your system.
- Adjust the block size parameter based on the router's memory and processing capabilities.
- The program runs for 5 seconds per algorithm to provide a consistent benchmark.
