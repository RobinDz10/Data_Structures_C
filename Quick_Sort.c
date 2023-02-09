#include <stdio.h>
#include <stdlib.h>

void swap(int* n1, int* n2){
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
    return;
}

void quick_sort(int* nums, int left, int right){
    int i = left, j = right;
    int pivot = nums[left];
    if(left >= right) return;
    while(left < right){
        while(left < right && pivot <= nums[right])
            --right;
        if(pivot > nums[right]){
            swap(&nums[left], &nums[right]);
            ++left;
        }
        while(left < right && pivot >= nums[left])
            ++left;
        if(pivot < nums[left]){
            swap(&nums[left], &nums[right]);
            --right;
        }
    }
    nums[left] = pivot;
    quick_sort(nums, i, left - 1);
    quick_sort(nums, left + 1, j);
}

void print_arr(int* nums, int len){
    for(int i = 0; i < len; i++)
        printf("%d ", nums[i]);
    printf("\n");
    return;
}

void test(){
    int arr[10] = {1, 9, 2, 8, 3, 7, 4, 6, 5, 0};
    int size = sizeof(arr) / sizeof(arr[0]);
    quick_sort(arr, 0, size - 1);
    print_arr(arr, size);
}

int main(){
    test();
    return 0;
}
