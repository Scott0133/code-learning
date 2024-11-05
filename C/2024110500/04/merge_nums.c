// 合并两个[有序]数组

typedef struct nums {
    int *nums; // 数组表
    int length; // 数组长度
} nums;


void merge_nums(nums nums1, nums nums2, nums nums3) // 参数为三个数组结构体
{
    int i, j, k = 0; // 初始化各数组下标
    while (i<nums1.length && j<nums2.length) { // 当数组1和2还有剩余元素
        if (nums1.nums[i] < nums2.nums[j]) { // 若当前数组1小于数组2
            nums3.nums[k++] = nums1.nums[i++]; // 将nums1的当前元素赋值给nums3，各下标再自增1
        } else {
            nums3.nums[k++] = nums2.nums[j++];
        }
    }
    while (i<nums1.length) { // 当nums2处理完nums1还有剩余元素
        nums3.nums[k++] = nums1.nums[i++];
    }
    while (j<nums2.length) {
        nums3.nums[k++] = nums2.nums[j++];
    }
}