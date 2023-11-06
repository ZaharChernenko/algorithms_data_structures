#include <iostream>
#include <unordered_map>
#include <vector>
#include <numeric>
using std::cin, std::cout;

int main()
{
    int n, m, q;
    int min = -2147483647, max = 2147483647;
    cin >> n >> m >> q;
    std::vector<std::vector <int>> arr(n, std::vector<int>(m));
    std::unordered_map<int, std::vector<int>> low_up_dict;
    std::unordered_map<int, bool> excl_dict;
    std::unordered_map<std::string, int> dict;

    std::string word;
    for (int i = 0; i < m; ++i) {
        cin >> word;
        dict[word] = i;
        low_up_dict[i] = { min, max };
    }

    for (int i = 0; i < n; ++i) {
        excl_dict[i] = true;
        for (int j = 0; j < m; ++j) {
            cin >> arr[i][j];
        }
    }

    char act;
    int num;

    for (int i = 0; i < q; ++i) {
        cin >> word >> act >> num;
        if (act == '<') {
            low_up_dict[dict[word]][1] = std::min(low_up_dict[dict[word]][1], num);
        }
        else {
            low_up_dict[dict[word]][0] = std::max(low_up_dict[dict[word]][0], num);
        }
    }

    for (const auto& pair : low_up_dict) {
        for (int j = 0; j < n; ++j) {
            if (!excl_dict[j] || !(pair.second[0] < arr[j][pair.first] && arr[j][pair.first] < pair.second[1])) {
                excl_dict[j] = false;
            }
        }
    }

    long long sum = 0;

    for (const auto& pair : excl_dict) {
        if (pair.second) {
            for (int i = 0; i < m; ++i) {
                sum += arr[pair.first][i];
            }
        }
    }
    cout << sum;
    return 0;
}