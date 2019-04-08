#pragma once

#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<tuple>
#include<iomanip>

using namespace std;

enum Command{ADD, DEL, FIND, PRINT};

struct s_Date{
    int year = 0;
    int month = 0;
    int day = 0;
};

class Date {
    s_Date date;
public:
    Date(s_Date);
    Date(int year, int month, int day);
    s_Date GetDate() const;
};

bool operator<(const Date& lhs, const Date& rhs);


class Database {
    map<Date, set<string> > mdata;
public:
    void AddEvent(const Date& date, const string& event);
    void DeleteEvent(const Date& date, const string& event);
    void DeleteDate(const Date& date);
    void Find(const Date& date) const;
    void Print() const;
};

void CheckFormat(stringstream& stream);//Проверяет правильный ли разделяющий знак в записи даты, и если правильный, то пропускает его.

s_Date ParseDate(const string& s);

struct Line{
    Command com;
    s_Date date;
    string event = "";
};

Line ParsLine(string& s);


