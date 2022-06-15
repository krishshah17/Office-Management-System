#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define True 1
#define False 0
#define MAX 30
/*
Office Mangement System:
Menu driven functions-done
Read from file-done
Write to file-done
User defined data type-emp-done
array of emp to store data-done
create new employees-done
Overtime hours-done
calculate salary based on working days and role-done
delete employee
Attendance logs
Feedback system
Promotion and Retirement(Questionable)
Post description and availability
Separate functions for CEO(menu driven): promotion, retire, see feedback
*/

int salary_array[]={1000000,900000,900000,750000,500000,450000,300000,150000};
char role_array[8][15]={"CEO","COO","CTO","MAN", "AMAN", "SALES", "PEON", "SEC"};
int count_emp=0;
FILE *fp1;
typedef struct Employee_Data
{
	char name[MAX];
	char role[MAX];
	int wd;
	int salary;	
}emp;

emp emp_array[MAX];

void end()
{
    printf("\n__________________________________________________________\n");
    printf("\n____Thank you for using our Office Management System______\n");
    printf("\n__________________________________________________________\n");
}

int calc_salary(int atten, char role[])
{	
    int flag = True;
    int i =0;
    while(flag)
    {
        if(strcmp(role,role_array[i])==0)
        {
            flag=False;
        }
        else
        {
            i++;
        }
    }
    int sal = salary_array[i] - (((25-atten)*salary_array[i])/100);
    return sal;
    
}

void print_emp(emp emp1)
{   
    printf("Name: %s\n",emp1.name);
    printf("Role: %s\n",emp1.role);
    printf("Working Days: %d\n",emp1.wd);
    printf("Salary: %d\n",emp1.salary);

}

emp create_emp()
{
	emp new;
	printf("\nEnter Name: ");
	scanf(" %[^\n]s ",new.name);
    printf("\nEnter Role: ");
    scanf(" %[^\n]s ",new.role);
    printf("\nEnter working days:");
    scanf("\n %d",&new.wd);
    new.salary=calc_salary(new.wd,new.role);
	return new;
}

void writefile(char fname[])
{
	fclose(fp1);
	fp1=fopen(fname,"w");
	for(int i =0;i<count_emp;i++)
	{	if(strcmp(emp_array[i].name,"XXX")!=0)
		{
			fprintf(fp1, "%s %s %d\n",emp_array[i].name,emp_array[i].role,emp_array[i].wd);
		}
	}
}

void new_emps()
{
	int num;
	printf("Enter number of new employees: ");
	scanf("%d",&num);
	for(int i =0;i<num;i++)
	{	printf("Employee %d",i+1);
		emp_array[count_emp]=create_emp();
		count_emp++;
	}
	
}
void readfile(char fname[])
{	
	char data1[MAX];
	char data2[MAX];
	int rand;
	emp emp1;
	printf("Reading data from file: \n");
    fp1=fopen(fname,"r+");
    if(fp1==NULL)
    {
    	printf("File Not Found");
    }
    else
    {	while(fscanf(fp1,"%s %s %d",emp1.name,emp1.role,&emp1.wd)!=EOF)
    	{
    		emp1.salary=calc_salary(emp1.wd,emp1.role);
    		//print_emp(emp1);
    		emp_array[count_emp]=emp1;
    		count_emp++;

    	}
    }

  
}
/*void del_emp()
{
	fp1=fopen("data.txt","w");
	for(int i=0;i<count_emp;i++)
	{
		if(emp_array[i].wd<12)
		{
			printf("\nEmployee having name %s  and role %s  is now fired for having no commitment as their number of working days is :  %d",emp_array[i].name,emp_array[i].role,emp_array[i].wd);
			strcpy(emp_array[i].name,"XXX");
		}
	
	}
	writefile("data.txt");
	readfile("data.txt");
}
*/







int main()
{
	char name[MAX];
	int choice;
	printf("Enter file name with extension: ");
	scanf(" %s",name);
	readfile(name);
	printf("\nEnter 1 to read employee data \nEnter 2 to add new employees\nEnter 0 to quit: ");
	scanf("%d",&choice);
	while(choice)
	{	
		switch (choice)
		{
			case 1:
				printf("\nPrinting array of structures: \n");
				for(int i=0;i<count_emp;i++)
				{	
					print_emp(emp_array[i]);
				}
				break;
			case 2:
				new_emps();
				writefile(name);
				break;
			/*case 3:
				printf("Employees having less than 12 working days will be fired\n");
				del_emp();
				break;
				*/
			
			default:
				break;
		}

		printf("\nEnter 1 to read employee data \nEnter 2 to add new employees\nEnter 0 to quit: ");
		scanf("%d",&choice);		
	}
	end();
}