#include <windows.h>
#include <fstream>
#include <cstring>
using namespace std;

struct Student {
    int id;
    char name[50];
    float marks;
};

HWND hId, hName, hMarks, hOutput;

// Save student to file
void addStudent() {
    Student s;
    char id[10], marks[10];

    GetWindowText(hId, id, 10);
    GetWindowText(hName, s.name, 50);
    GetWindowText(hMarks, marks, 10);

    s.id = atoi(id);
    s.marks = atof(marks);

    ofstream file("students.dat", ios::binary | ios::app);
    file.write((char*)&s, sizeof(s));
    file.close();

    SetWindowText(hOutput, "Student Added Successfully!");
}

// Display all students
void displayStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    char buffer[1000] = "";
    char temp[100];

    while(file.read((char*)&s, sizeof(s))) {
        sprintf(temp, "ID:%d Name:%s Marks:%.2f\n", s.id, s.name, s.marks);
        strcat(buffer, temp);
    }
    file.close();

    SetWindowText(hOutput, buffer);
}

// Search student
void searchStudent() {
    Student s;
    char id[10];
    GetWindowText(hId, id, 10);
    int sid = atoi(id);

    ifstream file("students.dat", ios::binary);
    char result[100] = "Not Found";

    while(file.read((char*)&s, sizeof(s))) {
        if(s.id == sid) {
            sprintf(result, "Found -> Name:%s Marks:%.2f", s.name, s.marks);
            break;
        }
    }
    file.close();

    SetWindowText(hOutput, result);
}

// Delete student
void deleteStudent() {
    Student s;
    char id[10];
    GetWindowText(hId, id, 10);
    int sid = atoi(id);

    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while(file.read((char*)&s, sizeof(s))) {
        if(s.id != sid) {
            temp.write((char*)&s, sizeof(s));
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    SetWindowText(hOutput, "Deleted Successfully!");
}

// Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch(msg) {
        case WM_CREATE:

            CreateWindow("STATIC", "ID:", WS_VISIBLE|WS_CHILD, 50,50,50,20, hwnd,0,0,0);
            hId = CreateWindow("EDIT","",WS_VISIBLE|WS_CHILD|WS_BORDER,100,50,100,20,hwnd,0,0,0);

            CreateWindow("STATIC", "Name:", WS_VISIBLE|WS_CHILD, 50,80,50,20, hwnd,0,0,0);
            hName = CreateWindow("EDIT","",WS_VISIBLE|WS_CHILD|WS_BORDER,100,80,100,20,hwnd,0,0,0);

            CreateWindow("STATIC", "Marks:", WS_VISIBLE|WS_CHILD, 50,110,50,20, hwnd,0,0,0);
            hMarks = CreateWindow("EDIT","",WS_VISIBLE|WS_CHILD|WS_BORDER,100,110,100,20,hwnd,0,0,0);

            CreateWindow("BUTTON","Add",WS_VISIBLE|WS_CHILD,50,150,60,30,hwnd,(HMENU)1,0,0);
            CreateWindow("BUTTON","Display",WS_VISIBLE|WS_CHILD,120,150,70,30,hwnd,(HMENU)2,0,0);
            CreateWindow("BUTTON","Search",WS_VISIBLE|WS_CHILD,200,150,70,30,hwnd,(HMENU)3,0,0);
            CreateWindow("BUTTON","Delete",WS_VISIBLE|WS_CHILD,280,150,70,30,hwnd,(HMENU)4,0,0);

            hOutput = CreateWindow("STATIC","Output...",WS_VISIBLE|WS_CHILD,
                                   50,200,300,100,hwnd,0,0,0);
            break;

        case WM_COMMAND:
            switch(LOWORD(wp)) {
                case 1: addStudent(); break;
                case 2: displayStudents(); break;
                case 3: searchStudent(); break;
                case 4: deleteStudent(); break;
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
    wc.lpszClassName = "StudentApp";

    RegisterClass(&wc);

    HWND hwnd = CreateWindow("StudentApp","Student Management System",
                             WS_OVERLAPPEDWINDOW,200,200,400,350,
                             NULL,NULL,hInst,NULL);

    ShowWindow(hwnd,nCmdShow);

    MSG msg;
    while(GetMessage(&msg,NULL,0,0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}