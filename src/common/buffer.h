#ifndef AKIAMA_COMMON_BUFFER_H_
#define AKIAMA_COMMON_BUFFER_H_

#include <memory>
#include <vector>
#include "RefCountObj.h"
#include "page.h"

namespace akiama {
namespace common {

class BufferRaw : public RefCountObj {
public:
	explicit BufferRaw(size_t len) {
		m_data = new char[len];
		m_len = len;
	}

	BufferRaw(char *ptr, size_t len) : m_data(ptr),
		m_len(len) {
	}

	BufferRaw(const BufferRaw &b) = delete;
	BufferRaw& operator = (const BufferRaw &b) = delete;

	~BufferRaw() {
		delete[] m_data;
		m_data = nullptr;
		m_len = 0;
	}

	char *data() {
		return m_data;
	}

	const char *data() const {
		return m_data;
	}

	size_t len() {
		return m_len;
	}

	bool is_page_algined() const {
		return !((long)m_data & ~AKIAMA_PAGE_MASK);
	}

	bool is_page_algined_len() const {
		return !(m_len & ~AKIAMA_PAGE_MASK);
	}

	size_t crc() const {
		// TODO
		return 0;
	}
private:
	char *m_data;
	size_t m_len;
};

class BufferPageAlginedRaw : public BufferRaw {
public:
	// TODO
};

class BufferPtr {
public:
	BufferPtr();

	explicit BufferPtr(BufferRaw *r);

	BufferPtr(BufferRaw *r, size_t off, size_t len);

	explicit BufferPtr(size_t len);

	BufferPtr(char *ptr, size_t len);

	BufferPtr(const BufferPtr &b);

	BufferPtr& operator = (const BufferPtr &b);

	~BufferPtr() {
		release();
	}

	char *data() {
		if (m_raw) {
			return m_raw->data() + m_off;
		}
		return nullptr;
	}

	const char *data() const {
		if (m_raw) {
			return m_raw->data() + m_off;
		}
		return nullptr;
	}

	void release();

	size_t offset() const {
		return m_off;
	}

	void set_offset(size_t off) {
		assert(m_raw);
		assert((off + m_len) < m_raw->len());
		m_off = off;
	}

	size_t len() const {
		return m_len;
	}

	void set_len(size_t len) {
		assert(m_raw);
		assert((m_off + len) < m_raw->len());
		m_len = len;
	}

	size_t tail_unused_len() {
		if (m_raw) {
			return m_raw->len() - (m_off + m_len);
		}
		return 0;
	}
	size_t append(const char *ptr, size_t len);
private:
	size_t m_off;
	size_t m_len;
	BufferRaw *m_raw;
};

class BufferList {
public:
	typedef std::vector<BufferPtr> list;
	typedef std::vector<BufferPtr>::iterator iterator;
	typedef std::vector<BufferPtr>::const_iterator const_iterator;

	BufferList();
	explicit BufferList(const BufferPtr &p);
	BufferList(const BufferList &l);
	BufferList& operator=(const BufferList &l);

	void append(const char *ptr, size_t len);
	void append(const std::string &s);
	void append(const BufferPtr &p);
	void append(const BufferList &l);

	iterator begin() {
		return m_buffers.begin();
	}

	const_iterator begin() const {
		return m_buffers.begin();
	}

	iterator end() {
		return m_buffers.end();
	}

	const_iterator end() const {
		return m_buffers.end();
	}

	size_t buffer_count() const {
		return m_buffers.size();
	}
	uint64_t len() const {
		return m_len;
	}
private:
	uint64_t m_len;
	list m_buffers;
	BufferPtr m_append_buffer;
};

}; // end of ns common
}; // end of ns akiama

#endif
