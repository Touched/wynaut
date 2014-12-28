cmake_minimum_required(VERSION 2.8.4)
project(wynaut)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(BISON)
find_package(FLEX)

BISON_TARGET(MyParser grammar/wynaut.y  ${CMAKE_SOURCE_DIR}/grammar/wynaut_parser.cpp)

FLEX_TARGET(MyScanner grammar/wynaut.l ${CMAKE_SOURCE_DIR}/grammar/wynaut_lexer.cpp)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

set(SOURCE_FILES
    main.cpp
    language/Type.cpp
    language/Type.hpp
    language/Dialect.hpp
    language/Dialect.cpp
    language/ImporterContext.hpp
    language/Module.hpp
    language/Module.cpp
    language/Importer.hpp
    language/Importer.cpp
    language/ImportHandler.hpp
    language/ImportHandler.cpp
    language/ImportError.hpp
    language/ImportError.cpp
    language/Function.hpp
    language/Function.cpp

    compiler/Blob.hpp
    compiler/Blob.cpp
    compiler/Fragment.hpp
    compiler/Fragment.cpp
    compiler/Piece.hpp
    compiler/Piece.cpp
    compiler/Reference.hpp
    compiler/Reference.cpp
    compiler/Script.hpp
    compiler/Script.cpp
)

add_executable(wynaut ${SOURCE_FILES} ${BISON_MyParser_OUTPUTS} ${FLEX_MyScanner_OUTPUTS})
target_link_libraries(wynaut ${FLEX_LIBRARIES} ${BISON_LIBRARIES})