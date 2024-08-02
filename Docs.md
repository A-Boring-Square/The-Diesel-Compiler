# Diesel Language Documentation

Diesel is a language that transpiles to C, aiming for efficiency, portability, and providing developers with a pleasant experience.


## Comments

In Diesel, comments are multiline and start with `#[` and end with `]#`.

```diesel
#[ Hi I am a comment ]#
```

## I/O
In Diesel I/O is managed by two built in functions
### Output
Output is managed by the `Out()` function and it takes one input witch is eaudher a `char` or a `str`
### Input
Input is managed by the`Input()` function and it takes one input witch is the prompt and returns a `str` of the users input

## Variables

Variables in Diesel are straightforward.

### Constant Variables

Constants in Diesel are declared using the `const` keyword followed by the variable name, a colon, the variable type, and the assigned value.

```diesel
const MyConstant: uint8 = 42;
```

### Reassignable Variables

Reassignable variables in Diesel are declared using the `var` keyword followed by the variable name, a colon, the variable type, and the assigned value.

```diesel
var MyVar: uint = 50;
```

## Types

Diesel supports several fundamental types: `int`, `float`, `char`, `str`, and `bool`.

### Integers

Integers in Diesel can be either signed or unsigned and are available in various bit sizes: 4-bit, 8-bit, 16-bit, 32-bit, and 64-bit, storing whole numbers.

```diesel
const FourBitInt: int4 = 15;
const EightBitUnsignedInt: uint8 = 255;
const SixtyFourBitSignedInt: int64 = -9223372036854775808;
```

### Floats

Floats in Diesel can be either signed or unsigned and are available in two bit sizes: 32-bit, and 64-bit, storing decimals.

```diesel
const SixtyFourBitSignedFloat: float64 = -60.7;
```

### Chars

Chars in Diesel store a single character of text.

```diesel
const MyChar: char = "H";
```

### Strs

Strs in Diesel store multiple characters together in one place.

```diesel
const MyString: str = "Hi i am a string";
```

### Bools

Bools in Diesel store only two values: `true` or `false`.

```diesel
const MyBool: bool = true;
```

### Inherit

`inherit` is a special type in Diesel that makes assigning a new variable to an already existing variable much easier to read and safer.

#### How it Works

Instead of having to set the correct type, you can use `inherit` to have the compiler automatically set the type to the type of the variable you are assigning it to.

```diesel
var Text: string = "Hi";
var NewVar: inherit = Text;
```

## Functions

### Declareation
Functions are declared useing the `func` keyword and look like this
#### This is not valid Diesel code but the structure is corect
```
func FuncName(FuncArg: type): ReturnType {
  #[ Code that runs when the func is called ]#
  return Value
}
```
### Function Modifiers
Function modifiers are a new featcher unieke to Diesel
#### Entry
This Function Modifire is spicle because you can only use it once because is signifyes that that func is the entry point of the program

## Lists

Lists in Diesel start at 0 and aim to be as elegant as possible to work with.

### How to Make a List

To make a list, add `[]` at the end of the variable name. Use a number inside the `[]` to create a list with a fixed size.

```diesel
var MyDynamicList[]: uint8 = [15, 16, 7];
var MyStaticList[3]: uint8 = [30, 5, 7];
```

### How to Add Values to a List

Adding to a list is easy in Diesel. Use the built-in functions `AddToEnd()`, `AddToStart()`, and `Insert()`.

```diesel
var MyList[]: uint8 = [];
MyList.AddToEnd(5);
```

### How to Remove Values from a List

Removing from a list is also easy in Diesel. Use the built-in function `Remove()`.

```diesel
var MyList[]: uint8 = [15, 70, 5];
MyList.Remove(2);
```

## Memory

Diesel is a manual memory-managed language.

### Pointers

Pointers in Diesel use two built-in functions `Pointer()` and `Reference()` for readability and safety.

```diesel
var MyCoolVar: int64 = -5003;
var Ptr_MyCoolVar: inherit = Pointer(MyCoolVar);
```

### Allocate and Free

Use the built-in functions `Allocate()` and `Free()` to allocate and free memory, respectively.

```diesel
var SomeData: uint = 5;
Allocate(SomeData);
#[ do something with the data ]#
Free(SomeData);
```

## Naming Convention

In Diesel, we follow the PascalCase convention for naming identifiers.

### File Names

When naming files in Diesel, use PascalCase for clarity and consistency.

### Functions

Function names in Diesel also follow the PascalCase convention.

## Loops and Control Flow

### Loops

#### While

The `while` loop in Diesel allows you to repeatedly execute a block of code as long as a specified condition is true.

```diesel
var Counter: uint8 = 0;
while (counter < 5) {
  #[ Do something here ]#
  counter += 1;
}
```

#### For
```diesel
var Iterator[]: uint8 = [5, 6, 7, 8];
for (Iter in Iterator) {
  Output(Iter);
}
```

### Control Flow

#### If

```diesel
var Number: int8 = 10;
if (Number > 0) {    
  #[ do something if the condition is true ]# 
} else {
  #[ do something if the condition is false ]# 
}
```

#### Elif

```diesel
var Temperature: int8 = 25;
if (Temperature > 30) {
  #[ do something for high temperature ]#
} elif(Temperature > 20) {
  #[ do something for moderate temperature ]# 
} else {
  #[ do something for low temperature ]# 
}
```

## Technical Information

### The Error Checker

The Error Checker in Diesel has four stages and provides suggestions and best practices.

#### Stage 1

During Stage 1, the Error Checker logs simple mistakes such as unmatched brackets, parentheses, and curly brackets.

#### Stage 2

During Stage 2, the Error Checker checks for syntax errors and provides hints on how to fix common errors and suggests safer practices.

#### Stage 3

During Stage 3, the Error Checker logs type errors using the cached AST.

#### Stage 4

During Stage 4, the Error Checker checks memory usage for correct allocation and freeing, and ensures pointer safety.
