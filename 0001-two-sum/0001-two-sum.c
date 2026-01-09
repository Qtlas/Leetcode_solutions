/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int* result = malloc(sizeof(int) * 2);
    result[0] = -1;
    result[1] = -1;
    *returnSize = 2;
    for (int i=0; i<numsSize-1; i++) {
        for (int j=i+1; j<numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                result[0] = i;
                result[1] = j;
                return result;
            }
        }
    }
    return result;

}