/*
 * brief
 */
#include <iostream>
#include "catch.hpp"
#include "../List.hpp"
using namespace List;

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if( !head || k <= 1 ) return head;
        int count = k;
        auto tail = head;
        while( --count ) {
            tail = tail -> next;
            if( !tail ) return head;
        }
        tail -> next = reverseKGroup( tail -> next, k );
        return reverse( head, tail );
    }
    ListNode* reverse( ListNode* head, ListNode* tail ) {
        auto tmp = head -> next;
        while( head != tail ) {
            head -> next = tail -> next;
            tail -> next = head;
            head = tmp;
            tmp = head -> next;
        }
        return head;
    }
};

TEST_CASE("recursion") {
    Solution s;
    CHECK(printList(s.reverseKGroup(parseList("1->2->3->4->5"), 2)) == "2->1->4->3->5");
    CHECK(printList(s.reverseKGroup(parseList("1->2->3->4->5"), 3)) == "3->2->1->4->5");
}
