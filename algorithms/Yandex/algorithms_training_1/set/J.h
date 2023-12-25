#include <iostream>
#include <unordered_map>
#include <vector>
#include <tuple>
#include <string>


void expand(std::unordered_map<std::string, int>& points, int interval) {
    points["minXplusY"] -= interval;
    points["maxXplusY"] += interval;
    points["minXminusY"] -= interval;
    points["maxXminusY"] += interval;
}


void intersect(std::unordered_map<std::string, int>& points, std::unordered_map<std::string, int>& diffs_map) {
    points["minXplusY"] = std::max(points["minXplusY"], diffs_map["minXplusY"]);
    points["maxXplusY"] = std::min(points["maxXplusY"], diffs_map["maxXplusY"]);
    points["minXminusY"] = std::max(points["minXminusY"], diffs_map["minXminusY"]);
    points["maxXminusY"] = std::min(points["maxXminusY"], diffs_map["maxXminusY"]);
}


int solutionJ() {
    int interval, diff, n;
    std::cin >> interval >> diff >> n;

    std::unordered_map<std::string, int> points;
    points["minXplusY"] = 0;
    points["maxXplusY"] = 0;
    points["minXminusY"] = 0;
    points["maxXminusY"] = 0;

    int x, y;
    std::unordered_map<std::string, int> diffs_map;

    for (int i = 0; i != n; ++i) {
        expand(points, interval);

        std::cin >> x >> y;
        diffs_map["minXplusY"] = x + y - diff;
        diffs_map["maxXplusY"] = x + y + diff;
        diffs_map["minXminusY"] = x - y - diff;
        diffs_map["maxXminusY"] = x - y + diff;

        intersect(points, diffs_map);
    }

    std::vector<std::tuple<int, int>> final;

    for (int xPlusY = points["minXplusY"]; xPlusY <= points["maxXplusY"]; ++xPlusY) {
        for (int xMinusY = points["minXminusY"]; xMinusY <= points["maxXminusY"]; ++xMinusY) {
            if ((xPlusY + xMinusY) % 2 == 0)  {
                x = (xPlusY + xMinusY) / 2;
                y = xPlusY - x;
                final.emplace_back(x, y);
            }
        }
    }

    std::cout << final.size() << '\n';
    for (const auto& elem: final) {
        std::cout << std::get<0>(elem) << ' ' << std::get<1>(elem) << '\n';
    }
}