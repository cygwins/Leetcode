/*
 * keep a priority q of size k
 */
#include <iostream>
#include <vector>
#include <queue>
#include "catch.hpp"
#include "../List.hpp"
using std::vector;
using std::priority_queue;
using namespace List;

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // if( lists.empty ) return NULL;
        int K = lists.size();
        // compare func, return true if the first argument comes "before" the second in the order
        //  (usually returns true when first is smaller than second).
        // we want smallest in the queue, but because priority queue gives the one comes "last" in order,
        // so bigger ones come "before" smaller ones in this order.
        auto cmp = [](ListNode* left, ListNode* right) { return (left -> val) > (right -> val); };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> q(cmp);
        for(int i = 0; i < K; ++i) {
            if( lists[i] ) q.push( lists[i] );
        }
        if( q.empty() ) return NULL;
        auto head = q.top(), tail = head;
        while( q.size() > 1 ) {
            if( tail -> next ) q.push( tail -> next );
            q.pop();
            tail -> next = q.top();
            tail = tail -> next;
        }
        return head;
    }
};

TEST_CASE("processing", "[methodName]") {
    Solution s;
    vector<ListNode*> lists0;
    CHECK( printList( s.mergeKLists(lists0) ) == "" );
    lists0.push_back( NULL );
    CHECK( printList( s.mergeKLists(lists0) ) == "" );
    vector<ListNode*> lists1{ parseList("1") };
    CHECK( printList( s.mergeKLists(lists1) ) == "1" );
    vector<ListNode*> lists2{ parseList("1->4->5"), parseList("1->3->4"), parseList("2->6") };
    CHECK( printList( s.mergeKLists(lists2) ) == "1->1->2->3->4->4->5->6" );
    vector<ListNode*> lists3;
    for(int i = 1; i < 10; ++i) {
        lists3.push_back( new ListNode(i) );
    }
    CHECK( printList( s.mergeKLists(lists3) ) == "1->2->3->4->5->6->7->8->9" );
}
