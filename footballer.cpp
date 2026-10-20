#include <bits/stdc++.h>
using namespace std;

struct date_of_birth
{
    int day;
    char month[20];
    int year;
};

struct footballer
{
    char name_surname[50];
    char club[50];
    date_of_birth dob;
};

void strcopy(char *a, char *b)
{
    while(*b)
    {
        *a = *b;
        a++;
        b++;
    }
    *a = '\0';
}

int main()
{

    footballer f;
    strcopy(f.name_surname, "Kiril Atanasov");
    strcopy(f.club, "Real Madrid U18");
    f.dob.year = 2009;
    strcopy(f.dob.month, "Oktomvri");
    f.dob.day = 17;

    cout << f.name_surname << endl;
    cout << f.club << endl;
    cout << f.dob.day << " " << f.dob.month << " " << f.dob.year;

    return 0;
}
