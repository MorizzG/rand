project('Philox', 'cpp', 'c', default_options : [
    'warning_level=0',
    'werror=false',
    'cpp_std=c++20',
    'b_lto=true',
    # 'b_lto_mode=thin',
])

inc = include_directories('include')

philox_dep = declare_dependency(include_directories : inc)

add_project_arguments(
    '-Wno-writable-strings',  # TestU01 incorrectly uses char* instead of const char*

    language : 'cpp'
)

subdir('TestU01')

smallcrush_exe = executable('smallcrush', 'test/smallcrush.cc', dependencies : [philox_dep, testu01_dep])

crush_exe = executable('crush', 'test/crush.cc', dependencies : [philox_dep, testu01_dep])
