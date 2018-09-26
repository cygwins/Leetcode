/*
 * brief
 */
#include <iostream>
#include "catch.hpp"
#include "../List.hpp"
using namespace List;

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if( head == nullptr || head -> next == nullptr ) return head;
        auto newHead = head -> next;
        head -> next = swapPairs( newHead -> next );
        newHead -> next = head;
        return newHead;
    }
};

TEST_CASE("processing", "[methodName]") {
    Solution s;
    CHECK(printList(s.swapPairs(parseList("1->2->3->4"))) == "2->1->4->3");
}
