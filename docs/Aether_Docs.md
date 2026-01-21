# 🌌 Aether Programming Language v2.7
**Ethereal Edition** - *The high-performance AI & Logic Language*

Aether is designed to be the easiest, most readable, and fastest language for human-AI collaboration. It compiles directly to x86-64 Assembly for blazing-fast execution.

---

## 💎 Core Syntax

### 1. Variables & Data Types
Aether is smart. It automatically detects if you are using an Integer, Float, or String.
```aether
set score to 100            // Integer
set learning_rate to 0.001  // Float (AI Ready)
set name to "Alpha-1"       // String
set running to true         // Boolean (v2.7)
```

### 2. Output
```aether
say "Hello World"
say score
```

### 3. Control Flow
**If/Else:**
```aether
if score > 50 {
    say "You win!"
} else {
    say "Keep trying!"
}
```

**Loops:**
```aether
// Classic While
while score < 110 {
    set score to score + 1
}

// Pro For-Loop (v2.7)
for i from 1 to 10 {
    say i
}

// Ultra Fast Repeat
repeat 5 times {
    say "Fast Loop!"
}
```

### 4. Tasks (Functions) - v2.7
Encapsulate your logic into clean "Tasks".
```aether
task greet {
    say "Welcome to Aether!"
}

call greet
```

---

## 🤖 AI Primitives

### Tensors (Arrays)
Create efficient memory buffers for your weights or data.
```aether
array weights from 1000  // Allocates high-speed memory
```

### Built-in Functions
- `random(min, max)`: High-quality integer randomness.
- `time`: Milli-second precision timer for benchmarks.

---

## 🛡️ Smart Pro Debugger
Aether v2.7 doesn't just crash. It tells you what happened and how to fix it.
**Example Error:**
```text
ISSUE at Line 5, Col 10: Found an unexpected word.
FOUND: "10"
PRO-TIP: Forgot 'to'? Like 'set x TO 10'
```

---

## 🛠️ Usage
1. Save your code as `logic.ae`.
2. Compile: `ae logic.ae`.
3. Run: `.\logic.exe`.
