def threeSum(nums: list[int]) -> list[list[int]]:
    nums.sort()
    res = []
    for i in range(len(nums) - 2):
        if nums[i] > 0 or (i != 0 and nums[i] == nums[i - 1] == 0):
            break
        if i != 0 and nums[i] == nums[i - 1]: continue
        mid, right = i + 1, len(nums) - 1
        while mid < right:
            s = nums[i] + nums[mid] + nums[right]
            if s > 0:
                right -= 1
            elif s < 0:
                mid += 1
            else:
                res.append([nums[i], nums[mid], nums[right]])
                mid += 1
                right -= 1
                while mid < right and nums[mid] == nums[mid - 1]: mid += 1
                while mid < right and nums[right] == nums[right + 1]: right -= 1
    return res
