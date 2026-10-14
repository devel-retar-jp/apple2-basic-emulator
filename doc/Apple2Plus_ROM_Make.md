# Apple II and BASIC Overview

On the Apple II, the "type of BASIC" and the "model" are closely tied together.  
This section briefly sorts out the lineage of BASIC and the features of each model.

------------------------------------------------------------
## 1. Types of BASIC: There Are Three ROM Software Variants

### ■ Integer BASIC (1977)
- Built into the original Apple II
- Implemented by Steve Wozniak
- Integer arithmetic only, no floating point
- Rich set of graphics commands (PLOT, HLIN, VLIN)
- Fast (because it is integer-only)
- ROM size: 8KB

### ■ Applesoft BASIC (1978)
- Developed by Microsoft and supplied to Apple
- Supports floating point
- Slower than Integer BASIC but more versatile
- Standard BASIC from the Apple II Plus onward
- ROM size: 10KB (341-0011 to 0015)

### ■ AppleSoft BASIC II (Apple IIe / IIc)
- Improved version of Applesoft BASIC
- Bug fixes, better keyboard/peripheral support
- Model-specific extensions (80 columns, additional commands)

------------------------------------------------------------
## 2. Apple II Family Models and Hardware

### ■ Apple II (1977)
- Integer BASIC built in
- 48KB RAM (maximum)
- Can connect directly to a color TV
- Expandable via slots
- The first personal computer

### ■ Apple II Plus (1979)
- Applesoft BASIC built into ROM
- Autostart Monitor included (341-0020)
- Total ROM: 12KB (BASIC 10KB + Monitor 2KB)
- Automatically enters BASIC at startup
- The era when Microsoft BASIC became the standard OS

### ■ Apple IIe (1983)
- 80-column display support
- Memory expansion and bank switching (up to 128KB)
- Write a value to $C08B -> Bank A (page 1) becomes visible
- Write a value to $C08C -> Bank B (page 2) becomes visible
- Applesoft BASIC II
- Improved keyboard, better peripheral support
- Matured as a "practical machine"

### ■ Apple IIc (1984)
- Made compact (no slots)
- Built-in peripherals (floppy, serial)
- Applesoft BASIC II
- Portable-oriented
- The "finished form" of the Apple II

### ■ Apple IIgs (1986)
- 16-bit CPU (65816)
- GUI support
- Maintains compatibility with the II series
- Enhanced sound (Ensoniq)
- The final layer of Apple II civilization (a bridge to the 16-bit era)

------------------------------------------------------------
## 3. BASIC vs. Model Table

| Model         | BASIC type             | ROM structure                 |
|---------------|------------------------|-------------------------------|
| Apple II      | Integer BASIC          | 8KB                           |
| Apple II Plus | Applesoft BASIC        | BASIC 10KB + Monitor 2KB      |
| Apple IIe     | Applesoft BASIC II     | Model-specific extended ROM   |
| Apple IIc     | Applesoft BASIC II     | ROM for built-in peripherals  |
| Apple IIgs    | Applesoft-compatible + GS/OS | 16-bit extended ROM     |

------------------------------------------------------------
## 4. Where Apple II Plus ROM Generation Fits In

With the Apple II Plus, Microsoft BASIC was burned into ROM  
and became the OS of the Apple II.  
Microsoft BASIC is a program written by Bill Gates himself.

The ROMs are 2K each and carry Apple part numbers.  
Files containing copies of the ROMs are available online.  
When reproducing it in a modern PC emulator, it is easiest to handle  
if you copy them into contiguous memory addresses.

The Apple II apparently was somewhat short on features?
The Apple II Plus has extended features.
Later models tended to have their RAM area squeezed by hardware extensions.
For that reason, the Apple II Plus is easy to work with.

The Apple II Plus is a system of just 12K,
yet nearly 50 years ago people developed on it.

Required ROMs:
- Applesoft BASIC (the five chips 341-0011 to 0015) -> 10K total
- Autostart Monitor (341-0020) -> 2K

------------------------------------------------------------
## 5. Apple II Plus ROM Generation Notes

### Required ROM Files (2KB each)
At the time, ROMs were split into 2K-byte units when programmed.
Each ROM was given its own part number.
Upgrades were done by swapping ROMs,
in a cassette/cartridge style.

Obtain them from the following site:

https://mirrors.apple2.org.za/Apple%20II%20Documentation%20Project/Computers/Apple%20II/Apple%20II%20plus/ROM%20Images/

### Applesoft BASIC (10KB)
- 341-0011.bin
- 341-0012.bin
- 341-0013.bin
- 341-0014.bin
- 341-0015.bin

### Autostart Monitor (2KB)
- 341-0020.bin

### (Optional) Video ROM (2KB)
- 341-0036.bin  
* Not needed to start the emulator. It contains the display font.

------------------------------------------------------------
## 6. Combining the ROMs (Windows / copy /b)
They are easier to handle when concatenated by function.

### BASIC ROM (10KB, basic.bin)
copy /b 341-0011.bin + 341-0012.bin + 341-0013.bin + 341-0014.bin + 341-0015.bin basic.bin

### Monitor ROM (2KB, monitor.bin)
copy /b 341-0020.bin monitor.bin

### Video ROM (optional, 2KB, monitor.bin)
copy /b 341-0036.bin video.bin

------------------------------------------------------------
## 7. Generated Files
- basic.bin (10KB)
- monitor.bin (2KB)
- video.bin (2KB) * optional

Only basic.bin + monitor.bin (12KB) are required to boot the Apple II Plus.  
video.bin is not needed for this emulator.

------------------------------------------------------------
## 8. Notes for Publishing on GitHub
The ROMs are copyrighted works, so do not include them in the repository.
They are merely tolerated thanks to Apple's goodwill.
Thank you!

### fake6502
This is the CPU emulator for the Apple II Plus.
Attach Apple's ROMs, memory, a program counter, and I/O to the CPU
and it becomes an Apple II Plus emulator.
It is like assembling a PC yourself.

It is published under GPL 2.0.

Download source for the 6502 emulator:

https://github.com/omarandlorraine/fake6502

### What May Be Included
- The emulator itself
- fake6502

### What Must Not Be Included
- basic.bin
- monitor.bin
- video.bin
- 341-00xx.bin (original ROMs)

------------------------------------------------------------

# Apple II Plus Memory Map
The memory layout of the Apple II Plus is the "bare structure"
from before modern operating systems existed.
The 6502 CPU's address space is 64KB ($0000-$FFFF).
RAM / I/O / ROM are mapped directly,
and you read and write raw addresses instead of using an API.

------------------------------------------------------------
## 1. Apple II Plus: Overall Layout (64KB)
Apple II Plus address space: 64KB ($0000-$FFFF)

The usable memory is effectively 48KB.
- $C000-$C0FF is I/O (not usable)
- $D000-$FFFF is ROM (read-only)

Range           Contents
------------------------------------------------------------
- $0000-$00FF     Zero page (fast area)
- $0100-$01FF     Stack
- $0200-$03FF     Text buffer / work area
- $0400-$07FF     Text screen (40x24)
- $0800-$1FFF     RAM (program area)
- $2000-$3FFF     Expansion RAM (card-dependent)
- $4000-$7FFF     Expansion RAM (card-dependent)
- $8000-$BFFF     Expansion ROM (card-dependent)
- $C000-$C0FF     I/O area
- $C100-$CFFF     Slot ROM (Slots 1-7)
- $D000-$FFFF     Main ROM (BASIC + Monitor)

------------------------------------------------------------
## 2. Apple II Plus: Details of Key Areas

■ $0000-$00FF: Zero page  
The 6502's fast area. Fastest because it can be accessed with 1-byte instructions.  
Uses: pointers, variables, indirect addressing, BASIC internal work area.

■ $0100-$01FF: Stack  
The 6502's hardware stack area.

■ $0400-$07FF: Text screen (40x24)  
The screen buffer lives in RAM.  
$0400 is the top left. Writing ASCII here displays it on screen.

■ $C000-$C0FF: I/O area  
Control registers for the keyboard, speaker, graphics modes, and so on.

Examples:
- $C000: Keyboard input
- $C010: Strobe clear
- $C030: Speaker click
- $C050: Text mode
- $C057: Graphics mode

■ $C100-$CFFF: Slot ROM  
ROMs on expansion cards such as Disk II and serial cards.

■ $D000-$FFFF: Main ROM (Apple II Plus)  
$D000-$F7FF: Applesoft BASIC  
$F800-$FFFF: Autostart Monitor  
12KB in total.

------------------------------------------------------------
## 3. Apple II Plus ROM Layout

ROM file         Size     Mapped range
------------------------------------------------------------
- 341-0011.bin      2KB      $D000-$D7FF
- 341-0012.bin      2KB      $D800-$DFFF
- 341-0013.bin      2KB      $E000-$E7FF
- 341-0014.bin      2KB      $E800-$EFFF
- 341-0015.bin      2KB      $F000-$F7FF
- 341-0020.bin      2KB      $F800-$FFFF

------------------------------------------------------------
## 4. Key Points for the Emulator Implementation

● CPU (fake6502)
- Implement the memory read/write functions yourself
- Special handling for the I/O area
- The ROM area is read-only

● Screen rendering
- Render $0400-$07FF as the text screen

● Keyboard
- Return the key code at $C000
- Reading $C010 clears the strobe

● Monitor startup
- Starts when the reset vector at $FFFC/$FFFD is loaded into the PC
- Loads and runs a program from memory at a specific address

● Addresses in unused areas can be used freely

● Since it is an emulator, you can read and write anywhere, including ROM

● There is no memory protection like in modern operating systems

------------------------------------------------------------
## 5. Summary

The Apple II memory map is the "bare structure" from before the abstractions of modern operating systems.  
The screen is written directly to RAM, I/O is wired straight to addresses, ROM is mapped as is, and the CPU sees the full 64KB directly.  
It is a primitive structure, but it is full of the charm of being able to play with how a computer works however you like.
You can experience a PC from half a century ago.