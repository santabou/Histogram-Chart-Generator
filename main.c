//
// Created by Thitiwat Sornmanee on 16/11/2021 AD.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "function.c"
int main()
{
    FILE* data = fopen("/Users/thitiwatsornmanee/Desktop/C Programming Lab/Histrogram-chart-generator1/Data.csv", "r");
    if (data == NULL)
    {
        printf("File not found");
        exit(1);
    }
    else
    {
        char line[200];
        int count = 0;
        char database[2000][10];
        char copy[10];
        int pass = 0;
        {
            while (fgets(line, sizeof(line), data))
            {
                char *token = strtok(line,",");
                token = strtok(NULL,",");
                strcpy(copy, token);
                for (int i = 0; i <=count   ; i++)
                {
                    if(strcmp(copy, database[i]) == 0)
                        pass = 1;

                }
                if(pass == 0)
                    strcpy(database[count], token);
                count++;
                pass = 0;
            }

        }


        for (int i = 0; i <=count; i++)
        {
            printf("%s",database[i]);
        }

    }
    fclose(data);
}
//remove duplicate
//count for each element
//svg