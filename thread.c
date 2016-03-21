/*
 #Family Name: Sarathmohan
 #Given Name: Nidhi
 #Section: Z
 #Student number: 211934619
 #cse login: cse22011
 
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>

pthread_t *thread;



static int comp(const void *m, const void *n)
{                                                               //This is my compare function, whose values(-1,1 or 0) I use in my qsort function later on in my code
    if (*(double*)m < *(double*)n)
        return -1;
    else if (*(double*)m > *(double*)n)
        return 1;
    else
        return 0;
}
char * calc(char *files)
{
    
    int i,senMax1,senMax2,senMax3,senMax4,senMax5,senMax6;
    double cosine;
    int counter = 0;
    
    char * final = (char *) malloc(sizeof(final));
    FILE *file = fopen(files,"r");                              // depending on the value of i, file pointer points to the text file at position i and reads it.
    
    if(file == NULL)
    {
        
        char *save = "File not found\n";        //if it points to a file that does not exist, for example the .txt file is not in the same folder as rvw.c then the file pointer points to NULL
        return save;
        
    }
    else
        
    {
        int y,w,c;
        char *pointer;
        char buffer[1000][20];
        double numbers[499500];             //stores cosine values.
        char temp[1000][20];                //stores all the words
        char temp1[1000][20];               //stores numbers in char version
        double numArr[1000][100];           //stores all numbers in double version
        double numerator;
        int anCount = 0;
        float nums,square1,square2,denom;
        
        while(fscanf(file,"%s",buffer[y]) >= 0)
        {
            strcpy(temp[y],buffer[y]);
            
            int count = 0;
            while(count < 100)
            {
                fscanf(file,"%s",buffer[y]);
                strcpy(temp1[y],buffer[y]);
                nums = atof(temp1[y]);
                numArr[y][count] = nums;
                count++;
            }
            y++;
            
            
            
        }
        y = 0;
        /*A nested for loop to go through numArr that stores all the decimal numbers in order to find the cosine value*/
        
        while(anCount < 1000)
        {
            for(w = 1;(w + anCount) < 1000;w++)
            {
                for(c = 0; c < 100;c++)
                {
                    
                    numerator = numerator + (numArr[anCount][c]*numArr[anCount+w][c]);            //numerator variable stores the value of the numerator.
                    square1 = square1 + (numArr[anCount][c]*numArr[anCount][c]);                  //in the cosine formula, there are squares for x and y values in the denominator so I stored them in square variables
                    square2 = square2 + (numArr[anCount+w][c]*numArr[anCount+w][c]);              // I keep adding it each time it goes through the for loop because there is a summation sign in the formula
                    
                }
                denom = sqrt(square1) * sqrt(square2);                                        //denominator variable stores the value of the denominator.
                cosine = numerator/denom;                                                     // cosine varibale saves the value of the cosine.
                
                numbers[counter++] = cosine;                                                 // then I save each value of the cosine into the numbers array. I sort this array later on.
                
                
                square1 = 0;                                                                //intializing all of these variables to zero, so it does not keep adding values over and over again
                square2 = 0;
                numerator = 0;
                denom = 0;
                cosine = 0;
                
            }
            anCount++;
        }
        
        
        qsort(numbers,499500,sizeof(double),comp);                                 //sorting the array so I can access the last,second last and third last element from the array as max, second max and thrid max respectively.
        
        /*Made this new for loop to find the cosine values again so I can compare it with the last three elements from numArr*/
        anCount = 0;
        while(anCount < 1000)
        {
            for(w = 1;(w + anCount) < 1000;w++)
            {
                for(c = 0; c < 100;c++)
                {
                    
                    numerator = numerator + (numArr[anCount][c]*numArr[anCount+w][c]);
                    square1 = square1 + (numArr[anCount][c]*numArr[anCount][c]);
                    square2 = square2 + (numArr[anCount+w][c]*numArr[anCount+w][c]);
                }
                denom = sqrt(square1) * sqrt(square2);                                 // since I am using a math function sqrt here and in the above for loop, I used gcc rvw.c -lm to compile
                cosine = numerator/denom;
                if(cosine == numbers[499499])                                         // comparing cosine to the last value
                {
                    senMax1 = anCount;
                    senMax2 = (anCount+w);
                    
                }
                else if(cosine == numbers[499498])                                   //comparing cosine to the second last value
                {
                    senMax3 = anCount;
                    senMax4 = (anCount+w);
                }
                else if(cosine == numbers[499497])                                  // comparing cosine to the thrid last value
                {
                    senMax5 = anCount;
                    senMax6 = (anCount+w);
                }
                
                square1 = 0;
                square2 = 0;
                numerator = 0;
                denom = 0;
                cosine = 0;
                
            }
            anCount++;
        }                 //line that prints the output
        snprintf(final, 100, "%s %s %s %.6f %s %s %.6f %s %s %.6f ",files,temp[senMax1],temp[senMax2],numbers[499499],temp[senMax3],temp[senMax4],numbers[499498],temp[senMax5],temp[senMax6],numbers[499497]);
        
        counter = 0;
        y = 0;
        senMax1 = 0;
        senMax2 = 0;
        senMax3 = 0;
        senMax4 = 0;
        senMax5 = 0;
        senMax6 = 0;
        return final;
    }
}


void callFunction(void *para)
{
    char *name = (char*)malloc(sizeof(char));
    name = (char*) para;
    char *finalPrint = (char *)malloc(sizeof(char));
    /*call method calc on name*/
    finalPrint = calc(name);
    printf("%s\n",finalPrint);
}

int main(int argc,char *argv[])
{
    
    thread = malloc((argc-1)*sizeof(pthread_t));
    
    
    int mo,tt;
    
    for(mo=1;mo < argc; mo++)
    {
        
        
        /*allocating memory for the file name*/
        char* fileNames = (char*)malloc(sizeof(char));
        
        /*Assigning the file name from argv*/
        fileNames = argv[mo];
        /*Creating threads*/
        
        pthread_create (&thread[mo], NULL, (void *) callFunction, (void *) fileNames);
        
    }
    /*waiting for all the threads to terminate*/
    for(tt=1;tt < argc; tt++)
    {
        pthread_join(thread[tt], NULL);
    }
    
    return(0);
    
}
