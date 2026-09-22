#pragma once
#include <iostream>
using namespace std;

template <class T>
class clsDblLinkedList
{
protected:

	int _Size = 0;

	

public:

	~clsDblLinkedList() { Clear(); }

	clsDblLinkedList() = default; //allows empty double-linked-list
	clsDblLinkedList(const clsDblLinkedList&) = delete; //Disable shallow copy
	clsDblLinkedList& operator = (const clsDblLinkedList&) = delete; //Disable copy assignment operator

	class clsNode
	{
	public:

		T Value;
		clsNode* Next;
		clsNode* Prev;
	};

	clsNode* Head = nullptr;

	void InsertBeginning(T Value)
	{
		clsNode* NewNode = nullptr;
		NewNode = new clsNode;

		NewNode->Value = Value;
		NewNode->Next = Head;
		NewNode->Prev = nullptr;

		if (Head != nullptr)
			Head->Prev = NewNode;

		Head = NewNode;
		_Size++;
	}

	void PrintList()
	{
		clsNode* TempHead = Head;

		while (TempHead != nullptr)
		{
			cout << TempHead->Value << " ";
			TempHead = TempHead->Next;
		}

		cout << endl;
	}

	clsNode* Find(T Value)
	{
		clsNode* TempHead = Head;

		while (TempHead != nullptr)
		{
			if (TempHead->Value == Value)
				return TempHead;

			TempHead = TempHead->Next;
		}

		return nullptr;
	}

	void InsertEnd(T Value)
	{
		clsNode* NewNode = nullptr;
		NewNode = new clsNode();

		NewNode->Value = Value;
		NewNode->Next = nullptr;

		if (Head == nullptr)
		{
			NewNode->Prev = nullptr;
			Head = NewNode;
		}
		else
		{
			clsNode* Current = Head;

			while (Current->Next != nullptr)
				Current = Current->Next;

			NewNode->Prev = Current;
			Current->Next = NewNode;
		}

		_Size++;
	}

	void InsertAfter(clsNode* Node, T Value)
	{
		if (Node == nullptr)
			return;

		clsNode* NextNode = Node->Next;

		clsNode* NewNode = new clsNode;
		NewNode->Value = Value;
		NewNode->Next = NextNode;
		NewNode->Prev = Node;

		Node->Next = NewNode;
		if (NextNode != nullptr)
			NextNode->Prev = NewNode;

		_Size++;
	}

	void DeleteNode(clsNode* Node)
	{
		if (Head == nullptr || Node == nullptr)
			return;

		if (Node->Next != nullptr)
			Node->Next->Prev = Node->Prev;

		(Node->Prev != nullptr) ? Node->Prev->Next = Node->Next : Head = Node->Next;

		delete Node;
		_Size--;
	}

	void DeleteFirstNode()
	{
		if (Head == nullptr)
			return;

		clsNode* FirstNode = nullptr;
		FirstNode = Head;

		Head = Head->Next;

		if (Head != nullptr)
			Head->Prev = nullptr;

		delete FirstNode;
		_Size--;
	}

	void DeleteLastNode()
	{
		if (Head == nullptr)
			return;
		if (Head->Next == nullptr)
		{
			delete Head;
			Head = nullptr;
			_Size--;
			return;
		}

		clsNode* LastNode = Head;

		while (LastNode->Next != nullptr)
			LastNode = LastNode->Next;

		LastNode->Prev->Next = nullptr;

		delete LastNode;
		_Size--;
	}

	short Size() { return _Size; }

	bool isEmpty() { return (_Size == 0); }

	void Clear()
	{
		while (_Size != 0)
			DeleteFirstNode();
	}

	void Reverse()
	{
		clsNode* Current = Head;
		clsNode* Temp = nullptr;

		while (Current != nullptr)
		{
			Temp = Current->Prev;
			Current->Prev = Current->Next;
			Current->Next = Temp;

			Current = Current->Prev;
		}

		if (Temp != nullptr)
			Head = Temp->Prev;
	}

	clsNode* GetNode(short Index)
	{
		if (Index < 0)
			return Head;
		if (Index > _Size - 1)
			Index = _Size - 1;

		clsNode* TempHead = Head;

		while (TempHead != nullptr && Index--)
			TempHead = TempHead->Next;

		return TempHead;
	}

	T GetItem(short Index)
	{
		clsNode* Node = GetNode(Index);

		if (Node == nullptr)
			return T();

		return Node->Value;
	}

	void UpdateItem(short Index, T Value)
	{
		clsNode* Node = GetNode(Index);

		if (Node != nullptr)
			Node->Value = Value;
	}

	void InsertAfter(short Index, T Value)
	{
		clsNode* Node = GetNode(Index);

		if (Node != nullptr)
			InsertAfter(Node, Value);
	}

};
