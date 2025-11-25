
#include <stdio.h>
#include <stdlib.h>

// 辅助函数：返回两数最小值
int min(int a, int b) {
    return a < b ? a : b;
}

// 辅助函数：返回两数最大值
int max(int a, int b) {
    return a > b ? a : b;
}

// 递归函数：计算区间 [left, right] 中当前玩家能获得的最大分数
int maxScore(int *nums, int left, int right) {
    // 终止条件1：无数字可选，得分为0
    if (left > right) {
        return 0;
    }
    // 终止条件2：仅剩一个数字，必须选它
    if (left == right) {
        return nums[left];
    }
    
    // 选择左端：当前分数 + 对方操作后自己的最小得分（对方会尽量让自己得分少）
    int chooseLeft = nums[left] + min(
        maxScore(nums, left + 1, right - 1),  // 对方选右端后，自己在剩余区间的得分
        maxScore(nums, left + 2, right)       // 对方选左端后，自己在剩余区间的得分
    );
    
    // 选择右端：当前分数 + 对方操作后自己的最小得分
    int chooseRight = nums[right] + min(
        maxScore(nums, left + 1, right - 1),  // 对方选左端后，自己在剩余区间的得分
        maxScore(nums, left, right - 2)       // 对方选右端后，自己在剩余区间的得分
    );
    
    // 返回两种选择的最大得分
    return max(chooseLeft, chooseRight);
}

int main() {
    int n;
    scanf("%d", &n);
    int *nums = (int *)malloc(n * sizeof(int));  // 动态分配数组内存
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);  // 读取数组元素
    }
    
    // 计算数组总和
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += nums[i];
    }
    
    // 玩家1的最大得分
    int p1 = maxScore(nums, 0, n - 1);
    // 玩家2的得分 = 总和 - 玩家1得分
    int p2 = total - p1;
    
    // 判断玩家1是否获胜
    if (p1 >= p2) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    
    free(nums);  // 释放动态内存
    return 0;
}
