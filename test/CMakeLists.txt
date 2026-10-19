set(target ${MP2_TESTS})

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} gtest ${MP2_LIBRARY})
target_include_directories(${target} PUBLIC ${CMAKE_SOURCE_DIR}/gtest ${MP2_INCLUDE})

# --- ФИКС ДЛЯ WINDOWS (MSVC + GTEST) ---
# Отключаем использование устаревшего std::tr1, из-за которого падает сборка в MSVC
if(MSVC)
    target_compile_definitions(${target} PRIVATE GTEST_HAS_TR1_TUPLE=0)
    target_compile_definitions(${target} PRIVATE GTEST_USE_OWN_TR1_TUPLE=0)
endif()
# ---------------------------------------

#OpenMP
find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${target} OpenMP::OpenMP_CXX)
endif()

add_test(${target} ${target})
