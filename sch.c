#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_SIZE 50

void FIFO(int);
void SJF(int);

typedef struct Jobs
{
    int id;
    int arrivalTime;
    int duration;
}Jobs;

Jobs jobA[MAX_ARRAY_SIZE];

int ReadFile(char *fileName);

int main(int argc, char *argv[])
{
    char *fileName = "jobs.dat";
    int totalJobs = ReadFile(fileName);

    int i = 0;
    printf("This is FIFO \n\n");
    FIFO(totalJobs);
    printf("This is SJF \n\n");
    SJF(totalJobs);
    /*for (i = 0; i < totalJobs; i++)
    {
        printf("ID : %d\n", jobA[i].id);
        printf("Arrival time  : %d\n", jobA[i].arrivalTime);
        printf("Duration : %d\n", jobA[i].duration);
        printf("\n");
    }*/

    exit(EXIT_SUCCESS);
}

int ReadFile(char *fileName)
{
    FILE *filePtr = NULL;
    int  i = 0;

    if ((filePtr = fopen(fileName, "r")) == NULL)
    {
        printf("Error : Unable to open %s for reading\n",fileName);
        exit(EXIT_FAILURE);
    }

    while (fscanf(filePtr, "%d%d%d", &jobA[i].id, &jobA[i].arrivalTime, &jobA[i].duration) != EOF)
    {
        i++;
    }

    fclose(filePtr);
    return i;
}

void FIFO(int totalJobs){
    int min;
    Jobs temp;
    int startTime[totalJobs];
    int finishTime[totalJobs];
    // One by one move boundary of unsorted subarray
    for (int i = 0; i < totalJobs-1; i++){
        // Find the minimum element in unsorted array
        min = i;
        for (int j = i+1; j < totalJobs; j++){
            if ( jobA[j].arrivalTime < jobA[min].arrivalTime){
                min = j;
            }
        }
        // Swap the found minimum element with the first element
        temp = jobA[min];
        jobA[min] = jobA[i];
        jobA[i] = temp;
    }
    int time = 0 ;
    
    for(int k=0; k < totalJobs; k++){
        startTime[k] = time;
        for(int l=0; l < jobA[k].duration; l++){
            time++;
        }
        finishTime[k] = time;
    }
    
    for(int m=0; m < totalJobs; m++){
        printf("ID %d\n", jobA[m].id);
        printf("Start Time %d\n",startTime[m]);
        printf("Finish Time %d\n",finishTime[m]);
        printf("Total Time %d\n",jobA[m].duration);
        printf("Response Time %d\n\n",(startTime[m]-jobA[m].arrivalTime));
    }
    
}

void SJF(int totalJobs){
    int min;
    Jobs temp;
    int i = 0;
    int bubbleStart[totalJobs];
    int bubbleStop[totalJobs];
    int startTime[totalJobs];
    int finishTime[totalJobs];
    for(int a = 0; a < totalJobs; a++){
        if(jobA[a].arrivalTime == jobA[a+1].arrivalTime){
            
            bubbleStart[i] = a;
            int b = a;
            while(jobA[b].arrivalTime == jobA[b+1].arrivalTime){
                bubbleStop[i] = b+1;
                b++;
            }
            for(int k = bubbleStart[i]; k < bubbleStop[i]; k++){
                for(int j = bubbleStart[i]; j < bubbleStop[i]-1-k; j++){
                    
                    if(jobA[j].duration > jobA[j+1].duration){
                        temp = jobA[j];
                        jobA[j] = jobA[j+1];
                        jobA[j+1] = temp;
                    }
                
                }
            }    
            i++;
        }
    }    
    int time = 0 ;
    
    for(int g = 0; g < totalJobs; g ++){
        startTime[g] = time;
        for(int l = 0; l < jobA[g].duration; l++){
            time++;
        }
        finishTime[g] = time;
    }
    
    for(int m = 0; m < totalJobs; m++){
        printf("ID %d\n", jobA[m].id);
        printf("Start Time %d\n",startTime[m]);
        printf("Finish Time %d\n",finishTime[m]);
        printf("Total Time %d\n",jobA[m].duration);
        printf("Response Time %d\n\n",(finishTime[m]-jobA[m].arrivalTime));
    }
}



