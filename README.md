# CPU Scheduler Simulator ⏱️

This project is a **CPU scheduler simulator** that implements five classic scheduling algorithms. It provides a **command-line interface** for comparing the performance of different scheduling strategies using user-defined process sets. Users can easily simulate scheduling algorithms like **First-Come, First-Served (FCFS)**, **Shortest Job First (SJF)**, **Shortest Remaining Time (SRT)**, **Round Robin (RR)**, and **Priority Scheduling**. This simulator calculates and displays detailed performance metrics, such as **waiting times** and **turnaround times**, to help users understand and analyze the efficiency of each algorithm.

![C](https://img.shields.io/badge/C-Language-blue) ![GCC](https://img.shields.io/badge/GCC-Compiler-orange) ![Make](https://img.shields.io/badge/Make-Utility-red)

---

<p align="center">
  <img width="447" alt="Screenshot 2025-03-07 at 7 51 09 PM" src="https://github.com/user-attachments/assets/523890ec-ef47-4a22-a587-48c0fbac7e5a" />
</p>

---

## Technologies Used
- **C**: The programming language used to implement the project
- **GCC**: Compiler for building the project
- **Make**: Utility for automating the build process

## Features

The simulator implements the following scheduling algorithms:

- **First-Come, First-Served (FCFS)**: Processes are executed in order of arrival
- **Shortest Job First (SJF)**: Non-preemptive algorithm that selects the process with the shortest burst time
- **Shortest Remaining Time (SRT)**: Preemptive version of SJF that can interrupt running processes
- **Round Robin (RR)**: Time-sliced approach where each process gets a fixed time quantum
- **Priority Scheduling**: Non-preemptive algorithm that schedules based on priority values

For each scheduling algorithm, the simulator calculates and displays:
- Individual **waiting time** for each process
- Individual **turnaround time** for each process
- Average waiting time across all processes
- Average turnaround time across all processes

## Getting Started

### Prerequisites

- **C compiler** (GCC recommended)
- **Make utility**

### Installation

1. Clone this repository:
   ```
   git clone https://github.com/mariarodr1136/CPU_SchedulerSimulator.git
   cd CPU_SchedulerSimulator
   ```

2. Compile the project:
   ```
   cd CODE
   make
   ```

### Usage

1. Create an input file named `input.txt` with your process information in the following format:
   ```
   Process Scheduling Information
   ----------------------------------------------------------
   <PID> <Burst Time> <Priority> <Arrival Time>
   <PID> <Burst Time> <Priority> <Arrival Time>
   ...
   ----------------------------------------------------------
   ```

2. Run the simulator:
   ```
   ./ass3
   ```

3. Use the interactive menu to select different scheduling algorithms and compare their performance metrics.

4. To clean build files:
   ```
   make clean
   ```

## Interactive Menu Options

When you run the program, you'll see a menu with the following options:

```
                 CPU Scheduling Algorithms
|-----------------------------------------------------------|
|   1. First-Come, First-Served (FCFS)                      |
|   2. Shortest Job First (SJF) - Nonpreemptive             |
|   3. Shortest Remaining Time (SRT) - Preemptive           |
|   4. Round Robin (RR)                                     |
|   5. Priority Scheduling - Nonpreemptive                  |
|   0. Exit                                                 |
|-----------------------------------------------------------|
```

### Selecting Options

- **Press 1**: Executes the FCFS algorithm and displays waiting time, turnaround time for each process, plus average waiting time and turnaround time across all processes.

- **Press 2**: Executes the SJF Non-preemptive algorithm and displays performance statistics. This algorithm prioritizes the shortest job available when the CPU becomes free.

- **Press 3**: Executes the SRT Preemptive algorithm and displays performance statistics. This algorithm switches to a new process if a shorter process arrives.

- **Press 4**: Prompts you to enter a time quantum value, then executes the Round Robin algorithm with the specified quantum and displays performance statistics. Each process gets a fixed time slice before being moved to the back of the queue.

- **Press 5**: Executes the Priority Scheduling Non-preemptive algorithm and displays performance statistics. This algorithm selects processes based on priority values (lower number means higher priority).

- **Press 0**: Exits the program.

After each algorithm execution, the menu reappears so you can select another algorithm or exit.

## Example Input

```
Process Scheduling Information
----------------------------------------------------------
1 6 2 0
2 2 4 1
3 8 1 2
4 3 3 3
5 4 5 4
----------------------------------------------------------
```

## Sample Output

When you select an algorithm (e.g., pressing "1" for FCFS), you'll see output similar to:

```
***************************************************************************************

FCFS Statistics...

Process    Waiting Time     Turnaround Time
  P1           0                 6
  P2           5                 7
  P3           6                 14
  P4           13                16
  P5           15                19

Average Waiting Time: 7.80

Average Turnaround Time: 12.40

***************************************************************************************
```

## How It Works

The simulator reads process information from the input file, including:
- Process ID
- CPU burst time
- Process priority
- Arrival time

When a scheduling algorithm is selected:

1. **FCFS (Option 1)**: Processes are executed based on their arrival time, first to arrive gets served first.

2. **SJF (Option 2)**: The process with the shortest burst time among available processes is selected for execution and runs to completion.

3. **SRT (Option 3)**: Similar to SJF, but the currently running process can be preempted if a new process arrives with a shorter remaining time.

4. **Round Robin (Option 4)**: Each process gets a fixed time slice (quantum). If a process doesn't complete within its time slice, it's moved to the back of the queue.

5. **Priority Scheduling (Option 5)**: Processes are executed based on their priority values, with lower numbers having higher priority.

The interactive menu allows users to compare the efficiency of different algorithms using the same process set.

## Contributing 
Feel free to submit issues or pull requests for improvements or bug fixes. You can also open issues to discuss potential changes or enhancements. All contributions are welcome to enhance the app’s features or functionality!

To contribute, please follow these steps:

1. Fork the repository.
2. Create a new branch for your feature or bug fix:
   ```bash
   git checkout -b feat/your-feature-name
- Alternatively, for bug fixes:
   ```bash
   git checkout -b fix/your-bug-fix-name
3. Make your changes and run all tests before committing the changes and make sure all tests are passed.
4. After all tests are passed, commit your changes with descriptive messages:
   ```bash
   git commit -m 'add your commit message'
5. Push your changes to your forked repository:
   ```bash
   git push origin feat/your-feature-name.
6. Submit a pull request to the main repository, explaining your changes and providing any necessary details.

## Contact 🌐
If you have any questions or feedback, feel free to reach out at [mrodr.contact@gmail.com](mailto:mrodr.contact@gmail.com).

## Acknowledgments

- This project was inspired by operating systems concepts and scheduler implementations
- Thanks to all contributors who have helped improve this simulator
