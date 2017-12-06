#ifndef AKIAMA_COMMON_BUFFER_H_
#define AKIAMA_COMMON_BUFFER_H_

#include <memory>
#include "RefCountObj.h"
#include "page.h"

namespace akiama {
namespace common {

class BufferRaw : public RefCountObj {
public:
	BufferRaw() : m_data(nullptr), m_len(0) {
	}

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
	explicit BufferPtr(BufferRaw *r);

	explicit BufferPtr(size_t len);

	BufferPtr(char *ptr, size_t len);

	BufferPtr(const BufferPtr &b);

	BufferPtr& operator = (const BufferPtr &b);

	~BufferPtr() {
		release();
	}

	char *data();

	const char *data() const;

	void release();

	size_t append(const char *ptr, size_t len);
private:
	size_t m_off;
	size_t m_len;
	BufferRaw *m_raw;
};

class BufferList {
public:
	typedef std::list<BufferPtr> list;
	typedef std::list<BufferPtr>::iterator iterator;
	typedef std::list<BufferPtr>::const_iterator const_iterator;

	BufferList();
	explicit BufferList(BufferPtr p);
	void append(const char *ptr, size_t len);
	void append(const std::string &s);
	void append(const BufferPtr &p);
	void append(const BufferList &l);

	iterator begin() {
		return m_buffers.begin();
	}

	const_interator begin() const {
		return m_buffers.begin();
	}

	iterator end() {
		return m_buffers.end();
	}

	const_iterator end() const {
		return m_buffers.end();
	}
private:
	list m_buffers;
	BUfferPtr m_append_buffer;
};

}; // end of ns common
}; // end of ns akiama

#endif
