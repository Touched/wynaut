cmake_minimum_required(VERSION 2.8.4)
project(wynaut)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Generate Bison and flex files
find_package(BISON)
find_package(FLEX)

bison_target(wynautParser grammar/wynaut.y  ${CMAKE_SOURCE_DIR}/grammar/wynautParser.cpp)
flex_target(wynautScanner grammar/wynaut.l ${CMAKE_SOURCE_DIR}/grammar/wynautLexer.cpp)

add_flex_bison_dependency(wynautScanner wynautParser)

# Create core libraries
set(SOURCE_FILES
    main.cpp

    lang/Type.cpp
    lang/Type.hpp
    lang/Dialect.hpp
    lang/Dialect.cpp
    lang/ImporterContext.hpp
    lang/Module.hpp
    lang/Module.cpp
    lang/Importer.hpp
    lang/Importer.cpp
    lang/ImportHandler.hpp
    lang/ImportHandler.cpp
    lang/ImportError.hpp
    lang/ImportError.cpp
    lang/Function.hpp
    lang/Function.cpp

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

    grammar/wynaut.h

    lang/Expression.hpp
    lang/Expression.cpp
    lang/Condition.hpp
    lang/Condition.cpp
    lang/Argument.hpp
    lang/Argument.cpp
    lang/Arguments.hpp
    lang/Arguments.cpp
    lang/arguments/Constant.hpp
    lang/arguments/Constant.cpp
    lang/arguments/String.hpp
    lang/arguments/String.cpp
    lang/arguments/ArgType.hpp
    lang/arguments/ArgType.cpp
)

add_executable(wynaut ${SOURCE_FILES} ${BISON_wynautParser_OUTPUTS} ${FLEX_wynautScanner_OUTPUTS})
target_link_libraries(wynaut ${FLEX_LIBRARIES} ${BISON_LIBRARIES})