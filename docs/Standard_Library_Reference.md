# Aether Standard Libraries

Aether comes with several built-in libraries that extend the language's capabilities.

## sound Library

Functions for playing sounds and audio feedback:

- `play_notif` - Play a notification sound (two quick beeps)
- `play_success` - Play a success melody (ascending 4-note scale)
- `play_alert` - Play an alert sound (repeating low tones)
- `sonar_ping` - Play a sonar sound with random depth detection
- `custom_beep` - Play a custom beep (set `beep_freq` and `beep_dur` variables first)

## gui Library

Functions for creating graphical user interfaces:

- `create_window` - Create a window (set `title`, `width`, and `height` variables first)
- `show_window` - Display the window
- `hide_window` - Hide the window
- `create_button` - Create a button (set `btn_text` variable first)
- `button_click` - Handle button click event
- `create_label` - Create a label (set `lbl_text` variable first)
- `create_input` - Create an input field (set `placeholder` variable first)
- `create_menu` - Create a menu (set `menu_title` variable first)
- `show_message` - Show a message box (set `msg_text` variable first)

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

## dialogs Library

Windows interface functions:

- `show_message` - Show a message in a dialog box
- `get_screen_info` - Get and display screen resolution (uses `screen_width()` and `screen_height()`)

## file_io Library

File system operations:

- `create_log` - Create a log file named aether_log.txt with initialization message
- `delete_temp` - Delete temporary log files
- `stamp_time` - Add timestamp (milliseconds since boot) to log file

## internet Library

Network and internet functions:

- `ping_site` - Test internet connectivity by pinging Google
- `get_my_ip` - Get your public IP address
- `download_file` - Download content from a URL to download.tmp
- `open_url` - Open default web browser to Aether repository
- `check_site` - Test connectivity to GitHub

## system Library

Application control:

- `shutdown` - Close the application cleanly
- `exit_app` - Exit the application

## math Library

Mathematical functions:

- `say_hi` - Display a welcome message from the math library
- `calc_magic` - Show an example calculation (sets x to 42)
- `add_numbers` - Add two numbers (set `num1` and `num2` variables first)
- `multiply` - Multiply two numbers (set `num1` and `num2` variables first)

## arrays Library

Array and data structure operations:

- `init_array` - Initialize a 10-element array with random values (1-100)
- `calc_result` - Perform basic calculation (input + bias, default bias=5)
- `benchmark_ops` - Run performance test with 1000 square root operations