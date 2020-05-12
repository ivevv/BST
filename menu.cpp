#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <queue>
#include <algorithm>

using namespace std;

struct tree;
int lvl = 0;
tree *root = NULL;
tree *f_leaf = NULL;

struct list;
list *head = NULL;
list *node = NULL;
int l_size, l_check = 0, t_check = 0;

bool check_value(tree *root, int data);
void find_leaf(tree *root, tree *&f_leaf, int data);
tree * find_max(tree *root);
void delete_leaf(tree *&leaf, int data);
void add_leaf(int data, int &lvl, tree *&leaf);
void t_insert(tree *&root, int &lvl);
void t_delete(tree *&root);
void t_get(tree *root, tree *&f_leaf);
void tree_by_size(tree *&root, int &lvl);
void tree_from_file(tree *&root, int &lvl);
void tree_by_elements(tree *&root, int &lvl);
void nlr_traversal(tree *root);
void lrn_traversal(tree *root);
void bfs_traversal(tree *root);
void bfs_traversal_to_file(tree *root);
void t_ind_task(tree *&root, int x, int y);
void delete_tree(tree*&root);

list * create_list(int data);
void add_node(int data, list *head);
void add_node(int data, list *head);
void l_insert(list *&head, int &size);
void l_del_by_id(list *&head, int &size, int id);
void l_del_by_value(list *&head, int &size);
void l_get_by_id(list *&head, list *&element, int &size, int id);
void l_get_by_value(list *&head, list *&element, int &size);
void list_by_size(list *&head, int &size);
void list_from_file(list *&head, int &size);
void list_by_elements(list *&head, int &size);
void delete_list(list *&head, int &size);
void l_get(list *&head, int size, list *&element);
void l_ind_task(list *&head, int size, int x, int y);

void menu(int &l_check, int &t_check);

void create_d_list(int &l_check)
{
	cout << "Create a doubly linked list:" << endl << "1. by size;";
	cout << endl << "2. by elements;" << endl << "3. from file?" << endl;
	int start;
	cin >> start;
	switch (start)
	{
	case 1:
	{
		list_by_size(head, l_size);
		l_check++;
		menu(l_check, t_check);
	}
	break;
	case 2:
	{
		list_by_elements(head, l_size);
		l_check++;
		menu(l_check, t_check);
	}
	break;
	case 3:
	{
		list_from_file(head, l_size);
		l_check++;
		menu(l_check, t_check);
	}
	break;
	default:
	{
		cout << "Invalid input! Please try again." << endl;
		create_d_list(l_check);
	}
	break;
	}
}

void create_tree(int &t_check)
{
	cout << "Create a binary search tree:" << endl << "1. by size;";
	cout << endl << "2. by elements;" << endl << "3. from file?" << endl;
	int start;
	cin >> start;
	switch (start)
	{
	case 1:
	{
		tree_by_size(root, lvl);
		t_check++;
		menu(l_check, t_check);
	}
	break;
	case 2:
	{
		tree_by_elements(root, lvl);
		t_check++;
		menu(l_check, t_check);
	}
	break;
	case 3:
	{
		tree_from_file(root, lvl);
		t_check++;
		menu(l_check, t_check);
	}
	break;
	default:
	{
		cout << "Invalid input! Please try again." << endl;
		create_tree(t_check);
	}
	break;
	}
}

void tree_output()
{
	cout << "Output a tree:" << endl << "1. to console;";
	cout << endl << "2. to file?" << endl;
	int start;
	cin >> start;
	switch (start)
	{
	case 1:
	{
		cout << "level:" << '\t' << "data:" << endl;
		bfs_traversal(root);
		menu(l_check, t_check);
	}
	break;
	case 2:
	{
		bfs_traversal_to_file(root);
		cout << "Output to tree.txt is finished." << endl;
		menu(l_check, t_check);
	}
	break;
	default:
	{
		cout << "Invalid input! Please try again." << endl;
		tree_output();
	}
	break;
	}
}


void menu(int &l_check, int &t_check)
{
	cout << "Please choose your option." << endl;
	cout << "Binary search tree:" << endl << "1. Create a new tree;" << endl << "2. Output a tree;" << endl;
	cout << "3. Insert a new element;" << endl;
	cout << "4. Delete an element;" << endl << "5. Get an element;" << endl;
	cout << "6. Pre-order traversal;" << endl << "7. Post-order traversal;" << endl;
	cout << "8. Data manupulation." << endl;
	cout << "Doubly linked list:" << endl << "9. Create a new list;" << endl << "10. Insert a new node;" << endl;
	cout << "11. Delete a node;" << endl;
	cout << "12. Get a node;" << endl << "13. Data manipulation." << endl;
	int start0;
	cin >> start0;
	cin.clear();
	switch (start0)
	{
	case 1:
	{
		if (t_check > 0)
		{
			cout << "Note: creating a new binary search tree will delete the previous one." << endl;
			delete_tree(root);
		}
		create_tree(t_check);
	}
	break;
	case 2:
	{
		if (t_check == 0)
		{
			cout << "You need to create a tree first." << endl;
			create_tree(t_check);
		}
		else
		{
			tree_output();
			menu(l_check, t_check);
		}
	}
	break;
	case 3:
	{
		if (t_check == 0)
		{
			cout << "You need to create a tree first." << endl;
			create_tree(t_check);
		}
		else
		{
			t_insert(root, lvl);
			menu(l_check, t_check);
		}
	}
	break;
	case 4:
	{
		if (t_check == 0)
		{
			cout << "You need to create a tree first." << endl;
			create_tree(t_check);
		}
		else
		{
			t_delete(root);
			menu(l_check, t_check);
		}
	}
	break;
	case 5:
	{
		if (t_check == 0)
		{
			cout << "You need to create a tree first." << endl;
			create_tree(t_check);
		}
		else
		{
			t_get(root,f_leaf);
			menu(l_check, t_check);
		}
	}
	break;
	case 6:
	{
		if (t_check == 0)
		{
			cout << "You need to create a tree first." << endl;
			create_tree(t_check);
		}
		else
		{
			nlr_traversal(root);
			cout << endl;
			menu(l_check, t_check);
		}
	}
	break;
	case 7:
	{
		if (t_check == 0)
		{
			cout << "You need to create a tree first." << endl;
			create_tree(t_check);
		}
		else
		{
			lrn_traversal(root);
			cout << endl;
			menu(l_check, t_check);
		}
	}
	break;
	case 8:
	{
		if (t_check == 0)
		{
			cout << "You need to create a tree first." << endl;
			create_tree(t_check);
		}
		else
		{
			srand(time(NULL));
			chrono::time_point<chrono::system_clock> start, end;
			cout << "Please enter an integer which will be substracted from odd elements of the tree:" << endl;
			start = chrono::system_clock::now();
			int x, y;
			cin >> x;
			cin.clear();
			y = rand() % 6;
			t_ind_task(root, x, y);
			end = chrono::system_clock::now();
			int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
			cout << "Updating a binary tree took " << dur << " seconds." << endl;
		}
	}
	break;
	case 9:
	{
		if (l_check > 0)
		{
			cout << "Note: creating a new doubly linked list will delete the previous one." << endl;
			delete_list(head, l_size);
		}
		create_d_list(l_check);
	}
	break;
	case 10:
	{
		if (l_check == 0)
		{
			cout << "You need to create a list first." << endl;
			create_d_list(l_check);
		}
		else
		{
			l_insert(head, l_size);
			menu(l_check, t_check);
		}
		
	}
	break;
	case 11:
	{
		if (l_check == 0)
		{
			cout << "You need to create a list first." << endl;
			create_d_list(l_check);
		}
		else
		{
			l_del_by_value(head, l_size);
			menu(l_check, t_check);
		}
	}
	break;
	case 12:
	{
		if (l_check == 0)
		{
			cout << "You need to create a list first." << endl;
			create_d_list(l_check);
		}
		else
		{
			l_get_by_value(head, node, l_size);
			menu(l_check, t_check);
		}
	}
	break;
	case 13:
	{
		if (l_check == 0)
		{
			cout << "You need to create a list first." << endl;
			create_d_list(l_check);
		}
		else
		{
			srand(time(NULL));
			chrono::time_point<chrono::system_clock> start, end;
			cout << "Please enter an integer which will be substracted from odd elements of the list:" << endl;
			start = chrono::system_clock::now();
			int x, y;
			cin >> x;
			cin.clear();
			y = rand() % 6;
			l_ind_task(head, l_size, x, y);
			end = chrono::system_clock::now();
			int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
			cout << endl << "Updating a doubly linked list took " << dur << " seconds." << endl;
			menu(l_check, t_check);
		}
	}
	break;
	default:
	{
		cout << "Invalid input! Please try again." << endl;
		menu(l_check, t_check);
	}
	break;
	}
}

int main()
{
	menu(l_check, t_check);
	return 0;
}
