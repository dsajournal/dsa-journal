# Sliding Window Maximum

## Problem

Given an array `nums` and an integer `k`, return the **maximum element in every contiguous window of size `k`**.

### Example

```text
nums = [1, 3, -1, -3, 5, 3, 6, 7]
k = 3
```

Windows:

```text
[1, 3, -1] → 3
[3, -1, -3] → 3
[-1, -3, 5] → 5
[-3, 5, 3] → 5
[5, 3, 6] → 6
[3, 6, 7] → 7
```

Output:

```text
[3, 3, 5, 5, 6, 7]
```

---

## Core Idea

Use a **Deque** to keep track of useful elements for the current window.

The deque stores **indices**, not values.

```text
Deque indices → values in decreasing order
Front         → index of maximum element
```

Example:

```text
Window: [1, 3, -1]

Deque values:
[3, -1]

Front = 3 → maximum
```

### Remember

```text
DEQUE = decreasing values
FRONT = maximum
```

---

## Why Remove From Back?

Suppose:

```text
Deque: 8 → 5 → 3
New:   10
```

Since `10` is bigger than all of them:

```text
8, 5, 3
```

can never become the maximum while `10` is in the window.

So remove smaller elements from the back:

```text
8 → 5 → 3
        ↓
10 arrives

Remove 3
Remove 5
Remove 8

Deque:
10
```

This keeps the deque decreasing.

```cpp
while (!dq.empty() && nums[dq.back()] <= nums[right])
    dq.pop_back();
```

---

## Why Remove From Front?

The deque stores indices.

When the window moves forward, an index can become **out of the window**.

For example:

```text
Window size = 3

[1, 2, 3]
 ↑
index 0
```

After sliding:

```text
[2, 3, 4]
```

Index `0` is no longer valid.

So if:

```cpp
dq.front() < left
```

remove it.

```cpp
dq.pop_front();
```

---

## Algorithm

For every `right` index:

```text
1. Remove indices from back whose values are smaller
2. Add current index to back
3. Remove front if it is outside the window
4. When window size becomes k:
      front of deque = maximum
      add nums[dq.front()] to answer
      move left forward
```

The important order is:

```text
REMOVE SMALLER
       ↓
ADD CURRENT
       ↓
REMOVE OUT OF WINDOW
       ↓
RECORD MAX
```

---

## Code

```cpp
vector<int> maxSlidingWindow(vector<int>& nums, int k) {

    deque<int> dq;
    vector<int> result;

    int left = 0;

    for (int right = 0; right < nums.size(); right++) {

        // Remove smaller elements from the back
        while (!dq.empty() &&
               nums[dq.back()] <= nums[right]) {

            dq.pop_back();
        }

        // Add current index
        dq.push_back(right);

        // Remove indices outside the window
        if (dq.front() < left) {
            dq.pop_front();
        }

        // Window has reached size k
        if (right - left + 1 == k) {

            // Front contains the maximum
            result.push_back(nums[dq.front()]);

            // Slide the window
            left++;
        }
    }

    return result;
}
```

---

## Mental Model

Think of the deque as a **candidate list for the maximum**.

```text
Current window

[ -1, -3, 5, 3, 6 ]

             ↓

Deque keeps only useful candidates:

[6]
```

Smaller elements behind a bigger element are useless.

Elements that leave the window are also removed.

So:

```text
Deque
  ↓
Only useful candidates
  ↓
Front = current maximum
```

---

## Why Is It O(n)?

At first it looks like the `while` loops could make the solution `O(n²)`.

But each index:

```text
is pushed into the deque once
and popped from the deque at most once
```

So across the entire array, the total number of deque operations is proportional to `n`.

Therefore:

```text
Time = O(n)
```

---

## Complexity

### Time: O(n)

Every element is added to the deque once and removed at most once.

Even though we use `while` loops, the total number of operations across the entire array is linear.

### Space: O(k)

The deque can contain indices from the current window, whose maximum size is `k`.

The result array is separate output space. The **auxiliary space** used by the algorithm is `O(k)`.

---

## Single Most Important Point

> **Keep the deque in decreasing order of values. The front always gives the maximum of the current window.**

```text
Remove smaller from back
        ↓
Add current index
        ↓
Remove expired from front
        ↓
Front = MAX
```
