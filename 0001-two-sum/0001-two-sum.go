func twoSum(nums []int, target int) []int {
    hashMap := make(map[int]int)
    result := []int{0, 0}
    for i := range nums {
        t, found := hashMap[nums[i]]
        if !found {
            hashMap[target - nums[i]] = i
        } else {
            result[0], result[1] = t, i
            return result
        }
    }
    return result
}