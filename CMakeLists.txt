cmake_minimum_required(VERSION 2.8.4)
project(wynaut)

# Set build path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "build")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Generate Bison and flex files
find_package(BISON)
find_package(FLEX)

bison_target(wynautParser src/grammar/wynaut.y  ${CMAKE_SOURCE_DIR}/src/grammar/wynautParser.cpp)
flex_target(wynautScanner src/grammar/wynaut.l ${CMAKE_SOURCE_DIR}/src/grammar/wynautLexer.cpp)

add_flex_bison_dependency(wynautScanner wynautParser)

# Create core libraries
set(SOURCE_FILES
    src/main.cpp

    src/lang/Type.cpp
    src/lang/Type.hpp
    src/lang/Dialect.hpp
    src/lang/Dialect.cpp
    src/lang/ImporterContext.hpp
    src/lang/Module.hpp
    src/lang/Module.cpp
    src/lang/Importer.hpp
    src/lang/Importer.cpp
    src/lang/ImportHandler.hpp
    src/lang/ImportHandler.cpp
    src/lang/ImportError.hpp
    src/lang/ImportError.cpp
    src/lang/Function.hpp
    src/lang/Function.cpp

    src/compiler/Blob.hpp
    src/compiler/Blob.cpp
    src/compiler/Fragment.hpp
    src/compiler/Fragment.cpp
    src/compiler/Piece.hpp
    src/compiler/Piece.cpp
    src/compiler/Reference.hpp
    src/compiler/Reference.cpp
    src/compiler/Script.hpp
    src/compiler/Script.cpp

    src/grammar/wynaut.h

    src/lang/Expression.hpp
    src/lang/Expression.cpp
    src/lang/Condition.hpp
    src/lang/Condition.cpp
    src/lang/Argument.hpp
    src/lang/Argument.cpp
    src/lang/Arguments.hpp
    src/lang/Arguments.cpp
    src/lang/arguments/Constant.hpp
    src/lang/arguments/Constant.cpp
    src/lang/arguments/String.hpp
    src/lang/arguments/String.cpp
    src/lang/arguments/ArgType.hpp
    src/lang/arguments/ArgType.cpp

    src/lang/dialects/pokescript/Dialect.hpp
    src/lang/dialects/pokescript/Dialect.cpp
    src/lang/dialects/pokescript/Type.hpp
    src/lang/dialects/pokescript/Type.cpp

    src/util/Glob.hpp
    src/util/Glob.cpp
)

add_executable(wynaut ${SOURCE_FILES} ${BISON_wynautParser_OUTPUTS} ${FLEX_wynautScanner_OUTPUTS})
target_link_libraries(wynaut ${FLEX_LIBRARIES} ${BISON_LIBRARIES})