#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "multithreading.h"

#define NB_THREADS	10

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
	pthread_t tid[NB_THREADS];
	int i;

	for (i = 0; i < NB_THREADS; i++)
		pthread_create(&tid[i], NULL, &_thread_entry, NULL);

	tprintf("Hello from main thread\n");

	for (i = 0; i < NB_THREADS; i++)
		pthread_join(tid[i], NULL);

	return (EXIT_SUCCESS);
}
alex@~/multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 20-main.c 1-tprintf.c -o 20-tprintf -pthread
alex@~/multithreading$ ./20-tprintf
[139996670035712] [139996678428416] [139996686821120] [139996695197504] Hello from thread
[139996644857600] Hello from thread
[139996628072192] Hello from thread
[139996619679488] Hello from thread
Hello from main thread
Hello from thread
Hello from thread
[139996611286784] Hello from thread
[139996661643008] Hello from thread
[139996636464896] Hello from thread
[139996653250304] Hello from thread
alex@~/multithreading$ gcc -Wall -Wextra -Werror -pedantic -g3 20-main.c 20-tprintf.c -o 20-tprintf -pthread
alex@~/multithreading$ ./20-tprintf
[140146877490944] Hello from thread
[140146852312832] Hello from thread
[140146843920128] Hello from thread
[140146860705536] Hello from thread
[140146835527424] Hello from thread
[140146869098240] Hello from thread
[140146818742016] Hello from thread
[140146885867328] Hello from main thread
[140146810349312] Hello from thread
[140146801956608] Hello from thread
[140146827134720] Hello from thread