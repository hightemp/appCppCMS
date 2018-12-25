cmake_minimum_required(VERSION 2.6)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)
set(PROJECT_DIR ../)

file(GLOB INCLUDE_DIRS
	"${PROJECT_DIR}app/*/"
)

# set(CMAKE_CXX_IMPLICIT_LINK_LIBRARIES "${GTEST_LIBRARIES} std")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
		-lstdc++ \
		-ldl \
		-lmysqlcppconn \
		/usr/lib/libcgicc.a \
		${SRC_DIR}../lib/segvcatch/lib/libsegvcatch.a")

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ${PROJECT_DIR} ${INCLUDE_DIRS})

file(GLOB TEST_SOURCE_FILES
	"*Test.cpp"
)

foreach (TEST_SOURCE_FILE ${TEST_SOURCE_FILES})
	# Link runTests with what we want to test and the GTest and pthread library
	GET_FILENAME_COMPONENT(TEST_OUTPUT_FILE ${TEST_SOURCE_FILE} NAME)
	string(REPLACE ".cpp" "" TEST_OUTPUT_FILE ${TEST_OUTPUT_FILE})
	add_executable(bin/${TEST_OUTPUT_FILE} ${TEST_SOURCE_FILE})
	target_link_libraries(bin/${TEST_OUTPUT_FILE} ${GTEST_LIBRARIES} pthread)
	execute_process(COMMAND bin/${TEST_OUTPUT_FILE})
endforeach(TEST_SOURCE_FILE)