#include <iostream>
#include <string>
#include <sstream>
using namespace std;

long long to_int(string& s) {
    return stoll(s);
}

void to_ip(string& s, int ip[]) {
    stringstream ss(s);
    char c;

    ss >> ip[0]; ss >> c;
    ss >> ip[1]; ss >> c;
    ss >> ip[2]; ss >> c;
    ss >> ip[3];
}

void to_ip(long long number, int ip[]) {
    ip[3] = number % 256;
    number >>= 8;
    ip[2] = number % 256;
    number >>= 8;
    ip[1] = number % 256;
    number >>= 8;
    ip[0] = number % 256;
}

int main() {
    {
        string s;
        cin >> s;
        int ip[4];
        to_ip(s, ip);
        long long number = ip[0];
        number <<= 8;
        number += ip[1];
        number <<= 8;
        number += ip[2];
        number <<= 8;
        number += ip[3];
        cout << number << endl;
    }
    {
        string s;
        cin >> s;
        long long number = to_int(s);
        int ip[4];
        to_ip(number, ip);
        cout << ip[0] << '.';
        cout << ip[1] << '.';
        cout << ip[2] << '.';
        cout << ip[3] << endl;
    }
}
