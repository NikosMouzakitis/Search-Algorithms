#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 20000

//________________________________ Implementation of selection sort algorithm.(Algorithms analysis)


void newline()
{
	printf("\n\n");
}

void selection_sort(int *p,int len)
{
	int i,j,min;
	int tmp;
	for(i = 0; i < len-1; i++)
	{
		min = p[i];

		for(j = i + 1; j < len; j++)
		{
			if(p[j] < min)
			{
				min = p[j];
					// swapping contexts.
				tmp = p[j];
				p[j] = 	p[i];		
				p[i] = tmp;
			}
		}
	}
}
int main(int argc,char *argv[])
{
	int pin[N],i,num,flag = 0;
	int loops_serial=0;

	srand(time(NULL));

	for(i = 0; i < N; i++)
	{
		pin[i] = (15*i) +(rand() % 7) * pow(-1,i);  // initialization of pin_array.
		printf("pin[%d]:%d\n",i,pin[i]);	// printing out the initialized data.
	}	
	
	printf("search value: \n");
	scanf("%d",&num);
	newline();
	selection_sort(pin,N);
	//_______________________________ code for serial search.	

	clock_t	s = clock();

	for(i = 0; i < N; i++)
	{
		loops_serial++;
		if(pin[i] == num)
		{
			printf("Loops run: %d\n",loops_serial);
			flag = 1;
			break;
		}
	}

	if(!flag)
		printf("Not found.\n");

	clock_t f = clock();
	
	printf("SERIAL SEARCH\n");
	printf("Total execution time: %f\n",(double)(f-s)/CLOCKS_PER_SEC);
	newline();	

	//_______________________________ code for binary search.

	flag=0;
	int low = 0,high = N-1;
	int loops = 0;
	s = clock();

	while(low <= high)
	{
		i = (low+high)/2;
		loops++;	
		if(pin[i] == num)
		{
			flag++;
			break;		
		}
		else if(pin[i] > num)
			high = i-1;
		else
			low = i+1;
	}
	if(flag)
		printf("Loops run: %d\n",loops);
	else
		printf("element not found\n");

	f = clock();

	printf("BINARY SEARCH\n");
	printf("Total execution time: %f\n",(double)(f-s)/CLOCKS_PER_SEC);
	newline();
	//______________________________ code for interpolation search.

	low =flag = 0,high = N-1;
	float fmid,fhigh;
	int inter_loops=0,mid;

	s = clock();

	while( (pin[high] >= num) && (num > pin[low]) )
	{
		fhigh = (float)high;
		fmid = low + ( (fhigh - low) * (num - pin[low])/(pin[high] - pin[low]) );
		mid = (int)ceil(fmid);
		inter_loops++;
//		sleep(1);		
//		printf("low: %d high: %d mid: %d \n",low,high,mid);	
		if(pin[mid] == num)
		{
			flag++;
			break;
		}

		else if(num > pin[mid])
			low = mid+1;
		else if(num < pin[mid])
				high = mid-1;
	}
	
	if(flag)
		printf("Loops run: %d\n",inter_loops);
	else
		printf("element not found\n");

	f = clock();

	printf("INTERPOLATION SEARCH\n");
	printf("Total execution time: %f\n",(double)(f-s)/CLOCKS_PER_SEC);
	newline();

	return 0;
}
