#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2. For a list of students, each having name, registration_number and 5 marks for current semester, 
// sort them in descending order of the average of the 5 marks, and display the students with identical average in alphabetical order.

struct Student
{
	// A student has a name(single-word), an ID and a set of 5 grades. 
	char name[10];
	int registration_number;
	int marks[5];	
};

struct Student read_student()
{
	// Read the name, only a single word. 
	printf("\nPlease enter the name of the student: ");
	char *name = malloc(10 * sizeof(char));
	scanf("%s", name);

	// Read the ID.
	printf("Please enter the registration number of the student: ");
	int *id = malloc(sizeof(int));
	scanf("%d", id);

	// Read the 5 grades. 
	printf("Please enter 5 grades for the student:\n");
	int *grades = malloc(5 * sizeof(int));
	for(int i = 0; i < 5; i++)
	{
		printf("Grade No.%d: ", i + 1);
		scanf("%d", (grades + i));
	}

	// Bring all the data together. 
	struct Student new_student;
	
	strcpy(new_student.name, name);
	new_student.registration_number = *id;
	for(int i = 0; i < 5; i++)
	{
		new_student.marks[i] = *(grades + i);
	}

	return new_student;
}

float calculate_average(struct Student student)
{
	int sum_of_marks = 0;
	int num_of_marks = 5;

	for(int i = 0; i < 5; i++)
		sum_of_marks += student.marks[i];

	return (sum_of_marks * 1.0) / num_of_marks;
}

void sort_students(struct Student *students_list, int left, int right)
{
	if(left < right)
	{
		int mid = left + (right - left) / 2;
		struct Student aux_student = *(students_list + left);
		*(students_list + left) = *(students_list + mid);
		*(students_list + mid) = aux_student;

		int i = left, j = right, d = 0;
		while(i < j)
		{
			if(calculate_average(*(students_list + i)) < calculate_average(*(students_list + j)))
			{
				// Sort the students by the average of the 5 grades. 
				aux_student = *(students_list + i);
				*(students_list + i) = *(students_list + j);
				*(students_list + j) = aux_student;
				d = 1 - d;
			} 
			else if(calculate_average(*(students_list + i)) == calculate_average(*(students_list + j)))
			{
				// In case of equal averages, sort alphabetically. 
				if(strcmp((students_list + i) -> name, (students_list + j) -> name) > 0)
				{
					aux_student = *(students_list + i);
					*(students_list + i) = *(students_list + j);
					*(students_list + j) = aux_student;
					d = 1 - d;
				}
			}
			i += d;
			j -= 1 - d;
		}
		sort_students(students_list, left, i - 1);
		sort_students(students_list, i + 1, right);
	}
}

void print_student(struct Student student)
{
	// Just a string representation of a student. 
	printf("Student name: %s ~ ID: %d ~ Average: %f\n", student.name, student.registration_number, calculate_average(student));
}

int main()
{
	// Allocate memory for the number of students and read that value. 
	int *students_count = malloc(sizeof(int));
	printf("Enter the number of students: ");
	scanf("%d", students_count);

	// Now allocate memory for the students and read them.
	struct Student *students = malloc(*students_count * sizeof(struct Student));
	for(int i = 0; i < *students_count; i++)
		*(students + i) = read_student();

	// Sort the students.
	sort_students(students, 0, *students_count - 1);

	// Print the students.
	for(int i = 0; i < *students_count; i++)
		print_student(*(students + i));
	
	return 0;
}