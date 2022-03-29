# Philosophers
### Introduction to threads

```c
#include <pthread.h>
gcc -g -pthread main.c -o main
```

To define a place where the API can store the informations

To initialize threads we have to call a function

```c
pthread_t thread1; //variable type of pthread_t
int pthread_create(pthread_t *restrict thread, const pthread_attr_t *restrict attr, void *(*start_routine)(void *), void *restrict arg);
int pthread_join(pthread_t thread, void **retval);
```

### Race Condition

> A race condition occurs when two or more threads can access shared data and they try to change it at the same time. Because the thread scheduling algorithm can swap between threads at any time, you don't know the order in which the threads will attempt to access the shared data.
> 

### Mutex

> How to solve race condition.
> 

There is a function much safer than implementing our own lock.

Lock and unlock allow to protect a part of code.

```c
int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);

int pthread_mutex_destroy(pthread_mutex_t *mutex);

int pthread_mutex_lock(pthread_mutex_t *mutex);

int pthread_mutex_unlock(pthread_mutex_t *mutex);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
```

### What are detached threads

```c
#include <pthread.h>

int pthread_detach(pthread_t th);
```

A detached thread is no longer joinable. They clear their own results. 

> Cela garantit que les ressources mémoire consommées par *th* seront immédiatement libérées lorsque l'exécution de *th* s'achèvera. Cependant, cela empêche les autres threads de se synchroniser sur la mort de *th* en utilisant **[pthread_join](http://manpagesfr.free.fr/man/man3/pthread_join.3.html)**
> 

Be careful the main thread does not finish before the detached thread. 
```
while (check_alive(arg->philo) && !check_times_eat(arg->philo))
	ft_usleep(arg->philo, 1);
```

### Deadlocks

→ When you lock twice a mutex

→ Lock in a different order with if

## The Dining Philosophers problem

The ***dining philosophers problem*** is invented by E. W. Dijkstra.
Imagine that five philosophers who spend their lives just thinking and eating. In the middle of the dining room is a circular table with five chairs.  The  table has a big plate of spaghetti.  However, there are only five chopsticks available, as shown in the following figure.  Each philosopher thinks.  When he gets hungry, he sits down and picks up the two chopsticks that are closest 
to him.  If a philosopher can pick up ***both*** chopsticks, he eats for a while.  After a philosopher finishes eating, he puts down the chopsticks and starts to think.

## How to start ?

1. Initialise data structure with threads and mutexes

Every philosopher has his own thread and every fork has its mutex. 

A philosopher starts by taking his left fork. This means that his right fork belongs to his right neighbor.

```jsx
pthread_mutex_init(&philo[i].l_fork, NULL);
if (i == arg->n_philo - 1)
	philo[i].r_fork = &philo[0].l_fork;
else
	philo[i].r_fork = &philo[i + 1].l_fork;
```

You have to let the uneven-numbers go first, so they don't eat at the same time. In addition, we use the method of inverted philosophers to avoid that a philosopher waits two turns to eat, and therefore dies.

```jsx
	if (tp->id % 2 == 0)
	{
		pthread_mutex_lock(tp->r_fork);
		print_message(tp, tp->id,"has taken a fork\n");
		pthread_mutex_lock(&tp->l_fork);
		print_message(tp, tp->id,"has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(&tp->l_fork);
		print_message(tp, tp->id,"has taken a fork\n");
		pthread_mutex_lock(tp->r_fork);
		print_message(tp, tp->id,"has taken a fork\n");
	}
```

## Checking if the philosopher is alive

To know when to stop the program, we have to create a detached thread. This thread will consistently check if someone died. 

**How do we know when someone died ?** 

Simple, we have to check if the time to die is less than the time between two meals or the begining of the program. 

```jsx
actual_time() - tp->start_eat >= tp->ttd
```

### The 5rd argument

The 5rd argument consists in giving a number of meals for the philosopher before ending the program. 

> If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation ends. If this argument is not specified, then the simulation ends when a philosopher dies.
> 

```jsx
int check_times_eat(t_data *tp)
{
	int	eat;

	eat = 0;
	if (tp->c->m_eat != -1)
	{
		pthread_mutex_lock(&tp->c->general);
		eat = tp->h_eat;
		pthread_mutex_unlock(&tp->c->general);
		if (eat == tp->c->m_eat)
		{
			pthread_mutex_lock(&tp->c->general);
			tp->c->count++;
			pthread_mutex_unlock(&tp->c->general);
			return (1);
		}
	}
	return (0);
}
```

Once a philosopher has finished eating all his meals, the loop of his thread will stop.

### How to launch the program ?

``make`` ``./philo nb_philo time_2_die time_2_eat time_2_sleep nb_of_meals(optionnal)``

### Sources

Unix thread course https://code-vault.net/course/6q6s9eerd0:1609007479575

https://github.com/iciamyplant/Philosophers

Thanks to @GaetanGK for his great help ! https://github.com/GaetanGK
