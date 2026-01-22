# Getting Started with Aether

Aether is a programming language that compiles to Windows executables. This guide will help you set up and run your first Aether program.

## Installation

1. Download `setup.exe` from the repository
2. Run it as Administrator (needed to install globally)
3. The installer will:
   - Place the `ae` compiler in `C:\Aether`
   - Add it to your system PATH
   - Install required tools (NASM assembler and GCC linker)

## Verify Installation

Open a new command prompt and type:

```bash
ae
```

You should see the Aether logo and version information.

## Your First Program

Create a file called `hello.ae` with this content:

```aether
say "Hello, World!"
```

Compile and run it:

```bash
ae hello.ae -r
```

This will create `hello.exe` and run it immediately.

## Variables and Data Types

Aether automatically handles different data types:

```aether
set name to "Aether User"    // String
set count to 42              // Integer
set pi to 3.14159            // Float
set active to true            // Boolean
```

## Control Structures

Use `if` statements for conditional logic:

```aether
if count > 10 {
    say "Count is greater than 10"
} else {
    say "Count is 10 or less"
}
```

Use loops to repeat actions:

```aether
repeat 3 times {
    say "This repeats 3 times"
}

for i from 1 to 5 {
    say i
}
```

## Functions

Create reusable code blocks:

```aether
task greet {
    say "Hello from a function!"
}

call greet
```

## Installing Libraries

Aether has a package manager for libraries:

```bash
ae install sound
```

Then use it in your code:

```aether
import "sound"
call play_success
```

## Customization

Many libraries allow customization by setting variables before calling functions:

```aether
import "sound"

set beep_freq to 880    // Set frequency to 880Hz
set beep_dur to 200     // Set duration to 200ms
call custom_beep        // Play the custom beep
```

## Next Steps

Check out `Aether_Docs.md` for complete language reference and `Standard_Library_Reference.md` for detailed library functions.