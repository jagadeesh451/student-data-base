#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define pf printf
#define sf scanf
typedef struct st
{
        int rollno;
        char name[30];
        float percentage;
        struct st *next;
}student;
student *head;//head pointer declareed globally
void stud_add(void);
void stud_show(void);
void stud_del(void);
void del_rollno_wise(void);
void del_name_wise(void);
void print_samename_details(char *n);
void stud_mod(void);
void mod_rollno_based(void);
void mod_name_based(void);
void mod_percentage_based(void);
void print_samepercentage_details(float f);
void delete_all(void);
void reverse_list(void);
void stud_sort(void);
void sort_withname(void);
void sort_with_percentage(void);
void stud_sort(void);
void exit_prog(void);
void stud_save(void);
void save_and_exit(void);
int count(void);
//*************************MAIN PROGRAM***********************************
int main()
{
        char op;
        while(1)
        {
                pf("\033[41m**********STUDENT RECORD MENU***********\033[0m\n");
                pf("\033[33ma/A :add new record\nd/D :delete a record\ns/S :show the list\nm/M :modify a record\nv/V :save\ne/E :exit\nt/T :sort the list\nl/L :delete all the records\nr/R :reverse the list\033[0m\n");
                pf("\033[32;5mEnter your choise:\033[0m\n");
                sf(" %c",&op);
                if(op>='A'&&op<='Z')//condition to convert lower case
                        op=op+32;
                        pf("\033[36m");
                switch(op)
                {
                        case 'a':stud_add();break;
                        case 'd':stud_del();break;
                        case 's':stud_show();break;
                        case 'm':stud_mod();break;
                        case 'v':stud_save();break;
                        case 't':stud_sort();break;
                        case 'l':delete_all();break;
                        case 'r':reverse_list();break;
                        case 'e':exit_prog();break;
                        default :pf("wrong choise!\n");break;
                }
                pf("\033[0m");
        }
}
//********************* ADD DATA FUNCTION *************************
void stud_add(void)
{
        student *new=calloc(1,sizeof(student));
        pf("\033[32;5menter name and percentage:\033[0m\n");
        sf(" %s%f",new->name,&new->percentage);
        //condition for adding data if head contains empty
        if(head==0)
        {
                head=new;
                new->rollno=1;
                return;
        }
        int i=1,c=count(),flag=0;

        student *last=head;
        //condition for adding data if data is in reverse mode
        if(last->rollno>=c&&c!=1)
        {
                reverse_list();
                flag=1;
        }
        //condition for adding data if 1st node deleted
        if(last->rollno!=1)
        {
                new->next=last;
                new->rollno=1;
                head=new;
        if(flag)//flag if data is in reverse mode
                        reverse_list();
        pf("\033[32mdata added in records successfully!\033[0m\n");
                return;
        }
        i=2;
        while(last->next)
        {
                if(last->next->rollno!=i++) //condition for adding data if other than 1st node any node deleted
                {
                        new->next=last->next;
                        last->next=new;
                        new->rollno=i-1;

                        if(flag)
                        //rereversing if data is in reverse before adding
                                reverse_list();
        pf("\033[32mdata added in records successfully!\033[0m\n");
                        return;
                }
                last=last->next;
        }
        new->rollno=last->rollno+1;
        last->next=new;
        new->next=0;
                        //rereversing if data is in reverse before adding
        if(flag)
        reverse_list();
        pf("\033[32mdata added in records successfully!\033[0m\n");
        return;
}
///****************** function to print data **********************
void stud_show()
{
        if(head==0)//condition for checking if head is empty
        {
                pf("\033[31msorry! no data found!\033[0m\n");
                return;
        }
        pf("\033[31mrollno     name            percentage\033[0m\n");
        student *last=head;

        while(last)
        {
                pf("%-10d %-15s %.2f \n",last->rollno,last->name,last->percentage);
                last=last->next;
        }

}
//*************** function to delete data ****************
void stud_del(void)
{
        if(head==0)//condition for checking if head is empty
        {
                pf("\033[31msorry! no data found!\033[0m\n");
                return;
        }
        char op;
        pf("r/R :based on rollno\nn/N :based on name\n");
        pf("Enter your choise:\n");
        sf(" %c",&op);
        if(op>='A'&&op<='Z')
                op=op+32;
        switch(op)
        {
                case 'r':del_rollno_wise();break;
                case 'n':del_name_wise();break;
                default:("\033[31msorry! you choosed wrong choise!\033[0m\n");
        }
}
//****************** function to delete roll no wise ********************
void del_rollno_wise()
{
        if(head==0)//condition for checking if head is empty
        {
                pf("\033[31msorry! no data found!\033[0m\n");
                return;
        }
        student *last=head,*prev;
        int rn;
        pf("enter rollno:\n");
        sf("%d",&rn);


        if(last->next==0&&rn==last->rollno)
        {
                free(last);
                head=0;
                pf("data deleted!\n");
                return;
        }
        else if(head==last&&rn==last->rollno)
        {
                head=last->next;
                free(last);
                last=0;
                pf("data deleted!\n");
                return;
        }
        prev=last;
        last=last->next;
        while(last)
        {
                if(rn==last->rollno)
                {
                        prev->next=last->next;
                        free(last);
                        last=0;
                        pf("data deleted!\n");
                        return;
                }
                prev=last;
                last=last->next;
        }

}
//***************** function to delete data with name wise ***************
void del_name_wise(void)
{
        student *last=head,*prev;
        if(head==0)//condition for checking if head is empty
        {
                pf("\033[31msorry! no data found!\033[0m\n");
                return;
        }
        char n[30];
        pf("enter name:\n");
        sf("%s",n);
        int c=0;
        while(last)
        {
                if((strcmp(n,last->name)==0))
                {
                        c++;
                }

                last=last->next;
        }
        if(c>1)
        {
                pf("multiple names are present!\nso delete roll no wise!\n");
                print_samename_details(n);
                del_rollno_wise();
                return;
        }
        last=head;
        if(last->next==0&&(strcmp(n,last->name)==0))
        {
                free(last);
                head=0;
                pf("data deleted!\n");
                return;
        }
        else if(head==last&&(strcmp(n,last->name)==0))
        {
                head=last->next;
                free(last);
                last=0;
                pf("data deleted!\n");
                return;
        }
        prev=last;
        last=last->next;
        while(last)
        {
                if((strcmp(n,last->name)==0))
                {
                        prev->next=last->next;
                        free(last);
                        last=0;
                        pf("data deleted!\n");
                        return;
                }
                prev=last;
                last=last->next;
        }

}
//************* function to print same name data ************
void print_samename_details(char *n)
{
        student *last=head;
        while(last)
        {
                if(strcmp(n,last->name)==0)
                {
                        pf("%d  %s  %.2f\n",last->rollno,last->name,last->percentage);
                }
                last=last->next;
        }
        return;
}
//************ function to print same percentages data ***********88
void print_samepercentage_details(float f)
{
        student *last=head;
        while(last)
        {
                if(f==last->percentage)
                {
                        pf("%d  %s  %.2f\n",last->rollno,last->name,last->percentage);
                }
                last=last->next;
        }
        return;
}
//*************** fnctio to modify data ************************
void stud_mod(void)
{
        if(head==0)//condition for checking if head is empty
        {
                pf("\033[31msorry! no data found!\033[0m\n");
                return;
        }
        pf("enter which record to search for modification:\n");
        pf("R/r : to search a rollno\nN/n : to search a name\nP/p : percentage based\n");
        char op;
        pf("Enter your choise:\n");
        sf(" %c",&op);
        if(op>='A'&&op<='Z')
                op=op+32;
        switch(op)
        {
                case 'r':mod_rollno_based();break;
                case 'n':mod_name_based();break;
                case 'p':mod_percentage_based();break;
                default:pf("wrong choise!\n");break;
        }
}
//************* function modify data rollno wise *******************
void mod_rollno_based(void)
{
        int oldr,newr;
        pf("enter old rollno\n");
        sf("%d",&oldr);
        pf("enter new rollno\n");
        sf("%d",&newr);
        student *last=head;
        while(last)
        {
                if(oldr==last->rollno)
                {
                        last->rollno=newr;
                        pf("rollno modified!\n");
                        return;
                }
                last=last->next;
        }
        pf("roll no not exist:\n");
}
//************** function to modify name *****************
void mod_name_based(void)
{
        //condition for checking if head is empty
        if(head==0)
        {
                pf("sorry ! no data present to modify!\n");
                return;
        }
        student *last=head;
        char oldn[30];
        char newn[30];
        pf("enter oldname:\n");
        sf("%s",oldn);
        pf("enter new name:\n");
        sf("%s",newn);
        int c=0;
        while(last)
        {
                if((strcmp(oldn,last->name)==0))
                {
                        c++;
                }

                last=last->next;
        }
        if(c>1)
        {
                pf("multiple names are present!\n");
                print_samename_details(oldn);
        int r;
        pf("enter rollno to modify name\n");
        sf("%d",&r);
        last=head;
        while(last)
        {
                if(r==last->rollno&&(strcmp(oldn,last->name)==0))
                {
                        strcpy(last->name,newn);
                        pf("name modified!\n");
                        return;
                }
                last=last->next;
        }
        return;
        }
        last=head;
        while(last)
        {
                if(strcmp(last->name,oldn)==0)
                {
                        strcpy(last->name,newn);
                        pf("name modified!\n");
                        return;
                }
                last=last->next;
        }
        pf("sorry!\nrollno not matched with name!\n");
        return;
}
//******************* function to modify percentage ***************
void mod_percentage_based(void)
{
        //condition for checking if head is empty
        if(head==0)
        {
                pf("sorry ! no data present to modify!\n");
                return;
        }
        int c=0;
        float oldp,newp;
        pf("enter old percentage:\n");
        sf("%f",&oldp);
        pf("enter new percentage:\n");
        sf("%f",&newp);
        student *last=head;
        while(last)
        {
                if(oldp==last->percentage)
                {
                        c++;
                }

                last=last->next;
        }
        if(c>1)
        {
                pf("multiple percentages  are present with same percentage!\n");
                print_samepercentage_details(oldp);
        int r;
        pf("enter rollno to modify percentage:\n");
        sf("%d",&r);
        last=head;
        while(last)
        {
                if(r==last->rollno&&oldp==last->percentage)
                {
                        last->percentage=newp;
                        pf("percentage modified\n");
                        return;
                }
                last=last->next;
        }
        }
        last=head;
        while(last)
        {
                if(oldp==last->percentage)
                {
                        last->percentage=newp;
                        pf("percentage modified\n");
                        return;
                }
                last=last->next;
        }
        pf("sorry! roll no not matched with percentage!\n");
        return;
}
//************ function to deleta all nodes ******************
void delete_all()
{
        student *last=head,*prev;
        while(last)
        {
                prev=last;
                last=last->next;
                free(prev);
        }
        head=0;
        pf("all data deleted successfull!\n");
}
//************* sort data *******************
void stud_sort()
{
        int c=count();
        student *last=head;
        if(c<2)
        {
                pf("minimun two students data is required for sorting!\n");
                return ;
        }
        pf("Enter\nn/N : sort with name\np/P : sort with percentage\n");
        char op;
        pf("Enter your choise:\n");
        sf(" %c",&op);
        if(op>='A'&&op<='Z')
                op=op+32;
        switch(op)
        {
                case 'n':sort_withname();break;
                case 'p':sort_with_percentage();break;
                default:pf("wrong choise!\n");break;
        }
}
//*************** function sort with name *********************
void sort_withname(void)
{

        student *last=head,*pres;
        int i,c=count();
        for(i=0;i<c;i++)
        {
                pres=last->next;
                for(int j=0;j<c-i-1;j++)
                {
                        if(strcmp(last->name,pres->name)>0)
                        {
                                //swapping roll no
                                int t=last->rollno;
                                last->rollno=pres->rollno;
                                pres->rollno=t;
                                //swapping name
                                char t1[20];
                                strcpy(t1,last->name);
                                strcpy(last->name,pres->name);
                                strcpy(pres->name,t1);
                                //swapping marks
                                float f=last->percentage;
                                last->percentage=pres->percentage;
                                pres->percentage=f;
                        }
                        pres=pres->next;
                }
                last=last->next;

        }
        return;
}
//********************* function sort with name *****************************
void sort_with_percentage(void)
{

        student *last=head,*pres;
        int i,c=count();
        for(i=0;i<c;i++)
        {
                pres=last->next;
                for(int j=0;j<c-i-1;j++)
                {
                        if(last->percentage>pres->percentage)
                        {
                                //swapping roll no
                                int t=last->rollno;
                                last->rollno=pres->rollno;
                                pres->rollno=t;
                                //swapping name
                                char t1[20];
                                strcpy(t1,last->name);
                                strcpy(last->name,pres->name);
                                strcpy(pres->name,t1);
                                //swapping marks
                                float f=last->percentage;
                                last->percentage=pres->percentage;
                                pres->percentage=f;
                        }
                        pres=pres->next;
                }
                last=last->next;

        }
        return;
}
//**************** function to exit *******************
void exit_prog(void) {
        char op;
        pf("Enter\n S/s : save and exit\nE/e : exit without saving\n");
        sf(" %c", &op);
        if (op >= 'A' && op <= 'Z')
                op = op + 32;

        switch (op) {
                case 's': save_and_exit(); break;
                case 'e': exit(0); break; // Added exit code
                default: pf("wrong choice!\n"); break;
        }
}
//******************** function to save and exit **********************************
void save_and_exit(void)
{
        //condition for checking if head is empty
        if(head==0)
        {
                pf("no records!\n");
                return;
        }
        FILE *fp=fopen("student.txt","w");
        student *last=head;
        while(last)
        {
                fprintf(fp,"%d %s %f\n",last->rollno,last->name,last->percentage);
                last=last->next;
        }
        fclose(fp);
        pf("data saved successfully in -->(student.txt file)!\n");
        exit(0);
}
//************************* save file *************************
void stud_save(void)
{
        //condition for checking if head is empty
        if(head==0)
        {
                pf("no records!\n");
                return;
        }
        FILE *fp=fopen("student.txt","w");
        student *last=head;
        while(last)
        {
                fprintf(fp,"%d %s %f\n",last->rollno,last->name,last->percentage);
                last=last->next;
        }
        fclose(fp);
        pf("data saved successfully in -->(student.txt file)!\n");
}
//******************** function to reverse list *********************
void reverse_list()
{
        int c=count();
        student *last=head,*prev;
        prev=last;
        int i=0;
        c=c-1;
        for(i=1;i<=c;i++,c--)
        { int c1=c;
                while(c1)
                {
                        last=last->next;
                        c1--;
                } //swapping roll no
                int t=last->rollno;
                last->rollno=prev->rollno;
                prev->rollno=t;
                //swapping name
                char t1[20];
                strcpy(t1,last->name);
                strcpy(last->name,prev->name);
                strcpy(prev->name,t1);
                //swapping marks
                float f=last->percentage;
                last->percentage=prev->percentage;
                prev->percentage=f;

                prev=prev->next;
                last=head;
        }
}
//************ count nodes ******************
int count(void)
{
        student *last=head;
        int c=0;
        while(last)
        {
                c++;
                last=last->next;
        }
        return c;
}