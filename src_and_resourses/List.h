#ifndef LIST_H
#define LIST_H

#include <iostream>

template <class T> class List
{
private:
	template <class T> struct Node
	{
		T content;
		Node<T> *Next;
	};

	Node<T> *head;
public:
	List();
	List(T);
	~List();
	Node<T>* getHead();
	Node<T>* getLast();

	T at(int);

	void pushBack(T);

	void pushFront(T);

	void popBack();
	void popFront();

	bool isInside(T c, bool(*isEqual)(T, T));

	void print(std::ostream&);

	void input(std::istream&, std::ostream&);
};

template <class T> List<T>::List()
{
	head = nullptr;
}

template <class T> List<T>::List(T Content)
{
	head = new Node<T>;
	head->content = Content;
	head->Next = nullptr;
}

template <class T> List<T>::~List()
{
	while (head != nullptr)          //Пока по адресу не пусто
	{
		Node<T> *temp = head->Next;   //Временная переменная для хранения адреса следующего элемента
		delete head;                //Освобождаем адрес обозначающий начало
		head = temp;                //Меняем адрес на nullptr
	}
}

template <class T> List<T>::Node<T>* List<T>::getHead()
{
	return head;
}

template <class T> List<T>::Node<T>* List<T>::getLast()
{
	if (head == nullptr)
		return head;

	Node<T> *ptr = head;
	while (ptr->Next != nullptr)
		ptr = ptr->Next;
	return ptr;
}

template <class T> T List<T>::at(int k)
{
	if (k < 0)
	{
		cerr << endl << "ERROR:LIST<T> AT(k<0)!";
		assert(false);
	}
	if (head == nullptr)
	{
		cerr << endl << "ERROR:LIST<T> EMPTY AT(k)!";
		assert(false);
	}
	Node<T> *ptr = head;
	int i = 0;
	while (ptr->Next != nullptr && i != k)
	{
		ptr = ptr->Next;
		i++;
	}
	if (i == k)
		return ptr->content;
	cerr << endl << "ERROR:LIST<T> AT(k>MAX)!";
	assert(false);
}

template <class T> void List<T>::pushBack(T Content)
{
	if (head == nullptr)
	{
		head = new Node<T>;
		head->content = Content;
		head->Next = nullptr;
	}
	else
	{
		Node<T> *ptr = getLast();
		ptr->Next = new Node<T>;
		ptr->Next->content = Content;
		ptr->Next->Next = nullptr;
	}
}

template <class T> void List<T>::pushFront(T Content)
{
	if (head == nullptr)
	{
		head = new Node<T>;
		head->content = Content;
		head->Next = nullptr;
	}
	else
	{
		Node<T> *ptr = new Node<T>;
		ptr->content = Content;
		ptr->Next = head;
		head = ptr;
	}
}


template <class T> bool List<T>::isInside(T c, bool(*isEqual)(T, T))
{
	if (head == nullptr)
		return false;

	Node<T> *ptr = head;
	while (ptr->Next != nullptr && !isEqual(ptr->content, c))
		ptr = ptr->Next;
	if (isEqual(ptr->content, c))
		return true;
	else
		return false;
}

template <class T> void List<T>::popBack()
{
	if (head == nullptr)
		return;
	if (head->Next == nullptr)
	{
		delete head;
		head = nullptr;
		return;
	}

	Node<T> *ptr = head;
	while (ptr->Next->Next != nullptr)
		ptr = ptr->Next;
	delete ptr->Next;
	ptr->Next = nullptr;
}
template <class T> void List<T>::popFront()
{
	if (head == nullptr)
		return;
	
	Node<T> *ptr = head->Next;
	delete head;
	head = ptr;
}

template <class T> void List<T>::print(std::ostream& output)
{
	Node<T> *ptr = head;
	if (ptr != nullptr)
	{
		output << '{' << ptr->content;
		while (ptr->Next != nullptr)
		{
			ptr = ptr->Next;
			output << ", " << ptr->content;
		}
		output << '}';
	}
	else
		output << "{empty}";
}

template <class T> void List<T>::input(std::istream& input, std::ostream& output)
{
	output << "Введите длину списка >";
	int l;
	input >> l;
	output << "Вводите элементы по порядку:" << std::endl;
	output << "----------------------------" << std::endl;
	for (int i = 0; i < l; i++)
	{
		T temp;
		output << i + 1 << "-ый элемент >";
		input >> temp;
		pushBack(temp);
	}
}

#endif
