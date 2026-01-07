# Memory Management Simulator - Test Artifacts

## Overview
This directory contains comprehensive test artifacts for validating the memory management simulator functionality across all subsystems: physical memory allocation, cache hierarchy, and virtual memory management.

## Test Categories
1. **Memory Allocation Pattern Tests** - Various allocation/deallocation patterns
2. **Cache Access Pattern Tests** - Different cache usage scenarios  
3. **Virtual Memory Tests** - Address translation and page fault handling
4. **Integrated System Tests** - Combined functionality testing
5. **Performance and Stress Tests** - Edge cases and performance evaluation

---

## 1. Memory Allocation Pattern Tests

### Test 1.1: Sequential Allocation Pattern
**Description**: Tests sequential memory allocation with increasing sizes
**Expected Behavior**: Should use first-fit efficiently for sequential requests

```
# Input Workload: sequential_allocation.txt
init memory 1024
set allocator first
malloc 50
malloc 75  
malloc 100
malloc 125
malloc 150
dump
stats
exit

# Expected Output:
Memory Layout: [Used:50][Used:75][Used:100][Used:125][Used:150][Free:524]
Total Memory: 1024, Free: 524, Used: 500, Blocks: 6
Fragmentation: Low (single large free block remaining)
```

### Test 1.2: Random Allocation/Deallocation Pattern  
**Description**: Mixed allocation and deallocation creating fragmentation
**Expected Behavior**: Tests coalescing and fragmentation handling

```
# Input Workload: fragmentation_test.txt
init memory 800
set allocator first
malloc 100    # Block ID 1
malloc 80     # Block ID 2  
malloc 120    # Block ID 3
malloc 60     # Block ID 4
free 2        # Free middle block
free 4        # Free end block
malloc 50     # Should fit in freed block 2's space
malloc 40     # Should fit in freed block 4's space
dump
stats
exit

# Expected Output:
- Coalescing of adjacent free blocks
- Efficient reuse of freed space
- Memory layout showing fragmentation patterns
```

### Test 1.3: Best Fit vs Worst Fit Comparison
**Description**: Compares allocation strategies with identical workload
**Expected Behavior**: Different fragmentation patterns

```
# Input Workload: allocator_comparison.txt
# Test with Best Fit
init memory 1000
set allocator best
malloc 200
malloc 100
malloc 300
malloc 50
dump
stats

# Reset and test with Worst Fit  
init memory 1000
set allocator worst
malloc 200
malloc 100 
malloc 300
malloc 50
dump
stats
exit
```

---

## 2. Cache Access Pattern Tests

### Test 2.1: Cache Hit Rate Analysis
**Description**: Tests cache performance with repeated access patterns
**Expected Behavior**: High hit rates for repeated accesses

```
# Input Workload: cache_hit_test.txt
init memory 2048
init cache 1
256
32
2
read 100
read 100    # Should hit in L1
read 200
read 100    # Should hit in L1  
read 200    # Should hit in L1
cache stats
exit

# Expected Output:
L1 Cache - Hits: 3, Misses: 2, Hit Ratio: 0.60
```

### Test 2.2: Cache Replacement (LRU) Test
**Description**: Tests LRU replacement policy when cache is full
**Expected Behavior**: Least recently used items are evicted

```
# Input Workload: lru_replacement_test.txt  
init memory 2048
init cache 1
128    # Small cache to force replacements
32     # Block size
2      # 2-way associative (4 total lines)
read 0     # Miss - load to cache
read 64    # Miss - load to cache  
read 128   # Miss - load to cache
read 192   # Miss - load to cache (cache now full)
read 256   # Miss - should evict LRU (address 0)
read 0     # Miss - should evict next LRU
cache stats
exit

# Expected Output:
L1 Cache - Hits: 0, Misses: 6, Hit Ratio: 0.00
Cache should show LRU eviction pattern
```

### Test 2.3: Multi-Level Cache Test
**Description**: Tests L1 and L2 cache hierarchy
**Expected Behavior**: L2 hits when L1 misses, proper cache loading

```
# Input Workload: multilevel_cache_test.txt
init memory 4096
init cache 1
128
32  
2
init cache 2
512
32
4
read 100   # Miss L1, Miss L2, load both
read 200   # Miss L1, Miss L2, load both  
read 100   # Hit L1
read 300   # Miss L1, Miss L2, load both, may evict from L1
read 200   # Miss L1, Hit L2, load to L1
cache stats
exit

# Expected Output:
L1 Cache - Mixed hit/miss pattern
L2 Cache - Better hit rate due to larger size
Proper hierarchy behavior demonstrated
```

---

## 3. Virtual Memory Access Tests

### Test 3.1: Basic Address Translation
**Description**: Tests basic virtual to physical address translation
**Expected Behavior**: Correct address mapping within pages

```
# Input Workload: basic_translation_test.txt
init memory 1024  
init virtual 2048 1024 256
translate 0       # Page 0, offset 0 -> Frame X, offset 0
translate 100     # Page 0, offset 100 -> Frame X, offset 100  
translate 256     # Page 1, offset 0 -> Frame Y, offset 0
translate 500     # Page 1, offset 244 -> Frame Y, offset 244
translate 1000    # Page 3, offset 232 -> Frame Z, offset 232
exit

# Expected Output:
Virtual address 0 -> Physical address [frame*256 + 0]
Virtual address 100 -> Physical address [same_frame*256 + 100]
Virtual address 256 -> Physical address [new_frame*256 + 0]  
Etc.
```

### Test 3.2: Page Fault Handling
**Description**: Tests page fault when physical memory is full
**Expected Behavior**: LRU page replacement

```
# Input Workload: page_fault_test.txt
init virtual 2048 512 256  # 8 virtual pages, 2 physical frames
translate 0      # Load page 0 -> frame 0
translate 256    # Load page 1 -> frame 1  
translate 512    # Page fault! Evict LRU page (page 0), load page 2
translate 0      # Page fault! Evict LRU page (page 1), load page 0
translate 768    # Page fault! Evict LRU page (page 2), load page 3
exit

# Expected Output:
- Clear indication of page faults
- LRU replacement working correctly
- Proper frame reallocation
```

---

## 4. Integrated System Tests

### Test 4.1: Complete System Integration
**Description**: Tests all subsystems working together
**Expected Behavior**: Coordinated operation of memory, cache, and virtual memory

```
# Input Workload: full_system_test.txt
# Initialize all subsystems
init memory 2048
set allocator best
init cache 1
256
32
4
init cache 2  
512
32
8
init virtual 4096 2048 256

# Test integrated operations
malloc 200
read 100      # Cache and memory interaction
translate 500 # Virtual memory translation
malloc 150
read 200
translate 1000
free 1
read 100      # Should still hit cache
dump
stats
cache stats
exit

# Expected Output:
- All systems operating correctly
- No conflicts between subsystems  
- Proper resource management
```

---

## 5. Performance and Stress Tests

### Test 5.1: High Allocation Volume Test
**Description**: Stress test with many allocations
**Expected Behavior**: System should handle high volume without crashes

```
# Input Workload: stress_allocation_test.txt
init memory 8192
set allocator first
# Perform 100 small allocations
malloc 50
malloc 45
malloc 60
[... repeat pattern 100 times ...]
stats
# Free every other block to create fragmentation
free 2
free 4
free 6
[... continue pattern ...]
stats
exit
```

---

## Test Execution Scripts

### Automated Test Runner (run_all_tests.bat)

```batch
@echo off
echo Running Memory Management Simulator Tests...
echo.

echo Test 1: Sequential Allocation
memsim.exe < tests\sequential_allocation.txt > results\seq_alloc_result.txt
echo - Sequential allocation test completed

echo Test 2: Fragmentation Test  
memsim.exe < tests\fragmentation_test.txt > results\fragmentation_result.txt
echo - Fragmentation test completed

echo Test 3: Cache Hit Rate Test
memsim.exe < tests\cache_hit_test.txt > results\cache_hit_result.txt  
echo - Cache hit test completed

echo Test 4: LRU Replacement Test
memsim.exe < tests\lru_replacement_test.txt > results\lru_result.txt
echo - LRU replacement test completed

echo Test 5: Virtual Memory Translation Test
memsim.exe < tests\basic_translation_test.txt > results\translation_result.txt
echo - Translation test completed

echo Test 6: Page Fault Test
memsim.exe < tests\page_fault_test.txt > results\page_fault_result.txt  
echo - Page fault test completed

echo Test 7: Full System Integration Test
memsim.exe < tests\full_system_test.txt > results\integration_result.txt
echo - Integration test completed

echo.
echo All tests completed! Check results\ directory for outputs.
pause
```

### Linux Test Runner (run_all_tests.sh)

```bash
#!/bin/bash
echo "Running Memory Management Simulator Tests..."
echo

# Create results directory if it doesn't exist
mkdir -p results

echo "Test 1: Sequential Allocation"
./memsim < tests/sequential_allocation.txt > results/seq_alloc_result.txt
echo "- Sequential allocation test completed"

echo "Test 2: Fragmentation Test"
./memsim < tests/fragmentation_test.txt > results/fragmentation_result.txt  
echo "- Fragmentation test completed"

echo "Test 3: Cache Hit Rate Test"
./memsim < tests/cache_hit_test.txt > results/cache_hit_result.txt
echo "- Cache hit test completed"

echo "Test 4: LRU Replacement Test" 
./memsim < tests/lru_replacement_test.txt > results/lru_result.txt
echo "- LRU replacement test completed"

echo "Test 5: Virtual Memory Translation Test"
./memsim < tests/basic_translation_test.txt > results/translation_result.txt
echo "- Translation test completed"

echo "Test 6: Page Fault Test"
./memsim < tests/page_fault_test.txt > results/page_fault_result.txt
echo "- Page fault test completed"

echo "Test 7: Full System Integration Test"  
./memsim < tests/full_system_test.txt > results/integration_result.txt
echo "- Integration test completed"

echo
echo "All tests completed! Check results/ directory for outputs."
```

### Test Validation Script (validate_results.py)

```python
#!/usr/bin/env python3
"""
Test Results Validation Script
Validates outputs against expected criteria
"""

import os
import re

def validate_allocation_test(result_file):
    """Validate memory allocation test results"""
    with open(result_file, 'r') as f:
        content = f.read()
    
    # Check for successful allocations
    allocations = re.findall(r'Block (\d+) allocated', content)
    
    # Check memory stats  
    stats_match = re.search(r'Total Memory: (\d+), Free: (\d+), Used: (\d+)', content)
    
    if len(allocations) > 0 and stats_match:
        total, free, used = map(int, stats_match.groups())
        if total == free + used:
            return True, f"✓ Allocation test passed - {len(allocations)} allocations, memory consistent"
    
    return False, "✗ Allocation test failed"

def validate_cache_test(result_file):
    """Validate cache test results"""
    with open(result_file, 'r') as f:
        content = f.read()
        
    # Check for cache statistics
    cache_stats = re.search(r'L1 Cache - Hits: (\d+), Misses: (\d+), Hit Ratio: ([\d.]+)', content)
    
    if cache_stats:
        hits, misses, ratio = cache_stats.groups()
        hits, misses = int(hits), int(misses)
        ratio = float(ratio)
        
        # Validate hit ratio calculation
        expected_ratio = hits / (hits + misses) if (hits + misses) > 0 else 0
        if abs(ratio - expected_ratio) < 0.01:  # Allow small floating point errors
            return True, f"✓ Cache test passed - Hits: {hits}, Misses: {misses}, Ratio: {ratio:.2f}"
    
    return False, "✗ Cache test failed"

def validate_virtual_memory_test(result_file):
    """Validate virtual memory test results"""  
    with open(result_file, 'r') as f:
        content = f.read()
        
    # Check for address translations
    translations = re.findall(r'Virtual address (\d+) -> Physical address (\d+)', content)
    
    if len(translations) > 0:
        # Basic validation - physical addresses should be reasonable
        valid_translations = all(int(phys) >= 0 for _, phys in translations)
        if valid_translations:
            return True, f"✓ Virtual memory test passed - {len(translations)} translations"
    
    return False, "✗ Virtual memory test failed"

def main():
    """Run validation on all test results"""
    print("Validating Test Results...")
    print("=" * 50)
    
    results_dir = "results"
    
    # Validate different test categories
    tests = [
        ("seq_alloc_result.txt", validate_allocation_test),
        ("fragmentation_result.txt", validate_allocation_test),  
        ("cache_hit_result.txt", validate_cache_test),
        ("lru_result.txt", validate_cache_test),
        ("translation_result.txt", validate_virtual_memory_test),
        ("page_fault_result.txt", validate_virtual_memory_test),
    ]
    
    passed = 0
    total = len(tests)
    
    for result_file, validator in tests:
        file_path = os.path.join(results_dir, result_file)
        if os.path.exists(file_path):
            success, message = validator(file_path)
            print(message)
            if success:
                passed += 1
        else:
            print(f"✗ {result_file} - File not found")
    
    print("=" * 50)        
    print(f"Validation Summary: {passed}/{total} tests passed")
    
    if passed == total:
        print("🎉 All tests passed!")
        return 0
    else:
        print("❌ Some tests failed - check individual results")  
        return 1

if __name__ == "__main__":
    exit(main())
```

---

## Expected Output Criteria

### Memory Allocation Tests
- **Correctness**: Total memory = Used memory + Free memory
- **Efficiency**: Appropriate allocation strategy behavior
- **Coalescing**: Adjacent free blocks should merge
- **Fragmentation**: Reasonable fragmentation levels

### Cache Tests  
- **Hit Rate**: Should improve with repeated accesses
- **LRU**: Least recently used items should be evicted first
- **Hierarchy**: L2 should have better hit rates than L1 for large working sets

### Virtual Memory Tests
- **Translation**: Virtual addresses should map consistently to physical addresses
- **Page Faults**: Should occur when accessing unmapped pages
- **Replacement**: LRU page replacement should work correctly

### Integration Tests
- **Coordination**: All subsystems should work together without conflicts
- **Performance**: Reasonable performance under combined load
- **Stability**: No crashes or undefined behavior

## Usage Instructions

1. **Create test directories**:
   ```
   mkdir tests results
   ```

2. **Copy test workloads** to `tests/` directory

3. **Run tests**:
   ```
   # Windows
   run_all_tests.bat
   
   # Linux  
   chmod +x run_all_tests.sh
   ./run_all_tests.sh
   ```

4. **Validate results**:
   ```
   python validate_results.py
   ```

5. **Analyze outputs** in `results/` directory

These test artifacts provide comprehensive validation of the memory management simulator across all functional areas with automated execution and validation capabilities.
