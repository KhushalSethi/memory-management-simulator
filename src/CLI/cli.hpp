#include <iostream>
#include "../cache/cache.hpp"
#include "../virtual memory/virtual.hpp"
#include <vector>
#include <string>
using namespace std ;

struct cli{

    // Destructor for proper cleanup
    ~cli(){
        // Note: In a real implementation, you'd want proper cleanup here
        // For simplicity, we'll let the OS handle cleanup on program exit
    }

    vector < string > Split ( string &s )
    {

            vector < string > result ;
            string temp = "" ;
            for( auto a : s ){
                if( a == ' ' ){
                    if( temp.size() ) result.push_back( temp ) ;
                    temp = "" ;
                }
                else{
                    temp += a ;
                }
            }
            
            if( temp.size() ) result.push_back( temp ) ;

            return result ;

    }

    void run(){
        string cmd ;
        cout << "Memory Management Simulator" << endl ;
        cout << "Type 'help' for available commands" << endl ;
        cout << "> " ;
        
        int allocator = 1 ;
        Memory* memory = NULL ;
        cachelevel* l1_cache = NULL ;
        cachelevel* l2_cache = NULL ;
        virtual_memory* vmem = NULL ;

        while( getline( cin , cmd ) ){
            
            if( cmd == "exit" ){
                cout << "End" << endl ;
                break; 
            }
            
            if( cmd.empty() ){
                cout << "> " ;
                continue ;
            }
            
            vector < string > split = Split( cmd ) ;
            
            if( split.empty() ){
                cout << "> " ;
                continue ;
            }

            if( split[ 0 ] == "init" && split[ 1 ] == "memory" ){
                if( split.size() >= 3 ){
                    memory = new Memory( stoi( split[ 2 ] ) ) ;
                } else {
                    cout << "Usage: init memory <size>" << endl ;
                }
            }
            if( split[ 0 ] == "set" ){
                if( split.size() >= 3 ){
                    if( split[ 2 ][ 0 ] == 'f' ) allocator = 1 ;
                    else if( split[ 2 ][ 0 ] == 'b' ) allocator = 2 ;
                    else if( split[ 2 ][ 0 ] == 'w' ) allocator = 3 ;
                    else {
                        cout << "Invalid allocator. Use first, best, or worst" << endl ;
                        cout << "> " ;
                        continue ;
                    }
                    cout << "Allocator set" << endl ;   
                } else {
                    cout << "Usage: set allocator <first|best|worst>" << endl ;
                }
            }
            if( split[ 0 ] == "malloc" ){
                if( memory == NULL ){
                    cout << "Memory not initialized. Use 'init memory <size>' first" << endl ;
                } else if( split.size() >= 2 ){
                    if( allocator == 1 ) memory->first_fit( stoi( split[ 1 ] ) ) ;
                    if( allocator == 2 ) memory->best_fit( stoi( split[ 1 ] ) ) ;
                    if( allocator == 3 ) memory->worst_fit( stoi( split[ 1 ] ) ) ;
                } else {
                    cout << "Usage: malloc <size>" << endl ;
                }
            }
            if( split[ 0 ] == "free" ){
                if( memory == NULL ){
                    cout << "Memory not initialized" << endl ;
                } else if( split.size() >= 2 ){
                    memory->free_memory( stoi( split[ 1 ] ) ) ;
                } else {
                    cout << "Usage: free <id>" << endl ;
                }
            }
            if( split[ 0 ] == "dump" ){
                if( memory == NULL ){
                    cout << "Memory not initialized" << endl ;
                } else {
                    memory->print_memory() ;
                }
            }
            if( split[ 0 ] == "stats" ){
                if( memory == NULL ){
                    cout << "Memory not initialized" << endl ;
                } else {
                    memory->stats() ;
                }
            }
            
            // Virtual Memory Commands
            if( split[ 0 ] == "init" && split[ 1 ] == "virtual" ){
                int vmem_size = stoi( split[ 2 ] ) ;
                int pmem_size = stoi( split[ 3 ] ) ;
                int page_size = stoi( split[ 4 ] ) ;
                vmem = new virtual_memory( vmem_size, pmem_size, page_size ) ;
                cout << "Virtual memory initialized: " << vmem_size << " virtual, " << pmem_size << " physical, page size " << page_size << endl ;
            }
            
            if( split[ 0 ] == "translate" ){
                if( vmem != NULL ){
                    int virtual_addr = stoi( split[ 1 ] ) ;
                    int physical_addr = vmem->translate( virtual_addr ) ;
                    cout << "Virtual address " << virtual_addr << " -> Physical address " << physical_addr << endl ;
                } else {
                    cout << "Virtual memory not initialized" << endl ;
                }
            }

            if( split[ 0 ] == "cache" && split[ 1 ] == "stats" ){
                if( l1_cache != NULL ){
                    cout << "L1 Cache - Hits: " << l1_cache->hits << ", Misses: " << l1_cache->misses 
                         << ", Hit Ratio: " << l1_cache->hit_ratio() << endl ;
                }
                if( l2_cache != NULL ){
                    cout << "L2 Cache - Hits: " << l2_cache->hits << ", Misses: " << l2_cache->misses 
                         << ", Hit Ratio: " << l2_cache->hit_ratio() << endl ;
                }
            }

            if( split[ 0 ] == "help" ){
                cout << "\nAvailable Commands:" << endl ;
                cout << "init memory <size>              - Initialize physical memory" << endl ;
                cout << "init virtual <vmem> <pmem> <page> - Initialize virtual memory" << endl ;
                cout << "init cache <1|2>                - Initialize L1 or L2 cache" << endl ;
                cout << "set allocator <first|best|worst> - Set memory allocation strategy" << endl ;
                cout << "malloc <size>                    - Allocate memory" << endl ;
                cout << "free <id>                        - Free memory by ID" << endl ;
                cout << "read <address>                   - Read from memory (cache simulation)" << endl ;
                cout << "translate <virtual_addr>         - Translate virtual to physical address" << endl ;
                cout << "dump                             - Show memory layout" << endl ;
                cout << "stats                            - Show memory statistics" << endl ;
                cout << "cache stats                      - Show cache statistics" << endl ;
                cout << "help                             - Show this help message" << endl ;
                cout << "exit                             - Exit simulator" << endl ;
            }

            if( split[ 0 ] == "init" && split[ 1]  == "cache" ){
                string s ;
                
                int Size ;
                int Block_size ;
                int associativity ;
                
                if( split[ 2 ] == "1" ){

                    cout << "Enter Cache size" << endl ;
                    getline( cin , s ) ;
                    Size = stoi( s ) ;

                    cout << "Enter Block Size " << endl ;
                    getline( cin , s ) ;
                    Block_size = stoi( s ) ;

                    cout << "Enter associativity" << endl ;
                    getline( cin , s ) ;
                    associativity = stoi ( s ) ;

                    l1_cache = new cachelevel( Size , Block_size , associativity , memory ) ;

                }
                if( split[ 2 ] == "2" ){
                    
                    cout << "Enter Cache size" << endl ;
                    getline( cin , s ) ;
                    Size = stoi( s ) ;

                    cout << "Enter Block Size " << endl ;
                    getline( cin , s ) ;
                    Block_size = stoi( s ) ;

                    cout << "Enter associativity" << endl ;
                    getline( cin , s ) ;
                    associativity = stoi ( s ) ;

                    l2_cache = new cachelevel( Size , Block_size , associativity , memory ) ;

                }

            }
            
            if( split[ 0 ] == "read" ){
                int address = stoi( split[ 1 ] ) ;
                bool found_in_l1 = false ;
                bool found_in_l2 = false ;

                // Check L1 cache first
                if( l1_cache != NULL ){
                    found_in_l1 = l1_cache->read( address ) ;
                    if( found_in_l1 ){
                        cout << "Found in L1 cache" << endl ;
                    }
                }

                // If not in L1, check L2
                if( !found_in_l1 && l2_cache != NULL ){
                    found_in_l2 = l2_cache->read( address ) ;
                    if( found_in_l2 ){
                        cout << "Found in L2 cache" << endl ;
                        // Load into L1 cache
                        if( l1_cache != NULL ){
                            l1_cache->insert( address ) ;
                        }
                    }
                }

                // If not in cache, load from memory
                if( !found_in_l1 && !found_in_l2 ){
                    cout << "Found in main memory" << endl ;
                    // Load into both caches
                    if( l1_cache != NULL ) l1_cache->insert( address ) ;
                    if( l2_cache != NULL ) l2_cache->insert( address ) ;
                }
            }
            
            // Virtual Memory Commands
            if( split[ 0 ] == "init" && split[ 1 ] == "virtual" ){
                if( split.size() >= 5 ){
                    int vmem_size = stoi( split[ 2 ] ) ;
                    int pmem_size = stoi( split[ 3 ] ) ;
                    int page_size = stoi( split[ 4 ] ) ;
                    vmem = new virtual_memory( vmem_size, pmem_size, page_size ) ;
                    cout << "Virtual memory initialized: " << vmem_size << " virtual, " << pmem_size << " physical, page size " << page_size << endl ;
                } else {
                    cout << "Usage: init virtual <vmem_size> <pmem_size> <page_size>" << endl ;
                }
            }
            
            if( split[ 0 ] == "translate" ){
                if( vmem != NULL && split.size() >= 2 ){
                    int virtual_addr = stoi( split[ 1 ] ) ;
                    int physical_addr = vmem->translate( virtual_addr ) ;
                    cout << "Virtual address " << virtual_addr << " -> Physical address " << physical_addr << endl ;
                } else if( vmem == NULL ){
                    cout << "Virtual memory not initialized" << endl ;
                } else {
                    cout << "Usage: translate <virtual_address>" << endl ;
                }
            }

            if( split[ 0 ] == "cache" && split.size() >= 2 && split[ 1 ] == "stats" ){
                if( l1_cache != NULL ){
                    cout << "L1 Cache - Hits: " << l1_cache->hits << ", Misses: " << l1_cache->misses 
                         << ", Hit Ratio: " << l1_cache->hit_ratio() << endl ;
                }
                if( l2_cache != NULL ){
                    cout << "L2 Cache - Hits: " << l2_cache->hits << ", Misses: " << l2_cache->misses 
                         << ", Hit Ratio: " << l2_cache->hit_ratio() << endl ;
                }
                if( l1_cache == NULL && l2_cache == NULL ){
                    cout << "No cache initialized" << endl ;
                }
            }

            if( split[ 0 ] == "help" ){
                cout << "\nAvailable Commands:" << endl ;
                cout << "init memory <size>              - Initialize physical memory" << endl ;
                cout << "init virtual <vmem> <pmem> <page> - Initialize virtual memory" << endl ;
                cout << "init cache <1|2>                - Initialize L1 or L2 cache" << endl ;
                cout << "set allocator <first|best|worst> - Set memory allocation strategy" << endl ;
                cout << "malloc <size>                    - Allocate memory" << endl ;
                cout << "free <id>                        - Free memory by ID" << endl ;
                cout << "read <address>                   - Read from memory (cache simulation)" << endl ;
                cout << "translate <virtual_addr>         - Translate virtual to physical address" << endl ;
                cout << "dump                             - Show memory layout" << endl ;
                cout << "stats                            - Show memory statistics" << endl ;
                cout << "cache stats                      - Show cache statistics" << endl ;
                cout << "help                             - Show this help message" << endl ;
                cout << "exit                             - Exit simulator" << endl ;
            }

            cout << "> " ;
        }


    }
    

};