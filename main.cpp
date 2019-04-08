#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<tuple>
#include<iomanip>


#include "DataBase.h"

using namespace std;

int main() {
    Database db;

    string new_line;
    while (getline(cin, new_line))
    {
        if(new_line == "") continue;

        Line parsed_line;

        try
        {
            parsed_line = ParsLine(new_line);
        }
        catch(exception& ex)
        {
            cout<<ex.what()<<endl;
            continue;
        }
        //���� ������� PRINT, �� ������� ���� �� ����.
        if(parsed_line.com == PRINT)
        {
            db.Print();
            continue;
        }
        //������ ���� � ��������� �������.
        Date dt(parsed_line.date);

        switch(parsed_line.com)
        {
        case ADD:
            db.AddEvent(dt, parsed_line.event);
            break;
        case DEL:
            if(parsed_line.event == "")// ���� �� �������� �������, ������ ���� ������� ����.
            {
                db.DeleteDate(dt);
            }
            else db.DeleteEvent(dt, parsed_line.event);// � ��������� ������ ������� �������.
            break;
        case FIND:
            db.Find(dt);
            break;
        }
    }

  return 0;
}


