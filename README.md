# CS-3113Project1

##  void calcTurnaround
calcTurnaround creates an array of Turnaround times and assigns each calculated time time to an index whic is calculated by 
subtracting one from the corresponding pid. This makes sure that in case of a duplicate process id, only the turnaround time for  last occurence of the process id is calculated

## void calcTurnaroundResponse
calcTurnaroundResponse creates array to store turnaround times that are calculated only including first occurance od duplicate pid

## void firstBurst()
calculates burst times only including first occurance of duplicare pid

## void calcWaitingTime

calculates waiting  time for each pid by subtracting burst time from turnaround time for each index and storing these values in a separate array

## void calcResponseTime
calculates and stores response time for each pid, using the arrays created in calcTurnaroundResponse and firstBurst

##int  nonSwitch()
Calculates and returns the number of places where there is no context switch

## struct num buffer[SIZE]

A struct array ius used to store threads as it can have individual elemnts that hold pid, burst time and priority

Voluntary context switches = number of execution elements for this project

Non voluntary context switches are calculated by subtracting number of non switches from the total number of duplicate pids

Throughput time = burst time/voluntary switches

An array is is used to store waiting times and respnse times and find the cumulative values

These formulas were helpful:

waiting time =turnaround time- burst time

response time = turnaround time(only counting first occurance of duplicate pid) - burst time (only counting first occurance of duplicate pid)

The main serves the purpose of reading in the threads and counting duplicates, and most of the other calculations were done in the functions mentioned above




