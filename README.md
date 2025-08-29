# Philosopher

A C implementation of the classic Dining Philosophers problem using POSIX threads (pthreads). This project demonstrates thread synchronization, deadlock avoidance, and resource sharing in concurrent programming. It is designed for educational purposes and to showcase best practices in concurrent programming in C.

## Features
- Multi-threaded simulation of philosophers eating, thinking, and sleeping
- Mutex-based protection for shared resources (forks, meal times, printing)
- Accurate timing and monitoring of philosopher states
- Configurable number of philosophers and meal repetitions
- Graceful termination on death or completion
- Deadlock avoidance by careful fork acquisition order
- Thread-safe output using dedicated mutex
- Modular code structure for easy understanding and extension

## Getting Started

### Prerequisites
- GCC (or any C compiler supporting pthreads)
- Make
- Linux or Unix-like environment
- Basic knowledge of C and POSIX threads is helpful

### Build
Clone the repository and build the project:
```sh
git clone https://github.com/M-elhouary/Philosopher.git
cd Philosopher/philo
make
```
- The executable `philo` will be created in the `philo` directory.

### Run
Usage:
```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
Example:
```sh
./philo 5 800 200 200 7
```
Arguments:
- `number_of_philosophers`: Number of philosophers (and forks)
- `time_to_die`: Time (ms) before a philosopher dies if not eating
- `time_to_eat`: Time (ms) a philosopher spends eating
- `time_to_sleep`: Time (ms) a philosopher spends sleeping
- `number_of_times_each_philosopher_must_eat` (optional): Simulation ends when all philosophers have eaten this many times

#### Argument Details
- All arguments must be positive integers.
- If the last argument is omitted, the simulation runs until a philosopher dies.
- Philosophers are numbered from 1 to N.

## File Structure
- `main_philo.c`: Entry point, argument parsing, thread creation
- `creat_thread.c`: Thread initialization and management
- `monitor.c`: Monitors philosopher states, detects death and completion
- `simulation.c`: Philosopher actions (eat, sleep, think)
- `parse_arg.c`: Argument validation and parsing
- `initial_data.c`: Data structure initialization
- `utils.c`: Utility functions (timing, printing, etc.)
- `philo_header.h`: Shared data structures and function prototypes
- `Makefile`: Build instructions

### Code Organization
- All source files are in the `philo/` directory.
- The project uses a modular approach: each file handles a specific aspect of the simulation.
- Synchronization primitives (mutexes) are used to protect shared data and avoid race conditions.

## How It Works
1. Each philosopher is represented by a thread.
2. Philosophers alternate between eating, sleeping, and thinking.
3. Eating requires locking two forks (mutexes).
4. The monitor thread checks for death (starvation) and completion.
5. Output is synchronized to avoid race conditions.

### Philosopher Lifecycle
- **Thinking:** Philosopher waits before attempting to eat.
- **Eating:** Philosopher locks both forks (mutexes), updates last meal time, and eats for the specified duration.
- **Sleeping:** Philosopher releases forks and sleeps for the specified duration.
- **Death Detection:** If a philosopher does not eat within `time_to_die`, the monitor thread prints a death message and ends the simulation.
- **Completion:** If all philosophers have eaten the required number of times, the simulation ends gracefully.

### Synchronization
- **Forks:** Each fork is a mutex. Philosophers must lock both forks before eating.
- **Meal Time:** Access to last meal time is protected by a mutex to avoid race conditions.
- **Printing:** Output is protected by a mutex to prevent garbled messages.
- **End Condition:** A shared flag, protected by a mutex, signals when the simulation should end.

## Example Output
```
0 1 is thinking
200 1 is eating
400 1 is sleeping
...etc...
800 2 died
```
- Each line shows the timestamp (ms since start), philosopher ID, and action.
- If a philosopher dies, the simulation stops and prints a death message.

## Tips & Troubleshooting
- Ensure all arguments are positive integers.
- Use more philosophers to observe deadlock avoidance.
- If the program exits immediately, check argument validity.
- For debugging, add print statements in `monitor.c` and `simulation.c`.
- If philosophers die too quickly, increase `time_to_die` or decrease `time_to_eat`/`time_to_sleep`.
- If output is missing or garbled, check mutex usage in printing functions.
- For custom scenarios, modify `simulation.c` to change philosopher behavior.
- Use `valgrind` to check for memory leaks: `valgrind ./philo ...`
- To understand thread flow, add debug prints in thread creation and monitor logic.

## License
MIT

## Author
M-elhouary

---

### Contributing
Pull requests and suggestions are welcome! For major changes, please open an issue first to discuss what you would like to change.

### Contact
For questions or feedback, contact [M-elhouary](mailto:mel-houa@student.1337.ma)
