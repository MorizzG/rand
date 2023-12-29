cc = meson.get_compiler('c')
m_dep = cc.find_library('m')

inc = include_directories('include')

subdir('mylib')
subdir('probdist')
subdir('testu01')

mylib_lib = static_library('mylib', mylib_sources,
    include_directories : inc,
    dependencies : m_dep
)
mylib_dep = declare_dependency(link_with : mylib_lib, include_directories : inc)

probdist_lib = static_library('probdist', probdist_sources,
    include_directories : inc,
    dependencies : [m_dep, mylib_dep],
)
probdist_dep = declare_dependency(link_with : probdist_lib, include_directories : inc)

testu01_lib = static_library('testu01', testu01_sources,
    include_directories : inc,
    dependencies : [m_dep, mylib_dep, probdist_dep],
)
testu01_dep = declare_dependency(link_with : testu01_lib, include_directories : inc)



# subdir('examples')


fs = import('fs')

# inc = include_directories('../include')

bat1 = executable('bat1', 'examples/bat1.c', include_directories : inc, dependencies : testu01_dep)
test('bat1', bat1)

bat2 = executable('bat2', 'examples/bat2.c', include_directories : inc, dependencies : testu01_dep)
test('bat2', bat2)

fs.copyfile('examples/vax.bin')

bat3 = executable('bat3', 'examples/bat3.c', include_directories : inc, dependencies : testu01_dep)
test('bat3', bat3)

birth1 = executable('birth1', 'examples/birth1.c', include_directories : inc, dependencies : testu01_dep)
test('birth1', birth1)

birth2 = executable('birth2', 'examples/birth2.c', include_directories : inc, dependencies : testu01_dep)
test('birth2', birth2)

ex1 = executable('ex1', 'examples/ex1.c', include_directories : inc, dependencies : testu01_dep)
test('ex1', ex1)

ex3 = executable('ex3', 'examples/ex3.c', 'examples/my16807.c', include_directories : inc, dependencies : [testu01_dep, mylib_dep])
test('ex3', ex3)

ex4 = executable('ex4', 'examples/ex4.c', include_directories : inc, dependencies : testu01_dep)
test('ex4', ex4)

ex7 = executable('ex7', 'examples/ex7.c', 'examples/mrg32k3a.c', 'examples/xorshift.c', include_directories : inc, dependencies : testu01_dep)
test('ex7', ex7)

fbirth = executable('fbirth', 'examples/fbirth.c', include_directories : inc, dependencies : testu01_dep)
test('fbirth', fbirth)

fcoll = executable('fcoll', 'examples/fcoll.c', include_directories : inc, dependencies : testu01_dep)
test('fcoll', fcoll)

# scat = executable('scat', 'examples/scat.c', include_directories : inc, dependencies : testu01_dep)
# test('scat', scat)

scat2 = executable('scat2', 'examples/scat2.c', include_directories : inc, dependencies : testu01_dep)
test('scat2', scat2)
