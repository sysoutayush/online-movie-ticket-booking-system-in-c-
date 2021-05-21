#include <iostream>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include<fstream>
// https://www.geeksforgeeks.org/readwrite-class-objects-fromto-file-c/
using namespace std;
void welcomemain();
void movie_function(struct userEntity userItem);
void addNewMovie(struct userEntity userItem);
void clearScreen();
void storeMovieInfo(struct movieEntity movieItem);
void readMovieInfo();
void storeUserInfo(struct userEntity userItem);
void userLogin();
void userWelcomeScreen(struct userEntity globalUserItem);
void userSignup();
void validateUser(string userName,string password);
void showUsersList(struct userEntity globalUserItem);
void showMovieList(struct userEntity userItem);
void bookMovieTicket(struct userEntity userItem);
void updateMovieHistory(struct userEntity userItem,struct movieBookingEntity movieBookingItem);
void show_movie_booking_history(struct userEntity globalUserItem);
string getMobileNumber(bool ShowMessage);
string getprice(bool ShowMessage);
bool is_number(const std::string& s);
bool compareString(string str1,string str2);
movieEntity getMovieItemById(int movieId);
struct movieEntity {
    public:
    string name;
    string time;
    string price;
    string date;
    int maxSeat;
    bool status;
};
struct movieBookingEntity{
    public :
        int movie_id;
        string date;
        string show_time;
        int totaltickets;
        double amount;
};


struct userEntity{
    public:
        string name;
        string mobile_number;
        string password;
        string role;
        bool status;
};
int main()
{
   welcomemain();
    return 0;
}
void clearScreen(){
system("cls");
}
void welcomemain()
{    int choice;
    cout<<"Welcome, \n ";
    string message="1. login\n 2. signup\n please enter your choice\n";
    cout<<message;
    cin>>choice;
    switch(choice)
        {
        case 1:
            clearScreen();
            userLogin();
            break;
        case 2:
            clearScreen();
            userSignup();
            break;
        default:
            clearScreen();
            cout<<"invalid choice\n";
            welcomemain();
        }
}

void userLogin()
{
    string userName,password;
    cout<<"enter User Name/Mobile no.= "; cin>>userName;
    cout<<"enter password= "; cin>>password;
    validateUser(userName,password);
}

void userWelcomeScreen(userEntity globalUserItem){
    int choice;
    cout<<"Welcome "+globalUserItem.name+"\n";
    string message="choice:\n 1. Book Movie Ticket\n ";
    if(globalUserItem.name=="soham"){
        message=message+"2. Manage Movie,\n 3. Show UserList\n 4. Logout\n";
    }else{
        message=message+"2. Show History,\n 3. Logout\n";
    }
    message=message+"\n please enter your choice\n";
    cout<<message;
    cin>>choice;
    switch(choice)
        {
        case 1:
            clearScreen();
            bookMovieTicket(globalUserItem);
            break;
        case 2:
        if(globalUserItem.name=="soham"){
            clearScreen();
            movie_function(globalUserItem);
        }else{
            clearScreen();
            show_movie_booking_history(globalUserItem);
        }
        break;
        case 3:
             if(globalUserItem.name=="soham"){
                clearScreen();
                showUsersList(globalUserItem);
            }
            else{
                clearScreen();
                welcomemain();
            }
            break;
        case 4:
             if(globalUserItem.name=="soham"){
                clearScreen();
                welcomemain();
            }else{
                clearScreen();
                cout<<"Invalid choice\n";
                userWelcomeScreen(globalUserItem);
            }
        default:
            clearScreen();
            cout<<"Invalid choice\n";
            userWelcomeScreen(globalUserItem);
        }
}

void userSignup()
{
   struct userEntity userItem;
   cout<<"enter your Name=";
   cin>>userItem.name;
   cout<<"enter Your mobile number= ";
   /*cin>>*/
   userItem.mobile_number=getMobileNumber(false);
   cout<<"enter Your password= "; cin>>userItem.password;
   userItem.status=true;
   storeUserInfo(userItem);
   clearScreen();
   cout<<"You have sucessfully signup, Have a nice day\n";
   welcomemain();
}

void movie_function(userEntity globalUserItem)
{
    int choice;
    string option=" 1. add movie,\n 2. show list,\n 3. back\n please enter your choice\n";
    cout<<option;
    cin>>choice;
    switch(choice)
    {
    case 1:
        addNewMovie(globalUserItem);
        break;
    case 2:
        clearScreen();
        showMovieList(globalUserItem);
        break;
    case 3:
        clearScreen();
        userWelcomeScreen(globalUserItem);
        break;
    default:
        clearScreen();
        cout<<"invalid choice";
        movie_function(globalUserItem);
    }
}

string getMobileNumber(bool ShowMessage)
{
    string line;
    string mobileNumber;
     while (getline(cin, line))
    {
        if (line.size() == 10)
        {
            if(is_number(line)){
                mobileNumber=line;
                break ;
            }else{
                cout << "Please enter Valid Number\n";
            }
        } else if(ShowMessage){
            cout << "Please enter Valid Number\n";
        }else{
            ShowMessage=true;
        }
    }
    return mobileNumber;
}

string getprice(bool ShowMessage)
{
    string line;
    string price;
     while (getline(cin, line))
        {
            if(is_number(line)){
                price=line;
                break ;
            }else{
                cout << "Please enter Valid Number\n";
            }
        }
    return price;

}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void show_movie_booking_history(userEntity userItem)
{
    int movieId=0;
    ifstream inFile;
    inFile.open("UserShowHistory.txt", ios::in);
    movieEntity movieItem;

    cout <<"MovieId  ";
    cout <<"Movie Name  ";
    cout <<"Price    ";
    cout <<"Time  \n";

    inFile.read((char*)&movieItem, sizeof(movieItem));
    if(!movieItem.name.empty()){
        while (!inFile.eof()) {
                movieId++;
                cout << movieId;
                cout<<"\t\t";
                cout <<     movieItem.name+"\t";
                cout <<     movieItem.price<<"\t";
                cout <<     movieItem.time+"  ";
                cout<<"\n";
            inFile.read((char*)&movieItem, sizeof(movieItem));
        }
    }
     cout << "Press any key to Go Back";
     getch();
     clearScreen();
     userWelcomeScreen(userItem);
}

void showMovieList(userEntity userItem)
{
    int movieListChoice,movieIdToUpdate;
    string movieListOption="\n 1.Update Movie,\n 2. Back \n please enter your choice\n";
    readMovieInfo();
    cout<<movieListOption;
    cin>>movieListChoice;
    switch(movieListChoice){
    case 1:
        cout<<"Please enter MovieId to update";
        break;
    case 2:
        clearScreen();
        movie_function(userItem);
        break;
    default:
        clearScreen();
        cout<<"Invalid Choice";
        showMovieList(userItem);
    }
}

void addNewMovie(userEntity userItem)
{
   struct movieEntity movieItem;
   cout<<"enter movie Name=";
   cin>>movieItem.name;
   cout<<"enter Price= ";
   movieItem.price= getprice(false);
   char ch;
   cout<<"Is Movie Active "; cin>>ch;
   movieItem.status=(ch=='y');
   cout<<"Enter movie times in hh:mm format, with Comma separate if have multiple "; cin>>movieItem.time;
    cout<<"Available Seats= "; cin>>movieItem.maxSeat;
   storeMovieInfo(movieItem);
   clearScreen();
   cout<<"Movie Added successfully\n";
   movie_function(userItem);
}

void storeMovieInfo(struct movieEntity movieItem)
{   ofstream outfile;
    outfile.open("movieRecord.txt", ios::app);
    outfile.write((char*)&movieItem, sizeof(movieItem));
    outfile.close();
}

void bookMovieTicket(userEntity userItem)
{
    movieBookingEntity moviebookingitem;
    clearScreen();
    string movieListOption="\n please enter movie id for booking\n";
    int movieId;
    char ch;
    readMovieInfo();
    cout<<movieListOption;
    cin>>movieId;
    movieEntity movieEntityItem=getMovieItemById(movieId);
    if(movieEntityItem.name==""){
        clearScreen();
        cout<<"Invalid Choice \n";
        userWelcomeScreen(userItem);
    }else{
        moviebookingitem.movie_id=movieId;
        cout<<"enter booking date (dd/mm//yyyy format)\n";
        cin>>moviebookingitem.date;
        cout<<"which show time to book\n";
        cin>>moviebookingitem.show_time;
        cout<<"\n please enter no. of tickets\n";
        cin>>moviebookingitem.totaltickets;
        cout<<"Do you want to confirm booking for below Movie show\n";
        cout<<"Movie Name : "+movieEntityItem.name+",\n";
        cout<<"Date : "+moviebookingitem.date+",\nTime : "+moviebookingitem.show_time+",\n";
        cout<<"Total tickets : ";
        cout<<moviebookingitem.totaltickets;
        cout<<"\nTotal amount : ";
        //cout<<(movieEntityItem.price*moviebookingitem.totaltickets);//

        cin>>ch;
        if(ch=='y')
        {
            updateMovieHistory(userItem,moviebookingitem);
            clearScreen();
            cout<<" Movie Booking Succssfully,\n Enjoy your movie with your love once,\n Have a great day :)";
            userWelcomeScreen(userItem);
        }else{
            cout<<"Do you really want to cancel booking?";
            cin>>ch;
            if(ch=='y')
            {   clearScreen();
                userWelcomeScreen(userItem);
            }else{
                updateMovieHistory(userItem,moviebookingitem);
                clearScreen();
                cout<<" Movie Booking Succssfully,\n Enjoy your movie with your love once,\n Have a great day :)";
                userWelcomeScreen(userItem);
            }
        }
    }
}

movieEntity getMovieItemById(int movie_id)
{
    int movieId=0;
    ifstream inFile;
    inFile.open("movieRecord.txt", ios::in);
    movieEntity movieItem;

    inFile.read((char*)&movieItem, sizeof(movieItem));
    if(!movieItem.name.empty()){
        while (!inFile.eof()) {
                movieId++;
                if(movieId==movie_id){
                    return movieItem;
                }
            inFile.read((char*)&movieItem, sizeof(movieItem));
        }
    }
    return movieItem;
}

void updateMovieHistory(struct userEntity userItem,struct movieBookingEntity movieBookingItem)
{
    ofstream outfile;
    outfile.open("UserShowHistory.txt", ios::app);
    outfile.write((char*)&movieBookingItem, sizeof(movieBookingItem));
    outfile.close();
}

void storeUserInfo(struct userEntity userItem)
{
    ofstream outfile;
    outfile.open("userRecord.txt", ios::app);
    outfile.write((char*)&userItem, sizeof(userItem));
    outfile.close();
}

void validateUser(string userName,string userPassword)
{
    ifstream inFile;
    inFile.open("userRecord.txt", ios::in);
    userEntity userItem;
    bool isLoginNotSuccess=true;
    inFile.read((char*)&userItem, sizeof(userItem));
    if(!userItem.name.empty()){
    while (!inFile.eof()) {
           if(userName==userItem.name)
            {
                 cout<<"\n userName "+userName;
                 cout<<"\n userItem.name "+userItem.name;
                 cout<<"\n userPassword "+userPassword;
                 cout<<"\n userItem.password "+userItem.password;
                if(userPassword==userItem.password)
                {
                    isLoginNotSuccess=false;
                    clearScreen();
                    cout<<"Login Success \n";
                    userWelcomeScreen(userItem);
                    break;
                }
            }
        inFile.read((char*)&userItem, sizeof(userItem));
    }
    }
    if(isLoginNotSuccess){
        clearScreen();
        cout<<"Invalid Credantial,\n Please enter correct userId & password.\n";
        welcomemain();
    }
}

void showUsersList(userEntity globalUserItem){
    int userId=0;
    ifstream inFile;
    inFile.open("userRecord.txt", ios::in);
    userEntity userItem;

    cout <<"userId  ";
    cout << "User Name  ";
    cout << "User Mobile No. \n";

    inFile.read((char*)&userItem, sizeof(userItem));
     if(!userItem.name.empty()){
        while (!inFile.eof()) {
                userId++;
                cout << userId;
                cout<<" ";
                cout << userItem.name+"  ";
                cout <<userItem.mobile_number+" ";
                cout<<"\n";
            inFile.read((char*)&userItem, sizeof(userItem));
        }
    }
     cout << "Press any key to Go Back";
     getch();
     clearScreen();
     userWelcomeScreen(globalUserItem);
}

void readMovieInfo()
{
    try{
    int movieId=0;
    ifstream inFile;
    inFile.open("movieRecord.txt", ios::in);
    movieEntity movieItem;

    cout <<"MovieId  ";
    cout <<"Movie Name  ";
    cout <<"Price    ";
    cout <<"Time  \n";

    inFile.read((char*)&movieItem, sizeof(movieItem));
    if(!movieItem.name.empty()){
        while (!inFile.eof()) {
                movieId++;
                cout << movieId;
                cout<<"\t\t";
                cout <<     movieItem.name+"\t";
                cout <<     movieItem.price<<"\t";
                cout <<     movieItem.time+"  ";
                cout<<"\n";
            inFile.read((char*)&movieItem, sizeof(movieItem));
        }
    }}catch(exception e)
    {
        cout<<"Some thing Went Wrong...";
    }
}
