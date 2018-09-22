import Solution
test = Solution.Solution()
s = "2[abc]3[cd]ef"
print(s)
decoded_s = test.decodeString(s)
print(decoded_s)
print(decoded_s is "abcabccdcdcdef")
