cmake_minimum_required(VERSION 3.21)
project(Ex2OfirOOP)

set(CMAKE_CXX_STANDARD 14)

add_executable(Ex2OfirOOP main.cpp
        Account.cpp
        Account.h
        Bank.cpp
        Bank.h
        Person.cpp
        Person.h
        Transaction.cpp
        Transaction.h)
