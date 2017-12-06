#include <gtest/gtest.h>
#include "buffer.h"

using namespace akiama;
using namespace common;

TEST(BufferTest, BufferRaw) {
	BufferRaw null_raw;

	EXPECT_EQ(0, null_raw.len());

	BufferRaw b_raw(1024);
	EXPECT_EQ(1024, b_raw.len());

	char *ptr = new char[4096];
	BufferRaw c_raw(ptr, 4096);
	EXPECT_EQ(4096, c_raw.len());
	EXPECT_TRUE(c_raw.is_page_algined_len());
}

TEST(BufferTest, BufferPtr) {
	BufferRaw *null_raw(new BufferRaw);
	BufferRaw *raw_1024(new BufferRaw(1024));

	EXPECT_EQ(0, null_raw->count());
	BufferPtr ptr(null_raw);
	EXPECT_EQ(1, null_raw->count());

	BufferPtr ptr_1(null_raw);
	EXPECT_EQ(2, null_raw->count());
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
