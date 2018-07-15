/*
 * The only even lengthed prime palindrome is 11
 * so only try odd length palindromes
 */
#include <cmath>
#include "catch.hpp"
using std::log10;
using std::pow;

class Solution {
public:
    int primePalindrome(int N) {
        if( 7 < N && N <= 11 ) return 11;
        for( int i = 2; i < 100000; ++i ) {
            int pal = makePalindrome( i );
            if( pal >= N && isPrime( pal ) ) return pal;
        }
        return 0;
    }
    bool isPrime( int n ) {
        if( n < 2 || n % 2 == 0) return n == 2;
        for( int i = 3; i * i <= n; i += 2 ) {
            if( n % i == 0 ) return false;
        }
        return true;
    }
    int makePalindrome( int n ) {
        if( n < 10 ) return n;
        int left = n, right = 0, d = 1;
        n /= 10;
        while( n ) {
            right *= 10;
            right += n % 10;
            d *= 10;
            n /= 10;
        }
        int pal = left * d + right;
        return pal;
    }
};

TEST_CASE("calculating", "[primePalindrome]") {
    Solution s;
    CHECK(s.isPrime(4) == false);
    CHECK(s.isPrime(1) == false);
    CHECK(s.isPrime(7) == true);
    CHECK(s.makePalindrome(7) == 7);
    CHECK(s.makePalindrome(12) == 121);
    CHECK(s.primePalindrome(6) == 7);
    CHECK(s.primePalindrome(8) == 11);
    CHECK(s.primePalindrome(13) == 101);
    CHECK(s.primePalindrome(1) == 2);
    CHECK(s.primePalindrome(10) == 11);
    CHECK(s.primePalindrome(9989900) == 100030001);
}
