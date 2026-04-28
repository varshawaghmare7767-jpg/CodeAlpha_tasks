#include <windows.h>
#include <fstream>
using namespace std;

struct Account {
    int accNo;
    float balance;
};

HWND hAccNo, hAmount, hOutput;

// Find account
bool findAccount(Account &acc, int accNo) {
    ifstream file("account.dat", ios::binary);
    while(file.read((char*)&acc, sizeof(acc))) {
        if(acc.accNo == accNo) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// Save updated account
void updateAccount(Account acc) {
    fstream file("account.dat", ios::binary | ios::in | ios::out);
    Account temp;

    while(file.read((char*)&temp, sizeof(temp))) {
        if(temp.accNo == acc.accNo) {
            file.seekp(-sizeof(temp), ios::cur);
            file.write((char*)&acc, sizeof(acc));
            break;
        }
    }
    file.close();
}

// Deposit
void deposit() {
    char accStr[10], amtStr[10];
    GetWindowText(hAccNo, accStr, 10);
    GetWindowText(hAmount, amtStr, 10);

    int accNo = atoi(accStr);
    float amt = atof(amtStr);

    Account acc;
    if(findAccount(acc, accNo)) {
        acc.balance += amt;
        updateAccount(acc);

        SetWindowText(hOutput, "Deposit Successful!");
    } else {
        SetWindowText(hOutput, "Account Not Found!");
    }
}

// Withdraw
void withdraw() {
    char accStr[10], amtStr[10];
    GetWindowText(hAccNo, accStr, 10);
    GetWindowText(hAmount, amtStr, 10);

    int accNo = atoi(accStr);
    float amt = atof(amtStr);

    Account acc;
    if(findAccount(acc, accNo)) {
        if(acc.balance >= amt) {
            acc.balance -= amt;
            updateAccount(acc);
            SetWindowText(hOutput, "Withdrawal Successful!");
        } else {
            SetWindowText(hOutput, "Insufficient Balance!");
        }
    } else {
        SetWindowText(hOutput, "Account Not Found!");
    }
}

// Balance Enquiry
void checkBalance() {
    char accStr[10];
    GetWindowText(hAccNo, accStr, 10);

    int accNo = atoi(accStr);

    Account acc;
    if(findAccount(acc, accNo)) {
        char result[100];
        sprintf(result, "Balance: %.2f", acc.balance);
        SetWindowText(hOutput, result);
    } else {
        SetWindowText(hOutput, "Account Not Found!");
    }
}

// Create account (for first time)
void createAccount() {
    char accStr[10];
    GetWindowText(hAccNo, accStr, 10);

    int accNo = atoi(accStr);

    Account acc;
    acc.accNo = accNo;
    acc.balance = 0;

    ofstream file("account.dat", ios::binary | ios::app);
    file.write((char*)&acc, sizeof(acc));
    file.close();

    SetWindowText(hOutput, "Account Created!");
}

// Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch(msg) {

        case WM_CREATE:
            CreateWindow("STATIC","Account No:",WS_VISIBLE|WS_CHILD,50,50,100,20,hwnd,0,0,0);
            hAccNo = CreateWindow("EDIT","",WS_VISIBLE|WS_CHILD|WS_BORDER,150,50,120,20,hwnd,0,0,0);

            CreateWindow("STATIC","Amount:",WS_VISIBLE|WS_CHILD,50,80,100,20,hwnd,0,0,0);
            hAmount = CreateWindow("EDIT","",WS_VISIBLE|WS_CHILD|WS_BORDER,150,80,120,20,hwnd,0,0,0);

            CreateWindow("BUTTON","Create",WS_VISIBLE|WS_CHILD,50,120,70,30,hwnd,(HMENU)1,0,0);
            CreateWindow("BUTTON","Deposit",WS_VISIBLE|WS_CHILD,130,120,70,30,hwnd,(HMENU)2,0,0);
            CreateWindow("BUTTON","Withdraw",WS_VISIBLE|WS_CHILD,210,120,70,30,hwnd,(HMENU)3,0,0);
            CreateWindow("BUTTON","Balance",WS_VISIBLE|WS_CHILD,290,120,70,30,hwnd,(HMENU)4,0,0);

            hOutput = CreateWindow("STATIC","Output...",WS_VISIBLE|WS_CHILD,
                                   50,170,300,100,hwnd,0,0,0);
            break;

        case WM_COMMAND:
            switch(LOWORD(wp)) {
                case 1: createAccount(); break;
                case 2: deposit(); break;
                case 3: withdraw(); break;
                case 4: checkBalance(); break;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd,msg,wp,lp);
}

// Main
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "BankApp";

    RegisterClass(&wc);

    HWND hwnd = CreateWindow("BankApp","Banking System",
                             WS_OVERLAPPEDWINDOW,200,200,420,320,
                             NULL,NULL,hInst,NULL);

    ShowWindow(hwnd,nCmdShow);

    MSG msg;
    while(GetMessage(&msg,NULL,0,0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}