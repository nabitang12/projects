#include <iostream>
#include <vector>

using namespace std;

int BinarySearch(vector<int>& array , int target){
    int left = 0;
    int right = array.size()-1;
    int index = -1;
    while(left<=right){
        int mid = (left+right)/2;

        if(array[mid] >target){
            right = mid-1;
        }else if(array[mid] < target){
            left = mid+1;
        }else{
            index = mid;
            return index;
        }
        return index;
    }
}

int Binary_recursive(vector<int>& array,int left,int right,int target){
    if(left>right)return -1;
    int mid = (left+right)/2;

    if(array[mid]==target)return mid;
    if(array[mid]>target)Binary_recursive(array,left,mid-1,target);
    return Binary_recursive(array,mid+1,right,target);
}

int main() {
    vector<int> array = {1, 3, 5, 7, 9, 11, 13, 15}; // 정렬된 배열
    int target = 7;

    // 반복문 이진 탐색 테스트
    int iterative_result = BinarySearch(array, target);
    cout << "BinarySearch 결과: " << iterative_result << endl;

    // 재귀 이진 탐색 테스트
    int recursive_result = Binary_recursive(array, 0, array.size() - 1, target);
    cout << "Binary_recursive 결과: " << recursive_result << endl;

    // 존재하지 않는 값 테스트
    target = 8;
    iterative_result = BinarySearch(array, target);
    cout << "BinarySearch (없는 값) 결과: " << iterative_result << endl;

    recursive_result = Binary_recursive(array, 0, array.size() - 1, target);
    cout << "Binary_recursive (없는 값) 결과: " << recursive_result << endl;

    return 0;
}