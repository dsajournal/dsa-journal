# Add Two Numbers

## Problem

You are given two linked lists representing two non negative numbers.

The digits are stored **in reverse order**.

Add the two numbers and return the result as a linked list.

Example:

```text
l1 = 2 → 4 → 3
l2 = 5 → 6 → 4

342 + 465 = 807

result = 7 → 0 → 8
```

---

## Core Idea

Since the digits are already in **reverse order**, we can add them exactly like normal addition from right to left.

```text
  342
+ 465
-----
  807
```

The linked lists give us:

```text
2 → 4 → 3
5 → 6 → 4
```

So we simply add corresponding nodes while keeping track of the **carry**.

---

## Mental Model

Think of every step as:

```text
digit1 + digit2 + carry
          ↓
     new digit
     new carry
```

Example:

```text
2 + 5 + 0 = 7
7 % 10 = 7
7 / 10 = 0
```

Next:

```text
4 + 6 + 0 = 10
10 % 10 = 0
10 / 10 = 1
```

Next:

```text
3 + 4 + 1 = 8
8 % 10 = 8
8 / 10 = 0
```

Result:

```text
7 → 0 → 8
```

---

## Algorithm

### 1. Create a dummy node

Use a dummy node so we can easily build the result list.

```text
dummy → ?
          ↑
         cur
```

### 2. Keep a `carry`

Initially:

```cpp
int carry = 0;
```

### 3. Process both lists

At every step:

```text
v1 + v2 + carry
```

If a list has already ended, treat its value as `0`.

```text
l1 = 2 → 4 → 3
l2 = 5 → 6

       ↓

2 + 5
4 + 6
3 + 0
```

### 4. Create the new digit

```cpp
int sum = v1 + v2 + carry;

int digit = sum % 10;
carry = sum / 10;
```

### 5. Move the pointers

Move `l1` and `l2` if they are not `nullptr`.

### 6. Continue while either list or carry exists

This condition is important:

```cpp
while (l1 != nullptr || l2 != nullptr || carry != 0)
```

Why include `carry`?

Example:

```text
9 → 9
9 → 1
```

At the final step:

```text
9 + 9 + 1 = 19
```

We still need to create the final `1`.

```text
8 → 0 → 1
```

This is the key point from the approach. ([西维蜀黍][1])

---

## C++ Code

```cpp
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        ListNode dummy(0);
        ListNode* current = &dummy;

        int carry = 0;

        while (l1 != nullptr || l2 != nullptr || carry != 0) {

            // Missing node is treated as 0
            int value1 = 0;
            int value2 = 0;

            if (l1 != nullptr) {
                value1 = l1->val;
            }

            if (l2 != nullptr) {
                value2 = l2->val;
            }

            // Add values and carry
            int sum = value1 + value2 + carry;

            // Get digit and carry
            int digit = sum % 10;
            carry = sum / 10;

            // Create result node
            current->next = new ListNode(digit);
            current = current->next;

            // Move to next nodes
            if (l1 != nullptr) {
                l1 = l1->next;
            }

            if (l2 != nullptr) {
                l2 = l2->next;
            }
        }

        return dummy.next;
    }
};
```

---

## Example

```text
l1:     2 → 4 → 3
l2:     5 → 6 → 4
        ↓   ↓   ↓

carry:  0   0   1

        2 + 5 + 0 = 7
        4 + 6 + 0 = 10
        3 + 4 + 1 = 8

result: 7 → 0 → 8
```

---

## Important Tricky Point

The lists can have **different lengths**.

```text
l1 = 2 → 4 → 3
l2 = 5 → 6
```

Treat the missing value as `0`:

```text
2 + 5
4 + 6
3 + 0
```

So we don't need to make the lists equal length.

---

## Complexity

**Time: O(max(n, m))**

We process each node of both lists once.

**Space: O(max(n, m))**

The result list contains up to `max(n, m) + 1` nodes.

The algorithm itself uses only **O(1) extra pointer/variable space**, excluding the output list.

---

## Single Most Important Point

> **At every node: `sum = v1 + v2 + carry`, store `sum % 10`, and carry `sum / 10`.**

### Quick Revision

```text
DUMMY
  ↓
ADD → DIGIT + CARRY → MOVE
          ↓
     next iteration

Loop while:
l1 || l2 || carry
```
