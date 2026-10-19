set(target "gtest")

add_library(${target} STATIC gtest-all.cc)

if((${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR
    ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") AND
    (${CMAKE_SYSTEM_NAME} MATCHES "Linux"))
    set(pthread "-pthread")
endif()

target_link_libraries(${target} ${pthread})

# --- ‘» — ƒÀﬂ WINDOWS ---
if(MSVC)
    target_compile_definitions(${target} PRIVATE GTEST_HAS_TR1_TUPLE=0)
    target_compile_definitions(${target} PRIVATE GTEST_USE_OWN_TR1_TUPLE=0)
endif()