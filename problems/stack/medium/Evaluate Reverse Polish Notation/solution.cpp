using namespace std;
#include <vector>
#include <stack>
#include <string>

class Solution {
public:
    // TRIGGER: "evaluate an expression where operators FOLLOW their operands" -> stack.
    //   Operators consume the most recently produced values, which is LIFO by definition.
    //
    // NOTE TO SELF: expected to need a postfix tutorial first, derived it cold instead.
    //   RPN passes the "can I derive this in 25 min?" test. Calibration: I underestimate
    //   what I can derive. See notes/roadmap.md -> theory triage.
    int evalRPN(vector<string>& tokens) {
        stack<int> operands;

        // IMPROVE 1 — prefer `const string& str` : the reference is never mutated, and
        // const documents that plus allows const inputs.
        for (string& str: tokens) {
            char ch = str[0];

            // GOOD — this test is genuinely clever and correct. Every operator is
            // EXACTLY one character, so any token of length >= 2 must be a number.
            // That single fact handles negative literals ("-11") with no special case,
            // and a lone "-" still reads as an operator.
            //
            // IMPROVE 2 — parenthesise the && inside the ||. Correct by precedence
            // (&& binds tighter), but it makes the reader verify that, and GCC/Clang
            // warn here (-Wparentheses):
            //     if (str.size() > 1 || (ch >= '0' && ch <= '9'))
            if (str.size() > 1 || ch <= '9' && ch >= '0') {
                operands.push(stoi(str));
                continue;
            }
            // GOOD — operand order is right, and this is where most people fail.
            // "a b op" means a op b; a was pushed first, so b pops FIRST.
            // Commutative ops (+, *) hide the bug; - and / expose it.
            int b = operands.top(); operands.pop();   // right operand
            int a = operands.top(); operands.pop();   // left operand

            // IMPROVE 3 — four sequential `if`s: after '+' matches, the other three
            // still get tested, and nothing expresses that they're mutually exclusive.
            // Use a switch. This is also the SAME repetition-as-bug-farm shape that hid
            // the inverted `==` in Valid Parentheses -- no bug here, same structure.
            //
            //     switch (ch) {
            //         case '+': operands.push(a + b); break;
            //         case '-': operands.push(a - b); break;
            //         case '*': operands.push(a * b); break;
            //         case '/': operands.push(a / b); break;
            //     }
            //
            // NOTE — a/b truncates toward zero (GUARANTEED since C++11: -7/2 == -3),
            // which is exactly this problem's spec. Say that out loud in an interview.
            // NOTE — a*b is int arithmetic; safe only because the constraints promise
            // every intermediate fits in 32 bits. Flag the assumption, don't assume it.
            if (ch == '+') operands.push(a+b);
            if (ch == '-') operands.push(a-b);
            if (ch == '*') operands.push(a*b);
            if (ch == '/') operands.push(a/b);
        }
        return operands.top();
    }
};