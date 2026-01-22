# Aether Standard Libraries

Aether comes with several built-in libraries that extend the language's capabilities.

## sound Library

Functions for playing sounds and audio feedback:

- `play_notif` - Play a notification sound (two quick beeps)
- `play_success` - Play a success melody (ascending 4-note scale)
- `play_alert` - Play an alert sound (repeating low tones)
- `sonar_ping` - Play a sonar sound with random depth detection
- `custom_beep` - Play a custom beep (set `beep_freq` and `beep_dur` variables first)

## utility Library

General system utilities:

- `clear_screen` - Clear the console screen
- `pause_system` - Pause execution until a key is pressed
- `list_files` - Show files in current directory
- `show_system_info` - Display OS name and version
- `check_disk` - Show disk space information
- `list_processes` - Show currently running processes
- `show_current_dir` - Display current directory path
- `create_file` - Create a new empty text file named new_file.txt
- `show_date` - Display current date
- `show_time` - Display current time

## win_ui Library

Windows interface functions:

- `show_welcome` - Show a welcome message in a dialog box
- `check_display` - Get and display screen resolution (uses `screen_width()` and `screen_height()`)

## file_io Library

File system operations:

- `create_log` - Create a log file named aether_log.txt with initialization message
- `delete_temp` - Delete temporary log files
- `stamp_time` - Add timestamp (milliseconds since boot) to log file

## web_client Library

Internet and network functions:

- `ping_google` - Test internet connectivity by pinging Google
- `get_ip` - Get your public IP address
- `download_data` - Download content from a URL to download.tmp
- `open_browser` - Open default web browser to Aether repository
- `check_website` - Test connectivity to GitHub

## app_core Library

Application control:

- `shutdown` - Close the application cleanly
- `wait_and_exit` - Show exit dialog and then close application

## math_pro Library

Mathematical functions:

- `say_hi` - Display a welcome message from the math library
- `calc_magic` - Show an example calculation (sets x to 42)
- `add_numbers` - Add two numbers (set `num1` and `num2` variables first)
- `multiply` - Multiply two numbers (set `num1` and `num2` variables first)

## neural_core Library

Array and mathematical operations:

- `init_weights` - Initialize a 10-element array with random values (1-100)
- `calc_activation` - Perform basic calculation (input + bias, default bias=5)
- `benchmark_neural` - Run performance test with 1000 square root operations