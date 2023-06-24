//execute using "gcc -pthread -o name name.cpp"
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/time.h>
#include<pthread.h>

int x=0;

void capture()
{
    exit(0);
}

int get()
{
    return x;
}

void put()
{
    x++;
}

void node(char *p)
{
    int name;
    int seq1,seq2,i=0;
    long t;
    struct timeval tv;
    struct timezone tz;
    name=atoi(p);
    while(1)
    {
        seq1=get();
        seq2=get();
        if(seq1==seq2)
        {
            put();
            seq1=get(); 
            gettimeofday(&tv,&tz);
            printf("station %d transmitting frame %d at %ld \n",name,++i,tv,tz);
            usleep(10);
            seq2=get();
            if(seq1!=seq2)
            {
                printf("station %d collision occurred %d \n",name,i--);
                usleep(100);
            }
            else
            {
                printf("station %d transmission of frame %d success \n",name,i);
            }
        }
        usleep(200000);
    }
}

int main()
{
    pthread_t t1,t2,t3;
    signal(SIGINT,capture);
    pthread_create(&t1,0,(void *)node,"1");
    pthread_create(&t2,0,(void *)node,"2");
    pthread_create(&t3,0,(void *)node,"3");
    while(1);
}
