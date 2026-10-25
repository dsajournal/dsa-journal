# Find the Duplicate Number

## Problem

Given an array of `n + 1` integers where each number is between `1` and `n`, find the duplicate without modifying the array and using O(1) extra space.

```text
nums = [1, 3, 4, 2, 2]
Answer = 2
```

## Core Idea

Treat each index as a node. The value at that index tells us which index to visit next: `index → nums[index]`.

First arrange the nodes by index, then draw each arrow using the value in `nums[index]`.

```text
Index:   0   1   2   3   4
Value:   1   3   4   2   2

Connections:
0 → 1 → 3 → 2 → 4
            ↑       |
            └───────┘
```

The cycle is `2 → 4 → 2`. The duplicate value creates the cycle, so we can find the duplicate using Floyd's Cycle Detection algorithm.

## Algorithm

1. Move `slow` one step and `fast` two steps until they meet.
2. Reset `slow` to index `0`.
3. Move both pointers one step at a time. Their next meeting point is the duplicate.

## Why Do We Use `do while`?

```cpp
do {
    slow = nums[slow];
    fast = nums[nums[fast]];
} while (slow != fast);
```

At the start, both pointers are initialized to index `0`, so `slow == fast` is already true. But that is not a meaningful meeting inside the cycle because neither pointer has moved yet.

A regular `while (slow != fast)` would skip the loop completely. A `do while` always executes the body once before checking the condition, so both pointers move first and then their positions are compared.

For `nums = [1, 3, 4, 2, 2]`:

| Step | Slow (1 step) | Fast (2 steps) |
|---|---:|---:|
| Start | 0 | 0 |
| 1 | 1 | 3 |
| 2 | 3 | 4 |
| 3 | 2 | 4 |
| 4 | 4 | 4 |

They meet at index `4`, which is a meeting point inside the cycle. Next, reset `slow` to `0` and move both pointers one step at a time. They meet at index `2`, the start of the cycle and the duplicate number.

**Key point:** use `do while` because the pointers must move at least once before checking whether they meet.

## C++ Code

```cpp
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0;
        int fast = 0;

        // Step 1: Find a meeting point inside the cycle
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        // Step 2: Find the start of the cycle
        slow = 0;

        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }

        return slow;
    }
};
```

## Complexity

**Time: O(n)** because the pointers traverse the array a constant number of times.

**Space: O(1)** because we only use two pointers.

## Single Most Important Point

**Connect index `i` to index `nums[i]`. The duplicate creates a cycle, and the cycle's entry point is the answer.**
