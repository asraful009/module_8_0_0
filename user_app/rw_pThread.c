

//Tue Jan  3 05:20:24 2012 


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>	//nanosleep()
#include <unistd.h>	//usleep()

#define size 20

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void *print_message_function( void *ptr );
void *p_read(char *argv);
void *p_write(char *argv, char *a);

int  iret[size] ,i;

struct timespec s;

int main()
{

	
	pthread_t thread[size];
	char message1[100][100];
	
	int  iret[size] ,i;
	
    	/* Create independent threads each of which will execute function */

	
	s.tv_sec = 0;
	s.tv_nsec = 5L;

	for(i=0; i<size; i++)
	{
		sprintf(message1[i], "number_%d", i);
		iret[i] = pthread_create( 
						&thread[i],
						NULL,
						print_message_function,
						(void*) message1[i]
					);
		
		//printf("iret %d\n", iret[i]);
		
	}

     	

	for(i=0; i<size; i++)
	{
		pthread_join( thread[i], NULL);
		//printf("iret %d\n", iret[i]);
	}

	//for(i=0; i<size; i++)
	//	printf("Thread %d returns: %d\n", i, iret[i]);
	
     	//exit(0);
     
	return 0;
	
}

void *print_message_function( void *ptr)
{

	char *message;
   
   	
   	int i;
	//pthread_mutex_lock( &mutex1 ); //for "race condition" no mutex condition
   
   		//sleep(1);
		message = (char *) ptr;
		
		
		printf("print_message function \"%s\"\n%lu\n", message, pthread_self());
		
		//p_read("/dev/driver_open0");
		p_write("/dev/driver_open0", message);
		//sleep(1);
		usleep(1);
     		p_read("/dev/driver_open0");
     		
	//pthread_mutex_unlock( &mutex1 );	//for "race condition"
	
	pthread_exit(0);
	printf("exit pthread \"%s\"------------\n", message);
}


void *p_read(char *argv)
{

	char a[100];
	FILE *fl;

	printf("\n");

	printf("Open node %s for read\n", argv);
				
	fl=fopen(argv, "rb");
	printf("start read ID %lu\n", pthread_self());
	fgets(a, sizeof(char)*10, fl);
	
	printf("-------\"%s\"-----%lu----\n", a, pthread_self());
	
	
	fclose(fl);
	printf("\n");

}


void *p_write(char *argv, char *a)
{

	
	FILE *fl;
	int i=0;

	printf("\n");

	printf("Open node %s for write\n", argv);
	
	fl=fopen(argv, "wb");
	//scanf("%s", a);
	
	printf("start write ID %lu message \"%s\"\n", pthread_self(), a);
	while(strlen(a)>=i)
	{
		nanosleep(&s, NULL);
		fwrite(&a[i], sizeof(char), 1, fl);
		printf("read %d ID %lu\n", a[i], pthread_self());
		i++;
	}

	fclose(fl);
	printf("\n");
	
}



