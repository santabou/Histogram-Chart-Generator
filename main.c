//
// Created by Thitiwat Sornmanee on 16/11/2021 AD.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "svg.c"

int main()
{
    FILE* data = fopen("/Users/thitiwatsornmanee/Desktop/Histogram/Data.csv", "r");
    if (data == NULL)
    {
        printf("File not found");
        exit(1);
    }
    else
    {
        char sample_name[200];
        char categories[200];
        char line[200];
        int count = 0;
        char storage[200][10];
        char database[200][10];
        char database1D[200];
        char copy[10];
        int freq[200];
        int pass = 0;
        int elements = 0;
        {
            fgets(line, sizeof(line), data);
            char *token1 = strtok(line,",");
            strcpy(sample_name, token1);
            token1 = strtok(NULL,",");
            strcpy(categories,token1);
//            printf("%s %s",x_axis,y_axis);
            while (fgets(line, sizeof(line), data))
            {
                char *token2 = strtok(line,",");
                token2 = strtok(NULL,",");
                token2[strcspn(token2, "\r\n")] = 0;
                strcpy(copy, token2);
                for (int i = 0; i <=count   ; i++)
                {
                    if(strcmp(copy, database[i]) == 0)
                        pass = 1;
                    strcpy(storage[count], token2);
                }
                if(pass == 0)
                {
                    strcpy(database[elements], token2);
                    elements++;
                }
                count++;
                pass = 0;
            }

        }

        int counter = 0;
        for (int i = 0; i <=elements; i++)
        {
            for (int j = 0; j <= count ; j++)
            {
                if (*database[i] == *storage[j])
                    counter++;
            }
//            printf("%d",counter);
            freq[i] = counter;
            counter = 0;
        }
        for (int i = 0; i < (elements ); i++)
        {
            printf(" Categories: %s \n Freq: %d \n", database[i], freq[i]);
        }
        draw_histogram_svg(freq, elements, categories,*database);
    }
    fclose(data);
}
//remove duplicate
//count for each element
//svg