/*Реализуйте структуру данных “массив строк” на основе декартового дерева по неявному ключу со следующими методами: 
    // Добавление строки в позицию position.\\  
    // Все последующие строки сдвигаются на одну позицию вперед.\\  
    void InsertAt( int position, const std::string& value );\\  
    // Удаление строки из позиции position.\\  
    // Все последующие строки сдвигаются на одну позицию назад.\\  
    void DeleteAt( int position );\\  
    // Получение строки из позиции position.\\  
    std::string GetAt( int position );
Все методы должны работать за O(log n) в среднем, где n – текущее количество строк в массиве.*/



#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::pair;
using std::make_pair;
using std::move;

class StringArray
{
public:
	void Insert(long long pos, string value)
	{
		Node* help_node = new Node(value);
		pair<Node*, Node*> split_node = split(root, pos);

		Node* right_node = merge(help_node, split_node.second);
		root = merge(split_node.first, right_node);
	}

	void Delete(long long pos)
	{
		pair<Node*, Node*> split_node = split(root, pos);
		pair<Node*, Node*> help_node = split(split_node.second, 1);

		root = merge(split_node.first, help_node.second);
	}

	string Get(long long pos)
	{
		Node* current_node = root;
		long long left = Size(root->left_node);

		while (left != pos)
		{
			if (pos >= left) 
			{
				pos -= left + 1;
				current_node = current_node->right_node;
			}
			else 
			{
				current_node = current_node->left_node;
			}

			left = Size(current_node->left_node);
		}

		return current_node->value;
	}

private:
	struct Node
	{
		Node(string setValue)
		{
			value = move(setValue);
			prior = rand();
		}

		long long size_tree = 1;
		long long prior = 0;

		string value;

		Node* left_node = nullptr;
		Node* right_node = nullptr;
	};

	Node* root = nullptr;

	pair<Node*, Node*> split(Node* node, long long pos)
	{
		if (!node) 
		{
			return make_pair(nullptr, nullptr);
		}

		long long left_size = Size(node->left_node);


		if (left_size < pos)
		{
			pair<Node*, Node*> split_right = split(node->right_node, pos - left_size - 1);

			node->right_node = split_right.first;
			Update(node);

			return make_pair(node, split_right.second);
		}

		
		pair<Node*, Node*> split_size = split(node->left_node, pos);

		node->left_node = split_size.second;
		Update(node);

		return make_pair(split_size.first, node);
		
		
	}

	Node* merge(Node* left, Node* right)
	{
		if (!left)  return right;
		if (!right) return left;

		if (left->prior > right->prior)
		{
			left->right_node = merge(left->right_node, right);
			Update(left);

			return left;
		}

		
		right->left_node = merge(left, right->left_node);
		Update(right);

		return right;
		
	}

	long long Size(Node* node)
	{
		if (node)
		{
			return node->size_tree;
		}

		return 0;
	}

	void Update(Node* node)
	{
		if (node)
		{
			node->size_tree = 1 + Size(node->right_node) + Size(node->left_node);
		}
	}
};

int main() 
{
	StringArray mas;

	int k;
	cin >> k;

	string sign;
	int number;
	for (int j = 0; j < k; ++j)
	{
		cin >> sign >> number;

		if (sign[0] == '?')
		{
			cout << mas.Get(number) << endl;
		}

		else if (sign[0] == '-')
		{
			int pos;
			cin >> pos;

			for (long long i = number; i <= pos; ++i) 
			{
				mas.Delete(i);
			}
		}

		else if (sign[0] == '+')
		{
			string value;
			cin >> value;

			mas.Insert(number, value);
		}
	}
}