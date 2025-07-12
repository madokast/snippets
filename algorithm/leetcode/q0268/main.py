class Solution(object):
    def missingNumber(self, nums: list[int]):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        while True:
            exchanged = False
            missing = n
            for i in range(n):
                i_holder = nums[i]
                while i != i_holder and i_holder != n:
                    exchanged = True

                    # 需要放到目标位置 nums[i_holder]
                    temp = nums[i_holder]
                    nums[i_holder] = i_holder
                    i_holder = temp
                # 最后归宿 i
                nums[i] = i_holder
                if i != i_holder:
                    if exchanged and i_holder != n:
                        return i
                    missing = i
                
            if not exchanged:
                return missing

if __name__ == '__main__':
    m = Solution().missingNumber
    assert m([0]) == 1
    assert m([1]) == 0, m([0])
    assert m([0, 1]) == 2
    assert m([1, 0]) == 2
    assert m([3, 0, 1]) == 2, m([3, 0, 1])
    assert m([9,6,4,2,3,5,7,0,1]) == 8

