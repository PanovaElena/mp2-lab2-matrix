set(target "gtest")

add_library(${target} STATIC gtest-all.cc)
target_compile_definitions(${target} PUBLIC GTEST_HAS_TR1_TUPLE=0)
if((${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR
    ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") AND
    (${CMAKE_SYSTEM_NAME} MATCHES "Linux"))
    set(pthread "-pthread")
endif()

target_link_libraries(${target} ${pthread})
