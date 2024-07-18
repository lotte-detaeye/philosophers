Overview of the process:

Tests:
- ./philo 200 800 200 200 : should be ok
- ./philo 4 800 200 200 : should be ok
- ./philo 4 410 200 200 : should be ok
- ./philo 1 800 200 200 : a philo should die
- ./philo 4 310 200 100 : a philo should die
- ./philo 4 200 205 200 : a philo should die
- ./philo 5 800 200 200 7 : no one should die, simulation should stop after 7 eats
- ./philo 4 410 200 200 10 : no one should die, simulation should stop after 10 eats
- ./philo 5 600 200 200 : should error and not run (no crashing)
- ./philo 4 -5 200 200 : should error and not run (no crashing)
- ./philo 4 600 -5 200 : should error and not run (no crashing)
- ./philo 4 600 200 -5 : should error and not run (no crashing)
- ./philo 4 600 200 200 -5 : should error and not run (no crashing)

Things to pay attention to:
- Avoid nesting mutexes
- Ensure that the code between pthread_mutex_lock and pthread_mutex_unlock 
	is minimal and only includes operations that modify or check shared 
	resources.
- better not use any mutexes when performing the actions (sleeping, 
	thinking, eating) -- those are too time-consuming

Notes / Troubleshooting :
1. The general mutex
--> when using it too often, there isn't enough time to actually share
the resources and the philosophers die to soon
- i used to lock the mutex in all of my action functions, in print_message and 
check_if_eaten (before and after the values are modified) but 
the program seems to work alright (and is faster) without

2. Higher amounts of threads. 
In one of my first versions, Philosopher 50 only started eating after 25000 milliseconds 
(meaning that they already died before they could even start eating).
I used to have a waiting function and a function that would synchronize all
philosopher's timestamps but this problem was actually solved by allocating 
left and right forks alternatively for even and odd numbers, instead of
allocating them similarly execept for the last philosopher at the table. 

I found these tips online to solve the problem with the high numbers: 
OK - create your own sleep function; 
- avoid ifs outside mutex; 
- same start stamp for all philos and 
OK - delay or waiting strategy at start; 
OK - centralized print functions (mutex protected) 
OK and a mutex for “taking fork” function.
--> but some of these slowed the program down too much.

3. clean exits were also a problem
When a philosopher dies, the program would exit immediately but when all 
philosophers had eaten all of their meals the exit was less smooth and the 
program would still print out things like 'philosopher 4 has taken a fork'
(even  though the same 'has died' variable is used for both the meals-eaten and 
philo-died monitoring processes)
I tried adding a counter variable (din->meals_complete)
which increments when one of the philosophers has eaten all of their meals.
i wanted to avoid having to loop again and again through the same information
and hoped that this would accelerate the monitoring process but for some reason 
this addition slowed things down and didn't change the outcome.
The mutex in the printing function solved this problem

4. Bugs and unpredictable behavior
Some philosophers died even though they were eating, or had eaten recently:
// 1001 Philosopher 3 has taken a fork
// 1001 Philosopher 3 has taken a fork
// 1001 Philosopher 3 is eating
// 1001 Philosopher 5 has taken a fork
// 1001 Philosopher 5 has taken a fork
// 1001 Philosopher 5 is eating
// 1001 Philosopher 3 died
//
// and another one
// 1000 Philosopher 2 has taken a fork
// 1000 Philosopher 2 is eating
// 1000 Philosopher 4 has taken a fork
// 1000 Philosopher 4 has taken a fork
// 1000 Philosopher 4 is eating
// 1000 Philosopher 1 is thinking
// 1000 Philosopher 1 has taken a fork
// 1200 Philosopher 1 has taken a fork
// 1200 Philosopher 1 is eating
// 1200 Philosopher 5 is thinking
// 1400 Philosopher 5 has taken a fork
// 1400 Philosopher 5 has taken a fork
// 1400 Philosopher 5 is eating
// 1400 Philosopher 2 died

Turns out there was a problem with the value of dinner->philos[i].last_meal. It seemed to change
(to just a timestamp?) and I didn't really know where and when it happened even though 
I tried to track the process with a lot of printfs. The behavior of the program was just
unpredictable. 
The solution was to use long longs as data type for timestamps instead of size_t.
I also protected the gettime function in the monitoring function with a mutex.

5, Speed
Centralizing the mutexes and minimizing their number was the no1 solution for this. 
I put a mutex around the printf function instead of multiple ones around each action
