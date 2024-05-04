# Philosophers
> **42 Madrid's project: Basics of threading a process.**

## What is this about?
This project is the resolution of the [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) in C.
In C programming, this problem is often represented using threads and semaphores to control access to shared resources (the forks in this case). The goal is to design an algorithm that allows philosophers to acquire forks in a way that avoids deadlock and starvation, maintaining synchronization and avoiding race conditions.

### The dinning philosophers
The problem consists of a simulation where several philosophers sit around a round table with a plate of spaghetti in the center that they share among themselves. Each philosopher needs two forks to eat; however, there is only one fork between each pair of philosophers. This forces the philosophers to wait for their neighbor to finish eating to use both forks. When they finish eating, they go to sleep, and upon waking up, they start thinking. Each philosopher has a lifespan that resets every time they eat, but if it runs out before they can eat, they die, and the simulation ends.

## How to use
The program need the following arguments:
- number_of_philosophers: The number of philosophers and also the number
of forks.
- time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
- time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
- number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.


## How to compile
Clone the repository:

`git clone git@github.com:telufulu/philosophers.git telufulu_philosophers`

Compile it:

`cd telufulu_philosophers/philo`

`make`

Try this example:

`./philo 5 800 200 200 7`
