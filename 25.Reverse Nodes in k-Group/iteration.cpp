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
        ListNode* prev = new ListNode(-1);
        prev -> next = head;
        auto ret = prev, tail = head;
        int count = 0;
        for( auto it = head; it; ++count ) {
            if( count % k == 0 ) head = it;
            if( count % k == k - 1 ) {
                tail = it;
                it = it -> next;
                prev -> next = reverse( head, tail );
                prev = head;
                continue;
            }
            it = it -> next;
        }
        return ret -> next;
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
