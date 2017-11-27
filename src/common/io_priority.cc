#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */
#include <algorithm>

#include "io_priority.h"

namespace akiama {
namespace common {

pid_t akiama_gettid(void)
{
  return syscall(SYS_gettid);
}

int akiama_ioprio_set(int which, int who, int ioprio)
{
    return syscall(SYS_ioprio_set, which, who, ioprio);
}

int ioprio_string_to_class(const std::string& s)
{
  std::string l = s;
  std::transform(l.begin(), l.end(), l.begin(), ::tolower);

  if (l == "idle")
    return IOPRIO_CLASS_IDLE;
  if (l == "be" || l == "besteffort" || l == "best effort")
    return IOPRIO_CLASS_BE;
  if (l == "rt" || l == "realtime" || l == "real time")
    return IOPRIO_CLASS_RT;
  return -EINVAL;
}

}; // end of ns common
}; // end of ns akiama
