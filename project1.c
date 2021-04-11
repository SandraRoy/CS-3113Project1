#include<stdio.h>
#include<stdlib.h>
#define SIZE 50000
struct num{
        int id;  //process if
        int  burst; //burst time
        int  priority; // priority number

};

/* calcTurnaround creates an array of Turnaround times and assigns each calculated time time to an index whic is calculated by 
 *  subtracting one from the corresponding pid. This makes sure that in case of a duplicate process id, only the turnaround time for  last occurence of the process id is calculated */ 
void calcTurnaround (struct num arr[],int arr1[],int size)
{
	int ttime=0;
	for (int i=0;i<size;i++)
	{
		ttime+=arr[i].burst;
		arr1[arr[i].id-1]=ttime;

	}
}

// calcTurnaroundResponse creates array to store turnaround times that are calculated only including first occurance od duplicate pid
void calcTurnaroundResponse(struct num arr[],int arr1[],int size)
{
	for(int j=0;j<size;j++)
	{
		arr1[j]=0;
	}
	int rt=0;
	for(int i=0;i<size;i++)
	{
		rt+=arr[i].burst;
		if(arr1[arr[i].id-1]==0)
		{
			arr1[arr[i].id-1]= rt;
		}
	}
}

//calculates burst times only including first occurance of duplicare pid
void firstBurst(struct num arr[],int arr1[],int size)
{	
	for(int j=0;j<size;j++)
        {
                arr1[j]=0;
        }
	for(int i=0;i<size;i++)
	{	
		if(arr1[arr[i].id-1] ==0)
		{
			arr1[arr[i].id-1]=arr[i].burst;
		}

	}
}

//calculates and stores waiting  time for each pid
void calcWaitingTime(struct num arr[],int arr1[],int arr2[], int size)
{
	int wtime=0;
	for(int m=0;m<size;m++)
	{
		wtime=arr1[m]-arr[m].burst; //waiting time = turnaround time-burst time
		arr2[m]=wtime;

	}
}

//calculates and stores response time for each pid
void calcResponseTime(int  arr[],int arr1[],int arr2[],int size)
{
	int rtime=0;
	for(int j=0;j<size;j++)
	{
		rtime= arr[j]-arr1[j];// response time = turnaround time - burst time
		arr2[j]=rtime;
	}
}

//counts number of non switches
int  nonSwitch(struct num arr[],int size)
{
	int nv=0;
	for(int i=1;i<size;i++)
	{
		if(arr[i].id== arr[i-1].id)
		{
		
			nv+=1;
		}
		
	}
	return nv;
}

int main(int argc, char* argv[])
{
        struct num buffer[SIZE]; //struct array to hold pid, burst, priority
	
        int process;
        int line;
        int exec;
	int size=0;
	int index=0;
	int  vol=0; // holds number of voluntary context switches
        int i;
        int b;
        int p;
        FILE* fp;
	double  burst_time=0;// holds total burst time
	double throughput = 0;// calculates avg throughput
	int no_switch=0;
        if(argc>=2)
        {
                fp=fopen(argv[1],"r");//reads input from file
        }
	else
	{
		fp=stdin; //reads input from stdin
	}
	fscanf(fp,"%d",&process);
        fscanf(fp,"%d %d",&exec,&line);
        
        int turnaround[line];// array to store turnaround times
        int waiting[line]; // array to store waiting times
        int ttotal =0;// holds total turnaround time
        int wtotal=0; // holds total waiting time
        double turnaround_time=0;
        double waiting_time=0;// holds avg waiting  time
        double response=0;
        int non_vol =0;

	while(size<line && !feof(fp))// loop to read in file or through stdin
        {
		fscanf(fp,"%d %d %d", &i,&b,&p);
		int tracker=0; //Acts as an interator through all the process ids to check for duplicates
		while(tracker<=size)
		{

			if(i==buffer[tracker].id) //check for duplicate pids
			{ 
			index++;
			break;
			}
		
			
			tracker++;
		}
		vol=exec;

		//Assigning pid, burst time, and priority to the struct array
		buffer[size].id = i;
		buffer[size].burst = b;
		buffer[size].priority = p;
		
		//calculate total burst time
		burst_time +=b;
		size++;
	} 
	no_switch= nonSwitch(buffer,size);
	calcTurnaround(buffer,turnaround,size);
	for(int k=0;k<size; k++)
	{
		ttotal +=turnaround[k];
	}
	
	calcWaitingTime(buffer,turnaround,waiting,size);
	for(int n=0;n<size;n++)
	{
		wtotal+=waiting[n];
	}
	int turnaround_first[size];
	int burst1[size];
	int response_time[size];
	int total_rt=0;
	calcTurnaroundResponse(buffer,turnaround_first,size);
	firstBurst(buffer, burst1,size);
	calcResponseTime(turnaround_first,burst1,response_time,size);
	for(int n=0;n<size;n++)
        {
                total_rt+=response_time[n];
        }
	throughput =(double) vol/(double)burst_time;
	turnaround_time=(double)ttotal/(double)vol;
	waiting_time =(double)wtotal/(double)vol;
	response = (double)total_rt/(double)vol;

	printf("%d\n",vol);
	printf("%d\n",index-no_switch);
	printf("%.2f\n",100.00);
	printf("%.2f\n",throughput);
	printf("%.2f\n",turnaround_time);
	printf("%.2f\n",waiting_time);
	printf("%.2f\n",response);
	
	return 0;
}

