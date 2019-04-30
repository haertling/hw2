#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_SIZE 50

void FIFO(int);
void SJF(int);
void BJF(int);
void RR(int);
void bubbleSort(int,int);

typedef struct Jobs
{
    int id;
    int arrivalTime;
    int duration;
}Jobs;

void swap(Jobs, Jobs);

Jobs jobA[MAX_ARRAY_SIZE];

int ReadFile(char *fileName);

int main(int argc, char *argv[])
{
    char *fileName = "jobs.dat";
    int totalJobs = ReadFile(fileName);

    int i = 0;
    printf("This is FIFO \n");
    FIFO(totalJobs);
    printf("This is SJF \n");
    SJF(totalJobs);
    printf("This is BJF \n");
    BJF(totalJobs);
    printf("This is RR \n");
    RR(totalJobs);
    /*
    for (i = 0; i < totalJobs; i++)
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
        if( jobA[k].arrivalTime > time){//if no job available to run
                     time = jobA[k].arrivalTime;
        }
        startTime[k] = time;
        for(int l=0; l < jobA[k].duration; l++){
            time++;
        }
        finishTime[k] = time;
    }
    
    for(int m=0; m < totalJobs; m++){
        printf("ID %d\t", jobA[m].id);
        printf("Start Time %d\t",startTime[m]);
        printf("Finish Time %d\t",finishTime[m]);
        printf("Total Time %d\t",(finishTime[m]-jobA[m].arrivalTime));
        printf("Response Time %d\t\n",(startTime[m]-jobA[m].arrivalTime));
    }
    
}

void SJF(int totalJobs){
    Jobs temp;
    int startTime[totalJobs];
    int finishTime[totalJobs];
 

    for (int i=0; i < totalJobs; i++)
 
        for (int i = 0 ; i < totalJobs - 1; i++){
            for (int j = 0 ; j < totalJobs - i - 1; j++) {
                if(jobA[j].arrivalTime == jobA[j+1].arrivalTime){
                    if (jobA[j].duration > jobA[j+1].duration) { /* For decreasing order use < */
                        temp = jobA[j];
                        jobA[j] = jobA[j+1];
                        jobA[j+1] = temp;
                        }
                    }
            }
        }
 
 
  // for (c = 0; c < totalJobs; c++)
  //    printf("%d\n", jobA[c]);

int time = 0 ;
    
    for(int g = 0; g < totalJobs; g ++){
     if(jobA[g].arrivalTime > time){//if no job available to run
                     time = jobA[g].arrivalTime;
                }
        startTime[g] = time;
        for(int l = 0; l < jobA[g].duration; l++){
            time++;
        }
        finishTime[g] = time;
    }


 for(int m=0; m < totalJobs; m++){
        printf("ID %d\t", jobA[m].id);
        printf("Start Time %d\t",startTime[m]);
        printf("Finish Time %d\t",finishTime[m]);
        printf("Total Time %d\t",(finishTime[m]-jobA[m].arrivalTime));
        printf("Response Time %d\t\n",(startTime[m]-jobA[m].arrivalTime));
    }

}

void BJF(int totalJobs){
    Jobs temp;
    int startTime[totalJobs];
    int finishTime[totalJobs];
 

    for (int i=0; i < totalJobs; i++)
 
        for (int i = 0 ; i < totalJobs - 1; i++){
            for (int j = 0 ; j < totalJobs - i - 1; j++) {
                if(jobA[j].arrivalTime == jobA[j+1].arrivalTime){
                    if (jobA[j].duration < jobA[j+1].duration) { /* For decreasing order use < */
                        temp = jobA[j];
                        jobA[j] = jobA[j+1];
                        jobA[j+1] = temp;
                        }
                    }
            }
        }
 
 
  // for (c = 0; c < totalJobs; c++)
  //    printf("%d\n", jobA[c]);

int time = 0 ;
    
    for(int g = 0; g < totalJobs; g ++){
     if(jobA[g].arrivalTime > time){//if no job available to run
                     time = jobA[g].arrivalTime;
                }
        startTime[g] = time;
        for(int l = 0; l < jobA[g].duration; l++){
            time++;
        }
        finishTime[g] = time;
    }


 for(int m=0; m < totalJobs; m++){
        printf("ID %d\t", jobA[m].id);
        printf("Start Time %d\t",startTime[m]);
        printf("Finish Time %d\t",finishTime[m]);
        printf("Total Time %d\t",(finishTime[m]-jobA[m].arrivalTime));
        printf("Response Time %d\t\n",(startTime[m]-jobA[m].arrivalTime));
    }

}

void RR(int totalJobs){
    int time,i = 0;
    int completedJobs = 0;
    int numJobs = 0;
    int addedNum[totalJobs];
    int startTime[totalJobs];
    int finishTime[totalJobs];
    int jobVet[totalJobs];
    int done[totalJobs];
    
    
    Jobs jobC[MAX_ARRAY_SIZE];
    for(int d = 0; d < totalJobs; d++){
        jobC[d] = jobA[d];
    }
    for(int d = 0;d < totalJobs; d++){
        addedNum[d] = 0;
        startTime[d] = 0;
        finishTime[d] = 0;
        jobVet[d] = 0;
        done[d] = 0;
    }

    
    while(completedJobs < (totalJobs+1)){
        //printf("for loop\n");
        //printf("total jobs %d\n", totalJobs);
        //printf("CJ %d\n", completedJobs);
        
        do{    
            
            if(jobC[i].duration == 0){//if job done goes down this branch
            //printf("done\n");
                if(done[i] == 1){
                    //printf("really done\n");
                }
                else{// first time done
                    done[i] = 1;
                    completedJobs++;
                    //printf("completed jobs %d\n", completedJobs);
                    finishTime[i]=time;
                }
            }
            else{
                //printf("check arrival time\n");
                if(jobC[i].arrivalTime > time){//if no job available to run
                     time = jobC[i].arrivalTime;
                     //printf("time %d\t", time);
                }
                if(jobVet[i]==1){//if job has run before
                    //printf("duration %d\n", jobC[i].duration);
                    jobC[i].duration--;
                    
                    time++;
                    if(jobC[i].duration == 0){//if job done goes down this branch
                        //printf("done\n");
                        if(done[i] == 1){
                            //printf("really done\n");
                        }
                        else{// first time done
                            done[i] = 1;
                            completedJobs++;
                            //printf("completed jobs in already run %d\n", completedJobs);
                            finishTime[i]=time;
                        }
                    }// printf("vet time %d\n", time);
                }
                else{//if first run
                        //printf("I got to first run \n");
                        jobVet[i] = 1;
                        if(addedNum[i] == 0){
                            addedNum[i] = 1;
                            numJobs++;
                            //printf("numJobs %d\n", numJobs);
                        }
                        startTime[i] = time;
                       // printf("start time %d\n", startTime[i]);
                        //printf("duration %d\n", jobC[i].duration);
                        jobC[i].duration--;
                        time++;
                        //printf("time after 1st run %d\n", time);
                        if(jobC[i].duration == 0){//if job done goes down this branch
                            //printf("done\n");
                                if(done[i] == 1){
                                    //printf("really done\n");
                                }
                                else{// first time done
                                    done[i] = 1;
                                    completedJobs++;
                                    //printf("completed jobs in first run %d\n", completedJobs);
                                    
                                    finishTime[i]=time;
                                   // printf("finish time 1st run %d\n", time);
                                }
                        }
                }
            }
            i++;
            if(i > numJobs){
                i = 0;
            }
            
            //printf("i %d\n",i);
            //printf("numJobs %d\n", numJobs);
            //printf("completed %d\n", completedJobs);
        }while(completedJobs < numJobs);
        if(numJobs < totalJobs){
            time = jobC[numJobs+1].arrivalTime -1;  
             //printf("time outside while %d\n", time);
        }    
        //printf("outside while numJobs %d\n", numJobs);
        
    }
    for(int m=0; m < totalJobs; m++){
        printf("ID %d\t", jobC[m].id);
        printf("Start Time %d\t",startTime[m]);
        printf("Finish Time %d\t",finishTime[m]);
        printf("Total Time %d\t",(finishTime[m]-jobC[m].arrivalTime));
        printf("Response Time %d\t\n",(startTime[m]-jobC[m].arrivalTime));
    }
}




