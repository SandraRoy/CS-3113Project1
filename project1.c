#include<stdio.h>
#include<stdlib.h>
#define SIZE 50000
struct num{
        int id;
        int  burst;
        int  priority;

};

void calcTurnaround (struct num arr[],int arr1[],int size)
{
	int ttime=0;
	for (int i=0;i<size;i++)
	{
		ttime+=arr[i].burst;
		arr1[arr[i].id-1]=ttime;

	}
}
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

void calcWaitingTime(struct num arr[],int arr1[],int arr2[], int size)
{
	int wtime=0;
	for(int m=0;m<size;m++)
	{
		wtime=arr1[m]-arr[m].burst;
		arr2[m]=wtime;

	}
}

void calcResponseTime(int  arr[],int arr1[],int arr2[],int size)
{
	int rtime=0;
	for(int j=0;j<size;j++)
	{
		rtime= arr[j]-arr1[j];
		arr2[j]=rtime;
	}
}
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
int countDuplicate(struct num arr[], int size)
{
	int index=0;
	for(int i=0;i<size;i++)
	{
		int tracker=0;
		while(tracker<=i)
			if(arr[i].id== arr[tracker].id)
			{
				index++;
			}
		tracker++;
	}
	return index;

}
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
	int no_switch=0;
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
	int waiting[line];
	int ttotal =0;
	int wtotal=0;	
	double turnaround_time=0;
	double waiting_time=0;
	double response=0;
	int non_vol =0;
	while(size<line && !feof(fp))
        {
		fscanf(fp,"%d %d %d", &i,&b,&p);
		/*if(size==0)
                        {
                                turnaround[size]=b;
                        }
                        else
                        {
                                turnaround[size]=turnaround[size-1]+b;
                        }*/
		int tracker=0; //keeps track of repeated pid
		while(tracker<=size)
		{

			if(i==buffer[tracker].id) // 1 4 2 4 4 4 2 4 2
			{ //i=4;
			index++;
			break;
			}
		
			
			tracker++;
		}
		vol=exec;
		buffer[size].id = i;
		buffer[size].burst = b;
		buffer[size].priority = p;
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
	//printf("%d\n",total_rt);
	//printf("%.2f\n",waiting_time);
	//printf("%d\n",ttotal);
	printf("%d\n", index);
	printf("%d\n", no_switch);
	printf("%d\n",vol);
	printf("%d\n",index-no_switch);
	printf("%.2f\n",100.00);
	printf("%.2f\n",throughput);
	printf("%.2f\n",turnaround_time);
	printf("%.2f\n",waiting_time);
	printf("%.2f\n",response);
	
	return 0;
}

