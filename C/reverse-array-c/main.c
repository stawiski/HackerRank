#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num, *arr, i;
    scanf("%d", &num);
    arr = (int*) malloc(num * sizeof(int));
    for(i = 0; i < num; i++) {
        scanf("%d", arr + i);
    }

    /* Write the logic to reverse the array. */
    if (num > 1) {
        /* Compute array's half size. */
        int num_half = ((num % 2) == 1) ? ((num - 1)/2) : (num/2);
        
        /* Loop through array's items up to half of array size. */
        for (int j = 0; j < num_half; j++) {
            /* Remember value at index j. */
            int tmp = *(arr + j);
            /* Swap array value at index "j" with array value at index "(num - 1) - j" (reverses the order of the items). */
            *(arr + j) = *(arr + (num - 1) - j);
            *(arr + (num - 1) - j) = tmp;
        }
    }

    /* Print the reversed array. */
    for(i = 0; i < num; i++)
        printf("%d ", *(arr + i));
    return 0;
}
