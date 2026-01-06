# Memory Management Simulator - Test Suite

## Quick Start

### Running Tests (Windows)
```cmd
run_all_tests.bat
```

### Running Tests (Linux/Mac)
```bash
chmod +x run_all_tests.sh
./run_all_tests.sh
```

## Test Categories

### 1. Memory Allocation Tests
- `sequential_allocation.txt` - Basic sequential allocation pattern
- `fragmentation_test.txt` - Tests memory fragmentation and coalescing
- `allocator_comparison.txt` - Compares first/best/worst fit strategies
- `stress_allocation_test.txt` - High-volume allocation stress test

### 2. Cache System Tests  
- `cache_hit_test.txt` - Tests cache hit/miss behavior
- `lru_replacement_test.txt` - Validates LRU replacement policy
- `multilevel_cache_test.txt` - Tests L1/L2 cache hierarchy

### 3. Virtual Memory Tests
- `basic_translation_test.txt` - Basic address translation
- `page_fault_test.txt` - Page fault handling and replacement

### 4. Integration Tests
- `full_system_test.txt` - All subsystems working together

## Expected Outputs

### Memory Tests
- Successful allocations with block IDs
- Memory statistics showing total/free/used consistency  
- Proper coalescing of adjacent free blocks

### Cache Tests
- Hit/miss statistics with correct ratios
- LRU replacement working as expected
- L1/L2 hierarchy functioning properly

### Virtual Memory Tests
- Correct virtual-to-physical address translation
- Page fault handling when physical memory is full
- LRU page replacement policy

## Manual Testing

You can also run the simulator interactively:

```cmd
memory_simulator.exe
```

Then use commands like:
- `help` - Show available commands
- `init memory 1024` - Initialize memory
- `malloc 100` - Allocate memory
- `dump` - Show memory layout
- `exit` - Exit simulator

## Troubleshooting

### Tests Not Running
- Ensure `memory_simulator.exe` is in the project root directory
- Compile the simulator first using the build instructions in the main README

### Unexpected Output
- Check that test outputs contain expected patterns
- Verify simulator is working correctly with manual testing
- Review cache fix: cache hits should show "Found in L1 cache"
- Fragmentation test should show differences between allocation strategies
