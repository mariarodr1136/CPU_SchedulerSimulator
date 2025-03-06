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
   ./scheduler
   ```

3. Use the interactive menu to select different scheduling algorithms and compare their performance metrics.

4. To clean build files:
   ```
   make clean
   ```

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

## How It Works

The simulator reads process information from the input file, including:
- Process ID
- CPU burst time
- Process priority
- Arrival time

When a scheduling algorithm is selected, the program calculates key metrics based on the algorithm's behavior:
- Waiting time: Time spent waiting in the ready queue
- Turnaround time: Total time from arrival to completion

The interactive menu allows users to compare the efficiency of different algorithms using the same process set.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- This project was inspired by operating systems concepts and scheduler implementations
- Thanks to all contributors who have helped improve this simulator
