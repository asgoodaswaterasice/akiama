#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include "object.h"
#include "collection.h"

namespace akiama {
namespace objectstore {

class Transaction {
public:
	enum {
		OP_NOP = -1,
		OP_CREATE,
		OP_DELETE,
		OP_READ,
		OP_WRITE,
	};
	struct Op {
		__le32 op;
		__le64 cid;
		__le64 oid;
		__le64 off;
		__le64 len;
	} __attribute__((packed));

	void create(const coll_t &col, const object_t &obj);

	void del(const coll_t &col, const object_t &obj);

	void read(const coll_t &col, const object_t &obj, uint64_t off,
			uint64_t len, BufferList &buf);

	void write(const coll_t &col, const object_t &obj, uint64_t off,
			uint64_t len, const BufferList &buf);
private:
	// 记录最大的coll的id
	__le64 m_coll_id;
	// 记录最大的object的id
	__le64 m_object_id;
	// 维护coll_t到cid的映射
	std::map<coll_t, __le64> m_coll_index;
	// 维护object_t到oid的映射
	std::map<object_t, __le64> m_object_index;
};

}; // end of ns objectstore
}; // end of ns akiama

#endif
