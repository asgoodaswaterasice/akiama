#ifndef AKIAMA_COMMON_IO_PRIORITY_H
#define AKIAMA_COMMON_IO_PRIORITY_H

#include <string>

namespace akiama {
namespace common {

extern pid_t akiama_gettid();

#ifndef IOPRIO_WHO_PROCESS
# define IOPRIO_WHO_PROCESS 1
#endif
#ifndef IOPRIO_PRIO_VALUE
# define IOPRIO_CLASS_SHIFT 13
# define IOPRIO_PRIO_VALUE(class, data) \
		(((class) << IOPRIO_CLASS_SHIFT) | (data))
#endif
#ifndef IOPRIO_CLASS_RT
# define IOPRIO_CLASS_RT 1
#endif
#ifndef IOPRIO_CLASS_BE
# define IOPRIO_CLASS_BE 2
#endif
#ifndef IOPRIO_CLASS_IDLE
# define IOPRIO_CLASS_IDLE 3
#endif

extern int ioprio_set(int whence, int who, int ioprio);

extern int ioprio_string_to_class(const std::string& s);

}; // end of ns common
}; // end of ns akiama

#endif
