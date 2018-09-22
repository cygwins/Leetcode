public class Solution {
    public int missingNumber(int[] nums) {
        int n = (nums.length + 1) * nums.length / 2;
        for(int i : nums) n -= i;
        return n;
    }
}
