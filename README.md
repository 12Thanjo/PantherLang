![Logo](art_assets/Logo_scaled.png)
# Panther
Statically typed, compiled, high-performance, general-purpose programming language.

> [!IMPORTANT]
> This repository is largely just a proof of concept. No further development of the repository is expected. However, the project itself is still being developed, and you can find it [here](https://github.com/PCIT-Project/PCIT-CPP) as part of the [PCIT project](https://github.com/PCIT-Project). 

> [!WARNING]
> Because the project has moved, this repository will be deleted at some point in the future.

### Notes:
- This compiler is currently super early into development, so there's not any way to use it without directly editing settings in `pthr/main.cpp`
- It is not robust yet. For example, it is possible to get it to have a fatal error in some cases while parsing
- The code is not optimized yet, nor is it the absolute cleanest.
- There are lots of features that are disallowed now but will be added at some point in the future
- The logo may change in the future, but for now it's good enough


## Goals:
These are the goals that I wish to achieve with this language / compiler. In no particular order:
- Fast compile times
	- fast enough to compile all source code at once (create just one translation unit)
- Nice, readable, and helpful error messages
- Compiler helps you find mistakes (for example, nodiscard by default)
- Zero-cost abstractions
- Fast runtime (performance on-par with languages like C++)
- Language helps you catch mistakes without getting in the way (so nothing like Rust's borrow-checker)
- Seamless interop with C code (like Zig)
- Nice, readable code
	- No preprocessor
- Enjoyable to use
- Run arbitrary code at compile time (like Jai)
- Improved optimizability
	- Give the compiler more information about language constructs (without being verbose)
	- Attempt to run as much code at compile time as possible (yes, I'm aware of the halting problem)
- The build system is in Panther (like Zig and Jai)
- Compile-time reflection


## Long Term Goals:
These are the goals I have that are for after a 1.0.0 release:
- Rich and high-performance standard library
- Seamless interop with C++
	- May be impractical or impossible as Panther doesn't have features like inheritance or exceptions
- Self-hosted compiler (meaning, the Panther compiler is written in Panther)
- Panther debugger
- Package manager


## Downloading:
`git clone https://github.com/12Thanjo/Panther.git --recursive`

## Building:
Instructions on how to build (work on progress) can be found [here](documentation/building.md).

## Updates:
List of changes for each version can be found [here](CHANGELOG.md).



