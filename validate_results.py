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
        ("multilevel_cache_result.txt", validate_cache_test),
        ("translation_result.txt", validate_virtual_memory_test),
        ("page_fault_result.txt", validate_virtual_memory_test),
        ("integration_result.txt", validate_allocation_test),
        ("allocator_comparison_result.txt", validate_allocation_test),
        ("stress_allocation_result.txt", validate_allocation_test),
        ("allocation_failure_result.txt", validate_allocation_test),
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
