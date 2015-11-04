#include <Windows.h>
#include <string>
#include <Psapi.h>
#include <algorithm>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <qdebug.h>
#include <QDebug>

using namespace std;


#pragma comment (lib, "User32.lib")
#pragma comment (lib, "kernel32.lib")
//
// Callback function. It will be called by EnumWindows function
//  as many times as there are windows
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{

//cout << "hwnd_Child = " << hwnd << endl;
// if(IsWindowVisible(hwnd)) // check whether window is visible
{


     char wnd_title[256];
     GetWindowTextA(hwnd,wnd_title,sizeof(wnd_title));

     QFile tabHistory("tabHistory.txt");
     if(tabHistory.open(QIODevice::Append))
     {
         QTextStream title(&tabHistory);
         title << wnd_title << endl;
     }

     cout <<wnd_title<<endl;
}
 return true; // function must return true if you want to continue enumeration
}

bool checkForHangout()
{

    QFile tabHistory("tabHistory.txt");
    QString s ;bool a = false;
    if(tabHistory.open(QIODevice::ReadOnly))
    {
        QTextStream title(&tabHistory);
        while(!tabHistory.atEnd())
        {
            s +=title.readLine();


           // return a;
        }
        a = s.contains("Google Hangouts");
        qDebug() << " A :" <<a;
       // int indexAPP = s.indexOf("Google Hangouts"); //searching for string with *APPLICATION* wildcard
      //  qDebug() << indexAPP;

        //cout << indexAPP;
        //return a;
    }
tabHistory.remove();
    return a;
}

int main()
{
    //HWND hwnd; LPARAM lParam;
    //HWND hwnd = FindWindow(0,0);
    //   EnumWindows(EnumChildProc, 0);
    EnumWindows(EnumWindowsProc,0);

    bool isHangout = checkForHangout();
   // EnumChildWindows(hwnd,EnumChildProc,0);
 system("PAUSE");
 return 0;
}
