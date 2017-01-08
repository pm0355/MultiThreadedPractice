#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/sem.h>	
#define N_MACHINES 4
#define K_STATIONS 2


/*instantiate mutex lock for syncronization later*/
pthread_mutex_t lock;
int requests =3; // assume three customers, or one customer with 3 tokens 

/*define our thread data struct so we can id each machine*/
typedef struct str_thdata
{
    int thread_no;
    char message[100];
} thdata;


thdata data[N_MACHINES]; //create thread id array length of washers.

pthread_t station_tid[K_STATIONS]; // thread array containing registers threads
pthread_t machine_tid[N_MACHINES]; // thread array containing washer threads

/*instantiate functions for later use in the program */
void runMachine(void *ptr);
void setup(int stations, int machines);
void release(int machine);
int allocate();
void reg();


int main()
{
int station, machine;	

for(int j=0; j<N_MACHINES;j++){
  data[j].thread_no = j; 
}

setup(machine, station);
for(int i=0;i<requests; i++){
pthread_join(station_tid[i], NULL);
pthread_join(machine_tid[i], NULL);
}
    pthread_mutex_destroy(&lock);
}

/*Finds available machine returns, 1 upon completion */
int allocate(){
    pthread_mutex_lock(&lock);
    
    return 1;

}

/*Signals available machine with machine id, machine.*/
void release(int machine){
  
 printf("Machine %d is available.\n", machine);

}
/*Runs washing machine which sleeps for 5 sec, release grabs id of locked washer, and releases.*/
void runMachine(void *ptr){
	thdata *data;            
    data = (thdata *) ptr;

	printf("Machine running, brb in 5 seconds...\n");
	sleep(5);
	release(data->thread_no);
}
/*register thread allocates available machine for use.*/
void reg(){
   pthread_mutex_unlock(&lock);
	int machine_id = allocate();
}
/*creates threads for laundromat based on requests.*/
void setup(int machines, int stations)
{
	int i=0;
	while(i<requests){
	stations =pthread_create(&station_tid[i],NULL,(void *) reg, NULL);
	machines = pthread_create(&machine_tid[i],NULL,(void *)runMachine, (void *) &data[i]);
	i++;
}


}