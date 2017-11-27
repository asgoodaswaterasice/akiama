set(common_files
    Thread.cc
    page.cc
    io_priority.cc)

set(common_objs OBJECT ${common_files})

add_library(common STATIC ${common_objs})
