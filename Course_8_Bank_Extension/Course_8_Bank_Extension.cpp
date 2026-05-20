#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";
string CurrentUser = "";


void ShowMainMenue();
void ShowTransactionsMenue();

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;


};

vector<string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word   
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;

}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{

    sClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double


    return Client;

}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }


            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return false;


}

sClient ReadNewClient()
{
    sClient Client;

    cout << "Enter Account Number? ";

    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }


    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{

    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return vClients;

}

void PrintClientRecordLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void PrintClientRecordBalanceLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void ShowAllClientsScreen()
{


    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

void ShowTotalBalances()
{

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalances = 0;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.AccountBalance;

            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t   Total Balances = " << TotalBalances;

}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";

}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{

    for (sClient C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }

    }
    return false;

}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;

}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    for (sClient& C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }

    }

    return false;

}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;

            }

        }

        MyFile.close();

    }

    return vClients;

}

void AddDataLineToFile(string FileName, string  stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }

}

void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));

}

void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        //system("cls");
        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";


        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);

            //Refresh Clients 
            vClients = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }

}

bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }

            }

            SaveCleintsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }

}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients)
{


    char Answer = 'n';


    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {

        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveCleintsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;

                return true;
            }

        }


        return false;
    }

}

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;

}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);

}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);

}

void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddNewClients();

}

void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";

}

void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";

}

void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";


    sClient Client;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();


    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }


    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);

}

void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();


    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter withdraw amount? ";
    cin >> Amount;

    //Validate that the amount does not exceeds the balance
    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Amount;
    }

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);

}

void ShowTotalBalancesScreen()
{

    ShowTotalBalances();

}

enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3, eShowMainMenue = 4 };

enum enMainMenueOptions { eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
    eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6 ,eManageUsers =7,eLogout = 8 };

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();

}
void GoBackToTransactionsMenue()
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");
    ShowTransactionsMenue();

}
short ReadTransactionsMenueOption()
{
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption)
{
    switch (TransactionMenueOption)
    {
    case enTransactionsMenueOptions::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenue();
        break;
    }

    case enTransactionsMenueOptions::eWithdraw:
    {
        system("cls");
        ShowWithDrawScreen();
        GoBackToTransactionsMenue();
        break;
    }


    case enTransactionsMenueOptions::eShowTotalBalance:
    {
        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransactionsMenue();
        break;
    }


    case enTransactionsMenueOptions::eShowMainMenue:
    {

        ShowMainMenue();

    }
    }

}

void ShowTransactionsMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tTransactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";
    PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}

short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 7]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}
short ReadManageUsersOption()
{
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}
enum eUserOptions { eListUsers = 1, eAddUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eBack = 6 };
void PerfromUserOptions(eUserOptions UserOptions);
void ShowUsersOptionsMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tManage Users Menu Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menu.\n";
    cout << "===========================================\n";
    PerfromUserOptions((eUserOptions)ReadManageUsersOption());
}
void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eAddNewClient:
        system("cls");
        ShowAddNewClientsScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eUpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eShowTransactionsMenue:
        system("cls");
        ShowTransactionsMenue();
        break;
    case enMainMenueOptions::eManageUsers:
        system("cls");
        ShowUsersOptionsMenue();
        break;

    case enMainMenueOptions::eLogout:
        system("cls");
        ShowEndScreen();
        break;
    }

}

void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menu Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] LogOut.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}
struct stUser {
    string UserName, Password;
    short Permission;
    bool isRedFlag = false;
};

stUser ConvertUserLinetoRecord(string Line, string Seperator = "#//#")
{

    stUser User;
    vector<string> vUsertData;

    vUsertData = SplitString(Line, Seperator);

    User.UserName = vUsertData[0];
    User.Password = vUsertData[1];
    User.Permission = stoi(vUsertData[2]);
  
    return User;

}

string ConvertUserRecordToLine(stUser User, string Seperator = "#//#")
{

    string UserRecord = "";

    UserRecord += User.UserName + Seperator;
    UserRecord += User.Password + Seperator;
   
    UserRecord += to_string(User.Permission);

    return UserRecord;

}
vector <stUser> LoadUsersDataFromFile(string FileName)
{

    vector <stUser> vUsers;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        stUser User;

        while (getline(MyFile, Line))
        {

            User = ConvertUserLinetoRecord(Line);

            vUsers.push_back(User);
        }

        MyFile.close();

    }

    return vUsers;

}
vector<stUser> SaveUsersDateToFile(vector<stUser> vUsers, string FileName)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    string DateLine;
    if (MyFile.is_open())
    {
        for (stUser& U : vUsers)
        {
            if (U.isRedFlag == false) {
                DateLine = ConvertUserRecordToLine(U);
                MyFile << DateLine << endl;
            }
        }
        MyFile.close();
    }

    return vUsers;
}

void ShowLoginSceen()
{
    cout << "===========================================\n";
    cout << "\t\tLogin Screen\n";
    cout << "===========================================\n";
}


bool CheckLogin(string Username,string Password)
{

    vector<stUser> Users = LoadUsersDataFromFile(UsersFileName);
    for (stUser& User : Users)
    {
        if (User.UserName == Username && User.Password == Password)
            return true;
    }
    return false;
}

void Authontification()
{
    ShowLoginSceen();

    while (true)
    {
    string User, Password;
    cout << "UserName?\n";
    cin >> User;
    cout << "PassWord?\n";
    cin >> Password;
    if (CheckLogin(User, Password))
        {
            
            break;
        }
    cout << "\nInvalid Username or Password\n";

    }

    system("cls");
    ShowMainMenue();
    
}
void PrintUserRecordBalanceLine(stUser User)
{

    cout << "| " << setw(15) << left << User.UserName;
    cout << "| " << setw(15) << left << User.Password;
    cout << "| " << setw(12) << left << User.Permission;

}
void ShowUserListScreen()
{
    vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    cout << "\n\t\t\t\t\Users List (" << vUsers.size() << ") User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(15) << "Permissions";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vUsers.size() == 0)
    {
        cout << "\t\t\t\tNo Users Available In the System!";

    }
    else {
        for (stUser& User : vUsers)
        {
            PrintUserRecordBalanceLine(User);
            cout << endl;
        }
    }
    cout << "_________________________________________\n" << endl;
}
bool FindUserByUsername(string Username, vector<stUser> &vUsers, stUser& User)
{
    for (stUser &U : vUsers)
    {
        if (U.UserName == Username)
        {
            User = U;
            return true;
        }

    }
    return false;
}

string ReadUserName()
{
    string userName ="";
    cout << "\nEnter User Name?";
    cin >> userName;

    return userName;
}
void PrintUserCard(stUser User)
{
    cout << "\nUsername : " << User.UserName;
    cout << "\nPassword   : " << User.Password;

}
void ShowFindUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind User Screen";
    cout << "\n-----------------------------------\n";

    vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    stUser User;
    string UserName = ReadUserName();

    if (FindUserByUsername(UserName, vUsers, User)) {
        PrintUserCard(User);
    }
    else {
        cout << "\nUser With this "<<UserName<<" Not Found !";
    }

}
void GoBackToManageUsersMenue()
{
    cout << "\n\nPress any key to go back to Transactions Menu...";
    system("pause>0");
    ShowUsersOptionsMenue();

}

bool MarkUserAsRedFlag(string Username, vector<stUser>& vUsers)
{
    for (stUser& U : vUsers)
    {
        if (U.UserName == Username) {

            U.isRedFlag = true;
            return true;
        }

    }

    return false;
}

bool DeleteUserByUserName(vector<stUser> &vUsers,string UserName)
{
    
    stUser User;
    char Answer = 'n';
    if (FindUserByUsername(UserName, vUsers, User))
    {
        PrintUserCard(User);
        cout << "\nDo You want to delete this user(Y/N)?\n";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            
            MarkUserAsRedFlag(UserName,vUsers);
            SaveUsersDateToFile(vUsers, UsersFileName);

            vUsers = LoadUsersDataFromFile(UsersFileName);

            cout << "\n\User Deleted Successfully.";
            return true;
        }
        
    }
    else {
        cout << "\User with User Name (" << UserName << ") is Not Found!";
        return false;
    }
    
}
void ShowDeleteUserScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tDelete User Screen";
    cout << "\n-----------------------------------\n";
    vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    string UserName = ReadUserName();
    DeleteUserByUserName(vUsers, UserName);

}
bool UserExistByUserName(string Username)
{
    vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

    for (stUser& U : vUsers)
    {
        if (U.UserName == Username)
            return true;
    }

    return false;
}
int ReadPermission()
{
    int TotalPermissions = 0;
    char Answer = 'n';
    cout << "Do You want to give full access ? (y/n)\n";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
        return -1;

    cout << "Do You want to give access To List Client ? (y/n)\n";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
        TotalPermissions = TotalPermissions |1;

    cout << "Do You want to give access To Add Client ? (y/n)\n";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
        TotalPermissions = TotalPermissions |2;

    cout << "Do You want to give access To Delete Client ? (y/n)\n";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
        TotalPermissions = TotalPermissions |4;

    cout << "Do You want to give access To Update Client ? (y/n)\n";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
        TotalPermissions = TotalPermissions |8;

    cout << "Do You want to give access To Find Client ? (y/n)\n";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
        TotalPermissions = TotalPermissions |16;

    cout << "Do You want to give access To Trasactions Client ? (y/n)\n";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
        TotalPermissions = TotalPermissions |32;

    cout << "Do You want to give access To Manage Users ? (y/n)\n";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
        TotalPermissions = TotalPermissions |64;

    return TotalPermissions;
}
stUser ReadUser()
{
    stUser User;
    cout << "Enter UserName?\n";
    getline(cin >> ws, User.UserName);

    while (UserExistByUserName(User.UserName))
    {
        cout << "This User with username " << User.UserName << " Already exist.";
        getline(cin >> ws, User.UserName);

    }
    cout << "Enter Password?\n";
    getline(cin >> ws, User.Password);

    User.Permission = ReadPermission();

    return User;


}
void ShowAddUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\nAdd User Screen";
    cout << "\n-----------------------------------\n";
    
    stUser User;
    vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    char Answer = 'n';
    do {
        User = ReadUser();
        vUsers.push_back(User);
        SaveUsersDateToFile(vUsers, UsersFileName);
        cout << "User Added succesfully\n";
        cout << "Do You Wnat to add more users? (y/n)\n";
        cin >> Answer;
    } while (Answer == 'y' || Answer == 'Y');
}
void PerfromUserOptions(eUserOptions UserOptions) {
    switch (UserOptions)
    {
    case eUserOptions::eListUsers:
        system("cls");
        ShowUserListScreen();
        GoBackToManageUsersMenue();
        break;
    case eUserOptions::eFindUser:
        system("cls");
        ShowFindUserScreen();
        GoBackToManageUsersMenue();
        break;
    case eUserOptions::eDeleteUser:
        system("cls");
        ShowDeleteUserScreen();
        GoBackToManageUsersMenue();
        break;
    case eUserOptions::eAddUser:
        system("cls");
        ShowAddUserScreen();
        GoBackToManageUsersMenue();
        break;
    
    }
}
int main()

{
    Authontification();
    system("pause>0");
    return 0;
}