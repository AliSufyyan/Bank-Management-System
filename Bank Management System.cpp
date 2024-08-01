#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;
const long int col = 2;
long int countlines();
void readfromfile(string *, long int *, long int *);
void readpasswords(long int[][col], long int);
long int showmenu();
void loginmanu(string *, long int *, long int *, long int, long int[][col], long int);
void Registration(string *, long int *, long int *, long int, long int[][col], int);
string *grow_arr(string *, long int);
long int *grow_arr2(long int *, long int);
bool isValidName(string);
bool isValidId(string);
void sendtofile(string *, long int *, long int *, long int);
void sendtopasswords(long int[][col], long int);
void deposit(string *, long int *, long int *, long int, long int);
void withdrawl(string *, long int *, long int *, long int, long int);
void showholders(string *, long int *, long int *, long int);
void deleteaccount(string *, long int *, long int *, long int, long int, long int[][col]);
string *shrink_arr(string *, long int);
long int *shrink_arr2(long int *, long int);
void sendafterdeletion(long int[][col], long int);
int main()
{
    int choice;
    do
    {
        string *holder = nullptr;
        long int *username = nullptr;
        long int *balance = nullptr;
        long int lines = countlines();
        int actual_lines = lines;
        long int passwords[lines][col];
        if (lines != 0)
        {
            holder = new string[lines];
            username = new long int[lines];
            balance = new long int[lines];
            readfromfile(holder, username, balance);
            readpasswords(passwords, lines);
        }
        else
        {
            lines = 1;
            holder = new string[lines];
            username = new long int[lines];
            balance = new long int[lines];
            passwords[lines][col];
        }

        choice = showmenu();
        if (choice == 4)
        {
            delete[] holder;
            delete[] username;
            delete[] balance;
            cout << "We are glad you use our service See ya." << endl;
            return 0;
        }
        if (choice == 1) // log in section
        {
            loginmanu(holder, username, balance, lines, passwords, lines);
        }
        else if (choice == 2) // Register senction
        {
            Registration(holder, username, balance, lines, passwords, actual_lines);
        }
        else if (choice == 3)
        {
            showholders(holder, username, balance, actual_lines);
        }
        else
        {
            cout << "invalid choice" << endl;
        }
    } while (choice != 4);
    return 0;
}
long int countlines()
{
    ifstream datafile("data.txt");
    string temp;
    long int count = 0;
    if (datafile)
    {
        while (!datafile.eof())
        {
            getline(datafile, temp);
            count++;
        }
        datafile.close();
    }
    else
    {
        cout << "file not opened";
    }
    return count - 1;
}
void readfromfile(string *holder, long int *username, long int *balance)
{
    ifstream myfile("data.txt");
    if (myfile)
    {
        long int account = 0;
        while (myfile >> holder[account] >> username[account] >> balance[account])
        {
            account++;
        }
        myfile.close();
    }
    else
    {
        cout << "file not opened";
    }
}
void readpasswords(long int passwords[][col], long int size)
{
    ifstream myfile("password.txt");
    if (myfile)
    {
        long int index = 0;
        while (myfile >> passwords[index][0] >> passwords[index][1])
        {
            index++;
        }
        myfile.close();
    }
    else
    {
        cout << "file not opened";
    }
}
long int showmenu()
{
    int choice;
    cout << "-----------------BANK MANAGMENT SYSTEM-----------------" << endl;
    cout << "1.login" << endl;
    cout << "2.Registration" << endl;
    cout << "3.All account Holders(Admin Only)" << endl;
    cout << "4.Exit" << endl;
    cout << "Enter your choice(1-4)" << endl;
    cin >> choice;
    while (choice != 1 && choice != 2 && choice != 3 && choice != 4)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "invalid choice please select again" << endl;
        cout << "1.login" << endl;
        cout << "2.Registration" << endl;
        cout << "3.All account Holders(Admin Only)" << endl;
        cout << "4.Exit" << endl;
        cout << "Enter your choice(1-4)" << endl;
        cin >> choice;
    }
    cin.ignore();
    return choice;
}
void loginmanu(string *holder, long int *username, long int *balance, long int index, long int passwords[][col], long int size)
{

    char strnum[20], strpass[20];
    long int user_name, password;
    long int found_index = 0;
    bool isvalidname = false;
    bool is_valid_login_user = false;
    while (!isvalidname)
    {
        cout << "Ente ID(Numbers Only)";
        cin.getline(strnum, 20);
        is_valid_login_user = isValidId(strnum);
        if (is_valid_login_user)
        {
            is_valid_login_user = true;
            user_name = stoi(strnum);
            bool is_user_matched = false;
            for (long int i = 0; i < index; i++)
            {
                if (passwords[i][0] == user_name)
                {
                    is_user_matched = true;
                    found_index = i;
                    isvalidname = true;
                    cout << "ID matched" << endl;
                    break;
                }
            }
            if (!is_user_matched)
            {
                {
                    cout << "No record found" << endl;
                    return;
                }
            }
        }
        else
        {
            cout << "please enter only Numbers" << endl;
        }
    }
    bool isvalidpass = false;
    bool is_valid_login_pass = false;
    while (!isvalidpass)
    {
        cout << "Ente Password(Numbers Only)";
        cin.getline(strpass, 20);
        is_valid_login_pass = isValidId(strpass);
        if (is_valid_login_pass)
        {
            password = stoi(strpass);
            if (passwords[found_index][1] == password)
            {
                cout << "Password matched" << endl;
                isvalidpass = true;
                break;
            }
            else
            {
                cout << "password not matched" << endl;
                return;
            }
        }
        else
        {
            cout << "please enter only Numbers" << endl;
        }
    }
    cout << "---------Logged in Successfully----------" << endl;
    int choice;
    do
    {
        cout << "1.Deposit" << endl;
        cout << "2.Withdrawl" << endl;
        cout << "3.Balace Status" << endl;
        cout << "4.Delete Account" << endl;
        cout << "5.exit to main manu" << endl;
        cout << "Enter your choice(1-4)" << endl;
        cin >> choice;
        while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "invalid choice please select again" << endl;
            cout << "1.Deposit" << endl;
            cout << "2.Withdrawl" << endl;
            cout << "3.Balace Status" << endl;
            cout << "4.Delete Account" << endl;
            cout << "5.exit to main manu" << endl;
            cout << "Enter your choice(1-4)" << endl;
            cin >> choice;
        }

        if (choice == 1)
        {
            deposit(holder, username, balance, index, found_index);
        }
        else if (choice == 2)
        {
            withdrawl(holder, username, balance, index, found_index);
        }
        else if (choice == 3)
        {
            cout << holder[found_index] << " " << " your current balance is = " << balance[found_index] << endl;
        }
        else if (choice == 4)
        {
            deleteaccount(holder, username, balance, index, found_index, passwords);
            choice = 5;
        }
        else if (choice == 5)
        {
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
    } while (choice != 5);
    cout << "Going back to main menu" << endl;
}

bool isValidName(string name)
{
    bool is_valid;
    is_valid = false;
    for (char c : name)
    {
        if ((int(c) >= 65 && int(c) <= 90) || (int(c) >= 97 && int(c) <= 122) || int(c) == 32)
        {
            is_valid = true;
        }
        else
        {
            is_valid = false;
            break;
        }
    }
    if (is_valid)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool isValidId(string number)
{
    bool is_valid;
    is_valid = true;
    for (char c : number)
    {
        if (int(c) >= 48 && int(c) <= 57)
        {
            is_valid = true;
        }
        else
        {
            is_valid = false;
            break;
        }
    }
    if (is_valid)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void Registration(string *holder, long int *username, long int *balance, long int lines, long int passwords[][col], int actual_lines)
{
    long int index = lines;
    if (actual_lines >= 1)
    {
        holder = grow_arr(holder, lines);
        username = grow_arr2(username, lines);
        balance = grow_arr2(balance, lines);
        index += 1;
    }
    string name;
    char pass[20], amou[20];
    long int password, amount;
    bool is_valid_name = false;
    while (!is_valid_name)
    {
        cout << "Ente name:";
        getline(cin, name);
        is_valid_name = isValidName(name);
        if (is_valid_name)
        {
            is_valid_name = true;
        }
        else
        {
            cout << "please enter only alphabets" << endl;
        }
    }

    for (long int i = 0; name[i] != '\0'; i++)
    {
        if (name[i] == ' ')
        {
            name[i] = '_';
        }
    }
    bool is_valid_pass = false;
    while (!is_valid_pass)
    {
        cout << "Ente password(Numbers Only)";
        cin.getline(pass, 20);
        is_valid_pass = isValidId(pass);
        if (is_valid_pass)
        {
            is_valid_pass = true;
            password = stoi(pass);
        }
        else
        {
            cout << "please enter only Numbers" << endl;
        }
    }
    bool is_valid_amount = false;
    while (!is_valid_amount)
    {
        cout << "Ente Initial deposit amount(Numbers Only)";
        cin.getline(amou, 20);
        is_valid_amount = isValidId(amou);
        if (is_valid_amount)
        {
            is_valid_amount = true;
            amount = stoi(amou);
        }
        else
        {
            cout << "please enter only Numbers" << endl;
        }
    }
    holder[index - 1] = name;
    if (index == 1)
    {
        username[index - 1] = 1001;
    }
    else
    {
        username[index - 1] = username[index - 2] + 1;
    }
    long int id = username[index - 1];
    balance[index - 1] = amount;
    passwords[index - 1][0] = id;
    passwords[index - 1][1] = password;
    sendtofile(holder, username, balance, index);
    sendtopasswords(passwords, index);
    cout << "Registered Successfully." << endl;
    cout << "Dear " << name << " your account ID is " << id << endl;
}
string *grow_arr(string *holder, long int index)
{
    string *arr = new string[index + 1];
    for (long int i = 0; i < index; i++)
    {
        arr[i] = holder[i];
    }
    delete[] holder;
    return arr;
}
long int *grow_arr2(long int *arr1, long int index)
{
    long int *arr = new long int[index + 1];
    for (long int i = 0; i < index; i++)
    {
        arr[i] = arr1[i];
    }
    delete[] arr1;
    return arr;
}
void sendtofile(string *holder, long int *username, long int *balance, long int index)
{
    ofstream myfile("data.txt");
    if (myfile)
    {
        for (long int i = 0; i < index; i++)
        {
            myfile << holder[i] << " " << username[i] << " " << balance[i] << endl;
        }
        myfile.close();
    }
}
void sendtopasswords(long int passwords[][col], long int index)
{
    ofstream myfile("password.txt");
    if (myfile)
    {
        for (long int i = 0; i < index; i++)
        {
            myfile << passwords[i][0] << " " << passwords[i][1] << endl;
        }
        myfile.close();
    }
}
void deposit(string *holder, long int *username, long int *balance, long int index, long int found_index)
{
    bool is_valid_dep_amount = false;
    bool isvalidamount = false;
    char stramount[20];
    long int amount;
    while (!isvalidamount)
    {
        cout << holder[found_index] << " " << " your current balance is = " << balance[found_index] << endl;
        cout << "Ente Amount: ";
        cin >> stramount;
        // cin.ignore();
        is_valid_dep_amount = isValidId(stramount);
        if (is_valid_dep_amount)
        {
            is_valid_dep_amount = true;
            amount = stoi(stramount);
            isvalidamount = true;
            while (amount <= 0)
            {

                cout << "amount must be greater then ZERO." << endl;
                isvalidamount = false;
            }
        }
        else
        {
            cout << "please enter only Numbers(Positive)" << endl;
        }
    }
    cout << "Your amount will be deposited after admin approvel." << endl;
    string admin_id, admin_pass;
    cout << "Enter admin ID(Admin Only)" << endl;
    cin >> admin_id;
    cout << "Enter admin Password(Admin Only)" << endl;
    cin >> admin_pass;
    if (admin_id == "968627" && admin_pass == "968627")
    {
        balance[found_index] += amount;
        sendtofile(holder, username, balance, index);
        cout << "Deposit  successfully" << endl;
    }
    else
    {
        cout << "wrong Admin username or password" << endl;
        cout << "Going to login menu" << endl;
    }
}
void withdrawl(string *holder, long int *username, long int *balance, long int index, long int found_index)
{
    bool is_valid_dep_amount = false;
    bool isvalidamount = false;
    char stramount[20];
    long int amount;
    while (!isvalidamount)
    {
        cout << holder[found_index] << " " << " your current balance is = " << balance[found_index] << endl;
        cout << "Ente Amount: ";
        cin >> stramount;
        // cin.ignore();
        is_valid_dep_amount = isValidId(stramount);
        if (is_valid_dep_amount)
        {
            is_valid_dep_amount = true;
            amount = stoi(stramount);
            isvalidamount = true;
            if (amount <= 0)
            {

                cout << "amount must be greater then ZERO." << endl;
                isvalidamount = false;
            }
            if (amount > balance[found_index])
            {

                cout << "amount must be less then your available balance." << endl;
                isvalidamount = false;
            }
        }
        else
        {
            cout << "please enter only Numbers(Positive)" << endl;
        }
    }
    cout << "Your amount will be withdrawl after admin approvel." << endl;
    string admin_id, admin_pass;
    cout << "Enter admin ID(Admin Only)" << endl;
    cin >> admin_id;
    cout << "Enter admin Password(Admin Only)" << endl;
    cin >> admin_pass;
    if (admin_id == "968627" && admin_pass == "968627")
    {
        balance[found_index] -= amount;
        sendtofile(holder, username, balance, index);
        cout << "withdrawl successfully" << endl;
    }
    else
    {
        cout << "wrong Admin username or password" << endl;
        cout << "Going to Login menu" << endl;
    }
}
void showholders(string *holder, long int *username, long int *balance, long int index)
{

    if(index>0)
    {
        string admin_id, admin_pass;
    cout << "Enter admin ID(Admin Only)" << endl;
    cin >> admin_id;
    cout << "Enter admin Password(Admin Only)" << endl;
    cin >> admin_pass;
    if (admin_id == "968627" && admin_pass == "968627")
    {
        cout << "Name" << "\t\t\t" << "UserID" << "\t\t" << "Balance" << endl;
        for (int i = 0; i < index; i++)
        {
            cout << holder[i] << "\t\t" << username[i] << "\t\t" << balance[i] << endl;
        }
    }
    else
    {
        cout << "wrong Admin username or password" << endl;
        cout << "Going to main menu" << endl;
    }
    }
    else
    {
        cout<<"No data found"<<endl;
    }
}
void deleteaccount(string *holder, long int *username, long int *balance, long int index, long int found_index, long int passwords[][col])
{
    string choice;
    cout << "Are you sure you want to delete your account(Y/N)" << endl;
    cin >> choice;
    if (choice == "Y" || choice == "y")
    {
        if (index == 1)
        {
            ofstream myfile("data.txt");
            if (myfile)
            {
                myfile.close();
            }
            ofstream myfile2("password.txt");
            if (myfile2)
            {
                myfile2.close();
            }
        }
        else if (found_index == index - 1)
        {
            holder = shrink_arr(holder, index);
            username = shrink_arr2(username, index);
            balance = shrink_arr2(balance, index);
            index -= 1;
            sendtofile(holder, username, balance, index);
            sendafterdeletion(passwords, index);
        }
        else
        {
            for (int i = found_index; i < index - 1; i++)
            {
                holder[i] = holder[i + 1];
                username[i] = username[i + 1];
                balance[i] = balance[i + 1];
                passwords[i][0] = passwords[i + 1][0];
                passwords[i][1] = passwords[i + 1][1];
            }
            holder = shrink_arr(holder, index);
            username = shrink_arr2(username, index);
            balance = shrink_arr2(balance, index);
            index -= 1;
            sendtofile(holder, username, balance, index);
            sendafterdeletion(passwords, index);
        }

        cout << "account deleted successfully" << endl;
    }
    else if (choice == "N" || choice == "n")
    {
        cout << "Thanks for not deleting your account" << endl;
    }
    else
    {
        cout << "invalid choice" << endl;
    }
}
string *shrink_arr(string *holder, long int index)
{
    string *arr = new string[index - 1];
    for (long int i = 0; i < index - 1; i++)
    {
        arr[i] = holder[i];
    }
    delete[] holder;
    return arr;
}

long int *shrink_arr2(long int *arr1, long int index)
{
    long int *arr = new long int[index - 1];
    for (long int i = 0; i < index - 1; i++)
    {
        arr[i] = arr1[i];
    }
    delete[] arr1;
    return arr;
}
void sendafterdeletion(long int passwords[][col], long int index)
{

    ofstream myfile("password.txt");
    if (myfile)
    {
        for (long int i = 0; i < index; i++)
        {
            myfile << passwords[i][0] << " " << passwords[i][1] << endl;
        }
        myfile.close();
    }
}