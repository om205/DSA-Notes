# Best Time to Buy and Sell Stock

- Difficulty: Easy
- Topic: Array, Dynamic Programming, Greedy
- Platform: LeetCode
- Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

---

## Problem Statement

You are given an array `prices` where `prices[i]` is the price of a given stock on the `i`-th day. Your task is to maximize profit by choosing a single day to buy one stock and a different day in the future to sell it. Return the maximum profit you can achieve from this transaction, or 0 if no profit can be made.

---

## Examples

### Example 1

```txt
Input: prices = [7,1,5,3,6,4]

Output: 5
```

Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5. Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.

### Example 2

```txt
Input: prices = [7,6,4,3,1]

Output: 0
```

Explanation: In this case, no transactions are done and the max profit is 0.

---

## Constraints

- `1 <= prices.length <= 10^5`
- `0 <= prices[i] <= 10^4`
---

## Intuition

To maximize profit, we need to find the largest difference between a selling price and a buying price, where the buying day must occur before the selling day. We can achieve this by iterating through the prices, keeping track of the minimum price encountered so far. At each day, we calculate the potential profit if we were to sell on that day using the current minimum buying price, and then update our overall maximum profit found.

---

## Takeaways

- Problems requiring maximum difference between two elements (where order matters) can often be solved in a single pass.
- Maintain a running minimum (or maximum, depending on the problem) as you iterate through the array.
- A greedy approach often works efficiently by making the locally optimal choice (e.g., always buying at the lowest price seen so far) to achieve a globally optimal solution.

## C++ Concepts

-
