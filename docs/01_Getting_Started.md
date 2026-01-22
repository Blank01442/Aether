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

## Next Steps

Check out `Aether_Docs.md` for complete language reference.