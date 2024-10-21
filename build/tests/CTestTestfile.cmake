# CMake generated Testfile for 
# Source directory: /Users/jordan/Code/Supermarket Check Out/tests
# Build directory: /Users/jordan/Code/Supermarket Check Out/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(AllTests "/Users/jordan/Code/Supermarket Check Out/build/tests/RunTests")
set_tests_properties(AllTests PROPERTIES  _BACKTRACE_TRIPLES "/Users/jordan/Code/Supermarket Check Out/tests/CMakeLists.txt;36;add_test;/Users/jordan/Code/Supermarket Check Out/tests/CMakeLists.txt;0;")
subdirs("../_deps/catch2-build")
