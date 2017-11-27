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
    thread = TestThread();
    thread.create("test_thread");
    thread.join();
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TEST();
}
