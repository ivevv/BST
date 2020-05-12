#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>

using namespace std;

struct list
{
	int data;
	list *next;
	list *prev;
};

list * create_list(int data)
{
	list *head = new list;
	head->data = data;
	head->next = NULL;
	head->prev = NULL;
	return head;
}

void add_node(int data, list *head)
{
	list *node = new list;
	node->data = data;
	node->next = NULL;
	list *temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = node;
	node->prev = temp;
}

void delete_list(list *&head, int &size)
{
	list *temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	list *current;
	for (int i = (size - 1); i <= 0; i++)
	{
		current = temp;
		temp = temp->prev;
		delete[]current;
	}
}

void l_insert(list *&head, int &size)
{
	chrono::time_point<chrono::system_clock> start, end;
	int id, data;
	cout << "Enter the index (from 0 to " << size << ") of a new node:" << endl;
	cin >> id;
	cin.clear();
	if (id > size)
	{
		cout << "Invalid index! Please try again." << endl;
		l_insert(head, size);
	}
	else 
	{
		if (id == size)
		{
			cout << "Enter the value of a new node:" << endl;
			cin.ignore();
			cin >> data;
			cin.clear();
			start = chrono::system_clock::now();
			add_node(data, head);
			end = chrono::system_clock::now();
			int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
			cout << "The doubly linked list was updated:" << endl;
			list *temp = head;
			size++;
			for (int i = 0; i < size; i++)
			{
				cout << temp->data << " ";
				temp = temp->next;
			}
			cout << endl << "Inserting a new node took " << dur << " seconds." << endl;
		}
		else
		{
			cout << "Enter the value of a new node:" << endl;
			cin >> data;
			cin.clear();
			start = chrono::system_clock::now();
			if (id != 0)
			{
				list *node = new list;
				node->data = data;
				list *temp_p = head, *temp_n = head;
				for (int i = 0; i < (id - 1); i++)
					temp_p = temp_p->next;
				for (int i = 0; i < id; i++)
					temp_n = temp_n->next;
				node->prev = temp_p;
				node->next = temp_n;
				temp_p->next = node;
				temp_n->prev = node;
				end = chrono::system_clock::now();
				int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
				cout << endl << "The doubly linked list was updated:" << endl;
				list *temp = head;
				size++;
				for (int i = 0; i < size; i++)
				{
					cout << temp->data << " ";
					temp = temp->next;
				}
				cout << endl << "Inserting a new node took " << dur << " seconds." << endl;
			}
			else
			{
				list *node = new list;
				node->data = head->data;
				node->next = head->next;
				node->prev = head;
				head->data = data;
				head->next = node;
				end = chrono::system_clock::now();
				int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
				cout << "The linked list was updated:" << endl;
				list *temp = head;
				size++;
				for (int i = 0; i < size; i++)
				{
					cout << temp->data << " ";
					temp = temp->next;
				}
				cout << endl << "Inserting a new node took " << dur << " seconds." << endl;
			}
		}
	}
}

void l_del_by_id(list *&head, int &size, int id)
{
	if (id == (size-1))
	{ 
		list *n_tail = head, *tail = head;
		for (int i = 0; i < id; i++)
			n_tail = n_tail->next;
		for (int i = 0; i < size; i++)
			tail = tail->next;
		n_tail->next = NULL;
		delete[]tail;
		cout << "The doubly linked list was updated:" << endl;
		list *temp = head;
		size--;
		for (int i = 0; i < size; i++)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
	}
	else
	{
		if (id != 0)
		{
			list *temp_c = head, *temp_p, *temp_n;
			for (int i = 0; i < id; i++)
				temp_c = temp_c->next;
			temp_p = temp_c->prev;
			temp_n = temp_c->next;
			temp_n->prev = temp_p;
			temp_p->next = temp_n;
			delete[]temp_c;
			cout << "The doubly linked list was updated:" << endl;
			list *temp = head;
			size--;
			for (int i = 0; i < size; i++)
			{
				cout << temp->data << " ";
				temp = temp->next;
			}
		}
		else
		{
			list*n_head = head;
			n_head = n_head->next;
			n_head->prev = NULL;
			delete[] head;
			cout << "The doubly linked list was updated:" << endl;
			size--;
			head = n_head;
			list *temp = head;
			for (int i = 0; i < size; i++)
			{
				cout << temp->data << " ";
				temp = temp->next;
			}
		}
	}

}

void l_del_by_value(list *&head, int &size)
{
	chrono::time_point<chrono::system_clock> start, end;
	cout << "Enter the value of the node you want to delete:" << endl;
	cout << "Note: if there is more than one node with such value only the last one will be deleted." << endl;
	int value;
	cin >> value;
	cin.clear();
	start = chrono::system_clock::now();
	int count = 0, id;
	list *temp = head;
	for (int i = 0; i < size; i++)
	{
		if (temp->data == value)
		{
			count++;
			id = i;
		}
		temp = temp->next;
	}
	if (count == 0)
	{
		cout << "There is no such node! Please try again." << endl;
		l_del_by_value(head, size);
	}
	else
	{
		l_del_by_id(head, size, id);
		end = chrono::system_clock::now();
		int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
		cout << endl << "Deleting a node from a doubly linked list took " << dur << " seconds." << endl;
	}
}

void l_get_by_id(list *&head, list *&element, int &size, int id)
{
	list *temp = head;
	for (int i = 0; i < id; i++)
		temp = temp->next;
	element = temp;
	element->data = temp->data;
}

void l_get(list *&head, int size, list *&element)
{
	int id;
	cout << "Enter the index (from 0 to " << (size - 1) << ") of the node you want to get:" << endl;
	cin >> id;
	cin.clear();
	if (id > (size - 1))
	{
		cout << "Invalid index! Please try again." << endl;
		l_get(head, size, element);
	}
	else
	{
		chrono::time_point<chrono::system_clock> start, end;
		start = chrono::system_clock::now();
		l_get_by_id(head, element, size, id);
		end = chrono::system_clock::now();
		int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
		cout << "The address of this node: " << element;
		cout << endl << "The value of this node: " << (*element).data;
		cout << endl << "Getting a node from a doubly linked list took " << dur << " seconds." << endl;
	}
}

void l_get_by_value(list *&head, list *&element, int &size)
{
	chrono::time_point<chrono::system_clock> start, end;
	int id, value, count = 0;
	cout << "Enter the value of the element you want to get from the list:" << endl;
	cout << "Note: if there is more than one node with such value only the last one will be gotten." << endl;
	start = chrono::system_clock::now();
	cin >> value;
	cin.clear();
	list *temp = head;
	for (int i = 0; i < size; i++)
	{
		if (temp->data == value)
		{
			count++;
			id = i;
		}
		temp = temp->next;
	}
	if (count == 0)
	{
		cout << "There is no such node in the list! Please try again." << endl;
		l_get_by_value(head, element, size);
	}
	else
	{
		l_get_by_id(head, element, size, id);
	}
	end = chrono::system_clock::now();
	int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
	cout << "The address of this node: " << element;
	cout << endl << "The value of this node: " << (*element).data << endl;
	cout << "Getting a node from a doubly linked list took " << dur << " seconds." << endl;
}

void list_by_size(list *&head, int &size)
{
	cout << "Please enter the size of a doubly linked list:" << endl;
	chrono::time_point<chrono::system_clock> start, end;
	cin >> size;
	if (size == 0)
	{
		cout << "Invalid size! Please try again." << endl;
		list_by_size(head, size);
	}
	else
	{
		srand(time(NULL));
		start = chrono::system_clock::now();
		int data;
		data = rand() % 100;
		head = create_list(data);
		for (int i = 1; i < size; i++)
		{
			data = rand() % 100;
			add_node(data, head);
		}
		end = chrono::system_clock::now();
		int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
		cout << "Your doubly linked list of " << size << " randomised elements:" << endl;
		list *temp = head;
		for (int i = 0; i < size; i++)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl << "Creating your doubly linked list took " << dur << " seconds." << endl;
	}
}

void list_from_file(list *&head, int &size)
{
	cout << "Enter your list of integers in list.txt. Use arabic numerals." << endl;
	cout << "To start the reading of the list type in any number and press enter." << endl;
	int start;
	cin >> start;
	cin.clear();
	ifstream dataf("list.txt");
	if (!dataf.is_open())
	{
		cout << "Error! Can't access the file!" << endl;
	}
	else
	{
		chrono::time_point<chrono::system_clock> start, end;
		start = chrono::system_clock::now();
		size = 1;
		int data;
		dataf >> data;
		head = create_list(data);
		while (!dataf.eof())
		{
			dataf >> data;
			add_node(data, head);
			size++;
		}
		dataf.close();
		if ((size-1) == 0)
		{
			cout << "The file is empty! Please try again." << endl;
			dataf.close();
			list_from_file(head,size);
		}
		else
		{
			end = chrono::system_clock::now();
			int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
			cout << "Your doubly linked list:" << endl;
			list *temp = head;
			for (int i = 0; i < size; i++)
			{
				cout << temp->data << " ";
				temp = temp->next;
			}
			cout << endl << "Reading your doubly linked list took " << dur << " seconds." << endl;
		}
	}
}

void list_by_elements(list *&head, int &size)
{
	cout << "Please enter your list of integers, each of new line:" << endl;
	cout << "To finish the input enter 0." << endl;
	chrono::time_point<chrono::system_clock> start, end;
	int value;
	size = 1;
	cin >> value;
	cin.clear();
	head = create_list(value);
	start = chrono::system_clock::now();
	while (value != 0)
	{
		cin >> value;
		cin.clear();
		if (value == 0)
			break;
		add_node(value, head);
		size++;
	}
	end = chrono::system_clock::now();
	int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
	cout << "Your doubly linked list of " << size << " elements:" << endl;
	list *temp = head;
	for (int i = 0; i < size; i++)
	{
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl << "Creating your doubly linked list took " << dur << " seconds." << endl;
}

void l_ind_task(list *&head, int size, int x, int y)
{
	cout << "The linked list was updated:" << endl;
	list *temp = head;
	for (int i = 0; i < size; i++)
	{
		if ((temp->data / 2) == 0)
			temp->data = temp->data*y;
		else
			temp->data = temp->data - x;
		cout << temp->data << " ";
		temp = temp->next;
	}
}
