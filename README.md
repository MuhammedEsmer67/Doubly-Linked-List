# Doubly Linked List — C++

A generic, template-based doubly linked list implementation in C++ built as part of a Data Structures series.

![C++](https://img.shields.io/badge/C%2B%2B-OOP-blue)
![Platform](https://img.shields.io/badge/Platform-Windows-informational)
![IDE](https://img.shields.io/badge/IDE-Visual%20Studio%202022-purple)

---

## Description

This project implements a fully functional doubly linked list using C++ templates, allowing it to work with any data type. Each node holds a value and two pointers — one to the next node and one to the previous — enabling efficient traversal in both directions.

---

## Features

- Insert at beginning, end, or after a specific node/index
- Delete first node, last node, or any specific node
- Search for a value and return its node
- Traverse and print the list
- Reverse the list in-place
- Access or update items by index
- Get list size and check if empty
- Clear the entire list

---

## Project Structure

```
📁 Doubly-Linked-List/
├── 📄 DoublyLinkedList.sln
├── 📁 DoublyLinkedList/
│   ├── 📁 Header Files/
│   │   └── 📁 DS/
│   │       └── clsDblLinkedList.h  — Template class with all linked list logic
│   └── 📁 Source Files/
│       └── main.cpp
```

---

## Technologies

- Language: C++
- Paradigm: Object-Oriented Programming (OOP), Templates
- IDE: Visual Studio 2022
- Platform: Windows

---

## How to Use

1. Include the header file in your project:
```cpp
#include "clsDblLinkedList.h"
```

2. Create a list and start using it:
```cpp
clsDblLinkedList myList;

myList.InsertEnd(10);
myList.InsertEnd(20);
myList.InsertBeginning(5);

myList.PrintList();   // Output: 5 10 20
myList.Reverse();
myList.PrintList();   // Output: 20 10 5

cout << myList.Size() << endl;    // Output: 3
cout << myList.isEmpty() << endl; // Output: 0
```

---

## Topics

`cpp` `data-structures` `linked-list` `oop` `templates` `visual-studio-2022`