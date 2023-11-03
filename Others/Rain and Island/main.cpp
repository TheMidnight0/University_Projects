#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cmath>
using namespace std;

tuple<vector<int>, vector<double>> create(string line, int s) {
    vector<int> island;
    vector<double> water;
    string temp;
    int i = 0, index = 0;
    line = line + " ";
    while (i <= line.length()) {
        if (line[i] != ' ') {
            temp += line[i];
        } else {
            if (temp != "") {
                island.push_back(stoi(temp));
                water.push_back(0);
                temp = "";
                index += 1;
                if (index+1 > s) {
                    i = line.length();
                }
            }
        }
        i+= 1;
    }
    return make_tuple(island, water);
}

void rain(vector<int> a, vector<double> &b, int deb, bool drain) {
    int i = 0, j, max, min, memmin;
    while (i < a.size()) {
        memmin = a[i];
        max = 0;
        j = i+1;
        while (j < a.size()) {
            if (a[j] < memmin) {
                memmin = a[j];
            } else {
                if (a[j] > max) {
                    max = a[j];
                    min = memmin;
                    if (max >= a[i]) {
                        j = a.size();
                    }
                }
            }
            j+= 1;
        }
        if (max > min) {
            if (max > a[i]) {
                max = a[i];
            }
            j = i+1;
            while (a[j] < max) {
                if (drain) {
                    b[j] = min;
                } else {
                    b[j] = b[j] + (double(max-min)/100)*deb;
                    if (b[j] > max) {
                        b[j] = max;
                    }
                    if (b[j] < min) {
                        b[j] = min;
                    }
                }
                j += 1;
            }
            i = j;
        } else {
            i += 1;
        }
    }
}

void print(vector<int> a, vector<double> b) {
    string temp;
    cout<<"\n";
    for (int i = *max_element(a.begin(), a.end()); i > 0; i -= 1) {
        for (int j = 0; j < a.size(); j += 1) {
            if (i <= a[j] or i <= round(b[j])) {
                if (a[j] >= i) {
                    temp += "##";
                } else {
                    temp += "~~";
                }
            } else {
                temp += "  ";
            }
        }
        cout<<temp<<"\n";
        temp = "";
    }
    cout<<"\n";
}

int main() {
    string line, command;
    int size, deb_per;
    bool wait = true;
    cout<<"Введите максимальный размер острова в длину: ";
    cin>>size;
    cout<<"Введите процент воды, который заполнит остров за один ход: ";
    cin>>deb_per;
    cout<<"Введите высоты острова через пробел: ";
    cin.ignore(1);
    getline(cin, line);
    auto[island, water] = create(line, size);
    rain(island, water, 0, 1);
    rain(island, water, deb_per, 0);
    print(island, water);
    cout<<"Отлично! Попробуйте ввести команды:\n";
    cout<<"`help` - получить список команд\n";
    cout<<"`stop` - прекратить работу комманды\n";
    cout<<"`rain <ПРОЦЕНТ ДОЖДЯ>` - провести еще один дождь либо высушить остров\n";
    cout<<"`drain` -  полностью высушить остров\n";
    cout<<"`new_island` - пересоздать остров\n\n";
    while (wait != false) {
        cout<<"> ";
        cin>>command;
        if (command == "help") {
            cout<<"\n`help` - получить список команд\n";
            cout<<"`stop` - прекратить работу комманды\n";
            cout<<"`rain <ПРОЦЕНТ ДОЖДЯ>` - провести еще один дождь либо высушить остров\n";
            cout<<"`drain` -  полностью высушить остров\n";
            cout<<"`new_island` - пересоздать остров\n\n";
        }
        if (command == "stop") {
            wait = false;
        }
        if (command == "rain") {
            cin>>deb_per;
            rain(island, water, deb_per, 0);
            print(island, water);
        }
        if (command == "drain") {
            rain(island, water, 0, 1);
            print(island, water);
        }
        if (command == "new_island") {
            cout<<"\nВведите максимальный размер острова в длину: ";
            cin>>size;
            cout<<"Введите высоты острова через пробел: ";
            cin.ignore(1);
            getline(cin, line);
            tie(island, water) = create(line, size);
            rain(island, water, 0, 1);
            print(island, water);
        }
    }
    return 0;
}