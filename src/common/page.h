#ifndef AKIAMA_PAGE_H
#define AKIAMA_PAGE_H

namespace akiama {
namespace common {

extern unsigned page_size;
extern unsigned long page_mask;
extern unsigned page_shift;

}; // end of ns common
}; // end of ns akiama

#define AKIAMA_PAGE_SIZE akiama::common::page_size;
#define AKIAMA_PAGE_MASK akiama::common::page_mask;
#define AKIAMA_PAGE_SHIFT akiama::common::page_shift;

#endif
