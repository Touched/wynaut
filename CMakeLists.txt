cmake_minimum_required(VERSION 2.8.4)
project(wynaut)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(BISON)
find_package(FLEX)

BISON_TARGET(wynautParser grammar/wynaut.y  ${CMAKE_SOURCE_DIR}/grammar/wynautParser.cpp)

FLEX_TARGET(wynautScanner grammar/wynaut.l ${CMAKE_SOURCE_DIR}/grammar/wynautLexer.cpp)

ADD_FLEX_BISON_DEPENDENCY(wynautScanner wynautParser)

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

    util/Expression.hpp
    util/Expression.cpp
    util/Argument.hpp
    util/Argument.cpp
    util/ArgumentWrapper.hpp
    util/ArgumentWrapper.cpp
    util/Arguments.hpp
    util/Arguments.cpp
)

add_executable(wynaut ${SOURCE_FILES} ${BISON_wynautParser_OUTPUTS} ${FLEX_wynautScanner_OUTPUTS})
target_link_libraries(wynaut ${FLEX_LIBRARIES} ${BISON_LIBRARIES})