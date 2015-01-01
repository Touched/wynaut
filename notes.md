Project Notes
-------------

## Overview
The parser uses Bison and flex to generate the script. Scripts select a possible dialect, which handles very low level functions (these will be mapped to various scripting languages) such as conditional and unconditional branches, etc.

The 'dialect' will also act as an 'importer' factory, producing objects which will find 'modules'. The importer class is abstract, allowing variations on the parent with a possible plugin system. The plugin system will probably be implemented in pure C, as the C standard defines an ABI (whereas C++ does not, making it difficult to compile plugins).

The importers build module objects which contain functions that inject binary 'pieces' directly into 'fragments'. Fragments are basically collections of pieces that have an offset (thus they can be branched to and referenced elsewhere). The pieces are polymorphic, so fragments can contain mixed types. I've currently implemented two types of pieces. The first refers to another fragment (so it works like a dynamic label in XSE or whatever). The second just contains pure binary data. Functions will return pieces (or place them directly into the fragment - I haven't decided yet) thus making the body of the script.

Additionally, importers are given a 'context' which helps them decide what kind of module object to produce. The context will eventually contain information about the script, such as the dialect, target ROM header (so you can have separate functions based on the target ROM), and maybe some other features. There is currently no implementation for this class.

Dialects also define 'types' which are used to declare the variables and things used in the scripts. The only mandatory type is the constant type, which allows you to label a regular number. These labels will be replaced with this constant at compile time, allowing simple calculations (+, -, *, /) in parameters and such. These CANNOT be applied to actual variables outside of assignment statements due to the lack of scope - there is no local scope to store the result in and doing otherwise will pollute the global scope and introduce annoying errors for the unwary.

While only string literals, constants and identifiers are supported as arguments (expressions involving non-constants aren't allowed - see above reasoning), I plan to allow file path support for more complex functions that assemble ASM and integrate other languages. These will obviously need platform specific features. When the time comes, I will write a GNU/Linux implementation, and leave place for Windows-specific (and other platforms) code using conditional macros.

## Plug-in system
This still needs to be figured out, I have no idea what is even needed from a plug-in system yet. There will also be platform specific code needed, as we will be working with shared objects (DLLs). I want to allow multi-language support to allow Java, Python and C# plug-ins as well as plug-ins written in pure C.

## To-Do list
- [ ] Plug-ins
- [ ] Finish the compiler
- [ ] Refine the grammar
- [ ] Documentation
- [ ] Dialects
- [ ] Function and Module implementations