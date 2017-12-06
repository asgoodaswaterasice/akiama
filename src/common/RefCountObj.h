#ifndef AKIAMA_COMMON_REFCOUNTOBJ_H
#define AKIAMA_COMMON_REFCOUNTOBJ_H

#include <atomic>
#include <cassert>

namespace akiama {
namespace common {

class RefCountObj {
public:
	RefCountObj() : m_count(0) {
	}

	virtual ~RefCountObj() {
		assert(m_count == 0);
	}

	void put() {
		m_count--;
	}

	RefCountObj* get() {
		m_count++;
		return this;
	}

	uint32_t count() {
		return m_count;
	}

private:
	std::atomic<uint32_t> m_count;
};

}; // end of ns common
}; // end of ns akiama

#endif
