function(add_jit_executable)
    get_filename_component(target "${ARGV0}" NAME_WLE)
    message("generating jit target: ${target}")
    add_executable(${target} ${ARGV0})
    target_link_libraries(${target} PUBLIC xbyak::xbyak fmt::fmt)
endfunction()

add_jit_executable(test_const.cc)
add_jit_executable(test_isa.cc)
