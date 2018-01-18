#include "buffer.h"
#include "inline_memory.h"

namespace akiama {
namespace common {

BufferPtr::BufferPtr() : m_off(0), m_len(0), m_raw(nullptr) {
}

BufferPtr::BufferPtr(BufferRaw *r) : m_off(0),
	m_len(r->len()), m_raw(r) {
	r->get();
}

BufferPtr::BufferPtr(BufferRaw *r, size_t off, size_t len) :
	m_off(off), m_len(len), m_raw(r) {
	assert(r);
	assert((off + len) < r->len());
	r->get();
}

BufferPtr::BufferPtr(size_t len) : m_off(0), m_len(len) {
	m_raw = new BufferRaw(len);
	m_raw->get();
}

BufferPtr::BufferPtr(const BufferPtr &b) {
	m_off = b.m_off;
	m_len = b.m_len;
	m_raw = b.m_raw;
	if (m_raw) {
		m_raw->get();
	}
}

BufferPtr& BufferPtr::operator = (const BufferPtr &b) {
	m_off = b.m_off;
	m_len = b.m_len;
	m_raw = b.m_raw;
	if (m_raw) {
		m_raw->get();
	}
	release();
	return *this;
}

void BufferPtr::release() {
	if (m_raw) {
		m_raw->put();
		if (!m_raw->count()) {
			delete m_raw;
			m_raw = 0;
		}
	}
}

size_t BufferPtr::append(const char *ptr, size_t len) {
	assert(m_raw);
	char *l = m_raw->data() + m_off + m_len;
	maybe_inline_memcpy(l, ptr, len, 32);
	m_len += len;
	return m_off + m_len;
}

BufferList::BufferList() : m_len(0) {
}

BufferList::BufferList(const BufferPtr &p) {
	if (p.len()) {
		m_len = p.len();
		m_buffers.push_back(p);
	}
}

BufferList::BufferList(const BufferList &l) {
	m_len = l.m_len;
	m_buffers = l.m_buffers;
	m_append_buffer = l.m_append_buffer;
}

BufferList& BufferList::operator = (const BufferList& l) {
	m_len = l.m_len;
	m_buffers = l.m_buffers;
	m_append_buffer = l.m_append_buffer;
	return *this;
}

void BufferList::append(const char *ptr, size_t len) {
	// TODO
}

void BufferList::append(const std::string &s) {
	// TODO
}

void BufferList::append(const BufferPtr &p) {
	if (p.len()) {
		m_len += p.len();
		m_buffers.push_back(p);
	}
}
void BufferList::append(const BufferList &l) {
	if (l.len()) {
		const_iterator it = l.begin();
		for (; it != l.end(); ++it) {
			m_buffers.push_back(*it);
		}
		m_len += l.len();
	}
}

};
};
