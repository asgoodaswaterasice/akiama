set(common_files
    Thread.cc
    page.cc
    io_priority.cc)

add_library(common_objs OBJECT ${common_files})

set(akiama_common_objs 
	$<TARGET_OBJECTS:common_objs>)

add_library(common STATIC ${akiama_common_objs})
target_link_libraries(common pthread)
