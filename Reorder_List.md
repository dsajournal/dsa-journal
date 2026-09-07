# Reorder List

## Problem

You are given the head of a singly linked list.

You need to **reorder the nodes** in this pattern:

```text
L0 → L1 → L2 → ... → Ln

↓

L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → ...
```

### Example

```text
Input:
1 → 2 → 3 → 4

Output:
1 → 4 → 2 → 3
```

Another example:

```text
Input:
1 → 2 → 3 → 4 → 5

Output:
1 → 5 → 2 → 4 → 3
```

We must rearrange the existing nodes **in-place**.

---

## Core Idea

Break the problem into **3 simple steps**:

```text
1. Find the middle
2. Reverse the second half
3. Merge both halves alternately
```

Example:

```text
1 → 2 → 3 | 4 → 5
```

Reverse second half:

```text
1 → 2 → 3 | 5 → 4
```

Merge alternately:

```text
1 → 5 → 2 → 4 → 3
```

### Remember

```text
MIDDLE → REVERSE → MERGE
```

---

## Step 1: Find the Middle

Use the **slow and fast pointer** technique.

```text
slow → moves 1 step
fast → moves 2 steps
```

```cpp
ListNode* slow = head;
ListNode* fast = head;

while (fast != nullptr && fast->next != nullptr) {

    slow = slow->next;
    fast = fast->next->next;
}
```

For:

```text
1 → 2 → 3 → 4 → 5
```

`slow` reaches the middle:

```text
1 → 2 → 3 | 4 → 5
          ↑
         slow
```

---

## Step 2: Reverse the Second Half

We reverse the list starting from `slow`.

```text
4 → 5
```

becomes:

```text
5 → 4
```

Use the standard linked list reversal:

```cpp
ListNode* prev = nullptr;
ListNode* current = slow;

while (current != nullptr) {

    ListNode* next = current->next;

    current->next = prev;

    prev = current;
    current = next;
}
```

Now:

```text
First half:
1 → 2 → 3

Second half:
5 → 4
```

`prev` points to the head of the reversed second half.

---

## Step 3: Merge Alternately

Now take one node from each half:

```text
First:  1 → 2 → 3
Second: 5 → 4
```

Build:

```text
1 → 5 → 2 → 4 → 3
```

Before changing the links, save the next nodes:

```cpp
ListNode* nextFirst = first->next;
ListNode* nextSecond = second->next;
```

Then connect:

```cpp
first->next = second;
second->next = nextFirst;
```

Move both pointers:

```cpp
first = nextFirst;
second = nextSecond;
```

---

## Complete Code

```cpp
void reorderList(ListNode* head) {

    if (head == nullptr || head->next == nullptr)
        return;

    // Step 1: Find the middle
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr) {

        slow = slow->next;
        fast = fast->next->next;
    }

    // Step 2: Reverse the second half
    ListNode* prev = nullptr;
    ListNode* current = slow;

    while (current != nullptr) {

        ListNode* next = current->next;

        current->next = prev;

        prev = current;
        current = next;
    }

    // Step 3: Merge the two halves
    ListNode* first = head;
    ListNode* second = prev;

    while (second != nullptr) {

        ListNode* nextFirst = first->next;
        ListNode* nextSecond = second->next;

        first->next = second;
        second->next = nextFirst;

        first = nextFirst;
        second = nextSecond;
    }
}
```

---

## Why Do We Need to Reverse?

The required order is:

```text
1st → Last → 2nd → 2nd Last → ...
```

The first half already gives us:

```text
1 → 2 → 3
```

But we need the nodes from the end in reverse order:

```text
5 → 4
```

So:

```text
First half:  1 → 2 → 3

Second half: 5 → 4
```

Now alternating them gives:

```text
1 → 5 → 2 → 4 → 3
```

---

## Important Pointer Trick

Whenever you change a linked list pointer, **save the next node first**.

For merging:

```cpp
ListNode* nextFirst = first->next;
ListNode* nextSecond = second->next;
```

Then change the links.

Otherwise, you can lose access to the remaining nodes.

This same idea is used in **Reverse Linked List**.

---

## Example

Start:

```text
1 → 2 → 3 → 4 → 5
```

### Find Middle

```text
1 → 2 → 3 | 4 → 5
          ↑
         slow
```

### Reverse Second Half

```text
1 → 2 → 3

5 → 4
```

### Merge

```text
1 → 5
```

```text
1 → 5 → 2 → 4
```

```text
1 → 5 → 2 → 4 → 3
```

Done.

---

## Complexity

### Time: O(n)

We make three linear passes:

```text
Find middle  → O(n)
Reverse      → O(n)
Merge        → O(n)
```

Since these happen one after another:

```text
O(n) + O(n) + O(n) = O(n)
```

### Space: O(1)

We only use a fixed number of pointers:

```text
slow
fast
prev
current
first
second
```

No extra array, hash map, or linked list is created.

Therefore:

```text
Space = O(1)
```

---

## Single Most Important Point

> **Reorder List = Find the middle → reverse the second half → merge the two halves alternately.**

```text
MIDDLE → REVERSE → MERGE
```
