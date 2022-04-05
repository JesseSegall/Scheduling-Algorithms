#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

const int LEFT = 0;
const int RIGHT = 1;
const int LOWER_CYLINDER = 0;
const int UPPER_CYLINDER = 4999;

int* removeVal(int* arr, int* arrSzPtr, int val) {
    if (arr == NULL)
            return NULL;
    int sz = *arrSzPtr;

    if (sz == 1) {
            *arrSzPtr = 0;
            free(arr);
            return NULL;
    }
    int ind = -1;
    for (int i = 0; i<sz; i++) {
            if(arr[i]==val)
                    ind = i;
    }
    if (ind==-1) // not found
            return arr;
    int newSz = sz-1;
    *arrSzPtr = newSz;
    int* newArr = (int*)malloc(sizeof(arr[0])*newSz);
    for (int i = 0, j = 0; i<newSz; i++, j++) {
            if (arr[j]==val)
                    j++;
            newArr[i]=arr[j];
    }

    free(arr);
    return newArr;
}

int* copyArr(int arr[], int arrSz, int* newSzPtr) {
    *newSzPtr = arrSz;
    int* newArr = (int*)malloc(sizeof(int)*arrSz);
    for (int i=0; i<arrSz; i++) {
            newArr[i]=arr[i];
    }
    return newArr;
}

void sort(int* arr, int arrSz) {
    int min=arr[0];
    int minInd=0;
    int temp;
    for (int i = 0; i<arrSz; i++) {
            min=arr[i];
            minInd=i;
            for (int j = i; j<arrSz; j++) {
                    if(arr[j]<min){
                            min = arr[j];
                            minInd = j;
                    }
            }
            temp = arr[i];
            arr[i]=arr[minInd];
            arr[minInd] = temp;
    }
}

void printArr(int* arr, int arrSz) {
    for (int i = 0; i<arrSz;i++){
            printf("%d\n", arr[i]);
    }
    printf("\n");
}

int in(int* arr, int arrSz, int val) {
    for (int i = 0; i<arrSz; i++) {
        if (arr[i]==val)
            return 1;
    }
    return 0;
}

int SSTF(int requests[], int requestsSz, int initialPosition){ 

    int* rq = NULL;
    int rqSz;
    rq=copyArr(requests, requestsSz, &rqSz);
 
    
    int position = initialPosition;
    int movement = 0;
    
    while(rqSz > 0){
        int closest = abs(position - rq[0]);
        int closestIndex = 0;
        for(int i = 1; i < rqSz; i++){
            if (abs(position - rq[i]) < closest){
                closest = abs(position - rq[i]);
                closestIndex = i;
                
            }
        }

        movement += abs(position - rq[closestIndex]);
        position = rq[closestIndex];
        printf("Servicing %d\n", position);
        rq = removeVal(rq, &rqSz, position);

    }
    
    free(rq);
    return movement;
    
}


int FCFS(int requests[], int requestsSz, int initialPosition){
    int position = initialPosition;
    int movement = 0;
   
    for(int i = 0; i < requestsSz; i++){
        
        movement += abs(position - requests[i]);
        position = requests[i];
                printf("Servicing %d\n", position);
    }    
    return movement;
}

int SCAN(int requests[], int requestsSz, int initialPosition){
    int* rq = NULL;
    int rqSz;
    rq=copyArr(requests, requestsSz, &rqSz);
    int direction = RIGHT;
    int position = initialPosition;
    int movement = 0;

    while(rqSz > 0) {
        if ( in(rq, rqSz, position) ) {
                printf("Servicing %d\n", position);
                    rq = removeVal(rq, &rqSz, position);
                    if (rqSz==0)
                            break;
            }

        if(direction == LEFT && position > LOWER_CYLINDER){
            position -= 1;
        }

        if(direction == RIGHT && position < UPPER_CYLINDER){
            position += 1;
        }

        movement += 1;

        if(position == 0){
            direction = RIGHT;
        }
        if(position == UPPER_CYLINDER){
            direction = LEFT;
        }

    }
    free(rq);
    return movement;

}


int C_SCAN(int requests[], int requestsSz, int initialPosition) {

    int* rq = NULL;
    int rqSz;
    rq=copyArr(requests, requestsSz, &rqSz);
 
    int position = initialPosition;
    int movement = 0;

    while(rqSz > 0){
        if ( in(rq, rqSz, position) ) {
                printf("Servicing %d\n", position);
                    rq = removeVal(rq, &rqSz, position);
                    if (rqSz==0)
                            break;
            }
        if (position != UPPER_CYLINDER) {  // Needed in case initialPosition is 4999
                movement += 1;
                position +=1;
        }
        if (position == UPPER_CYLINDER){
            position = 0;
            movement += UPPER_CYLINDER;
        }
        
    }
    free(rq);
    return movement;

}



int LOOK(int requests [], int requestsSz,  int initialPosition) {
    int* rq = NULL;
    int rqSz;
    rq=copyArr(requests, requestsSz, &rqSz);
    int direction = RIGHT; // left is 0, right is 1
    sort(rq, rqSz);
    int position = initialPosition;
    int movement = 0;
    while(rqSz>0) {
            if (position<=rq[0])
                    direction=RIGHT;
            if (position>=rq[rqSz-1])
                    direction=LEFT;
            if ( in(rq, rqSz, position) ) {
                printf("Servicing %d\n", position);
                    rq = removeVal(rq, &rqSz, position);
                    if (rqSz==0)
                            break;
            }
            if (direction==LEFT && position>LOWER_CYLINDER)
                    position-=1;
            if (direction==RIGHT && position<UPPER_CYLINDER)
                    position+=1;
            movement+=1;
    }
    free(rq);
    return movement;

}

int C_LOOK(int requests [], int requestsSz,  int initialPosition) {
    int* rq = NULL;
    int rqSz;
    rq=copyArr(requests, requestsSz, &rqSz);
    sort(rq,rqSz);
    int position = initialPosition;
    int movement = 0;
    while (rqSz>0) {
        if ( in(rq, rqSz, position) ) {
                printf("Servicing %d\n", position);
                    rq = removeVal(rq, &rqSz, position);
                    if (rqSz==0)
                            break;
            }
        if (position > rq[rqSz-1]) {
            movement+=abs(position-rq[0]);
            position=rq[0];
        }
        else {
            movement+=1;
            position+=1;
        }
        
    }
    free(rq);
    return movement;
}

int main(int argc, char* argv[]) {
    if (argc<2) {
       printf("Enter the initial position!\n");
       return -1;
    }
    int initialPosition = atoi(argv[1]);
    if (initialPosition<LOWER_CYLINDER || initialPosition >UPPER_CYLINDER) {
        printf("Invalid initial position!\n");
        return -1;
    }
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int requestsSz = sizeof(requests)/sizeof(requests[0]);
    printf("\n\tFCFS = %d\n\n", FCFS(requests, requestsSz, initialPosition));
    printf("\n\tSSTF = %d\n\n", SSTF(requests, requestsSz, initialPosition));
    printf("\n\tSCAN = %d\n\n", SCAN(requests, requestsSz, initialPosition));
    printf("\n\tC_SCAN = %d\n\n", C_SCAN(requests, requestsSz, initialPosition));
    printf("\n\tLOOK = %d\n\n", LOOK(requests, requestsSz, initialPosition));
    printf("\n\tC_LOOK = %d\n\n", C_LOOK(requests, requestsSz, initialPosition));
    
    printf("Pausing program, press Enter to quit\n");
    int leave = 0;
    char in;
    while (leave != 1) {
        in = getc(stdin);
        if (in=='\n')
            leave=1;
    }
}