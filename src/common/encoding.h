#include "buffer.h"

namespace akiama {
namespace common {

template<typename T>
void encode(T &t, BufferList &l) {
	l.append(static_cast<const char*>(&t), sizeof(t));
}

template<typename T>
void decode(T &t, BufferList::iterator &l) {
	l.copy(static_cast<char*>(&t), sizeof(t));
}

}; // end of ns common 
}; // end os ns akiama
