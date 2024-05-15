#include <stdlib.h>
#include <stdio.h>
#include "glthreads.h"
#include <string.h>


#define offsetof(struct_name, field_name) \
     ((unsigned int)((size_t) &((struct_name *)0)->field_name))

typedef struct emp_ {
  char name[30];
  unsigned int salary;
  char designation[30];
  unsigned int emp_id;
  glthread_node_t glnode;
} emp_t;


// Print the Employee
void print_emp_details(glthread_node_t * glnode){
  printf("Employee Information\n");
  unsigned int offset = offsetof(emp_t,glnode);
  printf("Offset is: %u\n",offset);
  emp_t *employee = (emp_t *)((char *)glnode - offset);
  printf("Name: %s\n",employee->name);
  printf("Salary: %u\n",employee->salary);
  printf("Profession: %s\n",employee->designation);
  printf("ID: %u\n",employee->emp_id);

  
}

int main(){
    emp_t employee;
    strcpy(employee.name,"OFFSET PRACTICE");
    employee.salary = 1000;
    strcpy(employee.designation,"Software Engineering");
    employee.emp_id = 26; 
    print_emp_details(&employee.glnode);

}