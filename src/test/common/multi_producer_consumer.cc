#include "Thread.h"
#include <vector>
#include <condition_variable>
#include <iostream>
#include <atomic>
#include <thread>
#include <sstream>

using namespace akiama;
using namespace common;

class WorkQueue {
public:
	void enqueue(int64_t job) {
		std::unique_lock<std::mutex> lock(m_mutex);
		if (m_jobs.size() < BUFFER_JOB_MAX_NUM) {
			m_jobs.push_back(job);
			m_consumer_cond.notify_one();
		} else {
			m_producer_cond.wait(lock);
		}
	}
	bool dequeue(int64_t &job) {
		std::unique_lock<std::mutex> lock(m_mutex);
		if (m_jobs.size()) {
			job = m_jobs.back();
			m_jobs.pop_back();
			m_producer_cond.notify_one();
			return true;
		} else {
			m_consumer_cond.wait(lock);
			return false;
		}
	}
private:
	std::vector<int64_t> m_jobs;
	const int BUFFER_JOB_MAX_NUM = (1 << 20);
	mutable std::condition_variable m_producer_cond;
	mutable std::condition_variable m_consumer_cond;
	mutable std::mutex m_mutex;
};

class Counters {
public:
	Counters() {
		m_data[0] = 0;
		m_data[1] = 0;
	}
	void inc(int tag) {
		m_data[tag]++;
	}
	void print() const {
		std::cout << "producer " << m_data[0];
		std::cout << " consumer " << m_data[1] << std::endl;
	}
	int64_t jobs() const {
		return m_data[1];
	}
private:
	std::atomic<int64_t> m_data[2];
};

class Producer : public Thread {
public:
	Producer(WorkQueue &queue, Counters &counter) :
		m_queue(queue), m_counter(counter) {
	}
private:
	void *entry() override {
		while (true) {
			m_queue.enqueue(1);
			m_counter.inc(0);
		}
	}
private:
	WorkQueue &m_queue;
	Counters &m_counter;
};
// std::atomic_ullong Producer::job_last_id = 0;

class Consumer : public Thread {
public:
	Consumer(WorkQueue &queue, Counters &counter) :
		m_queue(queue), m_counter(counter) {
	}
private:
	void *entry() override {
		while (true) {
			int64_t job = -1;
			if (m_queue.dequeue(job)) {
				m_counter.inc(1);
			}
		}
	}
private:
	WorkQueue &m_queue;
	Counters &m_counter;
};

int main(int argc, char **argv)
{
	if (argc != 3) {
		std::cout << "Usage: <producer num> <consumer num>" << std::endl;
		return 1;
	}

	int pro_num = std::atoi(argv[1]);
	int con_num = std::atoi(argv[2]);

	Counters counter;
	WorkQueue wq;

	std::vector<std::unique_ptr<Producer> > producers;
	std::vector<std::unique_ptr<Consumer> > consumers;

	for (int i = 0; i < pro_num; i++) {
		std::unique_ptr<Producer> pro(new Producer(wq, counter));
		std::stringstream ss;
		ss << "producer-" << i;
		pro->create(ss.str().c_str());
		producers.push_back(std::move(pro));
	}

	for (int i = 0; i < con_num; i++) {
		std::unique_ptr<Consumer> con(new Consumer(wq, counter));
		std::stringstream ss;
		ss << "consumer-" << i;
		con->create(ss.str().c_str());
		consumers.push_back(std::move(con));
	}

	int64_t last_num = counter.jobs();
	while (true) {
		int64_t current_num = counter.jobs();
		std::cout << "qps " << (current_num - last_num) << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		last_num = current_num;
	}

	return 0;
}
