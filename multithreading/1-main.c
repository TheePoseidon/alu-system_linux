#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "multithreading.h"

/**
 * _thread_entry - Thread entry point. Prints out a string
 *
 * @arg: Unused
 *
 * Return: NULL
 */
void *_thread_entry(__attribute__((unused))void *arg)
{
	tprintf("Hello from thread\n");
	return (NULL);
}

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS
 */
int main(void)
{
	pthread_t tid;

	pthread_create(&tid, NULL, &_thread_entry, NULL);
	pthread_join(tid, NULL);

	tprintf("Hello from main thread\n");

	return (EXIT_SUCCESS);
}
alex@~/multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 1-main.c 1-tprintf.c -o 1-tprintf -pthread
alex@~/multithreading$ ./1-tprintf
[140095003338496] Hello from thread
[140095011714880] Hello from main thread
alex@~/multithreading$ ./1-tprintf
[139794647717632] Hello from thread
[139794656094016] Hello from main thread