# Aether Standard Libraries

Aether comes with several built-in libraries that extend the language's capabilities.

## sound Library

Functions for playing sounds and audio feedback:

- `play_success` - Play a success melody
- `play_notif` - Play a notification sound
- `play_alert` - Play an alert sound
- `sonar_ping` - Play a sonar sound
- `custom_beep` - Play a custom beep (set `beep_freq` and `beep_dur` first)

## utility Library

General system utilities:

- `pause_system` - Wait for user to press a key
- `clear_screen` - Clear the console
- `list_files` - Show files in current directory
- `show_system_info` - Display system information
- `check_disk` - Show disk space
- `list_processes` - Show running processes
- `show_current_dir` - Show current directory
- `create_file` - Create a new file
- `show_date` - Show current date
- `show_time` - Show current time

## win_ui Library

Windows interface functions:

- `alert(message)` - Show a message box
- `screen_width` - Get screen width in pixels
- `screen_height` - Get screen height in pixels

## file_io Library

File system operations:

- `create_log` - Create a log file
- `delete_temp` - Delete temporary files
- `stamp_time` - Add timestamp to log

## web_client Library

Internet and network functions:

- `ping_google` - Test internet connection
- `get_ip` - Get your public IP address
- `download_data` - Download files
- `open_browser` - Open default web browser
- `check_website` - Test website connectivity

## app_core Library

Application control:

- `exit` - Exit the program
- `shutdown` - Shut down the application

## math_pro Library

Mathematical functions:

- `say_hi` - Say hello from math library
- `calc_magic` - Example calculation
- `add_numbers` - Add two numbers
- `multiply` - Multiply two numbers