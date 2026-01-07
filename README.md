# Memory Management Simulator

A comprehensive, interactive memory management simulator implementing physical memory allocation, cache simulation, and virtual memory management with LRU replacement policies. This project demonstrates key operating system concepts including memory allocation strategies, cache performance, and virtual-to-physical address translation.

## 📺 Demonstration

Complete demonstration materials with screenshots showing:
- Memory allocation/deallocation behavior
- Cache hits and misses
- Page fault handling

See [Demonstration folder](./Demonstration/) for detailed screenshots and test results.
Video walkthrough: [videoDemonstration.pdf](./Demonstration/videoDemonstration.pdf)

## 📚 Documentation

Comprehensive technical documentation available in the [Documentation folder](./Documentation/).

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
cmake --build .
```

### Using Build Scripts
- **Linux/Mac**: `./build.sh`
- **Windows**: `build.bat`

### Manual Compilation (MinGW/GCC)
```bash
g++ -std=c++17 -Isrc -Isrc/allocator -Isrc/CLI -Isrc/cache -I"src/virtual memory" src/main.cpp -o memory_simulator.exe
```

## Usage

Run the simulator:
```bash
./memory_simulator  # Linux/Mac
memory_simulator.exe  # Windows
```

### Available Commands

#### Memory Management
- `init memory <size>` - Initialize physical memory with specified size
- `set allocator <first|best|worst>` - Set memory allocation strategy
  - **first-fit**: Allocates in the first available block
  - **best-fit**: Allocates in the smallest suitable block
  - **worst-fit**: Allocates in the largest available block
- `malloc <size>` - Allocate memory block
- `free <id>` - Free memory block by ID
- `dump` - Display current memory layout
- `stats` - Show memory usage statistics and fragmentation

#### Cache Management
- `init cache <1|2>` - Initialize L1 or L2 cache (prompts for parameters)
  - Interactive: Enter cache size, block size, and associativity
  - Command-line: `init cache <1|2> <size> <block_size> <associativity>`
- `read <address>` - Read from memory address (simulates cache behavior)
- `cache stats` - Display cache hit/miss statistics and hit ratio

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
├── tests/                    # Test cases for all features
│   ├── sequential_allocation.txt
│   ├── fragmentation_test.txt
│   ├── cache_hit_test.txt
│   ├── basic_translation_test.txt
│   ├── page_fault_test.txt
│   ├── allocator_comparison.txt
│   └── full_system_test.txt
├── Demonstration/            # Screenshots, video and demonstration materials
├── Documentation/            # Technical documentation
├── CMakeLists.txt           # Build configuration
├── build.sh                 # Linux/Mac build script
├── build.bat                # Windows build script
└── README.md                # This file
```

## 🧪 Testing

Run automated tests using the test files in the `tests/` directory:

```bash
# Run individual tests
Get-Content tests\sequential_allocation.txt | .\memory_simulator.exe
Get-Content tests\cache_hit_test.txt | .\memory_simulator.exe
Get-Content tests\page_fault_test.txt | .\memory_simulator.exe

# Run allocator comparison (shows fragmentation differences)
Get-Content tests\allocator_comparison.txt | .\memory_simulator.exe
```

### Test Results
- **First-fit & Best-fit**: 37.5% fragmentation
- **Worst-fit**: 62.5% fragmentation (highest)

Run tests from the `tests/` directory to see live results.

## Implementation Details

### Memory Allocation Algorithms
- **First-Fit**: Fast allocation, moderate fragmentation
- **Best-Fit**: Minimizes wasted space, can create small unusable fragments
- **Worst-Fit**: Maximizes remaining space in blocks, highest fragmentation
- Uses linked list of memory blocks with automatic coalescing
- Tracks allocation IDs for proper deallocation
- Calculates external fragmentation percentage

### Cache Architecture
- Set-associative cache with configurable parameters
- **LRU Replacement**: Uses deque for efficient least-recently-used tracking
- Supports multi-level cache hierarchy (L1 and L2)
- Tracks hit/miss statistics with hit ratio calculation
- Cache hits properly detected and reported

### Virtual Memory System
- Page table with valid/invalid bits
- **LRU Page Replacement**: Evicts least recently used pages on page faults
- Configurable page sizes for flexibility
- Address translation with bit manipulation for offset calculation
- Demonstrates page fault handling

## ✨ Key Features Demonstrated

1. **Allocation/Deallocation**: Visual memory layout with fragmentation analysis
2. **Cache Performance**: Hit/miss tracking with "Found in L1 cache" messages
3. **Page Faults**: Virtual-to-physical address translation with page replacement

## Requirements

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.10 or higher (optional, for build system)
- Windows: MinGW or Visual Studio
- Linux/Mac: GCC or Clang

## Notes

- Memory is measured in abstract units (not necessarily bytes)
- All addresses are relative within the allocated memory space
- Cache simulation works independently of actual memory allocation
- Virtual memory page faults trigger LRU replacement when physical memory is full
- The simulator is designed for educational purposes to demonstrate OS memory management concepts

## 📄 License

This project is available for educational purposes.
