#include <vector>

using namespace std;


class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int mid, right;
        vector<vector<int>> res;
        vector<int> triplet;
        for (size_t i = 0; i != nums.size() - 2; ++i) {
            if (nums[i] > 0 || (i >= 1 && nums[i - 1] == 0 && nums[i] == 0)) break;
            if (i != 0 && nums[i] == nums[i - 1]) continue;
            mid = i + 1; right = nums.size() - 1;
            while (mid < right) {
                if (nums[i] + nums[mid] + nums[right] > 0) --right;
                else if (nums[i] + nums[mid] + nums[right] < 0) ++mid;
                else {
                    triplet = {nums[i], nums[mid], nums[right]};
                    res.push_back(triplet);
                    --right; ++mid;
                    while (mid < right && nums[right] == nums[right + 1]) --right;
                    while (mid < right && nums[mid] == nums[mid - 1]) ++mid;
                }
            }
        }
        return res;
    }
};