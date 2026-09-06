# Merge Two Sorted Lists

## Problem

Merge two **sorted linked lists** into one sorted linked list.

```text
1 → 2 → 4
1 → 3 → 4

↓
1 → 1 → 2 → 3 → 4 → 4
```

---

## Core Idea

Both lists are already sorted, so repeatedly:

```text
COMPARE → TAKE SMALLER → MOVE → REPEAT
```

Use a **dummy node + tail pointer** to build the result.

---

## Mental Model

```text
list1 → 1 → 2 → 4
list2 → 1 → 3 → 4
          ↓
       compare
          ↓
      smaller node
          ↓
         tail
```

`tail` always points to the **last node of the merged list**.

---

## Algorithm

```text
1. Create dummy node
2. tail = dummy
3. While both lists exist:
      compare list1.val and list2.val
      attach smaller node to tail
      move that list forward
      move tail forward
4. Attach remaining list
5. Return dummy.next
```

---

## Why Dummy Node?

We don't know whether the first node comes from `list1` or `list2`.

```text
dummy → merged list
          ↑
         tail
```

So we don't need special handling for the first node.

---

## Important Trick

When one list becomes `NULL`:

```text
list1 → NULL

list2 → 5 → 7 → 9
```

Just attach the remaining list:

```cpp
tail->next = list1 ? list1 : list2;
```

No need to process it node by node because it's already sorted.

---

## Code

```cpp
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {

    ListNode dummy(0);
    ListNode* tail = &dummy;

    while (list1 && list2) {

        if (list1->val <= list2->val) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }

        tail = tail->next;
    }

    tail->next = list1 ? list1 : list2;

    return dummy.next;
}
```

---

Time Complexity
O(n)
Because we visit each node once.

Space Complexity
O(1)
Because we only use a few pointers and don't create
extra data structures.
`m` = nodes in list2

---

## Remember

> **Two sorted lists → compare their current nodes → attach the smaller → move forward.**

The 3 lines to remember:

```cpp
tail->next = smaller;
smaller = smaller->next;
tail = tail->next;
```

And at the end:

```cpp
tail->next = list1 ? list1 : list2;
return dummy.next;
```
