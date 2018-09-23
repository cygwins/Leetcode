/*
 * pair up in two, merge two, repeat
 * i 1 2  4
 * 0 -*-*---*
 * 1 / /   /
 * 2 -*   /
 * 3 /   /
 * 4 -*-*
 * 5 / /
 * 6 -*
 */
#include <iostream>
#include <vector>
#include "catch.hpp"
#include "../List.hpp"
using std::vector;
using namespace List;

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if( lists.empty() ) return NULL;
        int n = lists.size();
        for(int i = 1; i < n; i *= 2) { // i: who 0 merges with
            for(int j = 0; j < n; j += 2 * i) {
                if(j + i < n) {
                    // std::cout << j << " " << j + i << std::endl;
                    lists[j] = merge2Lists( lists[j], lists[j + i] );
                }
            }
        }
        return lists[0];
    }
    ListNode* merge2Lists(ListNode* l1, ListNode* l2) {
        if( !l2 ) return l1;
        if( !l1 ) return l2;
        auto head = ( l1 -> val < l2 -> val ? l1 : l2 ), tail = head;
        if( l1 -> val < l2 -> val ) {
            l1 = l1 -> next;
        } else {
            l2 = l2 -> next;
        }
        while ( l1 && l2 ) {
            if( l1 -> val < l2 -> val ) {
                tail -> next = l1;
                l1 = l1 -> next;
            } else {
                tail -> next = l2;
                l2 = l2 -> next;
            }
            tail = tail -> next;
        }
        tail -> next = l1 ? l1 : l2;
        return head;
    }
};

TEST_CASE("processing", "[methodName]") {
    Solution s;
    vector<ListNode*> lists0{ parseList("0") };
    CHECK( printList( s.mergeKLists(lists0) ) == "0" );
    vector<ListNode*> lists1{ parseList("1->4->5"), parseList("1->3->4"), parseList("2->6") };
    CHECK( printList( s.mergeKLists(lists1) ) == "1->1->2->3->4->4->5->6" );
    vector<ListNode*> lists3;
    for(int i = 1; i < 10; ++i) {
        lists3.push_back( new ListNode(i) );
    }
    CHECK( printList( s.mergeKLists(lists3) ) == "1->2->3->4->5->6->7->8->9" );
}
