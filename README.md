# Memory Management Simulator

A comprehensive memory management simulator implementing physical memory allocation, cache simulation, and virtual memory management.

## Features

### Physical Memory Management
- **Memory Allocation Strategies**: First-fit, Best-fit, Worst-fit algorithms
- **Dynamic Memory Management**: Allocation and deallocation with automatic coalescing
- **Memory Block Tracking**: Unique ID system for allocated blocks
- **Fragmentation Analysis**: External fragmentation calculation and reporting
- **Memory Visualization**: Complete memory layout display with allocated/free regions

### Cache Simulation
- **Multi-level Cache**: L1 and L2 cache support
- **Set-associative Cache**: Configurable associativity
- **LRU Replacement Policy**: Least Recently Used cache replacement
- **Cache Statistics**: Hit/miss ratios and performance metrics

### Virtual Memory Management
- **Address Translation**: Virtual to physical address mapping
- **Page Table Management**: Page table entries with validation
- **Page Fault Handling**: LRU page replacement policy
- **Configurable Parameters**: Page size and memory size settings

## Building the Project

### Using CMake (Recommended)
```bash
mkdir build
cd build
cmake ..
make  # On Linux/Mac
# OR
cmake --build .  # On Windows
```

### Using Build Scripts
- **Linux/Mac**: `./build.sh`
- **Windows**: `build.bat`

### Manual Compilation
```bash
g++ -std=c++17 -I src -o memsim src/main.cpp
```

## Usage

Run the simulator:
```bash
./memsim  # Linux/Mac
memsim.exe  # Windows
```

### Available Commands

#### Memory Management
- `init memory <size>` - Initialize physical memory with specified size
- `set allocator <first|best|worst>` - Set memory allocation strategy
- `malloc <size>` - Allocate memory block
- `free <id>` - Free memory block by ID
- `dump` - Display current memory layout
- `stats` - Show memory usage statistics

#### Cache Management
- `init cache <1|2>` - Initialize L1 or L2 cache (prompts for parameters)
- `read <address>` - Read from memory address (simulates cache behavior)
- `cache stats` - Display cache hit/miss statistics

#### Virtual Memory
- `init virtual <vmem_size> <pmem_size> <page_size>` - Initialize virtual memory
- `translate <virtual_addr>` - Translate virtual to physical address

#### Utility
- `help` - Show all available commands
- `exit` - Exit the simulator

## Example Usage Session

```
Memory Management Simulator
Type 'help' for available commands
> init memory 1024
memory of size 1024 created 

> set allocator first
Allocator set

> malloc 100
Memory allocated with ID: 2 using first-fit

> malloc 200
Memory allocated with ID: 3 using first-fit

> dump
Free memory from: 0 to: 0
Memory alloted from: 1 to: 100 to user with ID: 2
Memory alloted from: 101 to: 300 to user with ID: 3
Free memory from: 301 to: 1023

> stats
Total memory 1024
Free memory 724
Allocated memory 300
External Fragmentation 0%

> init cache 1
Enter Cache size
256
Enter Block Size 
32
Enter associativity
4

> read 150
Found in main memory

> read 150
Found in L1 cache

> cache stats
L1 Cache - Hits: 1, Misses: 1, Hit Ratio: 0.5

> exit
End
```

## Project Structure

```
memory-simulator/
├── src/
│   ├── main.cpp              # Main entry point
│   ├── CLI/
│   │   └── cli.hpp           # Command-line interface
│   ├── allocator/
│   │   └── memory.hpp        # Physical memory management
│   ├── cache/
│   │   └── cache.hpp         # Cache simulation
│   └── virtual memory/
│       └── virtual.hpp       # Virtual memory management
├── CMakeLists.txt            # Build configuration
├── build.sh                 # Linux/Mac build script
├── build.bat                # Windows build script
└── README.md                # This file
```

## Implementation Details

### Memory Allocation
- Uses linked list of memory blocks
- Implements coalescing of adjacent free blocks
- Tracks allocation IDs for proper deallocation
- Calculates external fragmentation

### Cache Architecture
- Set-associative cache with configurable parameters
- Implements LRU replacement policy using deque
- Supports multi-level cache hierarchy
- Tracks hit/miss statistics for performance analysis

### Virtual Memory
- Page table with valid/invalid bits
- LRU page replacement for page faults
- Configurable page sizes
- Address translation with offset calculation

## Requirements

- C++17 compatible compiler (GCC, Clang, MSVC)
- CMake 3.10 or higher (optional, for build system)

## Notes

- Memory is measured in abstract units (not necessarily bytes)
- All addresses are virtual addresses when virtual memory is enabled
- Cache simulation works independently of actual memory allocation
- The simulator is designed for educational purposes to demonstrate memory management concepts
