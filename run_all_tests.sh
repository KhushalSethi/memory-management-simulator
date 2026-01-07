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

echo "Test 8: Multi-level Cache Test"
./memsim < tests/multilevel_cache_test.txt > results/multilevel_cache_result.txt
echo "- Multi-level cache test completed"

echo "Test 9: Allocator Comparison Test"
./memsim < tests/allocator_comparison.txt > results/allocator_comparison_result.txt
echo "- Allocator comparison test completed"

echo "Test 10: Stress Allocation Test"
./memsim < tests/stress_allocation_test.txt > results/stress_allocation_result.txt
echo "- Stress allocation test completed"

echo "Test 11: Allocation Failure Test"
./memsim < tests/allocation_failure_test.txt > results/allocation_failure_result.txt
echo "- Allocation failure test completed"

echo
echo "All tests completed! Check results/ directory for outputs."
echo "Run python validate_results.py to check test correctness."
