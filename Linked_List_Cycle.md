# Linked List Cycle

## Problem

Given the head of a linked list, determine whether the list contains a cycle.

```text
1 → 2 → 3 → 4
    ↑       ↓
    └───────┘

Output: true
```

A cycle exists if we can keep following `next` pointers and eventually reach a node we've already visited.

---

## Core Idea

Use **two pointers**:

```text
slow → moves 1 step
fast → moves 2 steps
```

This is called **Floyd's Cycle Detection Algorithm**.

```text
slow = slow->next;
fast = fast->next->next;
```

### Key observation

If there is a cycle, `fast` will eventually catch `slow` inside the cycle.

If there is no cycle, `fast` will reach `nullptr`.

```text
Cycle     → slow == fast → true
No cycle  → fast == nullptr → false
```

---

## Mental Model

Think of `slow` and `fast` as two runners.

```text
slow → 1 step at a time
fast → 2 steps at a time
```

On a normal path:

```text
1 → 2 → 3 → 4 → NULL
                ↑
              fast
```

`fast` eventually falls off the list.

Inside a cycle:

```text
1 → 2 → 3 → 4
    ↑       ↓
    └───────┘
```

`fast` keeps going around the cycle and eventually catches `slow`.

---

## Algorithm

```text
1. slow = head
2. fast = head
3. While fast and fast->next exist:
      move slow by 1
      move fast by 2

      if slow == fast:
          return true
4. return false
```

---

## Why `fast && fast->next`?

We move:

```cpp
fast = fast->next->next;
```

So we must make sure both pointers exist before doing it.

```cpp
while (fast != nullptr && fast->next != nullptr)
```

Otherwise, we could dereference `nullptr`.

---

## Code

```cpp
bool hasCycle(ListNode* head) {

    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr) {

        // Slow moves one step
        slow = slow->next;

        // Fast moves two steps
        fast = fast->next->next;

        // They meet inside a cycle
        if (slow == fast)
            return true;
    }

    // Fast reached the end
    return false;
}
```

---

## Why Does Meeting Mean a Cycle?

If there is no cycle, the list has an end:

```text
1 → 2 → 3 → 4 → NULL
```

So `fast` must eventually reach `NULL`.

If there is a cycle:

```text
      ┌─────────┐
      ↓         │
1 → 2 → 3 → 4 ─┘
```

Neither pointer can leave the cycle.

Since `fast` moves faster than `slow`, it keeps closing the gap until:

```text
slow == fast
```

Therefore, a meeting point proves that a cycle exists.

---

## Example

```text
1 → 2 → 3 → 4
    ↑       ↓
    └───────┘
```

Initially:

```text
slow = 1
fast = 1
```

After one iteration:

```text
slow = 2
fast = 3
```

Next:

```text
slow = 3
fast = 2
```

Eventually:

```text
slow = 4
fast = 4
```

They meet, so:

```text
return true
```

---

## Alternative: Hash Set

We can store every node we've already visited.

```text
if node already exists in set
    → cycle
else
    → add node
```

This works, but uses extra memory.

```text
Time  → O(n)
Space → O(n)
```

The two-pointer solution is better because it uses **O(1) space**.

---

## Complexity

### Time: O(n)

In the worst case, the pointers traverse the list and/or cycle a linear number of steps before either finding the cycle or reaching `nullptr`.

### Space: O(1)

We only use two pointers, `slow` and `fast`, so the extra space stays constant.

---

## Remember

```text
slow → 1 step
fast → 2 steps

They meet     → Cycle
fast hits NULL → No cycle
```

### One-line takeaway

> **Two pointers moving at different speeds: if they meet, there is a cycle.**
