#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void    print_set(int *power_set, int size_powerset)
{
    int i = 0;

    while (i < size_powerset)
    {
        printf("%d", power_set[i]);
        if (i < size_powerset - 1)
            printf(" ");
        i++;
    }
    printf("\n");
}

void    powerset(int *set, int size, int target, int index, int *power_set, int size_powerset)
{
    int sum;
    int i;

    if (index == size)
    {
        sum = 0;
        i = 0;
        while (i < size_powerset)
        {
            sum = sum + power_set[i];
            i++;
        }
        if (sum == target)
            print_set(power_set, size_powerset);
        return ;
    }
    power_set[size_powerset] = set[index];
    powerset(set, size, target, index + 1, power_set, size_powerset + 1);
    powerset(set, size, target, index + 1, power_set, size_powerset);
    return ;
}

int main(int argc, char **argv)
{
    int target;
    int *set;
    int *power_set;
    int size;
    int i = 0;

    if (argc < 3)
        return (1);
    target = atoi(argv[1]);
    size = argc - 2;
    set = malloc(sizeof(int) * size);
    if (!set)
        return (1);
    power_set = malloc(sizeof(int) * size);
    if (!power_set)
        return (1);
    while (i < size)
    {
        set[i] = atoi(argv[i + 2]);
        i++;
    }
    powerset(set, size, target, 0, power_set, 0);
    free(set);
    free(power_set);
    return (0);
}