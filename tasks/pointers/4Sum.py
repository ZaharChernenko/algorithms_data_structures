def fourSum(nums: list[int], target: int) -> list[list[int]]:
    if len(nums) < 4: return []
    nums.sort()
    res = []
    for i in range(len(nums) - 3):
        if nums[i] * 4 > target: break
        if i > 0 and nums[i] == nums[i - 1]:
            continue
        for j in range(i + 1, len(nums) - 2):
            if j != i + 1 and nums[j] == nums[j - 1]:
                continue
            mid, right = j + 1, len(nums) - 1
            while mid < right:
                s = nums[i] + nums[j] + nums[mid] + nums[right]
                if s > target:
                    right -= 1
                elif s < target:
                    mid += 1
                else:
                    res.append([nums[i], nums[j], nums[mid], nums[right]])
                    mid += 1
                    right -= 1
                    while mid < right and nums[mid] == nums[mid - 1]: mid += 1
                    while mid < right and nums[right] == nums[right + 1]: right -= 1
    return res
