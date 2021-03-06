#ifndef AKIAMA_COMMON_THREAD_H_
#define AKIAMA_COMMON_THREAD_H_

#include <pthread.h>
#include <sys/types.h>
#include <mutex>

namespace akiama {
namespace common {

class Thread {
public:
	Thread();
	Thread(const Thread & t) = delete;
	Thread &operator=(const Thread &t) = delete;
	virtual ~Thread();
    const pthread_t &thread_id() const;
    pid_t pid() const;
    bool is_started() const;
    bool am_self() const;
    int kill(int signal);
    int join(void **retval = 0);
    int detach();
    int cancel();
    int set_ioprio(int cls, int prio);
    int set_affinity(int cpuid);
    int try_create(size_t stacksize);
    void create(const char *name, size_t stacksize = 0);
private:
    static void *entry_func(void *arg);
    /**
     * thread init procedure,set m_pid,thread ioprio,
     * thread cpu affinity, thread name
     */
    void *entry_warpper();

    virtual void *entry() = 0;
private:
    pthread_t m_thread_id;
    pid_t m_pid;
    int m_cpuid;
    int m_ioprio_class, m_ioprio_priority;
    mutable std::mutex m_lock;
    const char *m_thread_name;
};

}; // end of ns common 
}; // end of ns akiama

#endif
