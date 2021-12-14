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
        char sample_name[300];
        char categories[300];
        char line[300];
        int count = 0;
        char storage[300][300];
        char database[300][300];
        char copy[300];
        int freq[300];
        int pass = 0;
        int elements = 0;
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
        draw_histogram_svg(freq, elements, categories,database);
    }
    fclose(data);
}
//remove duplicate
//count for each element
//svg