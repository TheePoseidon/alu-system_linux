#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "multithreading.h"

#define NB_THREADS	8

/**
 * print_task_result - Print the result of a task
 *
 * @task: Pointer to the task to print the result of
 */
void print_task_result(task_t *task)
{

	list_t *factors = (list_t *)task->result;
	node_t *factor;

	printf("%s =", (char *)task->param);
	for (factor = factors->head; factor; factor = factor->next)
	{
		unsigned long n = *((unsigned long *)factor->content);

		printf("%s %lu", factor->prev ? " *" : "", n);
	}
	printf("\n");
}

/**
 * main - Entry point
 *
 * @ac: Arguments count
 * @av: Arguments vector
 *
 * Return: EXIT_SUCCESS upon success, EXIT_FAILURE otherwise
 */
int main(int ac, char **av)
{
	list_t tasks;
	pthread_t threads[NB_THREADS];
	size_t i;

	if (ac < 2)
	{
		fprintf(stderr, "Usage: %s n\n", av[0]);
		return (EXIT_FAILURE);
	}

	if (!list_init(&tasks))
		return (EXIT_FAILURE);

	for (i = 1; i < (size_t)ac; i++)
		list_add(&tasks,
			create_task((task_entry_t)prime_factors, av[i]));

	printf("Executing %lu tasks on %u threads\n", tasks.size, NB_THREADS);

	for (i = 0; i < NB_THREADS; i++)
		pthread_create(&threads[i], NULL,
			(void *(*) (void *))exec_tasks, &tasks);
	for (i = 0; i < NB_THREADS; i++)
		pthread_join(threads[i], NULL);

	list_each(&tasks, (node_func_t)print_task_result);

	list_destroy(&tasks, (node_func_t)destroy_task);

	return (EXIT_SUCCESS);
}
alex@~/multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 22-main.c 22-prime_factors.c 21-prime_factors.c list.c 20-tprintf.c -o 22-prime_factors -pthread
alex@~/multithreading$ ./22-prime_factors 234 23456 908345 9803475893 389475 9384 7538 4753876348956746 4985 39485734 9587398 7938475839 324 3453450
Executing 14 tasks on 8 threads
[139770218567424] [00] Started
[139770218567424] [00] Success
[139770218567424] [08] Started
[139770218567424] [08] Success
[139770218567424] [09] Started
[139770218567424] [09] Success
[139770218567424] [10] Started
[139770218567424] [10] Success
[139770218567424] [11] Started
[139770218567424] [11] Success
[139770218567424] [12] Started
[139770218567424] [12] Success
[139770218567424] [13] Started
[139770218567424] [13] Success
[139770159818496] [07] Started
[139770159818496] [07] Success
[139770201782016] [02] Started
[139770201782016] [02] Success
[139770184996608] [04] Started
[139770184996608] [04] Success
[139770168211200] [06] Started
[139770168211200] [06] Success
[139770193389312] [03] Started
[139770193389312] [03] Success
[139770176603904] [05] Started
[139770176603904] [05] Success
[139770210174720] [01] Started
[139770210174720] [01] Success
234 = 2 * 3 * 3 * 13
23456 = 2 * 2 * 2 * 2 * 2 * 733
908345 = 5 * 181669
9803475893 = 1153 * 8502581
389475 = 3 * 3 * 3 * 5 * 5 * 577
9384 = 2 * 2 * 2 * 3 * 17 * 23
7538 = 2 * 3769
4753876348956746 = 2 * 11 * 67 * 89 * 89 * 3373 * 120713
4985 = 5 * 997
39485734 = 2 * 37 * 47 * 11353
9587398 = 2 * 2141 * 2239
7938475839 = 3 * 3 * 7 * 7 * 17 * 53 * 19979
324 = 2 * 2 * 3 * 3 * 3 * 3
3453450 = 2 * 3 * 5 * 5 * 7 * 11 * 13 * 23