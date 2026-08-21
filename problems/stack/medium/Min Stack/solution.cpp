using namespace std;
#include <stack>
#include <deque>

// WHY THE FIRST ATTEMPT (commented out below) FAILED:
//   The monotonic deque was carried over from Sliding Window Maximum. Right
//   instinct, violated precondition:
//
//     Discarding a dominated element is only safe if that element is guaranteed
//     to leave BEFORE the element that dominated it.
//
//   Window (FIFO): oldest leaves first -> j < i means j exits first -> safe.
//   Stack  (LIFO): newest leaves first -> i pops BEFORE j -> j resurfaces as the
//                  minimum, so discarding it destroys data still in the stack.
//
//   Minimal failure: push(2), push(1), pop(), getMin() -> UB (answer should be 2).
//   Full write-up in README.md.
//
// TRANSFER RULE: ask "does the REASON it worked still hold?", not "does the shape fit?"
class MinStack {
    stack<int> st;
    // IMPROVE — this is only ever used as a stack (push_back/pop_back/back), as the
    // comment already notes. Declare `stack<int> mins;` so the type states the
    // invariant. A deque whose extra capability is unused misleads the reader.
    deque<int> dq; // we can use another stack instead
public:
    MinStack() {
        
    }
    
    // void push(int value) {
    //     st.push(value);
    //     while (!dq.empty() && dq.back() > value) {
    //         dq.pop_back();
    //     }
    //     dq.push_back(value);
    // }

    void push (int value) {
        st.push(value);
        // `>=` IS LOAD-BEARING, not style. With `>`, push(1); push(1) records only
        // one 1; the first pop() removes the sole copy from dq while a 1 remains in
        // st, and getMin() breaks. Duplicates must each be recorded.
        if (dq.empty() || dq.back() >= value) dq.push_back(value);
    }
    
    // void pop() {
    //     if (!dq.empty() && dq.front() == st.top()) dq.pop_front();
    //     st.pop();
    // }
    
    void pop() {
        if (dq.back() == st.top()) dq.pop_back();
        st.pop();
    }

    // int top() {
    //     return st.top();
    // }

    int top() {
        return st.top();
    }
    
    // int getMin() {
    //     return dq.front();
    // }

    int getMin() {
        return dq.back();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(value);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
