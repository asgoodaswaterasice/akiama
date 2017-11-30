#include "Thread.h"
#include "page.h"
#include "io_priority.h"
#include <assert.h>
#include <sched.h>
#include <signal.h>

namespace akiama {
namespace common {

Thread::Thread() : m_thread_id(0),
	m_pid(0), m_cpuid(0),
	m_ioprio_class(0), m_ioprio_priority(0),
    m_thread_name("") {
}

Thread::~Thread() {
}

const pthread_t & Thread::thread_id() const {
    return m_thread_id;
}

pid_t Thread::pid() const {
    std::lock_guard<std::mutex> lock(m_lock);
    return m_pid;
}

bool Thread::is_started() const {
    return m_thread_id != 0;
}

bool Thread::am_self() const {
    return pthread_self() == m_thread_id;
}

int Thread::kill(int signal) {
    if (m_thread_id) {
        return pthread_kill(m_thread_id, signal);
    }
    return -EINVAL;
}

int Thread::join(void **retval) {
    if (m_thread_id) {
        return pthread_join(m_thread_id, retval);
    }
    return -EINVAL;
}

int Thread::detach() {
    if (m_thread_id) {
        return pthread_detach(m_thread_id);
    }
    return -EINVAL;
}

int Thread::cancel() {
    if (m_thread_id) {
        return pthread_cancel(m_thread_id);
    }
    return -EINVAL;
}

int Thread::try_create(size_t stacksize) {
    int ret = 0;
    pthread_attr_t *attr_p = NULL;
    pthread_attr_t attr;

    stacksize &= AKIAMA_PAGE_MASK;
    if (stacksize) {
        attr_p = &attr;
        ret = pthread_attr_setstacksize(attr_p, stacksize);
        if (ret) {
            return ret;
        }
    }
    ret = pthread_create(&m_thread_id, attr_p, entry_func, (void*)this);
    if (ret) {
        return ret;
    }
    return 0;
}

void Thread::create(const char *name, size_t stacksize) {
    m_thread_name = name;
    int ret = try_create(stacksize);
    assert(ret == 0);
}

int Thread::set_ioprio(int cls, int prio) {
    std::lock_guard<std::mutex> lock(m_lock);
    m_ioprio_class = cls;
    m_ioprio_priority = prio;
    if (m_pid && cls >= 0 && prio >= 0) {
        return akiama_ioprio_set(IOPRIO_WHO_PROCESS,
                m_pid, IOPRIO_PRIO_VALUE(cls, prio));
    }
    return 0;
}

int Thread::set_affinity(int cpuid) {
    std::lock_guard<std::mutex> lock(m_lock);
    m_cpuid = cpuid;
    // TODO
    return 0;
}

void *Thread::entry_func(void *arg) {
    Thread *thread = (Thread*)arg;
    return thread->entry_warpper();
}

void *Thread::entry_warpper() {
    m_pid = akiama_gettid();
    {
        std::lock_guard<std::mutex> lock(m_lock);
        if (m_ioprio_class && m_ioprio_priority) {
            akiama_ioprio_set(IOPRIO_WHO_PROCESS,
                    m_pid,
                    IOPRIO_PRIO_VALUE(m_ioprio_class,
                        m_ioprio_priority));
        }
        cpu_set_t cpu_set;
        CPU_ZERO(&cpu_set);
        CPU_SET(m_cpuid, &cpu_set);
        if (m_cpuid >= 0) {
            sched_setaffinity(0, sizeof(cpu_set), &cpu_set);
        }
    }
    pthread_setname_np(m_thread_id, m_thread_name);
    return entry();
}

}; // end of ns common 
}; // end of ns akiama
