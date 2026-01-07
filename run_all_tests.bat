@echo off
echo Running Memory Management Simulator Tests...
echo.

if not exist results mkdir results

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

echo Test 8: Multi-level Cache Test
memsim.exe < tests\multilevel_cache_test.txt > results\multilevel_cache_result.txt
echo - Multi-level cache test completed

echo Test 9: Allocator Comparison Test
memsim.exe < tests\allocator_comparison.txt > results\allocator_comparison_result.txt
echo - Allocator comparison test completed

echo Test 10: Stress Allocation Test
memsim.exe < tests\stress_allocation_test.txt > results\stress_allocation_result.txt
echo - Stress allocation test completed

echo Test 11: Allocation Failure Test
memsim.exe < tests\allocation_failure_test.txt > results\allocation_failure_result.txt
echo - Allocation failure test completed

echo.
echo All tests completed! Check results\ directory for outputs.
echo Run validate_results.py to check test correctness.
pause
