#include <stdio.h>
#include <stdlib.h>

// 1. Write a program that reads 2 arrays and merges the two arrays into third array. 
// Before merging, sorte the 2 arrays in ascending order.

void read_array_length(int *length, char *message)
{
	// Read the length of the array from the console. 
	printf("Please enter the length of the %s array: ", message);
	scanf("%d", length);
}

void read_array(int *array, int *length)
{
	// Read the values of the array from the console. 
	for(int i = 0; i < *length; i++)
	{
		printf("Enter value no. %d: ", i + 1);
		scanf("%d", (array + i));
	}
}

void quick_sort(int *array, int left, int right)
{
	// Sort the values of the array using Quicksort. 
	if(left < right)
	{
		int middle = (left + right) / 2;

		int *aux = malloc(sizeof(int));
		*aux = *(array + left);
		*(array + left) = *(array + middle);
		*(array + middle) = *aux;

		int i = left, j = right, d = 0;

		while(i < j)
		{
			if(*(array + i) > *(array + j))
			{
				*aux = *(array + i);
				*(array + i) = *(array + j);
				*(array + j) = *aux;
				d = 1 - d;
			}
			i += d;
			j -= 1 - d; 
		}
		quick_sort(array, left, i - 1);
		quick_sort(array, i + 1, right);
	}
}

void merge(int *first_array, int *second_array, int *final_array, int *first_array_len, int *second_array_len, int *final_array_len)
{
	// Merge two sorted arrays into one. 
	int i = 0, j = 0;

	*final_array_len = 0;

	while(i < *first_array_len && j < *second_array_len)
	{
		if(*(first_array + i) < *(second_array + j))
		{
			*(final_array + *final_array_len) = *(first_array + i);
			i++;
		}
		else
		{
			*(final_array + *final_array_len) = *(second_array + j);
			j++;
		}
		(*final_array_len)++;
	}

	while(i < *first_array_len)
	{
		*(final_array + *final_array_len) = *(first_array + i);
		i++;
		(*final_array_len)++;
	}

	while(j < *second_array_len)
	{
		*(final_array + *final_array_len) = *(second_array + j);
		j++;
		(*final_array_len)++;
	}
}

void display_array(int *array, int *array_len)
{
	// Print a given array. 
	printf("{");
	for(int i = 0; i < *array_len; i++)
	{
		printf("%d ", *(array + i));
	}
	printf("}\n");
}

int main()
{
	// Allocate memory for the length of the first array and read it. 
	int *first_array_len = malloc(sizeof(int));
	read_array_length(first_array_len, "first");

	// Allocate memory for the first array and read it. 
	int *first_array = malloc(*first_array_len * (sizeof(int)));
	read_array(first_array, first_array_len);

	// Allocate memory for the length of the second array and read it. 
	int *second_array_len = malloc(sizeof(int));
	read_array_length(second_array_len, "second");

	// Allocate memory for the second array and read it. 
	int *second_array = malloc(*second_array_len * (sizeof(int)));
	read_array(second_array, second_array_len);

	// Sort the arrays.
	quick_sort(first_array, 0, *first_array_len - 1);
	quick_sort(second_array,0, *second_array_len - 1);

	// Allocate memory for the length of the final array and the array itself. 
	int *final_array_len = malloc(sizeof(int));
	int *final_array = malloc((*first_array_len + *second_array_len) * sizeof(int));

	// Merge the two sorted arrays. 
	merge(first_array, second_array, final_array, first_array_len, second_array_len, final_array_len);

	// Display the final array. 	
	printf("\nThe array obtained by the merging of the two arrays is:\n");
	display_array(final_array, final_array_len);

	return 0;
}