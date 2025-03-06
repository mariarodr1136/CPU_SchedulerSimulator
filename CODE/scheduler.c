// Add more header files if required...
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_PROCESSES 100

/* ========================================================================================*/
// Structure to store process information
typedef struct
{ // Add more variables to store process information if required...
    int pid;
    int priority;
    int burst_time;
    int arrival_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    bool is_completed;

} Process;

/* ========================================================================================*/
// Add more Global variables if required...
Process processes[MAX_PROCESSES];
int num_processes = 0;

/* ========================================================================================*/
// Add more Function prototypes suitable your implementation if required...
void fcfs();                        // First Come First Serve Scheduling
void sjf_non_preemptive();          // Shortest Job First - Non-preemptive
void srt_preemptive();              // Shortest Remaining Time - Preemptive
void round_robin(int time_quantum); // Round Robin Scheduling
void priority_non_preemptive();     // Priority Scheduling - Non-preemptive
void read_processes_from_file(const char *filename); //Read and process the process-related information form `input.txt` file
void calculate_average_times();     // Calculate and display average waiting & turnaround times
void display_results();             // Display scheduling results
void display_process_info();        // Display process details before scheduling
void clear_input_buffer();          // Clears input buffer to prevent invalid input issues
void reset_process_states();        // Resets process variables before each scheduling run
int min(int a, int b);              // Utility function to find the minimum of two numbers

/* ========================================================================================*/
// Main function
int main()
{
    // Add more variables suitable for your implementation if required...
    int choice;
    int time_quantum;
    char input[100]; // Buffer to store user input

    // Read process data from file
    read_processes_from_file("input.txt");

    // User-driven menu
    while (1)
    {
        printf("\n                 CPU Scheduling Algorithms\n");
        printf("|-----------------------------------------------------------|\n");
        printf("|   1. First-Come, First-Served (FCFS)                      |\n");
        printf("|   2. Shortest Job First (SJF) - Nonpreemptive             |\n");
        printf("|   3. Shortest Remaining Time (SRT) - Preemptive           |\n");
        printf("|   4. Round Robin (RR)                                     |\n");
        printf("|   5. Priority Scheduling - Nonpreemptive                  |\n");
        printf("|   0. Exit                                                 |\n");
        printf("|-----------------------------------------------------------|\n");

        printf("\nEnter your choice: ");
        if (!fgets(input, sizeof(input), stdin))
        {
            // Handle EOF (e.g., Ctrl+D)
            printf("\nExiting program.\n\n");
            break;
        }

        // Validate input: check if it's an integer
        if (sscanf(input, "%d", &choice) != 1)
        {
            printf("Invalid input. Please enter an integer between 0 and 5.\n");
            continue;
        }

        printf("\n");

        switch (choice)
        {
        case 1:
            fcfs();
            break;
        case 2:
            sjf_non_preemptive();
            break;
        case 3:
            srt_preemptive();
            break;
        case 4:
            printf("Enter time quantum for Round Robin Scheduling: \n");
            scanf("%d", &time_quantum);
            clear_input_buffer(); // Clear the buffer after reading input
            round_robin(time_quantum);
            break;
        case 5:
            priority_non_preemptive();
            break;
        case 0:
            printf("Exiting program.\n\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

/* ========================================================================================*/
// Function to read processes from a file (PLEASE DONOT MODIFY THIS FUNCTION CODE!!!)
void read_processes_from_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Buffer to hold each line from the file
    char line[256];
    int line_number = 0;

    // Skip the first two lines (header and separator)
    while (line_number < 2 && fgets(line, sizeof(line), file))
    {
        line_number++;
    }

    // Read process data from the file
    while (fgets(line, sizeof(line), file))
    {
        // Skip lines with separators like "====" or "----"
        if (line[0] == '=' || line[0] == '-')
        {
            continue;
        }

        char pid_str[10]; // Buffer to store process name like "P1" or "1"
        int pid, priority, burst_time, arrival_time;

        // Read the process ID and other values
        if (sscanf(line, "%s %d %d %d", pid_str, &burst_time, &priority, &arrival_time) == 4)
        {
            // Extract numeric part from 'P1' or read directly if it's just '1'
            if (sscanf(pid_str, "P%d", &pid) != 1)
            { // Check if it starts with 'P'
                if (sscanf(pid_str, "%d", &pid) != 1)
                { // Otherwise, try reading as a number
                    printf("Invalid process ID format: %s (skipped)\n", pid_str);
                    continue; // Skip invalid process IDs
                }
            }

            // Store the process data
            processes[num_processes].pid = pid;
            processes[num_processes].priority = priority;
            processes[num_processes].burst_time = burst_time;
            processes[num_processes].arrival_time = arrival_time;
            processes[num_processes].remaining_time = burst_time; // Remaining time equals burst time initially
            processes[num_processes].waiting_time = 0;            // Initialize waiting time for aging
            num_processes++;                                      // Increment process count
        }
        else
        {
            printf("Invalid line format: %s (skipped)\n", line); // Handle invalid data lines
        }
    }

    // Close the file after reading
    fclose(file);

    // Display the loaded process information
    display_process_info();
}

/* ========================================================================================*/
// Function to reset process states
void reset_process_states()
{
    // Also reset other process information variables if you have added to the 'Process' structure...
    for (int i = 0; i < num_processes; i++)
    {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].completion_time = 0;
        processes[i].is_completed = false;
    }
}

/* ========================================================================================*/
// Function to clear the input buffer (PLEASE DONOT MODIFY THIS FUNCTION CODE!!!)
void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ; // Consume characters until newline or EOF
}

/* ========================================================================================*/
// Function to display the scheduling information
void display_process_info()
{
    // Print fetched values in a table format
    printf("\n\n             Process Scheduling Information\n");
    printf("----------------------------------------------------------\n");
    printf("  | %-5s | %-12s | %-12s | %-12s |\n", "PID", "Burst Time", "Priority", "Arrival Time");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < num_processes; i++)
    {
        printf("  | %-5d | %-12d | %-12d | %-12d |\n",
               processes[i].pid, processes[i].burst_time,
               processes[i].priority, processes[i].arrival_time);
    }

    printf("----------------------------------------------------------\n\n");
}

/* ========================================================================================*/
// Finding minimum of two numbers
int min(int a, int b)
{
    return (a < b) ? a : b;
}

/* ========================================================================================*/
// Calculate Average Waiting Time & Average Turnaround Time
void calculate_average_times()
{
    int total_waiting_time = 0, total_turnaround_time = 0;
    
    // Sum up waiting time and turnaround time for all processes
    for (int i = 0; i < num_processes; i++)
    {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / num_processes);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround_time / num_processes);
}

/* ========================================================================================*/
// Display results
void display_results()
{
    // Display Individual Process Turnaround Time & Waiting Time
    printf("\nProcess    Waiting Time     Turnaround Time\n");
    for (int i = 0; i < num_processes; i++)
    {
        printf("  P%d           %d                 %d\n", processes[i].pid, processes[i].waiting_time, processes[i].turnaround_time);
    }

    // Display Average Waiting Time & Average Turnaround Time
    calculate_average_times();
}

/* ========================================================================================*/
// First-Come, First-Served (FCFS) Scheduling
void fcfs()
{
    // Reset process states before execution
    reset_process_states();

    // Sort processes by arrival time
    for (int i = 0; i < num_processes - 1; i++)
    {
        for (int j = 0; j < num_processes - i - 1; j++)
        {
            if (processes[j].arrival_time > processes[j + 1].arrival_time)
            {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    int current_time = 0;

    // Process each job in arrival time order
    for (int i = 0; i < num_processes; i++)
    {
        // If current time is less than arrival time, jump to arrival time
        if (current_time < processes[i].arrival_time)
        {
            current_time = processes[i].arrival_time;
        }

        // Calculate waiting time
        processes[i].waiting_time = current_time - processes[i].arrival_time;
        
        // Update current time after processing this job
        current_time += processes[i].burst_time;
        
        // Calculate completion time and turnaround time
        processes[i].completion_time = current_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].is_completed = true;
    }

    printf("***************************************************************************************\n\n");
    printf("FCFS Statistics...\n");
    display_results(); // Display Statistics
    printf("\n***************************************************************************************\n");
}

/* ========================================================================================*/
// Shortest Job First (SJF) - Non-Preemptive
void sjf_non_preemptive()
{
    // Reset process states
    reset_process_states();

    // Initialize variables
    int current_time = 0;
    int completed = 0;

    // Process until all processes are complete
    while (completed != num_processes)
    {
        int shortest_job_idx = -1;
        int shortest_burst = INT_MAX;

        // Find the process with the shortest burst time among the arrived processes
        for (int i = 0; i < num_processes; i++)
        {
            if (processes[i].arrival_time <= current_time && !processes[i].is_completed)
            {
                if (processes[i].burst_time < shortest_burst)
                {
                    shortest_burst = processes[i].burst_time;
                    shortest_job_idx = i;
                }
            }
        }

        // If no process is available at current time, advance time to next arrival
        if (shortest_job_idx == -1)
        {
            int next_arrival_time = INT_MAX;
            for (int i = 0; i < num_processes; i++)
            {
                if (!processes[i].is_completed && processes[i].arrival_time < next_arrival_time)
                {
                    next_arrival_time = processes[i].arrival_time;
                }
            }
            current_time = next_arrival_time;
            continue;
        }

        // Process the shortest job
        processes[shortest_job_idx].waiting_time = current_time - processes[shortest_job_idx].arrival_time;
        processes[shortest_job_idx].completion_time = current_time + processes[shortest_job_idx].burst_time;
        processes[shortest_job_idx].turnaround_time = processes[shortest_job_idx].completion_time - processes[shortest_job_idx].arrival_time;
        processes[shortest_job_idx].is_completed = true;

        // Update current time and completed count
        current_time += processes[shortest_job_idx].burst_time;
        completed++;
    }

    // Display results
    printf("***************************************************************************************\n\n");
    printf("SJF (Non-Preemptive) Statistics...\n");
    display_results();
    printf("\n***************************************************************************************\n\n");
}

/* ========================================================================================*/
// Shortest Remaining Time (SRT) - SJF Preemptive
void srt_preemptive()
{
    // Reset process states before execution
    reset_process_states();

    int current_time = 0;
    int completed = 0;
    // Remove unused variable

    // Create an array to store completion times
    int completion_times[MAX_PROCESSES] = {0};

    // Process until all processes are complete
    while (completed != num_processes)
    {
        int shortest_job_idx = -1;
        int shortest_remaining = INT_MAX;

        // Find the process with the shortest remaining time among the arrived processes
        for (int i = 0; i < num_processes; i++)
        {
            if (processes[i].arrival_time <= current_time && !processes[i].is_completed)
            {
                if (processes[i].remaining_time < shortest_remaining)
                {
                    shortest_remaining = processes[i].remaining_time;
                    shortest_job_idx = i;
                }
            }
        }

        // If no process is available at current time, advance time to next arrival
        if (shortest_job_idx == -1)
        {
            current_time++;
            continue;
        }

        // Decrement remaining time of the selected process
        processes[shortest_job_idx].remaining_time--;

        // If the process has completed
        if (processes[shortest_job_idx].remaining_time == 0)
        {
            completed++;
            processes[shortest_job_idx].is_completed = true;
            completion_times[shortest_job_idx] = current_time + 1;

            // Calculate turnaround time and waiting time
            processes[shortest_job_idx].turnaround_time = completion_times[shortest_job_idx] - processes[shortest_job_idx].arrival_time;
            processes[shortest_job_idx].waiting_time = processes[shortest_job_idx].turnaround_time - processes[shortest_job_idx].burst_time;
        }

        // Increment current time
        current_time++;
    }

    printf("***************************************************************************************\n\n");
    printf("SRT (Preemptive) Statistics...\n");
    display_results();
    printf("\n***************************************************************************************\n\n");
}

/* ========================================================================================*/
// Round Robin (RR) Scheduling
void round_robin(int time_quantum)
{
    // Reset process states before execution
    reset_process_states();

    // Sort processes by arrival time
    for (int i = 0; i < num_processes - 1; i++)
    {
        for (int j = 0; j < num_processes - i - 1; j++)
        {
            if (processes[j].arrival_time > processes[j + 1].arrival_time)
            {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Initialize variables
    int current_time = 0;
    int completed = 0;
    
    // Create a queue to manage processes
    int queue[MAX_PROCESSES];
    int front = 0, rear = 0;
    
    // Add the first arrived process to the queue
    queue[rear++] = 0;
    
    // Array to track if a process has been added to the queue
    bool in_queue[MAX_PROCESSES] = {false};
    in_queue[0] = true;

    while (completed != num_processes)
    {
        // If queue is empty, advance time to next arrival
        if (front == rear)
        {
            int next_arrival = INT_MAX;
            int next_idx = -1;
            
            for (int i = 0; i < num_processes; i++)
            {
                if (!processes[i].is_completed && processes[i].arrival_time < next_arrival)
                {
                    next_arrival = processes[i].arrival_time;
                    next_idx = i;
                }
            }
            
            if (next_idx != -1)
            {
                current_time = next_arrival;
                queue[rear++] = next_idx;
                in_queue[next_idx] = true;
            }
            continue;
        }
        
        // Get the next process from the queue
        int idx = queue[front++];
        
        // Execute the process for time quantum or remaining time
        int execute_time = min(time_quantum, processes[idx].remaining_time);
        processes[idx].remaining_time -= execute_time;
        current_time += execute_time;
        
        // Check for newly arrived processes during this time slice
        for (int i = 0; i < num_processes; i++)
        {
            if (!processes[i].is_completed && !in_queue[i] && processes[i].arrival_time <= current_time)
            {
                queue[rear++] = i;
                in_queue[i] = true;
            }
        }
        
        // If the process has remaining time, add it back to the queue
        if (processes[idx].remaining_time > 0)
        {
            queue[rear++] = idx;
        }
        else
        {
            // Process is completed
            processes[idx].is_completed = true;
            processes[idx].completion_time = current_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
            completed++;
        }
        
        // Reset in_queue flag for this process
        in_queue[idx] = false;
    }

    printf("***************************************************************************************\n\n");
    printf("RR Statistics (Time Quantum = %d)...\n", time_quantum);
    display_results(); // Display Statistics
    printf("\n***************************************************************************************\n");
}

/* ========================================================================================*/
// Priority Scheduling - Non-Preemptive
void priority_non_preemptive()
{
    // Reset process states before execution
    reset_process_states();

    // Initialize variables
    int current_time = 0;
    int completed = 0;

    // Process until all processes are complete
    while (completed != num_processes)
    {
        int highest_priority_idx = -1;
        int highest_priority = INT_MAX; // Lower value means higher priority

        // Find the process with the highest priority among the arrived processes
        for (int i = 0; i < num_processes; i++)
        {
            if (processes[i].arrival_time <= current_time && !processes[i].is_completed)
            {
                if (processes[i].priority < highest_priority)
                {
                    highest_priority = processes[i].priority;
                    highest_priority_idx = i;
                }
            }
        }

        // If no process is available at current time, advance time to next arrival
        if (highest_priority_idx == -1)
        {
            int next_arrival_time = INT_MAX;
            for (int i = 0; i < num_processes; i++)
            {
                if (!processes[i].is_completed && processes[i].arrival_time < next_arrival_time)
                {
                    next_arrival_time = processes[i].arrival_time;
                }
            }
            current_time = next_arrival_time;
            continue;
        }

        // Process the highest priority job
        processes[highest_priority_idx].waiting_time = current_time - processes[highest_priority_idx].arrival_time;
        processes[highest_priority_idx].completion_time = current_time + processes[highest_priority_idx].burst_time;
        processes[highest_priority_idx].turnaround_time = processes[highest_priority_idx].completion_time - processes[highest_priority_idx].arrival_time;
        processes[highest_priority_idx].is_completed = true;

        // Update current time and completed count
        current_time += processes[highest_priority_idx].burst_time;
        completed++;
    }

    printf("***************************************************************************************\n\n");
    printf("Priority (PR) - Nonpreemptive Statistics...\n");
    display_results(); // Display Statistics
    printf("\n***************************************************************************************\n");
}