# Changelog

### v0.31.4
- Updated README to alert of the movement of the project

### v0.31.3
- Fixed imports causing fatal error
- Fixed incorrect error caused by passing a template expression parameter to a substruct template as a template argument
- Fixed fatal crash when using `uninit` as a default value for a struct member

### v0.31.2
- Removed the `cast` operator (merged with `as`)

### v0.31.1
- Fixed name mangling of templated structs
- Fixed some stores in LLVM IR incorrectly being volatile
- Fixed printing of templated struct types
- Fixed templates with values not being correctly detecting if they are the same type
- Fixed crashes caused by templated substructs

### v0.31.0
- Changed template delimiters to `<{` and `}>`
- Fixed fatal error when declaring imports at global scope
- Fixed fatal error when using using a struct initializer as a function argument
- Fixed fatal error when taking the address of a derefeference expression
- Added config options `badPracticeDerefOfAddr` and `badPracticeAddrOfDeref`

### v0.30.3
- Fixed fatal error when a struct member with type inference has the default value of `uninit`
- Changed the config option `allowStructMemberTypeInference` to be per file
- Fixed fatal error when setting a global variable to the value of a `copy` expr

### v0.30.2
- Fixed fatal error when using imported types as the type of a function parameter
- Fixed some incorrect error messages about constant-evaluated expressions
- Allowed imported types to be used in `alias` expressions and as function return types
- Added the config option `allowStructMemberTypeInference` (defaults to `false`)
- Fixed struct member variables not allowed to have the same name as a global variable, function, etc.

### v0.30.1
- Disallowed using expression operators as a statement (means that things like `1 + 2;` now emit an error)
- Added more checking for improper use of `uninit`
- Fixed improper error message for missing `;` at end of expression statement
- Fixed fatal error when getting a member of a dereferenced value (`(a.&).b`)
- Fixed imports of imports not always being handled properly in the semantic analysis

### v0.30.0
- Added the following built-in types:
	- `ISize`
	- `USize`
- Added the following intrinsic functions:
	- `@addISize(ISize read, ISize read) -> ISize`
	- `@addUSize(USize read, USize read) -> USize`
	- `@addWrapISize(ISize read, ISize read) -> ISize`
	- `@addUrapISUze(ISize read, USize read) -> USize`
	- `@subISize(ISize read, ISize read) -> ISize`
	- `@subUSize(USize read, USize read) -> USize`
	- `@subWrapISize(ISize read, ISize read) -> ISize`
	- `@subUrapISUze(ISize read, USize read) -> USize`
	- `@mulISize(ISize read, ISize read) -> ISize`
	- `@mulUSize(USize read, USize read) -> USize`
	- `@mulWrapISize(ISize read, ISize read) -> ISize`
	- `@mulUrapISUze(ISize read, USize read) -> USize`
	- `@divISize(ISize read, ISize read) -> ISize`
	- `@divUSize(USize read, USize read) -> USize`
	- `@negateISize(ISize read, ISize read) -> ISize`
	- `@equalISize(ISize read, ISize read) -> Bool`
	- `@notEqualISize(ISize read, ISize read) -> Bool`
	- `@lessThanISize(ISize read, ISize read) -> Bool`
	- `@lessThanEqualISize(ISize read, ISize read) -> Bool`
	- `@greaterThanISize(ISize read, ISize read) -> Bool`
	- `@greaterThanEqualISize(ISize read, ISize read) -> Bool`
	- `@equalUSize(USize read, USize read) -> Bool`
	- `@notEqualUSize(USize read, USize read) -> Bool`
	- `@lessThanUSize(USize read, USize read) -> Bool`
	- `@lessThanEqualUSize(USize read, USize read) -> Bool`
	- `@greaterThanUSize(USize read, USize read) -> Bool`
	- `@greaterThanEqualUSize(USize read, USize read) -> Bool`
	- `@convIntToISize(Int read) -> ISize`
	- `@convIntToUSize(Int read) -> USize`
	- `@convUIntToISize(UInt read) -> ISize`
	- `@convUIntToUSize(UInt read) -> USize`
	- `@convBoolToISize(Bool read) -> ISize`
	- `@convBoolToUSize(Bool read) -> USize`
	- `@convISizeToInt(ISize read) -> Int`
	- `@convISizeToUInt(ISize read) -> UInt`
	- `@convISizeToBool(ISize read) -> Bool`
	- `@convISizeToUSize(ISize read) -> USize`
	- `@convUSizeToInt(USize read) -> Int`
	- `@convUSizeToUInt(USize read) -> UInt`
	- `@convUSizeToBool(USize read) -> Bool`
	- `@convUSizeToISize(USize read) -> ISize`

### v0.29.0
- Fixed getting members of values returned from functions
- Fixed function call arguments not being printed correctly in the `PrintAST` output target
- Fixed missing location lookup for message reporting
- Added struct initializers
- Added struct member default values

### v0.28.0
- Added the following intrinsic functions:
	- `@convIntToUInt(Int read) -> UInt`
	- `@convIntToBool(Int read) -> Bool`
	- `@convUIntToInt(UInt read) -> Int`
	- `@convUIntToBool(UInt read) -> Bool`
	- `@convBoolToInt(Bool read) -> Int`
	- `@convBoolToUInt(Bool read) -> UInt`
- Added the following operators:
	- `as`
	- `cast`
- Fixed printing of pointer types to reflect the change from `^` to `&`

### v0.27.1
- Changed operator `&&` to `and`
- Changed operator `||` to `or`
- Changed pointer (`^`) to `&`
- Changed dereference (`.^`) to `.&`
- Changed template packs from using `{`/`}` as delimiters to using `|` as the delimiter
- Fixed logic with nested logical operators (for example: `true or (false and true)`)

### v0.27.0
- Changed the name mangling prefix from "P" to "PTHR"
- Added structs
	- members can be `var` or `def`
- Added accessor (`.`) operator to access struct members
- added `@__printBool`
	- This existence of this is just temporary
- Added checking for usage of `uninit` in not an assignment operation

### v0.26.1
- Added parsing of function parameter packs
- Fixed fatal error caused by not properly checking that an identifier can be called like a function
- Fixed function calls not being properly checked by semantic analysis

### v0.26.0
- Added the following intrinic functions:
	- `@equalInt(Int read, Int read) -> Int`
	- `@notEqualInt(Int read, Int read) -> Int`
	- `@lessThanInt(Int read, Int read) -> Int`
	- `@lessThanEqualInt(Int read, Int read) -> Int`
	- `@greaterThanInt(Int read, Int read) -> Int`
	- `@greaterThanEqualInt(Int read, Int read) -> Int`
	- `@equalUInt(UInt read, Uint read) -> UInt`
	- `@notEqualUInt(UInt read, Uint read) -> UInt`
	- `@lessThanUInt(UInt read, Uint read) -> UInt`
	- `@lessThanEqualUInt(UInt read, Uint read) -> UInt`
	- `@greaterThanUInt(UInt read, Uint read) -> UInt`
	- `@greaterThanEqualUInt(UInt read, Uint read) -> UInt`
	- `@equalBool(Bool read, Bool read) -> Bool`
	- `@notEqualBool(Bool read, Bool read) -> Bool`
	- `@logicalAnd(Bool read, Bool read) -> Bool`
	- `@logicalOr(Bool read, Bool read) -> Bool`
	- `@logicalNot(Bool read) -> Bool`
- Added the following operators:
	- `==`
	- `!=`
	- `<`
	- `<=`
	- `>`
	- `>=`
	- `&&`
	- `||`
	- `!`

### v0.25.0
- Fixed formatting for building documentation
- Added `alias` statements

### v0.24.1
- Added implicit conversion for infix operators
- Fixed an implicit conversion error not properly reporting
- Fixed some multiply operators calling the incorrect functions

### v0.24.0
- Added the UInt type
- Added implicit conversion for integral literals
- Added the intrinsic function `@__printUInt(UInt read)` and `@__printSeparator()`
	- This existence of this is just temporary
- Added the following intrinsic functions:
	- `@addInt(Int read, Int read) -> Int`
	- `@addUInt(UInt read, UInt read) -> UInt`
	- `@addWrapInt(Int read, Int read) -> Int`
	- `@addWrapUInt(UInt read, UInt read) -> UInt`
	- `@subInt(Int read, Int read) -> Int`
	- `@subUInt(UInt read, UInt read) -> UInt`
	- `@subWrapInt(Int read, Int read) -> Int`
	- `@subWrapUInt(UInt read, UInt read) -> UInt`
	- `@mulInt(Int read, Int read) -> Int`
	- `@mulUInt(UInt read, UInt read) -> UInt`
	- `@mulWrapInt(Int read, Int read) -> Int`
	- `@mulWrapUInt(UInt read, UInt read) -> UInt`
	- `@divInt(Int read, Int read) -> Int`
	- `@divUInt(UInt read, UInt read) -> UInt`
	- `@negateInt(Int read) -> Int`
- Added the following operators:
	- `+`
	- `+@` (addition with wrapping)
	- `-` (both negate and subtraction)
	- `-@` (subtraction with wrapping)
	- `*`
	- `*@` (multiplication with wrapping)
	- `/`
	

### v0.23.0
- Added function overloading
- Fixed fatal errors with using functions by explicitly disallowing it (only temporary)
- Fixed implicit conversions for function arguments
- Added checking for multiple functions with the attribute `#export` with the same name
- Temporarily disallowed functions with the attribute `#export` from having parameters
- Organized build-system
	- renamed CLI to pthr
	- added groupings
	- made the compiler the default start project
- Added the `#export` attribute for variables

### v0.22.1
- Added some missing uses of imports
	- `def sub_import = some_import.sub_import;` at local scope (at global scope will be supported eventually)
	- `def sub_import = @import("some_import.pthr").sub_import;`

### v0.22.0
- Added tokenizing and parsing of type `String`
- Fixed literal strings and literal chars not being printed correctly in the `PrintAST` output target
- Added checking if type is a literal float or literal char
	- (not supported yet, so it errors)
- Fixed intrinsic function calls as expressions causing a fatal error
- Fixed AST printer adding `[UNREACHABLE]` after a function call
- Added the `#pub` intrinsic
- Added the intrinsic function `@import(String read)`
- Fixed empty string / char literals causing a fatal error
- Added attributes for variable declarations
- Added error if discarding the return value of a function

### v0.21.4
- Removed being able to set global variables to be value of another variable
	- this is only temporary
- Added order-independent declaration (in global scope)
- Added variable type inference

### v0.21.3
- `read` parameters are no longer marked as `readonly` in LLVM IR automatically
	- The intention is to add this back in some optimization pass
- Added checking to prevent taking the address of an intrinsic

### v0.21.2
- Added the intrinsic function `@__printInt(Int read)`
	- This existence of this is just temporary
- Added warning if a `write`  parameter is known to never be written to

### v0.21.1
- Added a semantic analysis check to make sure that arguments to write parameters are mutable
- Added more parameter marking in LLVM IR
	- `read` parameters marked as `readonly`
	- `nonnull`
	- `write` parameters marked as `noalias`
	- `dereferenceable`

### v0.21.0
- Fixed printing of AST not having an arrow for function attributes
- Added function parameters
	- `read` and `write` parameters work
	- `in` is not supported yet
- Fixed call to breakpoint when type of return expression was incorrect
- Added implicit const pointer conversion for return statements
- Fixed incorrect LLVM IR code being generated for functions that return `Void` without an explicit `return` in all control paths

### v0.20.2
- Added implicit conversion from a non-const-pointer to a const-pointer

### v0.20.1
- Fixed assert firing when using a function as a value
- Fixed breakpoint firing when function marked with `#entry` does not return `Int`

### v0.20.0
- Added `def` variable declaration
- Fixed local variables being initialized with the value `uninit`
- Global variables can no longer be initialized with the value `uninit`
- Added const pointers (add `|` to the pointer)
- Fixed global variables being initialized with an `addr` expression
- Made it illegal to initialize a global variable with an dereference expression

### v0.19.0
- Added `unreachable` statements
- Added detection for unreachable code after `return` (and `unreachable`) statements inside conditionals
- Fixed `return` statements in conditionals causing LLVM to error
- Changed `@__printHelloWorld` from using `printf` to using `puts`
- Added `puts` to the list of functions that cannot be used as export names
- CLI now only waits for user input to exit when compiling with MSVC when not doing a ReleaseDist build

### v0.18.1
- Added tokenizing of string and char literals
	- supports escape characters: `\0`, `\a`, `\b`, `\t`, `\n`, `\v`, `\f`, `\r`, `\'`, `\"`, and `\\`
- Improved messaging location of multiline objects

### v0.18.0
- Added conditional statements
	- `if`
	- `else if`
	- `else`

### v0.17.0
- Added `@breakpoint` intrinsic
- Panther functions (not marked with `#export`) now use the fast calling convention

### v0.16.0
- Reorganized part of the build system
- Changed debug working directory to `/testing`
- Added output to Executable
- Added default file output naming

### v0.15.0
- Added the intrinsic function `@__printHelloWorld()`
	- This existence of this is just temporary

### v0.14.2
- Fixed printing of AST for postfix operators
- Fixed "crashing" when doing semantic analysis of intrinsics
- Added marking functions as not throwing (in LLVM IR)

### v0.14.1
- Added location printing for function calls
- Added location printing for return statements

### v0.14.0
- Added pointer types
- Added the `addr` keyword
- Added the dereference (`.^`) operator 

### v0.13.1
- Fixed `copy` expressions in globals
- Fixed bug where compiler sometimes incorrectly errored that the entry function returned the incorrect type

### v0.13.0
- Added `copy` expressions

### v0.12.0
- Added Panther runtime
- Added `#entry` function attribute

### v0.11.0
- Added parenthesis expressions
- Added function call expressions and statements
- Added printing of the current output target in verbose mode
- Added semantic analysis checking for literal, ident, and uninit expressions

### v0.10.0
- Added assigning new values to variables

### v0.9.0
- Added return statements
- Added `#export` function attribute
- Added tokenizing of intrinsics

### v0.8.0
- Made global variables have private linkage
- Semantic Ananlysis now catches setting global variables to variables with value uninit
- Fixed setting variables to identifiers

### v0.7.0
- Added build instruction for LLVM
- Improved Semantic Analysis
- Added uninit expression
- Added output to LLVMIR
- Added output to object file

### v0.6.0
- Added identifier expressions

### v0.5.0
- Added parsing and semantic analysis of functions

### v0.4.1
- Added messaging for location of variable already defined (when trying to use the sane identifier)

### v0.4.0
- Added Semantic Analysis of variables

### v0.3.0
- Added parsing
	- variable declarations
	- basic types
	- literals
- Added printing of the AST

### v0.2.0
- Added foundation for parsing
- Added printing of tokens

### v0.1.0
- Added basic tokenization

### v0.0.0
- initial creation
- setup of build system