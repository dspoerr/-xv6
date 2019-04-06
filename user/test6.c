#include "types.h"
#include "user.h"
#include "fcntl.h" 

#define PGSIZE 4096
#define USERTOP 0xA0000
#define INFO()\
	   printf(1, "failure in  %s : %s : %d\n", __FILE__, __func__, __LINE__);


// One process writes and another process reads
int main()
{
	char *ptr;
	int i;
	char arr[8] = "COP4610";
	printf(1, "BREAKPOINT 1 \n");
	ptr = shmem_access(2);
	if(ptr == NULL)
	{
		INFO();	
		printf(1, "TEST FAILED");
		exit();
	}
	printf(1, "BREAKPOINT 2 \n");
	int pid = fork();
	if(pid < 0)
	{
		INFO();	
		printf(1, "TEST FAILED");
		exit();
	}
	//printf(1, "BREAKPOINT 3 \n");
	else if(pid == 0)
	{
		printf(1, "BREAKPOINT 3 \n");
		sleep(20);
		for(i=0; i<7; i++)
		{
			printf(1, "BREAKPOINT 4 \n");
			if(*(ptr+i) != arr[i])
			{
				INFO();	
				printf(1, "TEST FAILED");
				exit();
			}
		}
		exit();
	}
	else
	{
		printf(1, "BREAKPOINT 5 \n");
		for(i=0; i<7; i++)
		{
			*(ptr+i) = arr[i];
		}
		wait();
	}
	printf(1, "%s TEST PASSED\n", __FILE__);
	exit();
}
