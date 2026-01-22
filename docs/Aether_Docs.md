# Aether Language Guide

Aether is a simple programming language that compiles to Windows executables. It's designed to be easy to learn but powerful enough for real applications.

## Basic Syntax

### Variables

Variables are declared with `set` and don't need types:

```aether
set count to 10
set name to "John"
set active to true
set price to 19.99
```

### Output

Print text to the console:

```aether
say "Hello, world!"
say count
```

### Control Flow

Conditional statements:

```aether
if age is 18 {
    say "Adult"
} else {
    say "Minor"
}
```

You can also use other comparison operators:
- `is` for equality (==)
- `>` for greater than
- `<` for less than
- `!=` for not equal

Loops:

```aether
// Repeat a fixed number of times
repeat 5 times {
    say "Counting..."
}

// Count from one number to another
for i from 1 to 10 {
    say i
}

// While condition is true
while running {
    say "Still running..."
}
```

### Functions

Define and call functions:

```aether
task greet {
    say "Hello!"
}

call greet
```

## Built-in Functions

Aether has several built-in functions:

- `say(value)` - Print to console
- `beep(freq, duration)` - Play a sound
- `alert(message)` - Show a message box
- `screen_width()` - Get screen width in pixels
- `screen_height()` - Get screen height in pixels
- `execute(command)` - Run a system command
- `write data to file` - Write to a file
- `append data to file` - Add to end of file
- `exit` - Stop the program

## File Operations

Create or overwrite a file:

```aether
write "Hello" to "myfile.txt"
```

Add to the end of a file:

```aether
append "More text" to "myfile.txt"
```

## Working with Libraries

Import libraries at the top of your file:

```aether
import "sound"
import "utility"

call play_success
call pause_system
```

Common libraries include:
- `sound` - Audio functions
- `utility` - System utilities
- `web_client` - Internet functions
- `file_io` - Advanced file operations
- `win_ui` - Windows interface functions