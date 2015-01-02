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

    grammar/wynaut.h

    language/Expression.hpp
    language/Expression.cpp
    language/Condition.hpp
    language/Condition.cpp
    language/Argument.hpp
    language/Argument.cpp
    language/Arguments.hpp
    language/Arguments.cpp
    language/arguments/Constant.hpp
    language/arguments/Constant.cpp
    language/arguments/String.hpp
    language/arguments/String.cpp
    language/arguments/ArgType.hpp
    language/arguments/ArgType.cpp
)

add_executable(wynaut ${SOURCE_FILES} ${BISON_wynautParser_OUTPUTS} ${FLEX_wynautScanner_OUTPUTS})
target_link_libraries(wynaut ${FLEX_LIBRARIES} ${BISON_LIBRARIES})