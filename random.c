#include <stdio.h>
#include <stdlib.h>
#define ARRAY_LENGTH 10

int    main(void)
{
    int *list1;
    int *list2;
    int i;
    list1 = malloc(sizeof(int) * ARRAY_LENGTH);
    list2 = malloc(sizeof(int) * ARRAY_LENGTH);
    for (i = 0; i <= ARRAY_LENGTH-1; i++)
    {
        list1[i] = rand() % 100; // use rand() function to get the random number
        list2[i] = list1[i]+ 1 + rand() % 100 ;
	}
    printf("array_lower1[ARRAY_LENGTH] = {");
    for (i = 0; i <= ARRAY_LENGTH-1; i++)
    {
        printf("%i, ",list1[i]);
    }
    printf("}\n");

    printf("array_upper1[ARRAY_LENGTH] {");
    for (i = 0; i <= ARRAY_LENGTH-1; i++)
    {
        printf("%i, ",list2[i]);
    }
    printf("}\n");
    free (list1);
    free (list2);
    return (0);
}