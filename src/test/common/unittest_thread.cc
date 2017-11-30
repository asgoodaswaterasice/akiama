#include "Thread.h"
#include <gtest/gtest.h>
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace akiama;
using namespace common;

class TestThread : public Thread {
private:
    void *entry() {
        while (true) {
            cout << "test thread running" << endl;
            sleep(1);
        }
    }
};

TEST(thread_test, normal) {
    TestThread thread;
    thread.create("test_thread");

	sleep(10);
	EXPECT_TRUE(0 == thread.cancel());

	EXPECT_TRUE(0 == thread.join());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
