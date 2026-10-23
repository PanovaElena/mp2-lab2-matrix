# Создаем исполняемый файл для теста скорости
add_executable(test_speed SpeedTest.cpp)

# Подключаем папку include, чтобы найти tmatrix.h
target_include_directories(test_speed PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)