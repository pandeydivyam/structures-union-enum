// Structures - 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int roll;
    char name[50];
    int age;
    float gpa;
} Student;

Student* create_student_list(int n) {
    return malloc(n * sizeof(Student));
}

void add_student(Student *studs, int i, int roll, char *name, int age, float gpa) {
    studs[i].roll = roll;
    strcpy(studs[i].name, name);
    studs[i].age = age;
    studs[i].gpa = gpa;
}

void display_students(Student *students, int size) {
    for (int i = 0; i < size; i++)
        printf("\nRoll: %d, Name: %s, Age: %d, GPA: %.2f",
        students[i].roll, students[i].name, students[i].age, students[i].gpa);
    printf("\n");
}

void free_student_list(Student *students) {
    free(students);
}

int search(Student *s, int n, int roll) {
    for (int i = 0; i < n; i++)
        if (s[i].roll == roll) return i;
    return -1;
}

int main() {
    int capacity, count = 0, choice, roll, age, pos;
    float gpa, sum;
    char name[50], temp[50];

    printf("Enter initial capacity: ");
    if (scanf("%d", &capacity) != 1 || capacity <= 0 || capacity > 1000000) {
        printf("Invalid capacity\n");
        return 1;
    }

    Student *student_list = create_student_list(capacity);
    if (!student_list) {
        printf("Memory allocation failed\n");
        return 1;
    }

    do {
        printf("\n\n1.Add  2.Display  3.Search  4.Update");
        printf("\n5.Delete  6.GPA Analysis  7.Sort  8.Exit");
        printf("\nEnter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input\n");
            break;
        }

        if (choice == 1) {
            printf("Enter roll number: ");
            scanf("%d", &roll);

            if (roll <= 0 || search(student_list, count, roll) != -1) {
                printf("Invalid or duplicate roll number\n");
                continue;
            }

            printf("Enter name: ");
            scanf(" %49[^\n]", name);

            printf("Enter age: ");
            scanf("%d", &age);

            printf("Enter GPA: ");
            scanf("%f", &gpa);

            if (age < 16 || age > 100 || gpa < 0 || gpa > 4) {
                printf("Invalid age or GPA\n");
                continue;
            }

            if (count == capacity) {
                if (capacity > 1000000 / 2) {
                    printf("Maximum capacity reached\n");
                    continue;
                }
                int new_capacity = capacity * 2;
                Student *temp_ptr = realloc(student_list, new_capacity * sizeof(Student));
                if (!temp_ptr) {
                    printf("Memory allocation failed\n");
                    continue;
                }
                student_list = temp_ptr;
                capacity = new_capacity;
            }

            add_student(student_list, count++, roll, name, age, gpa);
            printf("Student added successfully\n");
        }

        else if (choice == 2) {
            if (!count) printf("No student records\n");
            else display_students(student_list, count);
        }

        else if (choice == 3) {
            printf("Enter roll number: ");
            scanf("%d", &roll);
            pos = search(student_list, count, roll);

            if (pos == -1) printf("Student not found\n");
            else display_students(&student_list[pos], 1);
        }

        else if (choice == 4) {
            printf("Enter roll number: ");
            scanf("%d", &roll);
            pos = search(student_list, count, roll);

            if (pos == -1) {
                printf("Student not found\n");
                continue;
            }

            printf("Enter new name: ");
            scanf(" %49[^\n]", name);
            printf("Enter new age and GPA: ");
            scanf("%d %f", &age, &gpa);

            if (age < 16 || age > 100 || gpa < 0 || gpa > 4) {
                printf("Invalid age or GPA\n");
                continue;
            }

            strcpy(student_list[pos].name, name);
            student_list[pos].age = age;
            student_list[pos].gpa = gpa;
            printf("Record updated\n");
        }

        else if (choice == 5) {
            printf("Enter roll number: ");
            scanf("%d", &roll);
            pos = search(student_list, count, roll);

            if (pos == -1) printf("Student not found\n");
            else {
                for (int i = pos; i < count - 1; i++)
                    student_list[i] = student_list[i + 1];
                count--;
                printf("Student deleted\n");
            }
        }

        else if (choice == 6) {
            if (!count) {
                printf("No records available for GPA analysis\n");
                continue;
            }

            int high = 0, low = 0;
            sum = 0;

            for (int i = 0; i < count; i++) {
                sum += student_list[i].gpa;
                if (student_list[i].gpa > student_list[high].gpa) high = i;
                if (student_list[i].gpa < student_list[low].gpa) low = i;
            }

            printf("Highest GPA: %s (%.2f)\n", student_list[high].name, student_list[high].gpa);
            printf("Lowest GPA: %s (%.2f)\n", student_list[low].name, student_list[low].gpa);
            printf("Average GPA: %.2f\n", sum / count);
        }

        else if (choice == 7) {
            for (int i = 0; i < count - 1; i++)
                for (int j = i + 1; j < count; j++)
                    if (student_list[i].gpa < student_list[j].gpa ||
                    (student_list[i].gpa == student_list[j].gpa &&
                    student_list[i].roll > student_list[j].roll)) {
                        Student t = student_list[i];
                        student_list[i] = student_list[j];
                        student_list[j] = t;
                    }

            printf("Records sorted by GPA (descending)\n");
            display_students(student_list, count);
        }

        else if (choice != 8)
            printf("Invalid choice\n");

    } while (choice != 8);

    free_student_list(student_list);
    printf("Memory released. Program ended.\n");
    return 0;
}
