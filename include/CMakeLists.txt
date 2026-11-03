set(target ${MP2_CUSTOM_PROJECT})

project(${target})

file(GLOB hdrs "*.h*")

add_library(${target} INTERFACE)
target_sources(${target} INTERFACE ${hdrs})