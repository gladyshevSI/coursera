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
        //≈сли команда PRINT, то парсить дату не надо.
        if(parsed_line.com == PRINT)
        {
            db.Print();
            continue;
        }
        //ѕарсим дату и выполн€ем команду.
        Date dt(parsed_line.date);

        switch(parsed_line.com)
        {
        case ADD:
            db.AddEvent(dt, parsed_line.event);
            break;
        case DEL:
            if(parsed_line.event == "")// ≈сли не передали событие, значит надо удалить дату.
            {
                db.DeleteDate(dt);
            }
            else db.DeleteEvent(dt, parsed_line.event);// ¬ противном случае удал€ем событие.
            break;
        case FIND:
            db.Find(dt);
            break;
        }
    }

  return 0;
}


