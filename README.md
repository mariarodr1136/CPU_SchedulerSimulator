# CPU Scheduler Simulator

## Overview

This project is a CPU scheduler simulator that implements five classic scheduling algorithms. It offers a command-line interface for comparing the performance of different scheduling strategies with user-defined process sets.

## Features

The simulator implements the following scheduling algorithms:

- **First-Come, First-Served (FCFS)**: Processes are executed in order of arrival
- **Shortest Job First (SJF)**: Non-preemptive algorithm that selects the process with the shortest burst time
- **Shortest Remaining Time (SRT)**: Preemptive version of SJF that can interrupt running processes
- **Round Robin (RR)**: Time-sliced approach where each process gets a fixed time quantum
- **Priority Scheduling**: Non-preemptive algorithm that schedules based on priority values

For each scheduling algorithm, the simulator calculates and displays:
- Individual waiting time for each process
- Individual turnaround time for each process
- Average waiting time across all processes
- Average turnaround time across all processes

## Getting Started

### Prerequisites

- C compiler (GCC recommended)
- Make utility

### Installation

1. Clone this repository:
   ```
   git clone https://github.com/yourusername/cpu-scheduler-simulator.git
   cd cpu-scheduler-simulator
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

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- This project was inspired by operating systems concepts and scheduler implementations
- Thanks to all contributors who have helped improve this simulator
