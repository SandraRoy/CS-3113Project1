#include<stdio.h>
#include<stdlib.h>
#define SIZE 50000
struct num{
        int id;
        int  burst;
        int  priority;

};


int main(int argc, char* argv[])
{
        struct num buffer[SIZE];
	
        int process;
        int line;
        int exec;
	int size=0;
	int index=0;
	int  vol=0;
        int i;
        int b;
        int p;
        FILE* fp;
	double  burst_time=0;
	double throughput = 0;
	int ttime =0;
        if(argc>=2)
        {
                fp=fopen(argv[1],"r");
        }
	else
	{
		fp=stdin;
	}
	fscanf(fp,"%d",&process);
        fscanf(fp,"%d %d",&exec,&line);
        int repeat[line];
	int turnaround[line];	
	while(size<line && !feof(fp))
        {
		fscanf(fp,"%d %d %d", &i,&b,&p);
		if(size==0)
                        {
                                turnaround[size]=b;
                        }
                        else
                        {
                                turnaround[size]=turnaround[size-1]+b;
                        }
		int tracker=0; //keeps track of repeated pid
		while(tracker<=size)
		{

			if(i==buffer[tracker].id)
			{

			
			index++;
			}
			tracker++;
		}
		vol=line-index;
		buffer[size].id = i;
		buffer[size].burst = b;
		buffer[size].priority = p;
		//printf("%d\n",buffer[size].id);
		burst_time +=b;
		size++;
	} 
	throughput =(double) vol/(double)burst_time;
	printf("%d\n",100);
	printf("%d\n",vol);
	printf("%d\n",index);
	printf("%.2f\n",throughput);
	
}

