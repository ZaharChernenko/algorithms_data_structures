#include <iostream>
#include <unordered_map>

using std::cin, std::cout;


int main()
{
    int n, m, q;
    cin >> n >> m >> q;

    std::unordered_map<int, int> a, b;
    int var;

    for (int i = 0; i < n; ++i) {
        cin >> var;
        a.insert_or_assign(var, ++a[var]);
    }

    for (int i = 0; i < m; ++i) {
        cin >> var;
        b.insert_or_assign(var, ++b[var]);
    }


    int diff = 0;

    for (const auto &pair: a) {
        auto search = b.find(pair.first);
        if (search != b.end()) {
            diff += abs(pair.second - search->second);
        }
        else diff += pair.second;
        //cout << pair.first << ' ' << pair.second << ' ';
    }

    for (const auto &pair : b) {
        auto search = a.find(pair.first);
        if (search == a.end()) diff += pair.second;
    }

    int act, temp;
    char who;

    for (int i = 0; i < q; ++i) {
        cin >> act >> who >> var;
        if (who == 'A') {
            auto search = b.find(var);
            if (act == 1) {
                a.insert_or_assign(var, ++a[var]);
                temp = a[var] - 1;
            }
            else {
                --a[var];
                temp = a[var] + 1;
            }
                
            if (search == b.end()) {
                diff += act;
            }
            else {
                if (abs(temp - b[var]) > abs(a[var] - b[var])) {
                    --diff;
                }

                else ++diff;
            }

            
        }

        else {
            auto search = a.find(var);
            if (act == 1) {
                b.insert_or_assign(var, ++b[var]);
                temp = b[var] - 1;
            }
            else {
                --b[var];
                temp = b[var] + 1;
            }

            if (search == a.end()) {
                diff += act;
            }
            else {
                if (abs(temp - a[var]) > abs(a[var] - b[var])) {
                    --diff;
                }

                else ++diff;
            }
        }

        cout << diff << ' ';
    }
}