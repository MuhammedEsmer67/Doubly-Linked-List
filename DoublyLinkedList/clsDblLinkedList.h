#pragma once
#include <iostream>

using namespace std;

template <class T>
class clsDblLinkedList
{
protected:

	short _Size;

public:

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

		while (TempHead != NULL)
		{
			if (TempHead->Value == Value)
				return TempHead;

			TempHead = TempHead->Next;
		}

		return NULL;
	}

	void InsertEnd(T Value)
	{
		clsNode* NewNode = NULL;
		NewNode = new clsNode();

		NewNode->Value = Value;
		NewNode->Next = NULL;

		if (Head == NULL)
		{
			NewNode->Prev = NULL;
			Head = NewNode;
		}
		else
		{
			clsNode* Current = Head;

			while (Current->Next != NULL)
				Current = Current->Next;

			NewNode->Prev = Current;
			Current->Next = NewNode;
		}

		_Size++;
	}

	void InsertAfter(clsNode* Node, T Value)
	{
		clsNode* NextNode = Node->Next;

		clsNode* NewNode = new clsNode;
		NewNode->Value = Value;
		NewNode->Next = NextNode;
		NewNode->Prev = Node;

		Node->Next = NewNode;
		if (NextNode != NULL)
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

		while (TempHead != NULL && Index--)
			TempHead = TempHead->Next;

		return TempHead;
	}

	T GetItem(short Index)
	{
		clsNode* Node = GetNode(Index);

		if (Node == NULL)
			return NULL;

		return Node->Value;
	}

	void UpdateItem(short Index, T Value)
	{
		clsNode* Node = GetNode(Index);

		if (Node != NULL)
			Node->Value = Value;
	}

	void InsertAfter(short Index, T Value)
	{
		clsNode* Node = GetNode(Index);

		if (Node != NULL)
			InsertAfter(Node, Value);
	}

};
