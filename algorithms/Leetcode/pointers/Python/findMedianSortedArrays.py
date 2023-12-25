def findMedianSortedArrays(nums1: list[int], nums2: list[int]) -> float:
    total_len = len(nums1) + len(nums2)
    left = right = 0
    med1 = med2 = 0

    for _ in range(total_len // 2 + 1):
        med1 = med2
        if (left < len(nums1) and right < len(nums2) and nums1[left] <= nums2[right]) \
        or right == len(nums2):
            med2 = nums1[left]
            left += 1
        else:
            med2 = nums2[right]
            right += 1

    return med2 if total_len & 1 else (med1 + med2) / 2

