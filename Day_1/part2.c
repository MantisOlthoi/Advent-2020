#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

int main(void)
{
    size_t numValues = 0;

    FILE *fp = fopen("day1_input.txt", "r");
    assert(fp);

    // Let's just go ahead and figure out how many numbers there are.
    char *block = (char *)(malloc(4096));
    assert(block);
    while(!feof(fp))
    {
        size_t bytesRead = fread(block, 1, 4096, fp);
        if (bytesRead == 0)
        {
            if (ferror(fp))
            {
                perror("Failed to read input file while trying to get newline count");
                exit(1);
            }
            continue;
        }

        char *newlinePos = block;
        while((newlinePos = strchr(newlinePos, '\n') + 1) != (char *)1)
            numValues++;
    }
    free(block);
    numValues++; // Last value doesn't have a newline after it.

    // Rewind the file back to the start
    fseek(fp, 0, SEEK_SET);

    // Read in the values
    int *values = (int *)(malloc(sizeof(int[numValues])));
    assert(values);
    for (int i = 0; !feof(fp); i++)
    {
        int valuesRead = fscanf(fp, "%d", &values[i]);
        if (valuesRead != 1)
        {
            if (feof(fp)) break;
            perror("Failed to read in integer values from input file");
            exit(1);
        }
    }
    fclose(fp);

    int i, j, k;
    for (i = 0; i < numValues - 2; i++)
    {
        for (j = i + 1; j < numValues - 1; j++)
        {
            for (k = j + 1; k < numValues; k++)
            {
                if (values[i] + values[j] + values[k] == 2020)
                {
                    printf("%d * %d * %d = %d\n", values[i], values[j], values[k], values[i] * values[j] * values[k]);
                    exit(0);
                }
            }
        }
    }

    fprintf(stderr, "Failed to find three values that summed to 2020!\n");
    free(values);

    return 1;
}
