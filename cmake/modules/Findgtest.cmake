# - Find gtest
# Find gtest-devel library
#
# GTEST_INCLUDE_DIR
# GTEST_LIB
# GTEST_FOUND

find_path(GTEST_INCLUDE_DIR "gtest/gtest.h")
find_library(GTEST_LIB gtest)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(gtest DEFAULT_MSG GTEST_LIB GTEST_INCLUDE_DIR)

mark_as_advanced(
	GTEST_INCLUDE_DIR
	GTEST_LIB)
