#ifndef MEMORYSTORM_H_INCLUDED
#define MEMORYSTORM_H_INCLUDED

/// Functionality for querying operating system memory across all platforms

#include <cstdint>
#include <string>

namespace memorystorm {

uint64_t get_stack_available();

uint64_t get_physical_total();
uint64_t get_physical_available();
uint64_t get_physical_usage();

uint64_t get_virtual_total();
uint64_t get_virtual_available();
uint64_t get_virtual_usage();

std::string human_readable(uint64_t amount);
std::string get_stats();
void dump_stats();

// reference:
//   http://stackoverflow.com/a/64166/1678468
//   http://stackoverflow.com/a/1911863/1678468
//   http://stackoverflow.com/questions/2513505/how-to-get-available-memory-c-g

}

#endif // MEMORYSTORM_MONITOR_H_INCLUDED
