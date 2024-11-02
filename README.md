# Dining Philosophers Problem

## Introduction

The Dining Philosophers Problem is a classic synchronization problem in computer
science. It illustrates the challenges of avoiding deadlock and ensuring proper
resource allocation among concurrent processes.

## Problem Description

This problem, simply put, is a simulation that should produce accurate behavior
based on the input provided to the program.

**Example of Input:**
$ philo 2 200 100 100 3


**Explanation of Input:**
- `$`: represents the prompt in the terminal.
- `philo`	: is the name of the binary.
- `2`		: the number of philosophers.
- `200`		: time to die (in milliseconds), meaning how many milliseconds will pass
				before a philosopher dies if it does not eat.
- `100`		: time to sleep (in milliseconds).
- `100`		: time to think (in milliseconds).
- `3`		: (optional) refers to the number of meals a philosopher will eat before it’s considered full.

## Terms and Concepts

Before diving in, here are some terms and concepts that are essential to understanding this problem:

1. **Thread**
   - A thread is, simply put, a subprocess within the same main process, meaning
   that all threads of a program share the same resources.
   - **Why use threading?**
     - Threading allows for simultaneous execution of multiple processes by
     utilizing multiple CPU cores, which improves performance.

2. **Data Race**
   - In a multithreaded system, threads have access to the same resources, which
   can lead to unexpected discrepancies in output if two threads attempt to
   access and modify data simultaneously. This issue is called a data race.

3. **Mutex**
   - A mutex is a way to prevent multiple threads in a multithreaded system from
   accessing the same data at the same time, effectively eliminating data races.

4. **Deadlock**
	- Deadlock occurs when a thread is waiting for a condition that will never
	happen, causing it to be stuck indefinitely. 
	e.g. In the context of the Dining Philosophers Problem, deadlock can happen
	if each philosopher picks up one fork and waits for the other, resulting in
	a cycle where no philosopher can proceed to eat.
	
## Problem Explination

In this simulation, a group of philosophers sits around a table, each with a
single fork in front of them. Each philosopher can perform three actions:
eating, sleeping, and thinking, each of which takes a set amount of time.
However, if a philosopher does not eat before their designated "time to die"
expires, they will starve.

The challenge is that for a philosopher to eat, they need two forks—one from
each side. This means each philosopher must borrow an additional fork from a
neighboring philosopher, creating a situation where careful resource management
is necessary to prevent deadlock and ensure everyone gets a chance to eat.
