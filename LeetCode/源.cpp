#include<iostream>
#include<stdio.h>
#include<vector>
using namespace std;

//class Solution {
//public:
//    int findRepeatNumber(vector<int>& nums) {
//        /*int length = nums.size();
//        vector<int> result(nums.size());
//        for (int i = 0; i < length; i++)
//        {
//            if (++result[nums[i]]>1)
//            {
//                return nums[i];
//            }
//        }
//        return -1;*/
//        for (int i = 0; i < nums.size(); i++)
//        {
//            if (nums[i] = i)continue;
//            if (nums[i] != nums[nums[i]]) {
//                swap(nums[i], nums[nums[i]]);
//            }
//            else
//            {
//                return nums[i];
//            }
//            return 0;
//        }
//    }
//};

//class Solution {
//public:
//    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
//        /*int Row = matrix.size();
//        if (Row==0)
//        {
//            return false;
//        }
//        int Column = matrix[0].size();
//        if (Column==0)
//        {
//            return false;
//        }
//        if (Row==1&&Column==1)
//        {
//            return matrix[0][0] == target;
//        }
//        if (Row==1)
//        {
//            for (int i = 0; i < Column; i++) {
//                if (matrix[0][i]==target)
//                {
//                    return true;
//                }
//            }
//            return false;
//        }
//        if (Column==1)
//        {
//            for (int i = 0; i < Row; i++)
//            {
//                if (matrix[i][0] == target) {
//                    return true;
//                }
//            }
//            return false;
//        }
//        vector<int> C(Column,-1);
//        int O = 0;
//        vector<int> R(Row, -1);
//        int X = 0;
//        for (int i = 0; i < Column; i++)
//        {
//            if (matrix[0][i]>target)
//            {
//                break;
//            }
//            if (matrix[0][i]==target || matrix[Row-1][i]==target)
//            {
//                return true;
//            }
//            if (matrix[0][i]<target&&matrix[Row-1][i]>target)
//            {
//                C[O] = i;
//                O++;
//            }
//        }
//        for (int i = 0; i < Row; i++)
//        {
//            if (matrix[i][0] > target)
//            {
//                break;
//            }
//            if (matrix[i][0] == target || matrix[i][Column-1] == target)
//            {
//                return true;
//            }
//            if (matrix[i][0]<target && matrix[i][Column-1]>target)
//            {
//                R[X] = i;
//                X++;
//            }
//        }
//        for (int i = 0; i < O; i++)
//        {
//            for (int j = 0; j < X; j++) {
//                if (matrix[R[j]][C[i]]==target)
//                {
//                    return true;
//                }
//            }
//        }
//        return 0;*/
//        int Row = matrix.size();
//        if (Row == 0)
//        {
//            return false;
//        }
//        int Column = matrix[0].size();
//        int i = Row - 1;
//        int j = 0;
//        while (i>=0&&j<Column)
//        {
//            if (matrix[i][j] > target)i--;
//            else if (matrix[i][j] < target)j++;
//            else return true;
//        }
//        return false;
//    }
//};

//class Solution {
//public:
//    string replaceSpace(string s) {
//        int count = 0;
//        int length = s.size();
//        for (char a : s) {
//            if (a==' ')
//            {
//                count++;
//            }
//        }
//        s.resize(length + 2 * count);
//        for (int i = length-1,int j=s.size()-1; i < j ; i--,j--)
//        {
//            if (s[i] != ' ')s[j] = s[i];
//            else
//            {
//                s[j - 2] = '%';
//                s[j - 1] = '2';
//                s[j] = '0';
//                j -= 2;
//            }
//        }
//        return s;
//    }
//};


//Definition for singly-linked list.
struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {

    }
};

int main() {
    
}