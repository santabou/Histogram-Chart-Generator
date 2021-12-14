#include<stdbool.h>
#include<stdio.h>
#include<string.h>
typedef struct svg
{
    char* svg;
    int height;
    int width;
    bool finalized;
} svg;

void str_to_svg(svg* psvg, char* text)
{
    int l = strlen(psvg->svg) + strlen(text) + 1;

    char* p = realloc(psvg->svg, l);

    if(p)
    {
        psvg->svg = p;
    }

    strcat(psvg->svg, text);
}

void num_to_svg(svg* psvg, int n)
{
    char sn[16];

    sprintf(sn, "%d", n);

    str_to_svg(psvg, sn);
}

svg* svg_create(int width, int height)
{
    svg* psvg = malloc(sizeof(svg));

    if(psvg != NULL)
    {
        *psvg = (svg){.svg = NULL, .width = width, .height = height, .finalized = false};

        psvg->svg = malloc(1);

        sprintf(psvg->svg, "%s", "\0");

        str_to_svg(psvg, "<svg width='");
        num_to_svg(psvg, width);
        str_to_svg(psvg, "px' height='");
        num_to_svg(psvg, height);
        str_to_svg(psvg, "px' xmlns='http://www.w3.org/2000/svg' version='1.1' xmlns:xlink='http://www.w3.org/1999/xlink'>\n");

        return psvg;
    }
    else
    {
        return NULL;
    }
}

void svg_finalize(svg* psvg)
{
    str_to_svg(psvg, "</svg>");

    psvg->finalized = true;
}

void svg_save(svg* psvg, char* filepath)
{
    if(!psvg->finalized)
    {
        svg_finalize(psvg);
    }

    FILE* fp;

    fp = fopen(filepath, "w");

    if(fp != NULL)
    {
        fwrite(psvg->svg, 1, strlen(psvg->svg), fp);

        fclose(fp);
    }
}

void svg_free(svg* psvg)
{
    free(psvg->svg);

    free(psvg);
}

//Max value in array
int max(int arr[], int arr_length) {
    int maximum = arr[0];   // start with the first value
    for (int i = 1; i < arr_length; i++) {
        if (arr[i] > maximum) {
            maximum = arr[i];   // new maximum
        }
    }
    return maximum;
}
int m = 300;
int n = 300;
void draw_histogram_svg( int freq[], int count, char* category,char arr[m][n])
{
    svg* psvg;
    psvg = svg_create(1000, 1000);

    if(psvg == NULL)
    {
        puts("psvg is NULL");
    }
    else
    {
//Bar Graph
        for(int i = 0; i < count;i++)
        {
            str_to_svg(psvg, "    <rect fill='");
            str_to_svg(psvg, "skyblue");
            str_to_svg(psvg, "' stroke='");
            str_to_svg(psvg, "black");
            str_to_svg(psvg, "' ry='");
            num_to_svg(psvg, 0);
            str_to_svg(psvg, "' rx='");
            num_to_svg(psvg, 0);
            str_to_svg(psvg, "' y ='");
            num_to_svg(psvg, 300+(50*i));
            str_to_svg(psvg, "' x='");
            num_to_svg(psvg, 300);
            str_to_svg(psvg, "' stroke-width='");
            num_to_svg(psvg, 2);
            str_to_svg(psvg, "px' width='");
            num_to_svg(psvg,50*freq[i]);
            str_to_svg(psvg, "' height='");
            num_to_svg(psvg, 40);

            str_to_svg(psvg, "' />\n");
        }

// Highest Frequency
        int max_freq = max(freq,count);

// Line X-axis
        str_to_svg(psvg, "    <line stroke='");
        str_to_svg(psvg, "black");
        str_to_svg(psvg, "' stroke-width='");
        num_to_svg(psvg, 2);
        str_to_svg(psvg, "px' y2='");
        num_to_svg(psvg, 300+(50*count));
        str_to_svg(psvg, "' x2='");
        num_to_svg(psvg, 300);
        str_to_svg(psvg, "' y1='");
        num_to_svg(psvg, 300+(50*count));
        str_to_svg(psvg, "' x1='");
        num_to_svg(psvg, 310+(50*max_freq));
        str_to_svg(psvg, "' />\n");

// Line Y-axis
        str_to_svg(psvg, "    <line stroke='");
        str_to_svg(psvg, "black");
        str_to_svg(psvg, "' stroke-width='");
        num_to_svg(psvg, 2);
        str_to_svg(psvg, "px' y2='");
        num_to_svg(psvg, 290);
        str_to_svg(psvg, "' x2='");
        num_to_svg(psvg, 300);
        str_to_svg(psvg, "' y1='");
        num_to_svg(psvg, 300+(50*count));
        str_to_svg(psvg, "' x1='");
        num_to_svg(psvg, 300);
        str_to_svg(psvg, "' />\n");

//Frequency Label
        str_to_svg(psvg, "    <text x='");
        num_to_svg(psvg, (250+(50*max_freq)/2));
        str_to_svg(psvg, "' y = '");
        num_to_svg(psvg, (460+(50*count)/2));
        str_to_svg(psvg, "' stroke='");
        str_to_svg(psvg, "black");
        str_to_svg(psvg, "' fill='");
        str_to_svg(psvg, "black");
        str_to_svg(psvg, "' font-size='");
        num_to_svg(psvg, 20);
        str_to_svg(psvg, "px'>");
        str_to_svg(psvg, "Frequency");
        str_to_svg(psvg, "</text>\n");

// Categories Label
        str_to_svg(psvg, "    <text x='");
        num_to_svg(psvg, 250);
        str_to_svg(psvg, "' y = '");
        num_to_svg(psvg, 280);
        str_to_svg(psvg, "' stroke='");
        str_to_svg(psvg, "black");
        str_to_svg(psvg, "' fill='");
        str_to_svg(psvg, "black");
        str_to_svg(psvg, "' font-size='");
        num_to_svg(psvg, 20);
        str_to_svg(psvg, "px'>");
        str_to_svg(psvg, category);
        str_to_svg(psvg, "</text>\n");

        for(int i = 0; i < count;i++)
        {
            str_to_svg(psvg, "    <text x='");
            num_to_svg(psvg, 200);
            str_to_svg(psvg, "' y = '");
            num_to_svg(psvg, 330+(50*i));
            str_to_svg(psvg, "' stroke='");
            str_to_svg(psvg, "black");
            str_to_svg(psvg, "' fill='");
            str_to_svg(psvg, "black");
            str_to_svg(psvg, "' font-size='");
            num_to_svg(psvg, 20);
            str_to_svg(psvg, "px'>");
            char text[300];
            sprintf(text, "%s", arr[i]);
            str_to_svg(psvg, text);
            str_to_svg(psvg, "</text>\n");

            str_to_svg(psvg, "' />\n");
        }


        svg_finalize(psvg);
        svg_save(psvg, "histogram.svg");
        svg_free(psvg);
    }
}