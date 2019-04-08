#include "DataBase.h"

Date::Date(s_Date date): date(date){}
Date::Date(int year, int month, int day)
        : date({year, month, day}) {}

s_Date Date::GetDate() const
{
    return date;
}

bool operator<(const Date& lhs, const Date& rhs)
{
    s_Date L = lhs.GetDate();
    s_Date R = rhs.GetDate();
    return tie(L.year, L.month, L.day) < tie(R.year, R.month, R.day);
}


void Database::AddEvent(const Date& date, const string& event)
{
    mdata[date].insert(event);
}
void Database::DeleteEvent(const Date& date, const string& event)
{
    int res = mdata[date].erase(event);
    if(res) cout << "Deleted successfully" << endl;
    else cout << "Event not found" << endl;
}
void  Database::DeleteDate(const Date& date)
{
    int N = mdata[date].size();
    mdata.erase(date);
    cout << "Deleted " << N << " events" << endl;
}

void Database::Find(const Date& date) const
{
    for(const string& events : mdata.at(date))
    {
        cout << events << endl;
    }
}

void Database::Print() const
{
    for(const auto& pair_mdata : mdata)
    {
        for(const auto& events : mdata.at(pair_mdata.first))
        {
            cout<<setfill('0');
            cout << setw(4)<<pair_mdata.first.GetDate().year<<'-'
                <<setw(2)<<pair_mdata.first.GetDate().month<<'-'
                <<setw(2)<<pair_mdata.first.GetDate().day<<" "
                <<events<<endl;
        }
    }
}



void CheckFormat(stringstream& stream)//Проверяет правильный ли разделяющий знак в записи даты, и если правильный, то пропускает его.
{
    if(stream.peek() != '-')
    {
        throw 1;
    }
    stream.ignore(1);
}

s_Date ParseDate(const string& s)
{
    s_Date date;
    stringstream stream(s);
    //Считываем (если можем) год, месяц и день. Проверяем разделяющий знак.
    bool res = true;
    res = true && (stream >> date.year);
    if(!res) throw runtime_error("Wrong date format: " + s);

    try
    {
        CheckFormat(stream);
    }
    catch(int ex)
    {
        if(ex == 1) throw runtime_error("Wrong date format: " + s);
    }

    res = true && (stream >> date.month);
    if(!res) throw runtime_error("Wrong date format: " + s);

    try
    {
        CheckFormat(stream);
    }
    catch(int ex)
    {
        if(ex == 1) throw runtime_error("Wrong date format: " + s);
    }

    res = true && (stream >> date.day);
    if(!res) throw runtime_error("Wrong date format: " + s);

    //Проверяем месяц и день на корректность.
    if(date.month < 1 || date.month > 12)
    {
        string error = "Month value is invalid: " + to_string(date.month);
        throw runtime_error(error);
    }
    if(date.day < 1 || date.day > 31)
    {
        string error = "Day value is invalid: " + to_string(date.day);
        throw runtime_error(error);
    }

    return date;
}


Line ParsLine(string& s)
{
    Line new_line;
    stringstream stream(s);
    string command;
    stream >> command;
    if(command == "Add")  new_line.com = ADD;
    else if(command == "Del") new_line.com = DEL;
    else if(command == "Find") new_line.com = FIND;
    else if(command == "Print") new_line.com = PRINT;
    else
    {
        string error1;
        error1 = "Unknown command: " + command;
        throw runtime_error(error1);
    }
    /*
    В зависимости от команды распарсить остальную строку
    */
    switch(new_line.com)
    {
    case ADD:
    case DEL:
    case FIND:
        string dt;
        stream >> dt;

        new_line.date = ParseDate(dt);

        stream >> new_line.event;
        break;

    }



    return new_line;
}


