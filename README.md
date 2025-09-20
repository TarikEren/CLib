# CLib

Implementations of various data structures, algorithms and more in C. The functions are documented in the header files in detail.

## Logger
* A logger which logs messages onto the console screen. and each log level is coloured using an ANSI escape sequence. 
* It supports 3 levels:
  * Error (Coloured in red),
  * Warning (Coloured in yellow),
  * Info (Coloured in cyan as blue was a bit too dark for my taste)
* The logger also prepends the current timestamp on the message.
  * Detects the platform and using the current platform's libraries, gets the current timestamp.

## Stack
* Basic stack implementation which consists of:
  * creation,
  * pushing,
  * popping,
  * peeking,
  * checking if the stack is empty,
  * checking if the stack is full,
  * deleting the stack, (Note: Assumes that the elements in the stack is heap allocated)
  * dumping the stack to the console.

## Arena
* An arena allocator implementation
* It aligns the size of the given data chunk to `8`, `16` or `64` bits and allocates the aligned chunk to the arena.
* It supports:
  * creation
  * allocation
  * flushing (Sets the offset of the arena to 0)
  * destroying (De-allocates the entire arena at once)

## String
* An arena allocated string and related memory operations implementation
* It supports:
  * memory copying,
  * memory setting,
  * memory moving,
  * string creating,
  * string deleting,
  * string tokenising,
  * string getting sub-strings,
  * string appending,
  * string comparing,
  * string copying,
  * string conversion to upper and lower cases
