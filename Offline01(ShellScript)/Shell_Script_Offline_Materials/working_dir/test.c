#include <stdio.h>

typedef struct _student
{
    int stdid;
    char name[100];
    int phy, chem, math;
} student;

int n;
student std[10];

int main()
{
    FILE *fstd, *fphy, *fmath, *fchem;
    FILE *fout;

    fstd = fopen("std.txt", "r");
    if (!fstd)
    {
        printf("Cannot open std.txt\n");
        return 1;
    }
    fphy = fopen("phy.txt", "r");
    if (!fphy)
    {
        printf("Cannot open phy.txt\n");
        return 1;
    }
    fchem = fopen("chem.txt", "r");
    if (!fchem)
    {
        printf("Cannot open chem.txt\n");
        return 1;
    }
    fmath = fopen("math.txt", "r");
    if (!fmath)
    {
        printf("Cannot open math.txt\n");
        return 1;
    }
    fscanf(fstd, "%d", &n);
    for (int i = 0; i < n; i++)
    {
        fscanf(fstd, "%d %s", &std[i].stdid, std[i].name);
    }
    for (int i = 0; i < n; i++)
    {
        int id, mark;
        fscanf(fchem, "%d %d", &id, &mark);
        for (int j = 0; j < n; j++)
        {
            if (id == std[j].stdid)
            {
                std[i].chem = mark;
                break;
            }
        }
        fscanf(fmath, "%d %d", &id, &mark);
        for (int j = 0; j < n; j++)
        {
            if (id == std[j].stdid)
            {
                std[i].math = mark;
                break;
            }
        }
        fscanf(fphy, "%d %d", &id, &mark);
        for (int j = 0; j < n; j++)
        {
            if (id == std[j].stdid)
            {
                std[i].phy = mark;
                break;
            }
        }
    }

    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++)
        {
            if (std[j].stdid > std[j + 1].stdid)
            {
                student temp = std[j];
                std[j] = std[j + 1];
                std[j + 1] = temp;
            }
        }
    }

    fout = fopen("out.txt", "a");
    if (!fout)
    {
        printf("Cannot open file out.txt\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(fout, "%d %s %d %d %d\n", std[i].stdid, std[i].name, std[i].phy, std[i].chem, std[i].math);
    }

    fclose(fstd);
    fclose(fchem);
    fclose(fmath);
    fclose(fphy);
    fclose(fout);

    return 0;
}