#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    float salary;
};

void addEmployee() {
    FILE *fp = fopen("employee.txt", "a");
    struct Employee e;

    printf("\nEnter Employee ID: ");
    scanf("%d", &e.id);
    printf("Enter Employee Name: ");
    scanf("%s", e.name);
    printf("Enter Salary: ");
    scanf("%f", &e.salary);

    fprintf(fp, "%d %s %.2f\n", e.id, e.name, e.salary);
    fclose(fp);

    printf("\nEmployee Added Successfully!\n");
}

void displayEmployees() {
    FILE *fp = fopen("employee.txt", "r");
    struct Employee e;

    if(fp == NULL) {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEmployee Records:\n");
    printf("--------------------------------------\n");
    while(fscanf(fp, "%d %s %f", &e.id, e.name, &e.salary) != EOF) {
        printf("ID: %d\tName: %s\tSalary: %.2f\n", e.id, e.name, e.salary);
    }
    printf("--------------------------------------\n");

    fclose(fp);
}

void searchEmployee() {
    FILE *fp = fopen("employee.txt", "r");
    struct Employee e;
    int id, found = 0;

    printf("\nEnter Employee ID to Search: ");
    scanf("%d", &id);

    while(fscanf(fp, "%d %s %f", &e.id, e.name, &e.salary) != EOF) {
        if(e.id == id) {
            printf("\nRecord Found:\nID: %d\nName: %s\nSalary: %.2f\n", e.id, e.name, e.salary);
            found = 1;
            break;
        }
    }

    if(!found) printf("\nRecord Not Found!\n");
    fclose(fp);
}

void updateEmployee() {
    FILE *fp = fopen("employee.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Employee e;
    int id, found = 0;

    printf("\nEnter Employee ID to Update Salary: ");
    scanf("%d", &id);

    while(fscanf(fp, "%d %s %f", &e.id, e.name, &e.salary) != EOF) {
        if(e.id == id) {
            printf("Enter New Salary: ");
            scanf("%f", &e.salary);
            found = 1;
        }
        fprintf(temp, "%d %s %.2f\n", e.id, e.name, e.salary);
    }

    fclose(fp);
    fclose(temp);

    remove("employee.txt");
    rename("temp.txt", "employee.txt");

    if(found)
        printf("\nSalary Updated Successfully!\n");
    else
        printf("\nRecord Not Found!\n");
}

void deleteEmployee() {
    FILE *fp = fopen("employee.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Employee e;
    int id, found = 0;

    printf("\nEnter Employee ID to Delete: ");
    scanf("%d", &id);

    while(fscanf(fp, "%d %s %f", &e.id, e.name, &e.salary) != EOF) {
        if(e.id != id)
            fprintf(temp, "%d %s %.2f\n", e.id, e.name, e.salary);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove("employee.txt");
    rename("temp.txt", "employee.txt");

    if(found)
        printf("\nEmployee Deleted Successfully!\n");
    else
        printf("\nRecord Not Found!\n");
}

int main() {
    int choice;

    while(1) {
        printf("\n===== Employee Payroll System =====\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee\n");
        printf("4. Update Employee Salary\n");
        printf("5. Delete Employee\n");
        printf("6. Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: updateEmployee(); break;
            case 5: deleteEmployee(); break;
            case 6: exit(0);
            default: printf("\nInvalid Choice! Try Again.\n");
        }
    }
}