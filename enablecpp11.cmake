include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++11" CPP11_SUPPORTED)

if(CPP11_SUPPORTED)
    set_target_properties(CayenneLPP
        PROPERTIES COMPILE_FLAGS "-std=c++11"
    )
else()
    message(STATUS "${CMAKE_CXX_COMPILER} does not support c++11, please use a different compiler!")
endif()
