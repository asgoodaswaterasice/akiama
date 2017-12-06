#ifndef TRANSACTION_H_
#define TRANSACTION_H_

class Transaction {
public:
	enum {
		OP_NOP = -1,
		OP_CREATE,
		OP_DELETE,
		OP_READ,
		OP_WRITE,
	};

private:
};

#endif
