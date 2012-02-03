#include <iostream>
#include <iomanip>
#include<climits>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include<cctype>
#include<cstdio>
#include<soci.h>
#include<soci-sqlite3.h>
using namespace std;
using namespace soci;

int read_int();
int read1_int();
session sql (sqlite3, "Mod.db");
class login
{
    public:
        string master_id;
        string master_pass;
        login();              //Constractor function
        void check();
};
login::login()
{
    cout << "\t\t\tID AND PASSWORD VARIFICATION\n";
    cout << "\t\t\t-----------------------------\n";
    cout << "\nEnter Ticket master id:";
    cin >> master_id;
    cout << "Password:";
    cin >> master_pass;
}
void login::check()
{
    if (master_id == "pri" && master_pass == "123")
    {
        cout << "--------------------------------------------------\n";
    }
    else
    {
        cout << "You enter wrong Id & password!\n\n";
        cout << "Again ";
        login();
    }
}
class reserv
{
    public:
        int no;
        string date_of_travel;
        int seatno;
        string birth;
        string pasenger_name;
        int pasenger_age;
        int pasenger_pnr;
        string pasenger_address;
        void train_pasenger();
} p;

void reserv::train_pasenger()
{
   int no_seat;

    cout << "\t\t\t++++++++++++++++++++++\n";
    cout << "\t\t\t+ TICKET RESERVATION +\n";
    cout << "\t\t\t++++++++++++++++++++++";
    cout << "\n-------------------------------------------------------------------------------\n";
    cout << "Train no" << "\t" << "Train name" << "\t" << "Broding st." << "\t" << "Dest st." << "\t" << "Rate/Ticket";
    cout << "\n-------------------------------------------------------------------------------\n";
    cout << "1234" << "\t\t" << "Chennai mail" << "\t" << "MAS" << "\t\t" << "HWH" << "\t\t" << "400" << endl;

    cout <<"\nHow many seat do you want to reserve ?\n";
    cin>> no_seat;

    int count = 0;

  do
    {
    cout << "\n\t\t\t Enter Pasenger detail\n\n";

        cout << "\nEnter Date of Travel(DD/MM/YYYY):";
        cin >> date_of_travel;
        cout << "\nEnter pasenger name:";
        cin >> pasenger_name;
        cout << "\nEnter pasenger age:";
        cin >> pasenger_age;
        cout << "\nEnter pasenger address:";
        cin >> pasenger_address;
        cout << "\n\n";


       sql << "select min(Pas_pnr) \
                    from Pnr_status \
                    where Pas_pnr not in (select pasenger_pnr \
                                 from reserve)",
        into (pasenger_pnr);


        sql << "select min(seatno) \
                    from seat_nos \
                    where seatno not in (select seatno \
                                 from reserve \
                                 where date_of_travel = :date_of_travel)",
        use (date_of_travel),
        into (seatno);



            if (seatno % 3 == 0)
            {
                birth = "UB";
                sql << "insert into reserve(pasenger_pnr,pasenger_name, pasenger_age, pasenger_address, date_of_travel, seatno,birth) \
            values(:pasenger_pnr,:pasenger_name,:pasenger_age,:pasenger_address,:date_of_travel, :seatno,:birth)",
                use (pasenger_pnr),
                use (pasenger_name),
                use (pasenger_age),
                use (pasenger_address),
                use (date_of_travel),
                use (seatno),
                use (birth);


            }
            else if ( (seatno + 1) % 3 == 0)
            {
                birth = "MB";
                sql << "insert into reserve(pasenger_pnr,pasenger_name, pasenger_age, pasenger_address, date_of_travel, seatno,birth) \
            values(:pasenger_pnr,:pasenger_name,:pasenger_age,:pasenger_address,:date_of_travel, :seatno,:birth)",
                use (pasenger_pnr),
                use (pasenger_name),
                use (pasenger_age),
                use (pasenger_address),
                use (date_of_travel),
                use (seatno),
                use (birth);

            }
            else
            {
                birth = "LB";
                sql << "insert into reserve(pasenger_pnr,pasenger_name, pasenger_age, pasenger_address, date_of_travel, seatno,birth) \
            values(:pasenger_pnr,:pasenger_name,:pasenger_age,:pasenger_address,:date_of_travel, :seatno,:birth)",
                use (pasenger_pnr),
                use (pasenger_name),
                use (pasenger_age),
                use (pasenger_address),
                use (date_of_travel),
                use (seatno),
                use (birth);

            }
            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
            cout << "\n\n\t\t\tThe TICKET detail is:\n";
            cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout << "|                                                              |\n";
            cout << "| PNR" << "\t" << "Name" << "\t" << "Age" << "\t" << "Address" << "\t    " << "Date" << "\t" << "SeatNo" << "\t" << "Berth" << "  |" << endl;
            cout << "| ------------------------------------------------------------ |\n";
            cout << "| " << pasenger_pnr << "\t" << pasenger_name << "\t" << pasenger_age << "\t" << pasenger_address << "\t" << date_of_travel << "\t" << seatno << "\t" << birth << "     |" << endl;
            cout << "|                                                              |\n";
            cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";


        count++;
    }while(count<no_seat);
            cout << "\n**Ticket reserve successfully**";
            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout << "\nYou Have To pay Rs."<<400*no_seat<< "\tonly";
            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    }


class checkpnr: public reserv //inheritence
{
    public:
        void check_seat_status();
} d;
void checkpnr:: check_seat_status()
{
    cout << "\nEnter your PNR NO:";
    pasenger_pnr = read_int();
    reserv p;
    sql << "select pasenger_pnr,pasenger_name, pasenger_age, pasenger_address,date_of_travel, seatno, birth\
                    from reserve \
                    where pasenger_pnr = :pasenger_pnr",
    use (pasenger_pnr),
    into (p.pasenger_pnr),
    into (p.pasenger_name),
    into (p.pasenger_age),
    into (p.pasenger_address),
    into (p.date_of_travel),
    into (p.seatno),
    into (p.birth);

    if (pasenger_pnr == p.pasenger_pnr)
    {
        cout << "\nThe TICKET detail is:\n";
        cout << "PNR" << "\t" << "Name" << "\t" << "Age" << "\t" << "Address" << "\t    " << "Date" << "\t" << "SeatNo" << "\t" << "Berth" << endl;
        cout << "-------------------------------------------------------------\n";
        cout << p.pasenger_pnr << "\t";
        cout << p.pasenger_name << "\t";
        cout << p.pasenger_age << "\t";
        cout << p.pasenger_address << "\t  ";
        cout << p.date_of_travel << "\t";
        cout << p.seatno << "\t";
        cout << p.birth << "\n\n";
    }
    else
    {
        cout << "\nSorry you enter wrong PNR";
    }

}


class cancel: public reserv
{
    public:
        void cancellation();
} c;
void cancel ::cancellation()
{
    cout << "\t\t\t+++++++++++++++++\n";
    cout << "\t\t\t+ TICKET CANCEL +\n";
    cout << "\t\t\t+++++++++++++++++\n\n";
    cout << "\t\tTrain no" << "\t" << " Train name" << endl;
    cout << "\t\t----------------------------\n";
    cout << "\t\t1234" << "\t\t" << "Chennai mail" << endl;
    cout << "\n\nEnter PNR NO:";
    pasenger_pnr = read1_int();

    reserv p;
    sql << "select pasenger_pnr,pasenger_name, pasenger_age, pasenger_address,date_of_travel, seatno, birth \
                    from reserve \
                    where pasenger_pnr = :pasenger_pnr",
    use (pasenger_pnr),
    into (p.pasenger_pnr),
    into (p.pasenger_name),
    into (p.pasenger_age),
    into (p.pasenger_address),
    into (p.date_of_travel),
    into (p.seatno),
    into (p.birth);

    if (pasenger_pnr == p.pasenger_pnr)
    {
        cout << "PNR" << "\t" << "Name" << "\t" << "Age" << "\t" << "Address" << "\t  " << "Date" << "\t      " << "SeatNo" << "  " << "Berth" << endl;
        cout << "-----------------------------------------------------------\n";
        cout << p.pasenger_pnr << "\t";
        cout << p.pasenger_name << "\t";
        cout << p.pasenger_age << "\t";
        cout << p.pasenger_address << "\t";
        cout << p.date_of_travel << "\t";
        cout << p.seatno << "\t";
        cout << p.birth << "\n\n";


        sql << "delete from reserve \
                      where pasenger_pnr = :pasenger_pnr",
        use (pasenger_pnr);
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        cout << "\n**Ticket cancel successfully**\n\n";
        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        cout << "\nCancellation charge Rs.40";
        cout << "\nYou Will Get Refund Rs.370/- only";


    }

    else
    {
        cout << "\nSorry yuo enter wrong PNR so cancellation is not possible!";
    }

}



class view: public reserv
{
    public:
        void view_datewise_data();
        void view_totaldata();
} a;
void view:: view_datewise_data()
{
    cout << "\nEnter the Date(DD/MM/YYYY):";
    cin >> date_of_travel;

    string quary = "select pasenger_pnr,pasenger_name, pasenger_age, pasenger_address,date_of_travel,seatno,birth \
                    from reserve \
                    where date_of_travel=:date_of_travel";


    statement st = (sql.prepare << quary,
                    use (date_of_travel),
                    into (pasenger_pnr),
                    into (pasenger_name),
                    into (pasenger_age),
                    into (pasenger_address),
                    into (date_of_travel),
                    into (seatno),
                    into (birth));
    st.execute();
    cout << "\t" << "PNR"
         << "\t" << "NAME"
         << "\t" << "AGE"
         << "\t" << "ADDRESS"
         << " \t" << "DATE"
         << "\t " << "SEATNO"
         << "\t " << "BERTH"
         << endl;
    cout << "\n\t---------------------------------------------------------------\n";

    while (st.fetch())
    {

        cout << "\n";
        cout << "\t" << pasenger_pnr
             << "\t" << pasenger_name
             << "\t" << pasenger_age
             << "\t" << pasenger_address
             << "\t    " << date_of_travel
             << "\t    " << seatno
             << "\t " << birth
             << endl;
    }
}

void view:: view_totaldata()
{
    cout << "\t" << "PNR"
         << "\t" << "NAME"
         << "\t" << "AGE"
         << "\t" << "ADDRESS"
         << " \t" << "DATE"
         << "\t " << "SEATNO"
         << "\t " << "BERTH"
         << endl;
    cout << "\n\t---------------------------------------------------------------\n";
    string query = "select pasenger_pnr,pasenger_name, pasenger_age, pasenger_address,date_of_travel,seatno,birth \
                    from reserve";
    statement st = (sql.prepare << query,
                    into (pasenger_pnr),
                    into (pasenger_name),
                    into (pasenger_age),
                    into (pasenger_address),
                    into (date_of_travel),
                    into (seatno),
                    into (birth));
    st.execute();

    while (st.fetch())
    {
        cout << "\n";
        cout << "\t" << pasenger_pnr
             << "\t" << pasenger_name
             << "\t" << pasenger_age
             << "\t" << pasenger_address
             << "\t    " << date_of_travel
             << "\t    " << seatno
             << "\t " << birth
             << endl;
    }

}



void create_tables()
{
    sql << "create table if not exists seat_nos \
            (seatno)";

    sql << "create table if not exists reserve ( \
               pasenger_pnr integer primary key,\
               pasenger_name varchar, \
               pasenger_age integer, \
               pasenger_address varchar,\
               date_of_travel varchar, \
               seatno integer,\
               birth varchar\ )";
}
void take_action1 (int ch)
{
    login l;
    l.check();
    system ("cls");
    cout << "\t\t*------------Welcome to Indian railway------------*\n";
    int cho;

    do
    {

        cout << "\n\n\t\t\t       ***ADMIN MANU***";
        cout << "\n\t\t\t  ------------------------------";
        cout << "\n\t\t\t | 1:Reservation                |";
        cout << "\n\t\t\t | 2:Cancellation               |";
        cout << "\n\t\t\t | 3:PNR                        |";
        cout << "\n\t\t\t | 4:View Total Reservation     |";
        cout << "\n\t\t\t | 5:View Date-wise Reservation |";
        cout << "\n\t\t\t | 6:Exit                       |";
        cout << "\n\t\t\t  ------------------------------";
        cout << "\n\nEnter your choice(ADMIN): ";
        cin >> cho;

        switch (cho)
        {
            case 1:
                system ("cls");
                p.train_pasenger();
                break;

            case 2:
                system ("cls");
                c.cancellation();
                break;
            case 3:
                system ("cls");
                cout << "\t\t\tPNR STATUS CHECK\n";
                cout << "\t\t\t-----------------\n";
                d.check_seat_status();
                break;
            case 4:
                system ("cls");
                cout << "\t\t\tTOTAL RESERVATION DATABASE\n";
                cout << "\t\t\t--------------------------\n";
                a.view_totaldata();
                break;
            case 5:
                system ("cls");
                cout << "\t\t\tDATE-WISE RESERVATION DATABASE\n";
                cout << "\t\t\t------------------------------\n";
                a.view_datewise_data();
                break;
            case 6:
                exit (0);
        }
    }
    while (cho < 6);


}
void take_action2 (int ch)
{
    int che;

    do
    {

        cout << "\n\t\t\t       ***USER MANU***";
        cout << "\n\t\t\t  -------------------------------";
        cout << "\n\t\t\t | 1:PNR status check            |";
        cout << "\n\t\t\t | 2:View Date-wise Reservation  |";
        cout << "\n\t\t\t | 3:Exit                        |";
        cout << "\n\t\t\t  -------------------------------";
        cout << "\n\nEnter your choice(USER):";
        cin >> che;

        switch (che)
        {
            case 1:
                system ("cls");
                cout << "\t\t\tWELCOME TO PNR STATUS CHECK\n";
                cout << "\t\t\t---------------------------\n";
                d.check_seat_status();
                break;
            case 2:
                system ("cls");
                cout << "\t\t\tDATE-WISE RESERVATION DATABASE\n";
                cout << "\t\t\t------------------------------\n";
                a.view_datewise_data();
                break;
            case 3:
                exit (0);
        }
    }
    while (che < 3);
}
void clrscr()
{
    system ("cls");
}
int read_int()
{
    int temp;

    while (! (cin >> temp))
    {
        cin.clear();
        cin.ignore (INT_MAX, '\n');
        cout << "\n Invalid PNR number! ";
        cout << "\n\nAgain Enter Your PNR number: ";

    }

    return temp;
}
int read1_int()
{
    int temp;

    while (! (cin >> temp))
    {
        cin.clear();
        cin.ignore (INT_MAX, '\n');
        cout << "\n Invalid PNR number! ";
        cout << "\nIt is not possible to cancel";
        cout << "\n\nAgain Enter Your PNR number: ";

    }

    return temp;
}
int main()
{
    try
    {
        create_tables();
        int ch;

        do
        {
            cout << "\n\t\t\t    ***Manu***";
            cout << "\n\t\t\t ----------------";
            cout << "\n\t\t\t | 1:Admin      |";
            cout << "\n\t\t\t | 2:Local user |";
            cout << "\n\t\t\t ----------------";
            cout << "\n\nEnter your choice: ";
            cin >> ch;

            switch (ch)
            {
                case 1:
                    system ("cls");
                    take_action1 (ch);
                    break;

                case 2:
                    system ("cls");
                    cout << "*\t\t------------Welcome to Indian railway------------*\n";
                    take_action2 (ch);
                    break;
                case 3:
                    exit (0);
            }
        }
        while (ch < 3);
    }
    catch (exception &e)
    {
        cerr << "\n Error: " << e.what() << endl;
    }

    return 0;

}
