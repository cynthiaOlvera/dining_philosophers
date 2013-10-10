#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
  
#define N 5
#define PENSANDO 0
#define HAMBRIENTO 1
#define COMIENDO 2
#define IZQUIERDO (i+N-1)%N
#define DERECHO (i+1)%N
  
sem_t mutex;
sem_t s[N];
  
void filosofo(void *jc);
void tomar_tenedor(int);
void poner_tenedor(int);
void probar(int);
  
int estado[N];
int numero_f[N]={0,1,2,3,4};
  
void filosofo(void *jc)
{
	while(1)
    	{
		int *j = jc;
        	sleep(srand(time(NULL)+j*5));
        	tomar_tenedor(*j);
        	sleep(srand(time(NULL)+5));
        	poner_tenedor(*j);
    	}
}
  
void tomar_tenedor(int i)
{
    	sem_wait(&mutex);
    	estado[i] = HAMBRIENTO;
   	printf("El filosofo %d esta hambriento\n",i+1);
    	probar(i);
    	sem_post(&mutex);
    	sem_wait(&s[i]);
   	sleep(srand(time(NULL)+i*5));
}
  
void poner_tenedor(int i)
{
    	sem_wait(&mutex);
    	estado[i] = PENSANDO;
    	printf("El filosofo %d esta pensando\n",i+1);
    	probar(IZQUIERDO);
    	probar(DERECHO);
    	sem_post(&mutex);
}

void probar(int i)
{
    	if (estado[i] == HAMBRIENTO && estado[IZQUIERDO] != COMIENDO && estado[DERECHO] != COMIENDO)
    	{
        	estado[i] = COMIENDO;
        	printf("El filosofo %d esta comiendo\n",i+1);
		sleep(srand(time(NULL)+i*5));
        	sem_post(&s[i]);
    	}
}


int main()
{
    	int c;
    	void *n = filosofo;
    	pthread_t t_filosofos[N];
    	sem_init(&s[0],0,0);
    	sem_init(&s[1],0,0);
    	sem_init(&s[2],0,0);
    	sem_init(&s[3],0,0);
    	sem_init(&s[4],0,0);
    	sem_init(&mutex,0,1);

    	for(c=0;c<N;c++)
    	{
        	pthread_create(&t_filosofos[c],NULL,n,&numero_f[c]);
        	printf("El filosofo %d esta pensando\n",c+1);
    	}
    	pthread_join(t_filosofos[0],NULL);
    	pthread_join(t_filosofos[1],NULL);
    	pthread_join(t_filosofos[2],NULL);
    	pthread_join(t_filosofos[3],NULL);
    	pthread_join(t_filosofos[4],NULL);

}

