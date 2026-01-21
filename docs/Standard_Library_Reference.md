# 📚 Aether Standard Library Reference
**Core libraries included with Aether v1.0 (Universal Edition)**

The following libraries are included with every Aether installation. You can use them by adding `import "library_name"` at the top of your script.

---

## 1. `math_pro`
Standard mathematical utilities.
- `pi`: Returns a high-precision constant for PI.
- `square(n)`: Returns $n^2$.

## 2. `neural_core`
The foundation for building Aether AI agents.
- `say_neural`: Prints the Aether Neural identity.
- `init_weights(n)`: Initializes a memory array for weights.
- `calc_activation(val)`: Functional placeholder for activation logic.
- `benchmark_neural`: Runs a high-speed logic loop to test CPU performance.

## 3. `win_ui`
Native Windows Interaction.
- `alert(msg)`: Shows a standard Windows message box.
- `show_display_info`: Prints the user's screen resolution.

## 4. `app_core`
Application lifecycle and lifecycle control.
- `exit`: Standard process termination.
- `shutdown`: Application closure sequence.

## 5. `file_io`
Native Filesystem Automation.
- `create_log`: Generates a standard `aether_log.txt`.
- `delete_temp`: Safely removes temporary log files using native `execute`.
- `stamp_time`: Appends current system time to a log file.

## 6. `web_client`
Integration with the web and external networks.
- `ping_google`: Rapid network connectivity test.
- `get_ip`: Fetches the system's public IP using `curl`.
- `download_data`: Downloads remote assets to the local directory.

## 7. `utility`
General-purpose system management.
- `clear_screen`: Wipes the console for clean output.
- `pause_system`: Halts execution until a key is pressed.
- `list_files`: Shows all files in the current working directory.
- `show_system_info`: Displays OS and Version details.
- `check_disk`: Reports available storage on logical disks.
- `list_processes`: Displays current running processes.

## 8. `sound`
Advanced hardware audio control.
- `play_notif`: A high-pitched double-beep notification.
- `play_success`: A 4-step harmonic ascending scale.
- `play_alert`: A repeating low-frequency alarm.
- `sonar_ping`: A unique sonar-style pulse with a random depth indicator.
