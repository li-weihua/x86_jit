add_executable(example1 main.cc jit.cc jit.h)
target_link_libraries(example1 PRIVATE fmt::fmt)
