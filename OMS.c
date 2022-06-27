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
delete employee-done
Attendance logs
Feedback system
Separate functions for CEO(menu driven) access to emp, feedback-done
*/
char name[MAX]="datafile.txt";
char uname[MAX]="passwords.txt";

int salary_array[]={1000000,900000,900000,750000,500000,450000,300000,150000};

char role_array[8][15]={"CEO","COO","CTO","MAN", "AMAN", "SALES", "PEON", "SEC"};

int count_emp=0;
int count_user;
FILE *fp1;
FILE *fp2;
typedef struct Employee_Data
{
	char name[MAX];
	char role[MAX];
	int wd;
	int salary;	
}emp;

typedef struct up
{
	char name[MAX];
	char pass[MAX];
}user;

emp emp_array[MAX];

user user_array[MAX];

void login()
{	
	user user1;
	count_user=0;
	//printf("Reading data from file: \n");
    fp2=fopen(uname,"r+");
    if(fp2==NULL)
    {
    	printf("File Not Found");
    }
    else
    {	while(fscanf(fp2,"%s %s",user1.name,user1.pass)!=EOF)
    	{
    		user_array[count_user]=user1;
    		count_user++;

    	}
    }

}

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
void readfile()
{	
	emp emp1;
	count_emp=0;
	//printf("Reading data from file: \n");
    fp1=fopen(name,"r+");
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
void writefile()
{
	fclose(fp1);
	fp1=fopen(name,"w");
	for(int i =0;i<count_emp;i++)
	{	
		if(strcmp(emp_array[i].name,"XXX")!=0)
		{	//printf("%s\n",emp_array[i].name);
			fprintf(fp1, "%s %s %d\n",emp_array[i].name,emp_array[i].role,emp_array[i].wd);
		}
	}
	fclose(fp1);
	readfile();
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

void del_emp()
{	int flag=0;
	fp1=fopen("datafile.txt","w");
	for(int i=0;i<count_emp;i++)
	{
		if(emp_array[i].wd<12)
		{
			printf("\nEmployee having \nname: %s \nand role:%s \nis now fired for having no commitment as their number of working days is :  %d",emp_array[i].name,emp_array[i].role,emp_array[i].wd);
			strcpy(emp_array[i].name,"XXX");
			flag++;
			//printf("%s",emp_array[i].name);
		}
	
	}
	if(flag==0)
	{
		printf("All employee's are outstanding, no one has been fired");
	}
	writefile();
	fclose(fp1);
	readfile();
}

int check( char u[],char p[])
{
	for(int i=0;i<count_user;i++)
	{	int uv=strcmp(user_array[i].name,u);
		int pv=strcmp(user_array[i].pass,p);
		int res=(!uv && !pv);
		//printf("%d\n",res );
		if(res)
		{
			if(!strcmp(u,"CEO"))
			{
				return 1;
			}
			else
			{
				return -1;
			}
		}
	}
	return 0;
}

void add_up()
{	user u1;
	printf("\nEnter username:");
	scanf("%s",u1.name);
	printf("\nEnter password:");
	scanf("%s",u1.pass);
	user_array[count_user]=u1;
	count_user++;
	fclose(fp2);
	fp2=fopen(uname,"w");
	for (int i = 0; i < count_user; i++)
	{
		fprintf(fp2, "%s %s\n",user_array[i].name,user_array[i].pass);
	}
	fclose(fp2);
	login();

}

int main()
{
	int choice;
	readfile();
	login();
	//printf("%d\n",count_user);
	char u[10],p[10];
	printf("\nEnter username:");
	scanf("%s",u);
	printf("\nEnter password:");
	scanf("%s",p);
	int c=check(u,p);
	switch(c)
	{
		case 1:
			printf("\nEnter 1 to read employee data \nEnter 2 to add new employees\nEnter 3 to fire underperforming employees\nEnter 4 to enter new employee login\nEnter 0 to quit: ");
			scanf("%d",&choice);
			while(choice)
			{	
				switch (choice)
				{
					case 1:
						printf("\nCurrent Employees: \n");
						for(int i=0;i<count_emp;i++)
						{	
							print_emp(emp_array[i]);
						}
						break;
					case 2:
						new_emps();
						writefile();
						break;
					case 3:
						printf("Employees having less than 12 working days will be fired\n");
						del_emp();
						break;
					case 4:
						add_up();
						break;
					default:
						writefile();
						break;
				}
				printf("\n");
				printf("\nEnter 1 to read employee data \nEnter 2 to add new employees\nEnter 3 to fire underperforming employees\nEnter 4 to enter new employee login\nEnter 0 to quit: ");
				scanf("%d",&choice);		
			}
			break;
		case -1:
			printf("\nEnter 1 to read employee data \nEnter 2 to add new employees\nEnter 0 to quit: ");
			scanf("%d",&choice);
			while(choice)
			{	
				switch (choice)
				{
					case 1:
						printf("\nCurrent Employees: \n");
						for(int i=0;i<count_emp;i++)
						{	
							print_emp(emp_array[i]);
						}
						break;
					case 2:
						new_emps();
						writefile();
						break;
					default:
						writefile();
						break;
				}
				printf("\n");
				printf("\nEnter 1 to read employee data \nEnter 2 to add new employees\nEnter 0 to quit: ");
				scanf("%d",&choice);		
			}
			break;
		default:
			printf("\nEmployee DNE");
			break;
	}
	end();
}
