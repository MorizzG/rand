project('Rand', 'cpp', 'c', default_options : [
    'warning_level=3',
    'werror=false',
    'cpp_std=c++20',
    'b_lto=true',
    # 'b_lto_mode=thin',
])

inc = include_directories('include')

rand_dep = declare_dependency(include_directories : inc)

subdir('TestU01')

executable('philox_smallcrush', 'test/philox/smallcrush.cc', dependencies : [rand_dep, testu01_dep])
executable('philox_crush', 'test/philox/crush.cc', dependencies : [rand_dep, testu01_dep])
