#include <unistd.h>

namespace akiama {
namespace common {

int get_bits_of(unsigned v) {
    int n = 0;
    while (v) {
        n++;
        v = v>>1;
    }
    return n;
}

unsigned page_size = sysconf(_SC_PAGESIZE);
unsigned long page_mask = ~((unsigned long)(page_size - 1));
unsigned page_shift = get_bits_of(page_size - 1);

};
};
