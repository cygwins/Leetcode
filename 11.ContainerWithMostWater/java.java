import java.lang.Math;

class Solution {
    public int maxArea(int[] height) {
        int water = 0, i = 0, j = height.length - 1;
        while(i < j) {
            water = Math.max(water, (j - i) * Math.min(height[i], height[j]));
            // height[i] < height[j] ? i++ : j--; // this does not work, need to assign
            if(height[i] < height[j]) i++;
            else j--;
        }
        return water;
    }
    public static void main(String[] args) {
        int[] a = {1,2,3,4,5};
        Solution s = new Solution();
        System.out.println(s.maxArea(a));
    }
}
