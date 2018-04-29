import re
class Solution(object):
    def decodeString(self, s):
        """
        :type s: str
        :rtype: str
        """
        if s is '':
            return ''
        parsed = re.sub(r'([^0-9\[\]]+)', r'"\1"', s) # quote all string
        # print(parsed, 'quote')
        parsed = parsed.replace('[', '*(') # fill missing * between k and string
        # print(parsed, '*')
        parsed = parsed.replace(']', ')') # parentheses ensure hierarchy
        # print(parsed, ')')
        parsed = re.sub(r'([^0-9])([0-9])', r'\1+\2', parsed) # fill missing + before k
        # print(parsed, '+k')
        parsed = parsed.replace(')"', ')+"') # fill missing + before string
        # print(parsed, '+"')
        # note: character before string is either k or ']'
        return eval(parsed)
