# Applesoft BASIC Command Reference

A list of commands for the Applesoft BASIC built into the Apple II Plus.
It covers the main commands that can be run on this emulator.

------------------------------------------------------------
## 1. Screen Control

### HOME
```
Syntax: HOME
Description: Clears the screen and moves the cursor to the top left
Example: HOME
```

### CLEAR
```
Syntax: CLEAR
Description: Clears memory and resets variables
Example: CLEAR
```

### PRINT (or ?)
```
Syntax: PRINT expr1, expr2, ... or PRINT "string"
Description: Outputs text to the screen (separating multiple expressions with commas aligns them in columns)
Example: PRINT "HELLO WORLD"
Example: PRINT "X="; X; "Y="; Y
Example: ? 10 + 20
```

### PRINT TAB
```
Syntax: PRINT TAB(n) "string"
Description: Outputs the string starting at column n
Example: PRINT TAB(10) "RIGHT"
```

### INPUT
```
Syntax: INPUT variable or INPUT "message"; variable
Description: Accepts user input from the keyboard
Example: INPUT X
Example: INPUT "Enter your age:"; AGE
```

------------------------------------------------------------
## 2. Variables and Arrays

### LET (or direct assignment)
```
Syntax: LET variable = expr or variable = expr
Description: Assigns a value to a variable
Example: LET X = 10
Example: Y = X + 5
```

### DIM
```
Syntax: DIM array(size), array2(size)
Description: Declares an array and allocates memory
Example: DIM A(100)
Example: DIM X(50), Y(50)
```

------------------------------------------------------------
## 3. Control Flow

### IF-THEN
```
Syntax: IF condition THEN statement or IF condition THEN line-number
Description: If the condition is true, runs the following statement
Example: IF X > 10 THEN PRINT "BIG"
Example: IF X = 0 THEN 100
```

### IF-THEN-ELSE (Applesoft extension)
```
Syntax: IF condition THEN statement : ELSE statement
Description: Conditional branch (handles both the true and false cases)
Example: IF X > 0 THEN PRINT "POSITIVE" : ELSE PRINT "NOT POSITIVE"
```

### FOR-NEXT
```
Syntax: FOR variable = start TO end [STEP step]
      ...
      NEXT variable
Description: Loop. Repeats while changing the variable from the start value to the end value
Example: FOR I = 1 TO 10
      PRINT I
    NEXT I
Example: FOR J = 10 TO 1 STEP -1
      PRINT J
    NEXT J
```

### GOTO
```
Syntax: GOTO line-number
Description: Jumps to the specified line number
Example: GOTO 100
```

### GOSUB-RETURN
```
Syntax: GOSUB line-number
      ...
      RETURN
Description: Calls a subroutine and returns with RETURN
Example: 100 GOSUB 500
    200 END
    500 PRINT "SUBROUTINE"
    510 RETURN
```

### END
```
Syntax: END
Description: Ends the program
Example: END
```

------------------------------------------------------------
## 4. Numeric Calculation and Functions

### Basic Operators
```
+ : Addition
- : Subtraction
* : Multiplication
/ : Division
^ : Exponentiation
MOD : Remainder
```

### ABS
```
Syntax: ABS(expr)
Description: Returns the absolute value
Example: X = ABS(-10)  -> X = 10
```

### INT
```
Syntax: INT(expr)
Description: Returns the integer part
Example: X = INT(3.7)  -> X = 3
```

### SQR
```
Syntax: SQR(expr)
Description: Returns the square root
Example: X = SQR(16)  -> X = 4
```

### RND
```
Syntax: RND(expr) or RND
Description: Returns a random number (between 0 and 1)
Example: X = RND(1)
```

### SIN, COS, TAN
```
Syntax: SIN(angle), COS(angle), TAN(angle)
Description: Trigonometric functions (in radians)
Example: X = SIN(0)  -> X = 0
```

### LOG, EXP
```
Syntax: LOG(expr), EXP(expr)
Description: Natural logarithm, exponential function
Example: X = LOG(10)
Example: Y = EXP(1)
```

------------------------------------------------------------
## 5. String Handling

### LEN
```
Syntax: LEN(string)
Description: Returns the length of the string
Example: X = LEN("HELLO")  -> X = 5
```

### MID$
```
Syntax: MID$(string, start, length)
Description: Extracts part of a string
Example: X$ = MID$("HELLO", 2, 3)  -> X$ = "ELL"
```

### LEFT$
```
Syntax: LEFT$(string, length)
Description: Extracts the specified number of characters from the left of the string
Example: X$ = LEFT$("HELLO", 3)  -> X$ = "HEL"
```

### RIGHT$
```
Syntax: RIGHT$(string, length)
Description: Extracts the specified number of characters from the right of the string
Example: X$ = RIGHT$("HELLO", 2)  -> X$ = "LO"
```

### STR$
```
Syntax: STR$(number)
Description: Converts a number to a string
Example: X$ = STR$(123)  -> X$ = "123"
```

### VAL
```
Syntax: VAL(string)
Description: Converts a string to a number
Example: X = VAL("123")  -> X = 123
```

### CHR$
```
Syntax: CHR$(ASCII code)
Description: Returns the character for the ASCII code
Example: X$ = CHR$(65)  -> X$ = "A"
```

### ASC
```
Syntax: ASC(string)
Description: Returns the ASCII code of the first character of the string
Example: X = ASC("A")  -> X = 65
```

------------------------------------------------------------
## 6. Memory Access

### PEEK
```
Syntax: PEEK(address)
Description: Reads the value at the specified memory address
Example: X = PEEK(1024)  -> reads the start of the text screen
Example: X = PEEK(49152)  -> reads graphics memory
```

### POKE
```
Syntax: POKE address, value
Description: Writes a value to the specified memory address
Example: POKE 1024, 65  -> draws "A" on the text screen
```

### CALL
```
Syntax: CALL address
Description: Executes the machine code at the specified memory address
Example: CALL 768
```

------------------------------------------------------------
## 7. I/O and Keyboard

### GET
```
Syntax: GET variable
Description: Inputs one character from the keyboard and gets its ASCII code
Example: GET K
    IF K = 65 THEN PRINT "YOU PRESSED A"
```

------------------------------------------------------------
## 8. Graphics (for Text Mode)

### HTAB / VTAB
```
Syntax: HTAB column
      VTAB row
Description: Moves the cursor to the specified position (text mode)
Example: HTAB 10
    VTAB 5
    PRINT "HERE"
```

### COLOR
```
Syntax: COLOR = color-number
Description: Sets the text color (for graphics mode)
Example: COLOR = 1
```

### PLOT
```
Syntax: PLOT column, row
Description: Draws a point in graphics mode
Example: PLOT 100, 50
```

### HLIN / VLIN
```
Syntax: HLIN column1, column2 AT row
      VLIN row1, row2 AT column
Description: Draws a horizontal / vertical line in graphics mode
Example: HLIN 0, 39 AT 10
Example: VLIN 0, 20 AT 15
```

------------------------------------------------------------
## 9. Other Commands

### REM
```
Syntax: REM comment or ' comment
Description: Comment line (not executed)
Example: REM THIS IS A COMMENT
Example: ' This is also a comment
```

### RANDOMIZE
```
Syntax: RANDOMIZE
Description: Initializes the random seed
Example: RANDOMIZE
```

### SPEED
```
Syntax: SPEED = value
Description: Sets the screen output speed (0 to 255)
Example: SPEED = 100
```

------------------------------------------------------------
## 10. Comparison and Logical Operators

### Comparison Operators
```
=   : Equal to
<   : Less than
>   : Greater than
<=  : Less than or equal to
>=  : Greater than or equal to
<>  : Not equal to
```

### Logical Operators
```
AND : Logical AND
OR  : Logical OR
NOT : Negation
```

Examples:
```
IF X > 5 AND Y < 10 THEN PRINT "OK"
IF X = 0 OR X = 10 THEN PRINT "BOUNDARY"
IF NOT (X = 0) THEN PRINT "NOT ZERO"
```

------------------------------------------------------------
## 11. Notes

### Memory Addresses
- $0400-$07FF: Text screen buffer
- $C000: Keyboard input
- $C030: Speaker click

### Floating-Point Arithmetic
Applesoft BASIC fully supports floating point,
whereas Integer BASIC (original Apple II) supports integers only.

------------------------------------------------------------
## 12. References

- Apple II Technical Reference Manual
- Applesoft BASIC Programming Reference
- Apple II Documentation Project: 
- https://mirrors.apple2.org.za/

