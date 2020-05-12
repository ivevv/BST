#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <queue>
#include <algorithm>
#include <random>

using namespace std;

struct tree
{
	int data;
	int lvl;
	tree *left;
	tree *right;
};

bool check_value(tree *root, int data)
{
	bool check = false;
	if (root != NULL)
	{
		if (root->data == data)
			check = true;
		if (root->data > data)
			check = check_value(root->left, data);
		if (root->data < data)
			check = check_value(root->right, data);
	}
	return check;
}

void find_leaf(tree *root, tree *&f_leaf, int data)
{
	if (root != NULL)
	{
		if (root->data == data)
			f_leaf = root;
		else
		{
			if (root->data > data)
				find_leaf(root->left, f_leaf, data);
			if (root->data < data)
				find_leaf(root->right, f_leaf, data);
		}
	}
}

tree * find_max(tree *root)
{
	if (root->right == NULL)
		return root;
	else
		find_max(root->right);
}

void delete_leaf(tree *&leaf, int data)
{
	if (leaf != NULL)
	{
		if (leaf->data == data)
		{
			if ((leaf->left == NULL) && (leaf->right == NULL))
			{
				leaf = NULL;
				delete[]leaf;
			}
			else
			{
				if ((leaf->left != NULL) && (leaf->right != NULL))
				{
					tree *temp1;
					temp1 = find_max(leaf->left);
					leaf->data = temp1->data;
					delete_leaf(leaf->left, leaf->data);
				}
				else
				{
					if (leaf->left != NULL)
					{
						tree *temp;
						temp = leaf;
						leaf = leaf->left;
						leaf->lvl--;
						delete[] temp;
					}
					if (leaf->right != NULL)
					{
						tree *temp;
						temp = leaf;
						leaf = leaf->right;
						leaf->lvl--;
						delete[] temp;
					}
				}
			}
		}
		else
		{
			if (leaf->data > data)
				delete_leaf(leaf->left, data);
			if (leaf->data < data)
				delete_leaf(leaf->right, data);
		}
	}
}

void add_leaf(int data, int &lvl, tree *&leaf)
{
	if (leaf == NULL)
	{
		leaf = new tree;
		leaf->data = data;
		leaf->lvl = lvl;
		lvl = 0;
		leaf->left = NULL;
		leaf->right = NULL;
	}
	else
	{
		lvl++;
  		if (data < leaf->data)
			add_leaf(data, lvl, *&leaf->left);
		if (data > leaf->data)
			add_leaf(data, lvl, *&leaf->right);
	}
}

void t_insert(tree *&root, int &lvl)
{
	chrono::time_point<chrono::system_clock> start, end;
	int data;
	cout << "Enter the value of a new element:" << endl;
	cin.ignore();
	cin >> data;
	cin.clear();
	bool check;
	check = check_value(root, data);
	start = chrono::system_clock::now();
	if (check == true)
	{
		cout << "There is an element with such value in the tree already." << endl;
	}
	else
	{
		add_leaf(data, lvl, root);
		end = chrono::system_clock::now();
		int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
		cout << "Inserting a new element took " << dur << " seconds." << endl;
	}
}

void t_delete(tree *&root)
{
	chrono::time_point<chrono::system_clock> start, end;
	int data;
	cout << "Enter the value of an element you want to delete:" << endl;
	cin.ignore();
	cin >> data;
	cin.clear();
	bool check;
	check = check_value(root, data);
	start = chrono::system_clock::now();
	if (check == false)
	{
		cout << "There is no such element in the tree" << endl;
	}
	else
	{
		delete_leaf(root, data);
		end = chrono::system_clock::now();
		int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
		cout << "Deleting an element from a binary tree took " << dur << " seconds." << endl;
	}
}

void t_get(tree *root, tree *&f_leaf)
{
	chrono::time_point<chrono::system_clock> start, end;
	int value;
	cout << "Enter the value of the element you want to get from the tree:" << endl;
	start = chrono::system_clock::now();
	cin >> value;
	cin.clear();
	bool check;
	check = check_value(root, value);
	if (check == false)
	{
		cout << "There is no such element in the tree" << endl;
	}
	else
	{
		find_leaf(root, f_leaf, value);
		end = chrono::system_clock::now();
		int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
		cout << "The address of this element: " << f_leaf << endl;
		cout << "Getting a element from a binary tree took " << dur << " seconds." << endl;
	}
}

void tree_by_size(tree *&root, int &lvl)
{
	/*cout << "Please enter the size of a binary tree:" << endl;
	chrono::time_point<chrono::system_clock> start, end;
	int size;
	cin >> size;
	if (size == 0)
	{
		cout << "Invalid size! Please try again." << endl;
		tree_by_size(root, lvl);
	}
	else
	{
		srand(time(NULL));
		start = chrono::system_clock::now();
		int data, temp;
		int *pool, *id;
		pool = (int*)malloc(size * sizeof(int));
		id = (int*)malloc(size * sizeof(int));
		pool[0] = rand();
		id[0] = 0;
		for (int i = 1; i < size; i++)
		{
			pool[i] = pool[i - 1] + 1;
			id[i] = i;
		}
		random_shuffle(id[0], id[size - 1]);
		for (int i = 0; i < size; i++)
		{
			temp = rand() % 3;
			data = pool[id[i]]%100;
			for (int j = 0; j < temp; j++)
				data = data * (-1);
			add_leaf(data, lvl, root);
		}
		free(pool);
		free(id);
		end = chrono::system_clock::now();
		int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
		cout << "Creating your binary tree of " << size << " elements took " << dur << " seconds." << endl;
		
	}
	*/
}

void tree_from_file(tree *&root, int &lvl)
{
	cout << "Enter the elements (integers) of your binary tree in user_tree.txt. Use arabic numerals." << endl;
	cout << "Note: values of binary tree elements can't repeat." << endl;
	cout << "To start the reading of the binary tree type in any number and press enter." << endl;
	int start;
	cin >> start;
	cin.clear();
	ifstream dataf("user_tree.txt");
	if (!dataf.is_open())
	{
		cout << "Error! Can't access the file!" << endl;
	}
	else
	{
		chrono::time_point<chrono::system_clock> start, end;
		start = chrono::system_clock::now();
		int size = 0;
		int data;
		while (!dataf.eof())
		{
			dataf >> data;
			add_leaf(data, lvl, root);
			size++;
		}
		dataf.close();
		if ((size - 1) == 0)
		{
			cout << "The file is empty! Please try again." << endl;
			dataf.close();
			tree_from_file(root, lvl);
		}
		else
		{
			end = chrono::system_clock::now();
			int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
			cout << "Creating your binary tree of " << size << " elements took " << dur << " seconds." << endl;
		}
	}
}

void tree_by_elements(tree *&root, int &lvl)
{
	int size = 0;
	cout << "Please enter the elements (integers) of your binary tree, each of new line:" << endl;
	cout << "Note: values of binary tree elements can't repeat." << endl;
	cout << "To finish the input enter 0." << endl;
	chrono::time_point<chrono::system_clock> start, end;
	int value = 1;
	start = chrono::system_clock::now();
	while (value != 0)
	{
		cin >> value;
		cin.clear();
		if (value == 0)
			break;
		add_leaf(value, lvl, root);
		size++;
	}
	end = chrono::system_clock::now();
	int dur = chrono::duration_cast<chrono::seconds>(end - start).count();
	cout << "Creating your binary tree of " << size << " elements took " << dur << " seconds." << endl;
}

void nlr_traversal(tree *root)
{
	if (root != NULL)
	{
		cout << root->data << " ";
		nlr_traversal(root->left);
		nlr_traversal(root->right);
	}
}

void lrn_traversal(tree *root)
{
	if (root != NULL)
	{
		lrn_traversal(root->left);
		lrn_traversal(root->right);
		cout << root->data << " ";
	}
}

void bfs_traversal(tree *root)
{
	if (root != NULL)
	{
		queue<tree*> bfs;
		bfs.push(root);
		while (!bfs.empty())
		{
			tree *current;
			current = bfs.front();
			bfs.pop();
			cout << current->lvl << "\t" << current->data << endl;
			if (current->left != NULL)
				bfs.push(current->left);
			if (current->right != NULL)
				bfs.push(current->right);
		}
	}
}

void bfs_traversal_to_file(tree *root)
{
	ofstream dataf("tree.txt");
	if (!dataf.is_open())
	{
		cout << "Error! Can't access the file!" << endl;
	}
	else
	{
		dataf << "level:" << '\t' << "data:" << endl;
		if (root != NULL)
		{
			queue<tree*> bfs;
			bfs.push(root);
			while (!bfs.empty())
			{
				tree *current;
				current = bfs.front();
				bfs.pop();
				dataf << current->lvl << "\t" << current->data << endl;
				if (current->left != NULL)
					bfs.push(current->left);
				if (current->right != NULL)
					bfs.push(current->right);
			}
		}
	}
}


void t_ind_task(tree *&root, int x, int y)
{
	if (root != NULL)
	{
		if ((root->data / 2) == 0)
			root->data = root->data*y;
		else
			root->data = root->data - x;
		t_ind_task(root->left, x, y);
		t_ind_task(root->right, x, y);
	}
}

void delete_tree(tree*&root)
{
	if (root != NULL)
	{
		delete_tree(root->left);
		delete_tree(root->right);
		delete[]root;
	}
}
