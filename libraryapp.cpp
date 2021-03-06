//Code for LIBRARY MANAGEMENT SYSYTEM (LMS) IN C++

#include<fstream.h>
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip.h>
class book
{
char bno[6];
char bname[50];
char aname[20];
public:
void create_book()
{
cout<<"\n NEW BOOK ENTRY..\n";
cout<<"\nEnter the book no. ";
cin>>bno;
cout<<"\n\nEnter the Name of the book ";
gets(bname);
cout<<"\n\nEnter the Author's name ";
gets(aname);
cout<<"\n\nBook Created.. ";
}
void show_book()
{
cout<<"\nBook no.:- "<<bno;
cout<<"\nBook Name : ";
puts(bname);
cout<<"\nAuthor's name :-	";
puts(aname);
}
void modify_book()
{
cout<<"\nBook no. :"<<bno;
cout<<"\nModify book name : ";
gets(bname);
cout<<"\nModify Author's name of the book : ";
gets(aname);
}
char*retbno()
{ return bno; }
void report()
{ cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl; }
} ;
class student
{
char admno[6];
char name[20];
char stbno[6];
int token;
public:
void create_student()
{
clrscr();
cout<<"\nNEW STUDENT ENTRY.. \n";
cout<<"\nEnter the admission no. :- ";
cin>>admno;
cout<<"\n\nEnter the name of the student ";
gets(name);
token=0;
stbno[0]='\0';
cout<<"\nStudent record Created.. ";
}
void show_student()
{
cout<<"\nAdmission no. :- "<<admno;
cout<<"\nStudent name; ";
puts(name);
cout<<"\nNo. of books issued: "<<token;
if(token==1)
cout<<"\nBook No. "<<stbno;
}
void modify_student()
{
cout<<"\nAdmission no. : "<<admno;
cout<<"\nModify Student Name : ";
gets(name);
}
char* retadmno()
{ return admno; }
char* retstbno()
{ return stbno; }
int rettoken()
{ return token; }
void addtoken()
{ token=1; }
void resettoken()
{ token=0; }
void getstbno(char t[] )
{ strcpy(stbno,t); }
void report()
{      cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<token<<endl; }
};
fstream fp, fp1;
book bk;
student st;
void write_book()     //Function to write in file
{
char ch;
ofstream fp("book.dat",ios::app||ios::in);

do
{
clrscr();
bk.create_book();
fp.write((char*)&bk,sizeof(book));
cout<<"\n\nDo you want to add more record..(y/n)";
cin>>ch;
}
while (ch=='y'||ch=='Y');
fp.close();
}
void write_student()
{
char ch;
ofstream fp("student.dat",ios::app||ios::in) ;
do
{
st.create_student();
fp.write((char*)&st,sizeof(student));
cout<<"\n\nDo you want to add more record..(y/n) ";
cin>>ch;
} while(ch=='y'||ch=='y');
fp.close(); }
void display_spb(char n[])     //Function to read specific record
{
cout<<"\nBOOK DETAILS\n";
int flag=0;
fp.open("book.dat",ios::in);
while(fp.read((char*)&bk,sizeof(book)))
{
if(stricmp(bk.retbno(),n)==0)
{ bk.show_book();
flag=1;
}
}
fp.close();
if(flag==0)
cout<<"\n\nBook does not exist ";
getch();
}
void modify_book()  //Function to modify record of book
{
char n[6];
int found =0;
clrscr();
cout<<"\n\n\tMODIFY BOOK RECORD..";
cout<<"\n\n\tEnter The Book no. of the book:- ";
cin>>n;
fp.open("book.dat",ios::in||ios::out);
while(fp.read((char*)&bk,sizeof(book))&&found==0)
{
if(strcmpi(bk.retbno(),n)==0)
{ bk.show_book();
cout<<"\nenter the New Details of book"<<endl;
bk.modify_book();
int pos=-1*sizeof(bk);
fp.seekp(pos,ios::cur);
fp.write((char*)&bk,sizeof(book));
cout<<"\n\n\t Record Updated";
found=1; }
}
fp.close();
if(found==0)
cout<<"\n\nRecord not found ";
getch();
}
void modify_student()  //Function to modify record of student
{
char n[6];
int found=0;
clrscr();
cout<<"\n\n\tMODIFY STUDENT RECORED... ";
cout<<"\n\n\tEnter The admission no. of the student :";
cin>>n;
fp.open("student.dat",ios::in||ios::out);
while(fp.read((char*)&st,sizeof(student))&&found==0)
{
if(strcmpi(st.retadmno(),n)==0)
{ st.show_student();
cout<<"\nenter the new Details of student "<<endl;
st.modify_student();
int pos=-1*sizeof(st);
fp.seekp(pos,ios::cur);
fp.write((char*)&st,sizeof(student));
cout<<"\n\n\t Record updated ";
found=1; }
}
fp.close();
if(found==0)
cout<<"\n\n Record Not Foound ";
getch();
}
void delete_student() //Function to delete student record
{
char n[6];
int flag=0;
clrscr();
cout<<"\n\n\n\n\t DELETE STUDENT... ";
cout<<"\n\nEnter The Admission no. of the student you want to delete :";
cin>>n;
fp.open("student.dat",ios::in||ios::out);
fstream fp2;
fp2.open("temp.dat",ios::out) ;
fp.seekg(0,ios::beg) ;
while(fp.read((char*)&st,sizeof(student)))
{ if(stricmp(st.retadmno(),n)!=0)
fp2.write((char*)&st,sizeof(student));
else
flag=1;
}
fp2.close();
fp.close();
remove("student.dat");
rename("temp.dat","student.dat");
if (flag==1)
cout<<"\n\n Record deleted.. ";
else
cout<<"\n\n Record not found ";
getch();
}
void delete_book()  //Function to delete book record
{
char n[6];
clrscr();
cout<<"\n\n\n\t DELETE BOOK... ";
cout<<"\n\nEnter the Book no. of the book you want to delete ; ";
cin>>n;
fp.open("book.dat",ios::in||ios::out) ;
fstream fp2;
fp2.open("temp.dat",ios::out) ;
fp.seekg(0,ios::beg) ;
while(fp.read((char*)&bk,sizeof(book)))
{
if (strcmpi(bk.retbno(),n)!=0)
{ fp2.write((char*)&bk,sizeof(book)); }
}
fp2.close();
fp.close();
remove("book.dat");
rename("temp.dat","book.dat");
cout<<"\n\n\t Record Deleted.. ";
getch();
}

void display_alls()//Function to display student list
{
clrscr();
fp.open("student.dat",ios::in) ;
if(!fp)
{ cout<<"ERROR!! FILE COULD NOT BE OPEN ";
getch();
return; }
cout<<"\n\n\t\tSTUDENT LIST\n\n";
cout<<"==================================================================\n";
cout<<"\tAdmission No. "<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
cout<<"==================================================================\n";
while(fp.read((char*)&st,sizeof(student)))
{ st.report(); }
fp.close();
getch();
}
void display_allb()   //Function to display book list
{ clrscr();
fp.open("book.dat",ios::in);
if(!fp)
{
cout<<"ERROR!! FILE COULD NOT BE OPEN ";
getch();
return; }
cout<<"\n\n\t\tBOOK LIST\n\n";
cout<<"===================================================================\n";
cout<<"Book Number "<<setw(20)<<"Book Name"<<setw(25)<<"Authors\n";
cout<<"===================================================================\n";
while(fp.read((char*)&bk,sizeof(book)))
{ bk.report() ;  }
fp.close();
getch();
}
void book_issue()  //Function to issue book
{
char sn[6],bn[6];
int found=0,flag=0;
clrscr();
cout<<"\n\nBOOK ISSUE... ";
cout<<"\n\nEnter The student's admission no. ";
cin>>sn;
fp.open("student.dat",ios::in||ios::out);
fp1.open("book.dat",ios::in||ios::out);
while(fp.read((char*)&st,sizeof(student))&& found==0)
{ if(strcmpi(st.retadmno(),sn)==0)
{ found=1;
if(st.rettoken()==0)
{ cout<<"\n\n\tenter the book no. :- ";
cin>>bn;
while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
{ if(strcmpi(bk.retbno(),bn)==0)
{ bk.show_book();
flag=1;
st.addtoken();
st.getstbno(bk.retbno());
int pos=-1*sizeof(st);
fp.seekg(pos,ios::cur);
fp.write((char*)&st,sizeof(student));
cout<<"\n\n\t Book issued successfully "; }
}
if(flag==0)
cout<<"Book does not exist ";
}
else
cout<<"You have not returned the last book "; }
}
if(found==0)
cout<<"Student record not exist.. ";
getch();
fp.close();
fp1.close();
}
void book_deposit()  //Function to deposit book
{
char sn[6],bn[6];
int found=0,flag=0,day,fine;
clrscr();
cout<<"\n\n BOOK DEPOSIT ... ";
cout<<"\n\n\tEnter the student's admission no. ";
cin>>sn;
fp.open("student.dat",ios::in||ios::out);
fp1.open("book.dat",ios::in||ios::out);
while(fp.read((char*)&st,sizeof(student))&& found==0)
{ if(strcmpi(st.retadmno(),sn)==0)
{ found=1;
if(st.rettoken()==1)
{ while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
{ if(strcmpi(bk.retbno(),st.retstbno())==0)
{ bk.show_book();
flag=1;
cout<<"\n\nBook deposited in no. of days";
cin>>day;
if(day>15)
{ fine=(day-15)*1 ;
cout<<"\n\nFine has to deposited Rs. "<<fine; }
st.resettoken();
int pos=-1*sizeof(st);
fp.seekg(pos,ios::cur);
fp.write((char*)&st,sizeof(student));
cout<<"\n\n\t Book deposited successfully "; }
}
if(flag==0)
cout<<" Book no. does not exist "; }
else
cout<<"No book is issued..please check!! "; }
}
if(found==0)cout<<"Student record not exist.. ";
getch();
fp.close();
fp1.close();
}
void deleteall() //Function to delete data
{ clrscr();
int a;
cout<<"Press 1 to delete all the data "<<"\n";
cout<<"Press 2 to go back "<<"\n";
cin>>a;
if(a==1)
{ clrscr();
cout<<"PLEASE BE SURE THAT YOU HAVE TAKEN THE BACKUP OF UR DATA ";
cout<<"BECAUSE THE FILES IF DELETED WILL NOT BE ABLE TO RESTORED"<<"\n";
cout<<"Press any key to continue"<<"\n";
getch();
ofstream delstu("student.dat",ios::trunc);
delstu.close();
ofstream delboo("book.dat",ios::trunc);
delboo.close();
clrscr();
cout<<"All the data deleted"<<"\n";
cout<<"Press any kry to go back"<<"\n";
getch();
return; }
else
return; }
void backdat()  //Function to backup data
{ clrscr();
cout<<"The backupupes file will be store in"<<"\n";
cout<<"Press any key to continue"<<"\n";
getch();
system("save") ;
//SAVE IS A BATCH FILE WHOSE CODING IS GIVEN AT THE END OF PROGRAM
clrscr();
cout<<"YOUR DATA HAS BEEN SAVED TO DOCUMENTS SUCCESSFULLY!! "<<"\n";
cout<<"Press any key to go back"<<"\n";
getch();
return; }
void admin_menu()   //Administration menu
{ clrscr();
int ch2;
cout<<"\n\n\n\t\t ADMINISTRATION MENU";
cout<<"\n\t1.CREATE STUDENT RECORD";
cout<<"\n\t2.DISPLAY ALL STUDENT RECORD";
cout<<"\n\t3.DISPLAY SPECIFIC STUDENT RECORD";
cout<<"\n\t4.MODIFY STUDENT RECORD";
cout<<"\n\t5.DELETE STUDENT RECORD";
cout<<"\n\t6.CREATE BOOK ";
cout<<"\n\t7.DISPLAY ALL BOOKS ";
cout<<"\n\t8.DISPLAY SPECIFIC BOOK ";
cout<<"\n\t9.MODIFY BOOK ";
cout<<"\n\t10.DELETE BOOK ";
cout<<"\n\t11.DELETE ALL THE DATA ";
cout<<"\n\t12.BACKUP YOUR DATA ";
cout<<"\n\t13.BACK TO MAIN MENU ";
cout<<"\n"<<"Please choose an option from (1-12);- ";
cin>>ch2;
switch(ch2)
{
case 1: clrscr();
write_student();
break;
case 2: display_alls() ;
break;
case 3: char num[6];
clrscr();
cout<<"\n\n\tPlease Enter the Admission No. ";
cin>>num;
display_sps(num);
break;
case 4: modify_student() ;
break ;
case 5: delete_student();
break;
case 6: clrscr();
write_book() ;
break;
case 7: display_allb();
break;
case 8: { char num[6];
clrscr();
cout<<"\n\n\tPlease enter the Book no. ;- ";
cin>>num;
display_spb(num);
break; }
case 9: modify_book();
break;
case 10: delete_book();
break;
case 11: deleteall();
break;
case 12: backdat();
break;
case 13: return;
default : cout<<"\a";
}
admin_menu();
}
void intro() //Introductory function
{ clrscr();
cout<<"\t\t\t\t\t\t\t\t\t\t\t\t GENESIS GLOBAL SCHOOL,NOIDA,INDIA"<<"\n\n";
cout<<"\t\t\t\t\t\t\t\t\t\t\t\t       LIBRARY MANAGMENT "<<"\n\n";
cout<<"                          WELCOME"<<"\n\n\n\n\n";
cout<<"                      	 MADE BY;- PRANIT GUPTA ";
cout<<"\n\n"<<"Press any key to continue... ";
getch(); }
void main()
{ char ch;
intro();
do{ clrscr();
cout<<"\n\n\n\tMAIN MENU";
cout<<"\n\n\t01. BOOK ISSUE";
cout<<"\n\n\t02. BOOK DEPOSIT";
cout<<"\n\n\t03. ADMINISTRATION MENU";
cout<<"\n\n\t04. EXIT ";
cout<<"\n\n\tPlease Select your option(1-4) ";
cin>>ch;
switch(ch)
{
case '1':clrscr();
book_issue();
break;
case '2':book_deposit();
break;
case '3':admin_menu();
break;
case '4': exit(0);
break;
default : cout<<"\a";
}
} while(ch!='4');
}


//Code Finished and error free code written using file handling and classes 
