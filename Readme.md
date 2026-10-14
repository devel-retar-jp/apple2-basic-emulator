# About the Apple II Plus Emulator

A minimal Apple II Plus (1979) emulator 
with auto-generated ROMs, 
demonstrating faithful 6502 CPU emulation 
and Applesoft BASIC support on vintage hardware.

------------------------------------------------------------
## 0. Features of the Apple II Plus ROM BASIC

### Input / Output

- **Input**: Edit BASIC code in a Windows editor
  - Edit it as a text file
  - CRLF line endings, ASCII codes
  - Passed to the emulator executable as an argument and loaded

- **Output**: Text screen (40x24)
  - Standard Apple II Plus text mode
  - ASCII codes 35-126 (96-character limit)
  - Characters outside the output range are replaced with other characters

### Operating Modes

- **Batch mode**: -> Implemented
  - Loads a BASIC program from a file and runs it
  - Script-style usage

- **Interactive mode (REPL)**: -> Not implemented
  - Interactive operation from the keyboard
  - A point for future modification (contributions welcome)

### Technical Specifications

- **CPU**: MOS 6502 emulation (fake6502)
- **Memory**: 48KB RAM + 12KB ROM
- **Character set**: ASCII 35-126 (96 characters)
- **ROM initialization**: Auto-generated
- **Random SEED**: Set by writing 1 byte

### License

**GNU General Public License v2.0**

This project depends on fake6502 (GPL 2.0), so it is licensed under GPL 2.0.

See the `LICENSE` file for details.

------------------------------------------------------------
## 1. Build Instructions for the Apple II Plus Emulator

### Platform Support

- **Windows** (Visual Studio 2026): -> Development and verification complete
- **Linux/macOS**: Can be supported with minor changes (contributions welcome)

### Requirements

- **OS**: Windows 11
- **IDE**: Visual Studio 2026 or later
- **CMake**: 3.20 or later
- **C++**: A C++20-capable compiler
- **vcpkg** (optional): For dependency management (recommended)

```
# Build
cmake CMakeLists.txt
```

------------------------------------------------------------
## 2. Downloading the Source Code
### From GitHub

```bash
git clone https://github.com/YOUR_USERNAME/apple2-basic-emulator.git
cd apple2-basic-emulator
```

------------------------------------------------------------
## 3. Downloading the ROMs

### Details of ROM Generation
The historical background is summarized in "Apple II and BASIC Overview".
See `docs/Apple2Plus_ROM_Make_jp.md` for details.

### Intellectual Property

- The Apple II ROMs are protected property of Apple Computer, Inc.
- This emulator does not distribute ROM files
- Users obtain the generated data from genuine ROMs themselves

------------------------------------------------------------
## 4. Running the Sample BASIC Code

### BASIC Sample Program

#### codeTest.bas - 96-character set test

This program displays all 96 characters (ASCII 35-126)
supported by the Apple II Plus Monitor ROM.

#### **How to run**:

```
.\apple2-emulator.exe codeTest.bas
```
------------------------------------------------------------
## 5. Quick Manual for the Apple II Plus ROM BASIC

See `docs/APPLE2_BASIC_REFERENCE_jp.md` for details.


------------------------------------------------------------
## 6. dumpTool

Made for analyzing binary files and the like.
It is actually used in development.

### Usage
```
     dumpTool.exe -f <target file> [-b|-h|-d]

     -b : bit string  -> <target file name>_BYTE.txt
     -h : hex         -> <target file name>_HEX.txt
     -d : decimal     -> <target file name>_DEC.txt
     (none)       -> output all three of the above
```
### License

**MIT License**
