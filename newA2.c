#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_SIZE 50

void FIFO(int);
void SJF(int);
void BJF(int);
void RR(int);
void STCF(int);

// Job Structure
// Fields for JOB_ID, ARRIVALTIME, DURATION
typedef struct Jobs{
    int id;
    int arrivalTime;
    int duration;
}Jobs;

// Define array of Job objects
Jobs jobA[MAX_ARRAY_SIZE];

// ReadFile function for file I/O
int ReadFile(char *fileName);

// Main Function
int main(int argc, char *argv[]){
    
    // Change file name here to testing <.dat> file
    char *fileName = "jobs.dat";
    int totalJobs = ReadFile(fileName);

    // FIFO test
    printf("This is FIFO \n");
    FIFO(totalJobs);
    
    // BJF test
    printf("This is BJF \n");
    BJF(totalJobs);
    
    // SJF test
    printf("This is SJF \n");
    SJF(totalJobs);
    
    // STCF test
    printf("This is STCF \n");
    STCF(totalJobs);
    
    // RR test
    printf("This is RR \n");
    RR(totalJobs);

    // exit?
    exit(EXIT_SUCCESS);
}

int ReadFile(char *fileName){
    // ReadFile returns number of total jobs given in <.dat> input file
    FILE *filePtr = NULL;
    int  i = 0;

    if ((filePtr = fopen(fileName, "r")) == NULL){
        printf("Error : Unable to open %s for reading\n",fileName);
        exit(EXIT_FAILURE);
    }
    
    // Scan integers
    
    while (fscanf(filePtr, "%d%d%d", &jobA[i].id, &jobA[i].arrivalTime, &jobA[i].duration) != EOF){
        i++;
    }

    fclose(filePtr);
    return i;
}

void FIFO(int totalJobs){
    int min = 0;
    Jobs temp;
    int startTime[totalJobs];// start time array
    int finishTime[totalJobs];// finish time array
    
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
        if( jobA[k].arrivalTime > time){
            // if no job available to run
            // jump to first job arrival time
            time = jobA[k].arrivalTime;
        }
        // set start time
        startTime[k] = time;
        for(int l=0; l < jobA[k].duration; l++){
            // increment time through each job
            time++;
        }
        // set finish time
        finishTime[k] = time;
    }
    
    // Output
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
    int startTime[totalJobs];// start time array
    int finishTime[totalJobs];// finish time array
 
    for (int i=0; i < totalJobs; i++){
        for (int i = 0 ; i < totalJobs - 1; i++){
            for (int j = 0 ; j < totalJobs - i - 1; j++) {
                if(jobA[j].arrivalTime == jobA[j+1].arrivalTime){
                    if (jobA[j].duration > jobA[j+1].duration) {
                        // SWAP
                        temp = jobA[j];
                        jobA[j] = jobA[j+1];
                        jobA[j+1] = temp;
                    }
                }
            }
        }
    }
    
    int time = 0;
    for(int g = 0; g < totalJobs; g ++){
        if(jobA[g].arrivalTime > time){
            // if no job available to run
            // Jump to first job start time
            time = jobA[g].arrivalTime;
        }
        startTime[g] = time;
        for(int l = 0; l < jobA[g].duration; l++){
            time++;
        }
        // set finish time
        finishTime[g] = time;
    }
    
    // Output
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
    int startTime[totalJobs];// Start time array
    int finishTime[totalJobs];// Finish time array
 
    for (int i=0; i < totalJobs; i++){
        for (int i = 0 ; i < totalJobs - 1; i++){
            for (int j = 0 ; j < totalJobs - i - 1; j++) {
                if(jobA[j].arrivalTime == jobA[j+1].arrivalTime){
                    // Opposite of SJF
                    if (jobA[j].duration < jobA[j+1].duration) { 
                        // SWAP
                        temp = jobA[j];
                        jobA[j] = jobA[j+1];
                        jobA[j+1] = temp;
                    }
                }
            }
        }
    }    
    
    int time = 0 ;
    
    for(int g = 0; g < totalJobs; g ++){
        if(jobA[g].arrivalTime > time){
            // if no job available to run
            // Jump to first job arrival time
            time = jobA[g].arrivalTime;
        }
        startTime[g] = time;
        for(int l = 0; l < jobA[g].duration; l++){
            time++;
        }
        // Set finish time
        finishTime[g] = time;
    }

    // Output
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
    
    // Copy over from jobA 
    Jobs jobC[totalJobs];
    for(int d = 0; d < (totalJobs); d++){
        jobC[d] = jobA[d];
    }
    
    // Initialize arrays
    for(int d = 0;d < totalJobs; d++){
        addedNum[d] = 0;
        startTime[d] = 0;
        finishTime[d] = 0;
        jobVet[d] = 0;
        done[d] = 0;
    }    
    // Iterate until we run out of jobs
    while(completedJobs < (totalJobs)){
        do{    
            if(jobC[i].duration == 0){// if job done goes down this branch
                if(done[i] == 1){}
                else{// first time done
                    done[i] = 1;
                    completedJobs++;
                    finishTime[i]=time;
                }
            }
            else{// increment time path
                if((jobC[i].arrivalTime) >= time){// if no job available to run
                     time = jobC[i].arrivalTime;
                }
                if(jobVet[i] == 1){// if job has run before
                    jobC[i].duration--;
                    time++;
                    if(jobC[i].duration < 1){// if job done goes down this branch
                        done[i] = 1;
                        completedJobs++;
                        finishTime[i]=time;
                    }
                }
                else if(jobVet[i] < 1){// if first run
                    jobVet[i] = 1;
                    startTime[i] = time;
                    jobC[i].duration--;
                    time++;
                    if(jobC[i].duration < 1){// if job done goes down this branch
                        done[i] = 1;
                        completedJobs++;
                        finishTime[i] = time;   
                    }
                }
            }
            if(jobC[i].arrivalTime <= time){
                if(addedNum[i] == 0){
                    addedNum[i] = 1;
                    numJobs++;
                }
            }
            i++;
            if(jobC[i].arrivalTime <= time){
                if(addedNum[i] == 0){
                    addedNum[i] = 1;
                    numJobs++;
                }
            }
            if(i == numJobs){
                i = 0;
            }
        }while(completedJobs < numJobs);
        // End Do-While
        
        
        if(numJobs < (totalJobs)){
            time = jobC[numJobs+1].arrivalTime - 1;
        }    
    }
    // Output
    for(int m=0; m < totalJobs; m++){
        printf("ID %d\t", jobC[m].id);
        printf("Start Time %d\t",startTime[m]);
        printf("Finish Time %d\t",finishTime[m]);
        printf("Total Time %d\t",(finishTime[m]-jobC[m].arrivalTime));
        printf("Response Time %d\t\n",(startTime[m]-jobC[m].arrivalTime));
    }
}

void STCF(int totalJobs){
    int time = 0;
    int completedJobs = 0;
    int startTime[totalJobs];
    int finishTime[totalJobs];
    int jobVet[totalJobs];
    int shortestTime = 9999;
    int shortRun = 0;
    int shortJob = 0;
    
    // Create a new Job array, copy over from jobA
    Jobs jobC[totalJobs];
    for(int d = 0; d < totalJobs; d++){
        jobC[d] = jobA[d];
    }
    for(int d = 0;d < totalJobs; d++){
        startTime[d] = 0;
        finishTime[d] = 0;
        jobVet[d] = 0;
    }    
    while(completedJobs < totalJobs){
        // While the current job duration is not zero
            for(int a = 0; a < totalJobs; a++){
                if(jobC[a].arrivalTime <= time)  
                    if(jobC[a].duration < shortestTime)
                        if(jobC[a].duration > 0){
                            shortestTime = jobC[a].duration;
                            shortJob = a;
                            shortRun = 1;
                        }
            }
            if(shortRun == 0){
                time++;
                continue;
            }
            if(jobVet[shortJob] < 1){//first start
                startTime[shortJob] = time;
                jobVet[shortJob] = 1;
            }
            time++;
            jobC[shortJob].duration--;
            shortestTime--;
            
            if(jobC[shortJob].duration < 1){
                completedJobs++;
                shortRun = 0;
                shortestTime = 9999;
                finishTime[shortJob] = time;
            }
    }
    
    // Output
    for(int m=0; m < totalJobs; m++){
        printf("ID %d\t", jobC[m].id);
        printf("Start Time %d\t",startTime[m]);
        printf("Finish Time %d\t",finishTime[m]);
        printf("Total Time %d\t",(finishTime[m]-jobC[m].arrivalTime));
        printf("Response Time %d\t\n",(startTime[m]-jobC[m].arrivalTime));
    }
}
