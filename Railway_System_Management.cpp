#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<time.h>
#include<ctype.h>
#include <time.h>
#include <windows.h>
#include <process.h>
#include <unistd.h>
#include<iostream>
#include<istream>
#include<ostream>
#include<fstream>
using namespace std;


int number_of_trains = 1;


void process_time(int index, int coo);
void gotoxy(int x, int y);
int options();
void setter_basic();
void setter_infos(int n);
void time_sc();
void current_time();
void intro();
void allocate_trains();
void change_current_info();

/*bool timelag()
{
   time_t ob;
   int seconds;
   ob = clock();
   seconds = ob/CLOCKS_PER_SEC;

   if(seconds == 60)
   {
       system("cls");
   }
}*/
class train
{
private:
    char from[50];
    char to[50];
    bool seats[100];
    int leaveing_time[3];
    int price_of_ticket;
public:
    train()
    {
        strcpy(from,"dhaka");
        strcpy(to , "NULL");
        for(int i=0;i<100;i++)
        {
            seats[i] = 0;
        }
        price_of_ticket = 250;
        leaveing_time[0]=0;
        leaveing_time[1]=0;
        leaveing_time[2]=0;
    }
    void set_from(char from_temp[20])
    {
        strcpy(from, from_temp);
    }
    void set_price_of_ticket(int temp)
    {
        price_of_ticket = temp;
    }
    void set_to(char to_temp[20])
    {
        strcpy(to,to_temp);
    }
    void set_seats(bool temp, int pos)
    {
        seats[pos] = temp;
    }
    void set_leaveing_time(int temp[3])
    {
        for(int i=0; i<3; i++)
        {
            leaveing_time[i]=temp[i];
        }
    }
    char* get_from()
    {
        return from;
    }
    char* get_to()
    {
        return to;
    }
    bool* get_seats_com()
    {
        return seats;
    }
    int* get_leaveing_time()
    {
        return leaveing_time;
    }
    int get_price_of_tickets(int i)
    {
        return i*price_of_ticket;
    }
    void book_seats(int i)
    {

        int book;
        cout<<"Loading... Please wait"<<endl;
        for(int c=0; c<i; c++)
        {
            while(1)
            {
                 srand(time(NULL));
                 book = rand() % 100;
                 if(seats[book] == 0)
                 {
                     break;
                 }
            }
            seats[book] = 1;
        }
    }
    int available_seats()
    {
        int available=0;
        for(int i=0; i<100;i++)
        {
            if(seats[i]==0)
            {
                available++;
            }
        }
        return available;
    }
} *ob;
void check_seats()
{
        system("cls");
        Sleep(1000);//////
        int j=3;
        system("cls");
        current_time();
        int trains=0;
        gotoxy(2, 2);
        cout<<"---------------------------------------------------------------------------";
        for(j=3; j<(number_of_trains*2)+3; j=j+2)
        {
            for(int i=0; i<75; i++)
            {

               gotoxy(2+i, j+1);
               cout<<"-";
               gotoxy(25, j);
               cout<<"|";
               gotoxy(50, j);
               cout<<"|";
               gotoxy(15, j);
               cout<<ob[trains].get_to();
               gotoxy(35,j);
               cout<<ob[trains].available_seats();//////seats available
               process_time(trains,j);

           }
           trains++;
       }/////deletable
       gotoxy( 0, j+1);
    int booked_seats;
    int train_no;
    cout<<"Please enter the number of train you want to book ticket in: ";
    cin>>train_no;
    cout<<"There are "<<ob[train_no-1].available_seats()<<" available sits"<<endl;
    cout<<"Please enter how many seats you want to book: ";
    cin>>booked_seats;
    cout<<"The price of those ticket is: "<<ob[train_no-1].get_price_of_tickets(booked_seats)<<endl;
    cout<<"Do you want to proceed? (yes = 1 and no = 0): ";
    bool choice;
    cin>>choice;
    if(choice)
    {
        ob[train_no-1].book_seats(booked_seats);
        cout<<"Seats has been booked"<<endl<<"There are about "<<ob[train_no-1].available_seats()<<" remaining seats"<<endl;
    }

}
void file_to_class()
{
    system("cls");
    ifstream iopen;
    char filename[20];
    char from[100][20];
    char to[100][20];
    int train_time[100][3];
    int counter_train=0;
    int price[100];

    cout<<"Please enter the name of the file (make sure it is in the same folder as the cpp file itself):";
    cin>>filename;
    iopen.open(filename);

    if(!iopen.is_open())
    {
        system("cls");
        cout<<"Failed to open the file you were looking for. Please enter the name correctly with .txt ";
//        return 0;
    }

    while(iopen>>from[counter_train]>>to[counter_train]>>train_time[counter_train][0]>>train_time[counter_train][1]>>train_time[counter_train][2]>>price[counter_train])
    {
        counter_train++;
    }
    number_of_trains = counter_train;
    allocate_trains();
    system("cls");
    cout<<"Loading all the files.....Please wait"<<endl;
    for(int i=0; i<counter_train; i++)
    {
        ob[i].set_from(from[i]);
        ob[i].set_to(to[i]);
        ob[i].set_leaveing_time(train_time[i]);
        ob[i].set_price_of_ticket(price[i]);
    }
    cout<<"Successful..."<<endl;
    Sleep(1000);
    int c=0;
    while(c<=10)
    {
        system("cls");
        time_sc();
        c++;
        Sleep(1000);
    }

}
void process_time(int index, int coo)
{
    int *temp_time = ob[index].get_leaveing_time();
    time_t now;
    tm leaving_time;
    int seconds, temp_second, temp_minutes, temp_hour;

    time(&now);  /* get current time; same as: now = time(NULL)  */

    leaving_time = *localtime(&now);

    leaving_time.tm_hour = temp_time[0]; leaving_time.tm_min = temp_time[1]; leaving_time.tm_sec = temp_time[2];
    leaving_time.tm_mon = 10;  leaving_time.tm_mday = 17;

    seconds = difftime(mktime(&leaving_time),now);
    if(seconds/60 >= 60)
    {
        temp_hour= seconds / 3600;
        seconds = seconds % 3600;
        temp_minutes = seconds / 60;
        seconds = seconds % 60;
    }
    else if(seconds >=60)
    {
        temp_hour= 0;
        temp_minutes = seconds / 60;
        seconds = seconds % 60;
    }
    else
    {
        temp_hour = 0;
        temp_minutes = 0;

    }
    gotoxy(59, coo);
    printf ("%d : %d : %d",temp_hour, temp_minutes, seconds);
}
void gotoxy(int x, int y)
{

    COORD coord;

    coord.X = x;

    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
int options()
{
    while(1)
    {
        gotoxy(20, 0);
        cout<<"Railway Station Of Dhaka"<<endl;
        current_time();
        cout<<"Please choose what you want to do-"<<endl;
        cout<<"1. Take informations from file"<<endl;
        cout<<"2. Check informations about trains"<<endl;
        //cout<<"2. Check seats on a particular train"<<endl;
        cout<<"3. Tickets booking"<<endl;
        cout<<"4. Pause the system"<<endl;
        cout<<"5. Edit the train information"<<endl;
        cout<<"6. Put in information about trains"<<endl;
        cout<<"7. Refresh the screen"<<endl;
        cout<<"8. Exit"<<endl;
        cout<<"Set your choice: ";

        int choice;
        cin>>choice;
        if(choice == 1)
        {
            file_to_class();
        }
        else if(choice == 2)
        {
            int c=0;
            while(c<=10)
            {
                system("cls");
                time_sc();
                c++;
                Sleep(1000);
            }
        }
        else if(choice == 3)
        {
            check_seats();
            system("pause");
        }
        else if(choice == 4)
        {
            cout<<endl;
            system("pause");
        }
        else if(choice == 6)
        {
            setter_basic();
        }
        else if(choice == 7)
        {
            system("cls");
        }
        else if(choice == 8)
        {
            exit(0);
        }
        else if(choice == 5)
        {
            change_current_info();
        }
        system("cls");
    }
}
void change_current_info()
{
    system("cls");
    time_sc();
    gotoxy(0, (number_of_trains*2)+3);
    cout<<"put the serial number of the train: ";
    int train_no;
    cin>>train_no;
    cout<<"Please select what do you want to change: "<<endl;
    cout<<"1. Destination";
    cout<<"2. Departure time";
    cout<<"3. Amount of seats";
    cout<<"4. Price of a ticket";
    int i;
    cin>>i;
    if(i==1)
    {
        system("cls");
        Sleep(1000);
        char changed_destination[20];
        cout<<"Please enter the name of that place: ";
        cin>>changed_destination;
        ob[train_no].set_to(changed_destination);
    }
}
void allocate_trains()
{
    ob = new train[number_of_trains];
}
void setter_basic()
{
    system("cls");
    cout<<"Please enter the number of trains you want to keep track of:";
    cin>>number_of_trains;
    allocate_trains();
    setter_infos(number_of_trains);
}
void setter_infos(int n)
{
    for(int i=0; i<n; i++)
    {
        char from[50], to[50];
        cout<<"Please enter the place where it is leaving from: ";
        cin>>from;
        ob[i].set_from(from);
        cout<<"Where is the train headed: ";
        cin>>to;
        ob[i].set_to(to);
        int temp_time[3];
        cout<<"Please enter the time when the train will leave"<<endl;
        cout<<"hour :";
        cin>>temp_time[0];
        cout<<"minutes : ";
        cin>>temp_time[1];
        cout<<"seconds : ";
        cin>>temp_time[2];
        ob[i].set_leaveing_time(temp_time);
        cout<<"Price of a ticket is: ";
        int price;
        cin>>price;
        ob[i].set_price_of_ticket(price);
        system("cls");
        Sleep(1000);
    }
}
void time_sc()
{
   // system("cls");
    int c=0;
    //while(1 && c<=10)
    {
     //   Sleep(1000);
       // system("cls");
        current_time();
        int trains=0;
        gotoxy(2, 2);
        cout<<"---------------------------------------------------------------------------";
        for(int j=3; j<(number_of_trains*2)+3; j=j+2)
        {
            for(int i=0; i<75; i++)
            {

               gotoxy(2+i, j+1);
               cout<<"-";
               gotoxy(20, j);
               cout<<"|";
               gotoxy(38, j);
               cout<<"|";
               gotoxy(56, j);
               cout<<"|";
               gotoxy(8, j);
               cout<<ob[trains].get_to();
               gotoxy(25,j);
               cout<<ob[trains].available_seats();//////seats available
               gotoxy(42, j);
               cout<<ob[trains].get_price_of_tickets(1);
               gotoxy(59, j);
               process_time(trains,j);

           }
           trains++;
       }
      // c++;
    }


}
void current_time()
{
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    gotoxy(50,1);
    cout<<asctime(timeinfo);

}
void intro()
{
    /*gotoxy(20, 0);
    cout<<"This is the railway station of Dhaka"<<endl;
    current_time();*/
    options();
}
int main()
{
       ob = new train;
       intro();
       Sleep(1000);
       system("cls");



}
