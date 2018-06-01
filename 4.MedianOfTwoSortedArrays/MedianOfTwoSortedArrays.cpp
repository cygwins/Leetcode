/*
 * Binary Search for divider i of shorter array (m <= n)
 * a[0] .. a[i-1] | a[i] .. a[m-1], i = 0 .. m
 * b[0] .. b[j-1] | b[j] .. b[n-1], j = 0 .. n
 * #left == #right || #right - 1
 */
#include <iostream>
#include <algorithm> // max min
#include <vector>

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
// #define CATCH_CONFIG_RUNNER // if our own main() is provided
#include "catch.hpp" // define CATCH_CONFIG_MAIN / CATCH_CONFIG_RUNNER before including header


using std::vector;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        if(m > n) { return findMedianSortedArrays(nums2, nums1); } // ensure m <= n
        if(m == 0) { // a empty, b is not
            return median(nums1, nums2, 0);
        }
        int imin = 0, imax = m, i, j;
        while(imin < imax) {
            i = (imin + imax) / 2;
            j = (m + n) / 2 - i;
            // std::cout << "min " << imin << ", max " << imax << std::endl;
            // std::cout << "i = " << i << ", j = " << j << std::endl;
            // std::cout << "left " << left(nums1, nums2, i) << std::endl;
            // std::cout << "right " << right(nums1, nums2, i) << std::endl;
            // char t; // pause
            // std::cin >> t;
            if(j < 0 || (i > 0 && j < n && nums1[i - 1] > nums2[j])) { // i too big
                imax = i - 1;
                continue;
            }
            else if(j > n || (i < m && j > 0 && nums1[i] < nums2[j - 1])) { // i too small
                imin = i + 1;
                continue;
            }
            else { // lucky guess
                return median(nums1, nums2, i);
            }
        } // imin >= imax here
        return median(nums1, nums2, imin);
    }
    inline int left(vector<int>& nums1, vector<int>& nums2, const int i) { // biggist of left
        int m = nums1.size(), n = nums2.size();
        int j = (m + n) / 2 - i;
        if(i == 0) { // a left is empty
            return nums2[j - 1];
        }
        if(j == 0) { // b left is empty
            return nums1[i - 1];
        }
        return std::max(nums1[i - 1], nums2[j - 1]);
    }
    inline int right(vector<int>& nums1, vector<int>& nums2, const int i) { // smallest of right
        int m = nums1.size(), n = nums2.size();
        int j = (m + n) / 2 - i;
        if(i == m) { // a right is empty
            return nums2[j];
        }
        if(j == n) { // b right is empty
            return nums1[i];
        }
        return std::min(nums1[i], nums2[j]);
    }
    inline double median(vector<int>& nums1, vector<int>& nums2, const int i) {
        int m = nums1.size(), n = nums2.size();
        if((n + m) % 2) { // n + m is odd
            return static_cast<double>(right(nums1, nums2, i));
        }
        else { // n + m is even
            return (left(nums1, nums2, i) + right(nums1, nums2, i)) / 2.0;
        }
    }
};

TEST_CASE( "Medians are computed", "[findMedianSortedArrays]" ) {
    Solution s;
    vector<int> a{1,3}, b{2}, c{1}, d{2,3,4,5}, e{};
    REQUIRE( s.findMedianSortedArrays(a, b) == 2.0 );
    REQUIRE( s.findMedianSortedArrays(c, d) == 3.0 );
    REQUIRE( s.findMedianSortedArrays(d, e) == 3.5 );
}

/*
int main() {
    int result = Catch::Session().run();
    return result;
}
*/
