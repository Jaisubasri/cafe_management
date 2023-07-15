#include<iostream>
#include<fstream>
#include<cstring>
#include<stdio.h>
#include<cctype>
#include<iomanip>
using namespace std;
struct Time         //the structure stores the time with hour ,min and seconds
{
    float hour;
    float mins;
    float secs;
};
Time findTimeDifference(Time t1, Time t2)           //function finds the difference between the times
{
    Time diff;
    if(t2.secs > t1.secs)
    {
        --t1.mins;
        t1.secs += 60;
    }

    diff.secs = t1.secs - t2.secs;
    if(t2.mins > t1.mins)
    {
        --t1.hour;
        t1.mins += 60;
    }

    diff.mins = t1.mins-t2.mins;
    diff.hour = t1.hour-t2.hour;

    return diff;
}
int check_phone(char* phone_no)             //the phone number is validated
{
    int i,f=0;
    for(i=0;phone_no[i]!='\0';i++)
    {
        if(isdigit(phone_no[i]))
        {
            f++;
            continue;
        }
        else
        {
            f=0;
            cout<<"\n";
            cout<<setw(60)<<"INVALID MOBILE NUMBER!\n\n";
            cout<<setw(60)<<"Please enter correct mobile number\n";
            return 0;
        }
    }
    if(i!=10)
    {
        cout<<"\n";
        cout<<setw(60)<<"INVALID MOBILE NUMBER!\n\n";
        cout<<setw(60)<<"Please enter correct mobile number\n";
        return 0;
    }
    if(f!=0)
        return 1;
}
class login                     //login class for user to login in
{
    public:
    string name,email,phone;
    public:
    friend istream& operator >> (istream& cin, login& obj3)
    {
        int num,n;
        cout<<setw(50)<<"Enter your name\t\t";
        cin>>obj3.name;
        cout<<"\n";
        cout<<setw(50)<<"Enter mail id\t\t";
        cin>>obj3.email;
        cout<<"\n";
        do
        {
            cout<<setw(50)<<"Enter phone number\t\t";
            cin>>obj3.phone;
            n=obj3.phone.length();
            char arr[n+1];
            strcpy(arr,obj3.phone.c_str());
            num=check_phone(arr);
        }while(num==0);
        return cin;
    }
};
class booking               //booking is use to book either for member login or nonmember login
{
    public:
    void memberlogin();
    void nonmemberlogin();
    void loggedin_mem();
};
class computerentry : public login          //this is the user for add computers
{
    public:
    void addcomputer();
    void show_computer();
    void search_computer();
    void delete_computer();
    void update_computer();
    void display_stock();
};
class memberentry               //this is the member entry to do members operations
{
    public:
    void addmember();
    void show_member();
    void search_member_id();
    void search_member_name();
    void delete_member();
};
class  masterentry : public login           //this is the master entry to do master operations
{
    memberentry *member = new memberentry();
    computerentry *computer = new computerentry();
    public:
    void member_enter();
    void computer_enter();
};
class cafemanagement : public login                //the class cafemanagement is to book charges and login
{
    booking *b=new booking();
    public:
    void book();
    int charges();
};
int isSubstring(string s1, string s2)
{
    int j;
    int M = s1.length();
    int N = s2.length();
    for (int i = 0; i <= N - M; i++)
    {
        for (j = 0; j < M; j++)
            if (s2[i + j] != s1[j])
                break;
        if (j == M)
            return i;
    }

    return -1;
}
void masterentry :: member_enter()
{
    int choice=0;
    do{
    cout<<"\n\n\n\t\t1.ADD MEMBER\n\n\t\t2.SHOW MEMBERS \n\n\t\t3.SEARCH MEMBER BY ID\n\n\t\t4.SEARCH BY NAME\n\n\t\t5.DELETE MEMBER\n\n\t\t6.EXIT\t";
    cin>>choice;
    switch(choice)
    {
        case 1:
            member->addmember();
            break;
        case 2:
            member->show_member();
            break;
        case 3:
            member->search_member_id();
            break;
        case 4:
            member->search_member_name();
            break;
        case 5:
            member->delete_member();
            break;
        case 6:
            break;
        default:
            break;
    }
    }while(choice!=6);
}
void memberentry :: addmember()
{
    string name,address ,email,password,dummy;
    int check=0,member_id;
    string phone;
    cout<<"\n\t\tADDING MEMBER \t\n\n";
    cout<<setw(50)<<"Enter the member name to be added :\t";
    getline(cin,dummy);
    getline(cin,name);
    string file1("Members.txt");
    ofstream fout;
    fout.open(file1, std::ios_base::app);
    cout<<setw(50)<<"Enter the valid member id  :\t";
    cin>>member_id;
    cout<<setw(50)<<"Enter address :\t";
    getline(cin,dummy);
    getline(cin,address);
    cout<<setw(50)<<"Enter phone number :\t";
    cin>>phone;
    cout<<setw(50)<<"Enter the email id:\t";
    getline(cin,dummy);
    getline(cin,email);
    cout<<setw(50)<<"Enter password :\t";
    getline(cin,password);
    fout<<name<<"\t"<<member_id<<"\t"<<address<<"\t"<<phone<<"\t"<<email<<"\t"<<password<<"\n";
    fout.close();
    cout<<"\n\n\tTHE MEMBER IS SUCCESSFULLY ADDED !! ";
}
void memberentry :: show_member()
{
    string info;
    cout<<setw(50)<<"\n\nMEMBERS INFORMATION\n";
    ifstream file2("Members.txt");
    while(getline(file2,info))
    {
        cout<<info<<endl;
    }
    file2.close();
}
void memberentry :: search_member_id()
{
    int res;
    string search_id,info,dummy;
    system("cls");
    cout<<setw(50)<<"Enter the member id to be searched for \t";
    getline(cin,dummy);
    getline(cin,search_id);
    fstream file3;
    string word,word1;
    file3.open("Members.txt");
    ifstream file4("Members.txt");
    while(file3>>info)
    {
            if(info==search_id)
            {
                while(getline(file4,word))
                {
                    res=isSubstring(info,word);
                    if(res!=-1)
                    {
                       cout<<word;
                       break;
                    }
                }
            }
    }
    file3.close();
    file4.close();
}
void memberentry :: search_member_name()
{
    int res;
    string search_name,info,dummy;
    system("cls");
    cout<<setw(50)<<"Enter the member name to be searched for \t";
    getline(cin,dummy);
    getline(cin,search_name);
    fstream file3;
    string word,word1;
    file3.open("Members.txt");
    ifstream file4("Members.txt");
    while(file3>>info)
    {
            if(info==search_name)
            {
                while(getline(file4,word))
                {
                    res=isSubstring(info,word);
                    if(res!=-1)
                    {
                       cout<<word;
                       break;
                    }
                }
            }
    }
    file3.close();
    file4.close();
}
void memberentry :: delete_member()
{
    int res;
    string del_member,word,line;
    system("cls");
    cout<<setw(50)<<"Enter the name of the member to be deleted \t";
    cin>>del_member;
    fstream file4;
    file4.open("Members.txt");
    ifstream file5("Members.txt");
    string file("del_members.txt");
    ofstream fout;
    fout.open(file, std::ios_base::out);
    while(file4>>word)
    {
        if(word==del_member)
        {

            while(getline(file5,line))
            {
                res=isSubstring(word,line);
                if(res==-1)
                {
                   fout<<line;
                }
            }
        }
    }
    fout.close();
    file4.close();
    file5.close();
    ifstream file7("del_members.txt");
    string file6("Members.txt");
    ofstream fout1;
    fout1.open(file6, std::ios_base::out);
    while(getline(file7,word))
    {
        fout1<<word;
    }
}
void  masterentry :: computer_enter()
{
    int choice=0;
    cout<<setw(50)<<"COMPUTER ENTRY";
    do{
    cout<<"\n\n\n\n\t\t1.ADD COMPUTER\n\n\t\t2.SHOW COMPUTER \n\n\t\t3.SEARCH COMPUTER\n\n\t\t4.DELETE COMPUTER\n\n\t\t5.DISPLAY STOCK \n\n\t\t6.EXIT\n";
    cin>>choice;
    switch(choice)
    {
        case 1:
            computer->addcomputer();
            break;
        case 2:
            computer->show_computer();
            break;
        case 3:
            computer->search_computer();
            break;
        case 4:
            computer->delete_computer();
            break;
        case 5:
            computer->display_stock();
            break;
        default:
            break;
    }
    }while(choice!=6);
}
void computerentry :: addcomputer()
{
    string computer_name,ip_address,process_model,dummy;
    int memory,unique_code;
    update_computer();
    cout<<"\n\t\tADDING COMPUTER\n";
    cout<<setw(50)<<"\t\tEnter the computer unique code  to be added :\t";
    cin>>unique_code;
    string file5("computers.txt");
    ofstream fout;
    fout.open(file5, std::ios_base::app);
    cout<<setw(50)<<"\t\tEnter the computer Name\t";
    getline(cin,dummy);
    getline(cin,computer_name);
    cout<<setw(50)<<"\t\tEnter the ip address of the computer\t";
    getline(cin,ip_address);
    cout<<setw(50)<<"\t\tEnter the process model \t";
    getline(cin,process_model);
    cout<<setw(50)<<"\t\tEnter the memory address of the computer\t";
    cin>>memory;
    fout<<unique_code<<"\t"<<computer_name<<"\t"<<ip_address<<"\t"<<process_model<<"\t"<<memory;
    fout<<"\n";
    fout.close();
}
void computerentry :: show_computer()
{
    string info;
    cout<<"\n\n\t\tCOMPUTERS INFORMATION\n";
    ifstream file5("computers.txt");
    while(getline(file5,info))
    {
        cout<<info<<endl;
    }
    file5.close();
}
void computerentry :: search_computer()
{
    int res;
    string unique_id,info,dummy;
    system("cls");
    cout<<setw(50)<<"Enter the computer unique id to be searched for \t";
    getline(cin,dummy);
    getline(cin,unique_id);
    fstream file3;
    string word,word1;
    file3.open("computers.txt");
    ifstream file4("computers.txt");
    while(file3>>info)
    {
            if(info==unique_id)
            {
                while(getline(file4,word))
                {
                    res=isSubstring(info,word);
                    if(res!=-1)
                    {
                       cout<<word;
                       break;
                    }
                }
            }
    }
    file3.close();
    file4.close();
}
void computerentry :: delete_computer()
{
    int res;
    string del_computer,word,line;
    system("cls");
    cout<<"Enter the name of the computer to be deleted \t";
    cin>>del_computer;
    fstream file4;
    file4.open("computers.txt");
    ifstream file5("computers.txt");
    string file("del_computers.txt");
    ofstream fout;
    fout.open(file, std::ios_base::out);
    while(file4>>word)
    {
        if(word==del_computer)
        {

            while(getline(file5,line))
            {
                res=isSubstring(word,line);
                if(res==-1)
                {
                   fout<<line;
                }
            }
        }
    }
    fout.close();
    file4.close();
    file5.close();
    ifstream file7("del_computers.txt");
    string file6("computers.txt");
    ofstream fout1;
    fout1.open(file6, std::ios_base::out);
    while(getline(file7,word))
    {
        fout1<<word;
    }
}
void computerentry :: update_computer()
{
    int num;
    fstream file;
    file.open("stock.txt");
    file>>num;
    num=num+1;
    string file1("stock.txt");
    ofstream fout;
    fout.open(file1, std::ios_base::out);
    fout<<num;
}
void computerentry :: display_stock()
{
    int num;
    ifstream file("stock.txt");
    file>>num;
    cout<<"\t\t\the Total no of computers in our  cafe is "<<num<<endl;
}
void cafemanagement :: book()
{
    int choice;
    do{
        cout<<"\n";
        cout<<setw(60)<<"BOOKING";
        cout<<"\n\n\t\t1.MEMBER LOGIN\n\n\t\t2.NON MEMBER LOGIN\n\n\t\t3.LOGGED IN MEMBERS\n\n\t\t4.EXIT\t\t";
        cin>>choice;
        switch(choice)
        {
            case 1:
            {
                b->memberlogin();
                break;
            }
            case 2:
            {
               b->nonmemberlogin();
                break;
            }
            case 3:
            {
                b->loggedin_mem();
                break;
            }

        }
    }while(choice!=4);
}
void booking :: memberlogin()
{
    int timing,res,login_time_hrs,login_time_min;
    int count1=0,count2=0;
    string id,info,dummy,word,NAME,PASSWORD;
    system("cls");
    cout<<setw(60)<<"MEMBER LOGIN \n";
    cout<<setw(50)<<"Enter the computer unique id of the computer \t";
    getline(cin,dummy);
    getline(cin,id);
    fstream file3;
    file3.open("computers.txt");
    ifstream file4("computers.txt");
    while(file3>>info)
    {
            if(info==id)
            {
                while(getline(file4,word))
                {
                    res=isSubstring(info,word);
                    if(res!=-1)
                    {
                       cout<<word;
                       break;
                    }
                }
            }
    }
    file3.close();
    file4.close();
    Time t1;
    cout<<setw(50)<<"Enter your name\t";
    cin>>NAME;
    cout<<setw(50)<<"Enter your password\t";
    cin>>PASSWORD;
    cout<<setw(50)<<"Enter login time  - hours\t";
    cin>>t1.hour;
    cout<<setw(50)<<"Enter login time  - min\t";
    cin>>t1.mins;
    cout<<setw(50)<<"Enter login time  - sec\t";
    cin>>t1.secs;
    ifstream file("Members.txt");
    while(file>>word)
    {
        if(word==NAME && count1==0)
        {
                while(file>>word && count1!=4)
                {
                    count1=(count1+1)%6;
                    continue;
                }
                cout<<word;
                if(word==PASSWORD)
                {
                    cout<<setw(50)<<"The given password and user name is valid !!! \n";
                    break;
                }
                else
                {
                    cout<<setw(50)<<"The entered name and password is not valid . Try again ! \n";
                    break;
                }
        }
        count1=(count1+1)%6;
    }
    string file5("Loggedin_members.txt");
    ofstream fout;
    fout.open(file5, std::ios_base::app);
    fout<<NAME<<"\t"<<PASSWORD<<"\t"<<login_time_hrs<<"\t"<<login_time_min;
    fout<<"\n";
    Time t2,diff;
    cout<<setw(50)<<"Enter the logout time - hours\t";
    cin>>t2.hour;
    cout<<setw(50)<<"Enter the logout time - min\t";
    cin>>t2.mins;
    cout<<setw(50)<<"Enter the logout time - sec\t";
    cin>>t2.secs;
    diff=findTimeDifference(t2,t1);
    cout<<"TIMING THE PERSON IN THE CAFE :"<<endl;
    cout<<"\t"<<diff.hour<<"\t"<<diff.mins<<"\t"<<diff.secs<<"\n";
    diff.secs=diff.secs/3600.0;
    diff.mins=diff.mins/60.0;
    diff.hour=diff.hour+diff.secs+diff.mins;
    string file6("charges.txt");
    ofstream fout1;
    fout1.open(file6, std::ios_base::out);
    fout1<<NAME<<"\t"<<diff.hour;
    fout1<<"\n";
}
void booking :: nonmemberlogin()
{
    string NAME,PASSWORD,dummy;
    cout<<setw(50)<<"Enter the name  :\t";
    getline(cin,dummy);
    getline(cin,NAME);
    string file1("Loggedin_members.txt");
    ofstream fout;
    fout.open(file1, std::ios_base::app);
    fout<<NAME<<"\t";
    cout<<setw(50)<<"Enter password :\t";
    getline(cin,PASSWORD);
    fout<<PASSWORD<<"\t";
    Time t1;
    cout<<setw(50)<<"Enter the login time in hours\t";
    cin>>t1.hour;
    fout<<t1.hour<<"\t";
    cout<<setw(50)<<"Enter the login time in minutes\t";
    cin>>t1.mins;
    fout<<t1.mins<<"\t";
    cout<<setw(50)<<"Enter the login time in seconds\t";
    cin>>t1.secs;
    fout<<t1.secs<<"\t";
    fout<<"\n";
    fout.close();
    Time t2,diff;
    cout<<setw(50)<<"Enter the logout time - hours\t";
    cin>>t2.hour;
    cout<<setw(50)<<"Enter the logout time - min\t";
    cin>>t2.mins;
    cout<<setw(50)<<"Enter the logout time - sec\t";
    cin>>t2.secs;
    diff=findTimeDifference(t2,t1);
    cout<<"\t"<<"TIMIMG THE PERSON IN THE CAFE: "<<endl;
    cout<<"\t"<<diff.hour<<"\t"<<diff.mins<<"\t"<<diff.secs<<"\n";
    diff.secs=diff.secs/3600.0;
    diff.mins=diff.mins/60.0;
    diff.hour=diff.hour+diff.secs+diff.mins;
    string file6("charges.txt");
    ofstream fout1;
    fout1.open(file6, std::ios_base::out);
    fout1<<NAME<<"\t"<<diff.hour;
    fout1<<"\n";
}
void booking :: loggedin_mem()
{
    int count=0;
    string word;
    ifstream file("Loggedin_members.txt");
    while(file>>word)
    {
        if(count==0)
        {
            cout<<"Name : "<<word<<endl;
        }
        else if(count==1)
        {
            cout<<"Password : "<<word<<endl;
            cout<<"************************************"<<endl;
        }
        count=(count+1)%5;
    }
    file.close();
}
int cafemanagement :: charges()
{
    int flag=0,count1=0,flag1=0;
    string name,password,dummy,word,line;
    int choice;
    float num;
    cout<<"\n\n\t\tEnter your role \n\n\t\t1.MEMBER \n\n\t\t2.NON MEMBER\n";
    cin>>choice;
    if(choice==1)
    {
        cout<<setw(50)<<"\t\tEnter your name \t";
        getline(cin,dummy);
        getline(cin,name);
        cout<<setw(50)<<"\t\tEnter your password\t";
        getline(cin,password);
        ifstream file("Members.txt");
        while(file>>word)
        {
            if(word==name && count1==0)
            {
                    while(file>>word && count1!=4)
                    {
                        count1=(count1+1)%6;
                        continue;
                    }
                    if(word==password)
                    {
                        cout<<"\n\t\tThe given password and user name is valid !!! \n";
                        flag1=1;
                        break;
                    }
                    else
                    {
                        cout<<"\n\t\tThe entered name and password is not valid . Try again ! \n";
                        flag=1;
                        flag1=1;
                        break;
                    }
            }
            count1=(count1+1)%6;
        }
        file.close();
        if(flag1==0 || flag==1)
        {
            cout<<"\n\t\tThe entered name and password are not valid\n";
            return 0;
        }
        if(flag==0)
        {
            ifstream file1("charges.txt");
            while(file1>>line)
            {
                if(line==name)
                {
                    file1>>num;
                    cout<<"\n\t\tYou've worked for "<<num<<"\t"<<"hours\n";
                    cout<<"\t\tThe total charges is "<<num*200<<endl;
                    break;
                }
            }
            file1.close();
        }
    }
    else if(choice==2)
    {
        cout<<"\n\t\tEnter your name \t";
        getline(cin,dummy);
        getline(cin,name);
        ifstream file1("charges.txt");
        while(file1>>line)
            {
                if(line==name)
                {
                    file1>>num;
                    cout<<"\n\t\tYou've worked for "<<num<<"\t"<<"hours\n";
                    cout<<"\n\t\tThe total charges is "<<num*250<<endl;
                    break;
                }
            }
    }
}
int main()
{
    string Id,dummy;
    int choice=0,choice1=0,choice2=0;
    login obj;
    cout<<"\t\t"<<setw(70)<<setfill('*');
    cout<<"\n\n\n";
    cout<<setw(70)<<setfill(' ')<<"WELCOME  TO CYBER CAFE MANAGEMENT \n"<<endl;
    cout<<setw(55)<<"LOGIN"<<endl;
    cin>>obj;
    system("cls");
    do
    {
    cout<<"\n\t\t\tEnter your choice\n\n\n\t\t1.MASTER ENTRY\n\n\t\t2.CAFE MANAGEMENT\n\n\t\t3.EXIT\t";
    cin>>choice;
    system("cls");
    switch(choice)
    {
        case 1:
        {
            masterentry obj1;
            cout<<"\n\n\n\t\t\t1.MEMBER ENTRY \n\n\t\t\t2.COMPUTER ENTRY\n\n\t\t\t3.RETURN\t\t";
            cin>>choice1;
            system("cls");
            if(choice1==1)
            {
                obj1.member_enter();
            }
            else if(choice1==2)
            {
                obj1.computer_enter();
            }
            else if(choice1==3)
            {
                break;
            }
            break;
        }
        case 2:
        {
            choice2=0;
            cafemanagement obj2;
            cout<<"\n\n\t\t1.BOOKING\n\n\t\t2.CHARGES\n\n\t\t3.RETURN\t\t";
            cin>>choice2;
            if(choice2==1)
            {
                obj2.book();
            }
            else if(choice2==2)
            {
                obj2.charges();
            }
            else
            {
                break;
            }
        }
        default:
        break;
    }
    }while(choice!=3);
}
