project('Rand', 'cpp', 'c', default_options : [
    'warning_level=3',
    'werror=false',
    'cpp_std=c++20',
    'b_lto=true',
    # 'b_lto_mode=thin',
])

inc = include_directories('include')

rand_dep = declare_dependency(include_directories : inc)

if get_option('testu01')
    testu01_proj = subproject('TestU01')
    testu01_dep = testu01_proj.get_variable('testu01_dep')

    executable('smallcrush', 'test/crush.cc', dependencies : [rand_dep, testu01_dep])
    executable('crush', 'test/crush.cc', dependencies : [rand_dep, testu01_dep])
    executable('bigcrush', 'test/crush.cc', dependencies : [rand_dep, testu01_dep])
endif

if get_option('random123')
    random123_proj = subproject('random123')
    random123_dep = random123_proj.get_variable('random123_dep')

    test_philox_exe = executable('test_philox', 'test/test_philox.cc', dependencies : [rand_dep, random123_dep])
    test('test_philox', test_philox_exe)
endif
