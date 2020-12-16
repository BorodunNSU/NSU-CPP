cmake_minimum_required(VERSION 3.17)
project(Lab2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab2 main.cpp
        Calculator.cpp Calculator.h
        Context.h Operation.h OperationInterface.h
        OperationMaker.h Factory.h
        Operations/Push.cpp Operations/Define.cpp
        Operations/Div.cpp Operations/Mul.cpp
        Operations/Pop.cpp Operations/Print.cpp
        Operations/Sqrt.cpp Operations/Sub.cpp
        Operations/Sum.cpp Exceptions.h)