//
// Created by Thitiwat Sornmanee on 16/11/2021 AD.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "svg.c"

int main()
{
    FILE* data = fopen("/Users/thitiwatsornmanee/Desktop/Histogram-Chart-Generator/Data.csv", "r");
    if (data == NULL)
    {
        printf("File not found");
        exit(1);
    }
    else
    {
        fseek(data, 0L, SEEK_END);
        long int size = ftell(data);
        fseek(data, 0L, SEEK_SET);
        char sample_name[size];
        char categories[size];
        char line[size];
        int count = 0;
        char storage[size][size];
        char database[size][size];
        char copy[size];
        int pass = 0;
        int elements = 0;
        int freq[elements];
        {
//     get histogram categories title from csv
            fgets(line, sizeof(line), data);
            char *token1 = strtok(line,",");
            strcpy(sample_name, token1);
            token1 = strtok(NULL,",");
            strcpy(categories,token1);
//     get histogram categories title from csv

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
            freq[i] = counter;
            counter = 0;
        }
        for (int i = 0; i < (elements ); i++)
        {
            printf(" Categories: %s \n Freq: %d \n", database[i], freq[i]);
        }
        draw_histogram_svg(freq, elements, categories,database,size);
    }
    fclose(data);
}
//remove duplicate
//count for each element
//svg