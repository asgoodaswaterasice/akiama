option(WITH_COMMON_TESTS "enable the build of commom tests" ON)

if(WITH_COMMON_TESTS)
    add_subdirectory(common)
endif(WITH_COMMON_TESTS)
