#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) { }
};

void input(ListNode &l) {
    int d;
    std::cin >> d;
    if(d < 0 || d > 9) { return; }
    l.val = d;
    ListNode *p = &l, *c; // previous, current
    while(std::cin >> d, d >= 0 && d <= 9) {
        c = new ListNode(d);
        p -> next = c;
        p = c;
    }
}

void output(ListNode &l) {
    ListNode *c = &l; // current
    std::cout << c -> val;
    while(c -> next) {
        std::cout << " -> " << c -> next -> val;
        c = c -> next;
    }
    std::cout << std::endl;
}

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0, digit = 0;
        ListNode head(0), *p = &head;
        while(l1 || l2 || carry) {
            digit = carry; // of last digit
            if(l1) { digit += l1 -> val; l1 = l1 -> next; }
            if(l2) { digit += l2 -> val; l2 = l2 -> next; }
            // std::cout << "val " << answer -> val << std::endl;
            // std::cout << "carry " << carry << std::endl;
            carry = digit / 10;
            digit %= 10;
            // output(*answer);
            p -> next = new ListNode(digit);
            p = p -> next;
        }
        return head.next;
    }
};

int main() {
    Solution S;
    ListNode l1(0), l2(0), *ans;
    std::cout << "input l1 (-1 to stop):" << std::endl;
    input(l1);
    std::cout << "input l2 (-1 to stop):" << std::endl;
    input(l2);
    std::cout << "  "; output(l1);
    std::cout << "+ "; output(l2);
    ans = S.addTwoNumbers(&l1, &l2);
    std::cout << "= "; output(*ans);
    return 0;
}
