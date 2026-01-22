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

You can also assign directly to variables without `set` and `to`:

```aether
count to 10
name to "Jane"
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

Functions can accept parameters by setting global variables before calling:

```aether
task greet_person {
    if name {
        say "Hello, "
        say name
    } else {
        say "Hello, stranger!"
    }
}

set name to "Alice"
call greet_person
```

### Arrays

Create and use arrays:

```aether
array scores from 5  // Creates array with 5 elements
scores[0] to 85      // Set first element
scores[1] to 92      // Set second element

set first_score to scores[0]  // Read from array
```

## Built-in Functions

Aether has several built-in functions:

- `say(value)` - Print to console
- `beep(freq, duration)` - Play a sound (frequency in Hz, duration in ms)
- `alert(message)` - Show a message box
- `screen_width()` - Get screen width in pixels
- `screen_height()` - Get screen height in pixels
- `execute(command)` - Run a system command
- `write data to file` - Write to a file
- `append data to file` - Add to end of file
- `exit` - Stop the program
- `sqrt(value)` - Calculate square root
- `exp(value)` - Calculate exponent
- `random(min, max)` - Generate random integer between min and max
- `time` - Get current time in milliseconds since system boot

## Mathematical Operations

Aether supports basic arithmetic:

```aether
set sum to 5 + 3
set difference to 10 - 4
set product to 6 * 7
set quotient to 20 / 4
```

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

## Customization Options

### Custom Beeps

The sound library allows custom beeps by setting variables:

```aether
import "sound"

set beep_freq to 660    // Frequency in Hz
set beep_dur to 300     // Duration in milliseconds
call custom_beep
```

### Custom Calculations

The math library allows custom calculations by setting variables:

```aether
import "math_pro"

set num1 to 15
set num2 to 25
call add_numbers
```

### Array Operations

Use the neural_core library for advanced array operations:

```aether
import "neural_core"

call init_weights  // Creates a 10-element array called 'weights'
```

## Advanced Features

### Conditional Logic with Multiple Conditions

```aether
if age is 18 and status is "active" {
    say "Valid user"
}
```

### Nested Blocks

You can nest code blocks inside each other:

```aether
if logged_in {
    if admin {
        say "Admin panel"
    } else {
        say "User panel"
    }
}
```

## Common Libraries

Common libraries include:
- `sound` - Audio functions
- `utility` - System utilities
- `web_client` - Internet functions
- `file_io` - Advanced file operations
- `win_ui` - Windows interface functions
- `math_pro` - Mathematical functions
- `neural_core` - Array and matrix operations
- `app_core` - Application lifecycle