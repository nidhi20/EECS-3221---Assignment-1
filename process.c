/*
 #Family Name: Sarathmohan
 #Given Name: Nidhi
 #Section: Z
 
 
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

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
    
    int senMax1,senMax2,senMax3,senMax4,senMax5,senMax6;
    double cosine;
    int counter = 0;
    char buffer[1000000];
    char * final = (char *) malloc(sizeof(final));
    FILE *file = fopen(files,"r");                              // depending on the value of i, file pointer points to the text file at position i and reads it.
    
    if(file == NULL)
    {
        
        printf("File not found");        //if it points to a file that does not exist, for example the .txt file is not in the same folder as rvw.c then the file pointer points to NULL
        printf("\n");
        
    }
    else
        
    {
        int y,w,c;
        char *pointer;
        double numbers[499500];             //stores cosine values.
        char temp[1000][20];                //stores all the words
        char temp1[1000][20];               //stores numbers in char version
        double numArr[1000][100];           //stores all numbers in double version
        double numerator;
        int anCount = 0;
        float nums,square1,square2,denom;
        
        while(fgets(buffer, sizeof(buffer), file) != NULL)
        {
            
            pointer = strtok(buffer," ");                        //strtok divides every token in the buffer array that are separated by a space delimiter. In the first line pointer points at the first string. Every first string in .txt files are words. So I decided to store every first attempt by the pointer in each line into a temp[y] array. As fgets encounters a new line it goes back to while. So as the while increases I used varibale y as a counter to save each new first pointed string on a line into char temp[y] using sscanf.
            
            
            
            sscanf(pointer,"%s", temp[y]);        //value from the pointer stored inside temp array that consists words.
            int count = 0;
            while(count < 100)
            {
                pointer = strtok(NULL," ");     //When on a particular line strtok separates every string separated by a space and this time since the string is a number I stored it in a different array called temp1[y]. I used the same variable y as the word and these 100 numbers are on the same row. I used the while loop where count < 100 so the pointer goes through all the 100 numbers.
                
                sscanf(pointer,"%s", temp1[y]);       //value  from the pointer stored inside temp1[y] array that stores numbers represented in string version.
                nums = atof(temp1[y]);                //since my pointer was a char I could not use sscanf to store a char value into a double array. Hence I used a char array temp1 to store string values of the numbers. After doing that I used atof function that changes string values into double values. I stored every changed string to double value in the nums variable.
                
                numArr[y][count] = nums;              // I then assigned the value of nums to numArr array. Stepping from row to row and column to column.
                
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

int main(int argc,char *argv[])
{
    int i;
    char *temp = (char *)malloc(sizeof(char));
    char *splitCount = (char *)malloc(sizeof(char) * 10000000000);
   
    
    int p[2], j;
    int pid;
    
    /* open pipe */
    
    if(pipe(p) == -1)
    {    perror("pipe call error");
        exit(1);
    }
    for (i=1;i < argc; i++)
    {
        pid = fork();
        
        if (pid < 0)
        {
            perror("error: fork call");
            exit(2);
        }
        
        if(pid == 0)
        {
            /* if child then write down pipe */
            close(p[0]);  /* first close the read end of the pipe */
            printf(" \n"); /* My code prints fine without this statment on Mac but not on Linux. I discussed this with professor. On linux, without this printf statement, my code ternimates with no output. But on mac it gives me the right output.*/
            temp = calc(argv[i]);
            write(p[1], temp, 1000);
            exit(0);
            
        }
    }
    for (i=1;i < argc; i++)
    {
        
        if (pid > 0)/* parent reads pipe */
        {
            close(p[1]);  /* first close the write end of the pipe */
            
            read(p[0], splitCount, 1000);
            
            printf("%s",splitCount);
        }
    }
}
