#include <gtest/gtest.h>
#include "buffer.h"

using namespace akiama;
using namespace common;

TEST(BufferTest, BufferRaw) {
	BufferRaw b_raw(1024);
	EXPECT_EQ(1024, b_raw.len());

	char *ptr = new char[4096];
	BufferRaw c_raw(ptr, 4096);
	EXPECT_EQ(4096, c_raw.len());
	EXPECT_TRUE(c_raw.is_page_algined_len());
}

TEST(BufferTest, BufferPtr) {
	BufferRaw *raw_4(new BufferRaw(4));

	BufferPtr ptr_0(raw_4);
	EXPECT_EQ(1, raw_4->count());

	{
		BufferPtr ptr_1(raw_4);
		EXPECT_EQ(2, raw_4->count());
	}
	EXPECT_EQ(1, raw_4->count());

	char *data = new char[16];
	strncpy(data, "0123456789abcdef", 16);
	BufferRaw *raw_16(new BufferRaw(data, 16));

	BufferPtr ptr_2(raw_16, 0, 10);
	EXPECT_EQ(0, ptr_2.offset());
	EXPECT_EQ(10, ptr_2.len());
	EXPECT_EQ(16-10, ptr_2.tail_unused_len());
	EXPECT_EQ(0, strncmp(ptr_2.data(), "0123456789", 10));
	
	ptr_2.set_len(4);
	ptr_2.set_offset(4);
	EXPECT_EQ(4, ptr_2.offset());
	EXPECT_EQ(4, ptr_2.len());
	EXPECT_EQ(8, ptr_2.tail_unused_len());
	EXPECT_EQ(0, strncmp(ptr_2.data(), "4567", 4));

	ptr_2.append("aaa", 3);
}

TEST(BufferTest, BufferList) {
	BufferList null_list;
	EXPECT_EQ(0, null_list.buffer_count());
	EXPECT_EQ(null_list.begin(), null_list.end());

	BufferPtr ptr(1024);
	BufferList list_1, list_2(ptr);
	list_1.append(ptr);

	EXPECT_EQ(1, list_1.buffer_count());
	EXPECT_EQ(1, list_2.buffer_count());

	list_1.append(list_2);
	EXPECT_EQ(2, list_1.buffer_count());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
