if(EXISTS "E:/PEA/Project3/cmake-build-release/tests/Testing[1]_tests.cmake")
  include("E:/PEA/Project3/cmake-build-release/tests/Testing[1]_tests.cmake")
else()
  add_test(Testing_NOT_BUILT Testing_NOT_BUILT)
endif()
