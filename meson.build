project(
  'pizza',
  'cpp',
  version : '0.1.0',
  default_options : ['warning_level=3', 'cpp_std=c++11']
)

libDependencies = [
    dependency('openmp'),
]

srcFiles = [
    'pizza.cpp',
]

executable('pizza', srcFiles, install : true,  dependencies : libDependencies)
