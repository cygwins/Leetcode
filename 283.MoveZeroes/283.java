/*
 * swap non-zero number to tail of processed, O(n)
 */

class Solution {
    public void moveZeroes(int[] nums) {
        int tail = 0;
        for(int scan = 0; scan < nums.length; scan++)
            if(nums[scan] != 0) nums[tail++] = nums[scan];
        while(tail < nums.length) nums[tail++] = 0;
    }
    public static void main(String[] args) {
        Solution s = new Solution();
        int[] a = {0,1,0,3,12};
        s.moveZeroes(a);
        for(int i : a) System.out.println(i);
    }
}
