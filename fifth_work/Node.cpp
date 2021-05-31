#include "stdafx.h"


void Node::print_binary_tree(const std::string& prefix, const Node* node, bool is_right)
{
	if (node != nullptr)
	{
		std::cout << prefix << "|\n" << prefix << "|___";
		std::cout << node->key << std::endl;

		// enter the next tree level - left and right branch
		print_binary_tree(prefix + (is_right ? "|   " : "    "), node->right_node, true);
		print_binary_tree(prefix + (is_right ? "|   " : "    "), node->left_node, false);
	}
}


Node* Node::node_insert(Node*& root_pointer, int key, std::vector<char> vector)
{
	if (root_pointer == nullptr) {
		root_pointer = node_create(key, vector);
		return root_pointer;
	} else if (key < root_pointer->key) {
		root_pointer->left_node = node_insert(root_pointer->left_node, key, vector);
	} else {
		root_pointer->right_node = node_insert(root_pointer->right_node, key, vector);
	}
	return root_pointer;
}


void Node::two_children_nodes(Node*& root_pointer, int& amount_variable)
{
	if (root_pointer == nullptr)
		return;

	two_children_nodes(root_pointer->left_node, amount_variable);

	if (root_pointer->left_node != nullptr && root_pointer->right_node != nullptr)
		amount_variable++;

	two_children_nodes(root_pointer->right_node, amount_variable);
}


void Node::balanced_build(Node*& root_pointer, int start, int end)
{
	if (start > end) 
		return;

	int mid = (start + end) / 2;
	node_insert(root_pointer, sorted_keys[mid], sorted_data[mid]);
	balanced_build(root_pointer, start, mid - 1);
	balanced_build(root_pointer, mid + 1, end);
}


Node* Node::node_delete(Node*& root_pointer, int key)
{
	if (root_pointer == nullptr) {
		return nullptr;
	} else if (key > root_pointer->key) {
		root_pointer->right_node = node_delete(root_pointer->right_node, key);
	} else if (key < root_pointer->key) {
		root_pointer->left_node = node_delete(root_pointer->left_node, key);
	} else {	// Consider tree cases
		if (root_pointer->right_node == nullptr && root_pointer->left_node == nullptr) {	// 1. Node is a leaf
			delete root_pointer;
			root_pointer = nullptr;
			return nullptr;
		} else if (root_pointer->right_node == nullptr) {	// 2. Node has one child
			Node* temp_node = root_pointer->left_node;
			delete root_pointer;
			root_pointer = temp_node;
			return root_pointer;
		} else if (root_pointer->left_node == nullptr) {
			Node* temp_node = root_pointer->right_node;
			delete root_pointer;
			root_pointer = temp_node;
			return root_pointer;
		} else {	// 3. Node has two children
			Node* temp_node = node_find_min(root_pointer->right_node);
			root_pointer->key = temp_node->key;
			root_pointer->right_node = node_delete(root_pointer->right_node, temp_node->key);
		}
	}
	return root_pointer;	// saw in guide, imho its unreachable, but in other case function does not cotrol all of the return pathes
}


Node* Node::node_find(Node*& root_pointer, int key)
{
	// I finally found a bug! If i reverse a tree
	// and trying to found an element, find algorithm will
	// go to the left if an element less then root and 
	// go to the right if an element greater than root.
	// BUT TREE IS REVERSED, AND ALGORITHM REMAIN THE SAME
	// Algorithm cannot find small element for example in right part
	// There are two solution i came up with.
	// Create a flag that shows if tree is reverse or not,
	// or check left and right node of the root, and choose
	// between two algorithms.

	if (!is_reversed) {
		if (root_pointer->key == key || root_pointer == nullptr) {
			return root_pointer;	// return root 'cause it may not to be a null
		} else if (key < root_pointer->key) {
			return node_find(root_pointer->left_node, key);
		} else {
			return node_find(root_pointer->right_node, key);
		}
	} else {
		if (root_pointer->key == key || root_pointer == nullptr) {
			return root_pointer;
		} else if (key > root_pointer->key) {
			return node_find(root_pointer->left_node, key);
		} else {
			return node_find(root_pointer->right_node, key);
		}
	}
}


void Node::get_sorted_nodes(Node* root_pointer)
{
	if (root_pointer == nullptr) return;
	get_sorted_nodes(root_pointer->left_node);
	sorted_keys.push_back(root_pointer->key);
	sorted_data.push_back(root_pointer->data);
	get_sorted_nodes(root_pointer->right_node);
}


Node* Node::node_find_min(Node* root_pointer)
{
	while (root_pointer->left_node != nullptr)
		root_pointer = root_pointer->left_node;
	return root_pointer;
}


void Node::deletion(Node*& root_pointer)
{
	if (root_pointer == nullptr) return;
	deletion(root_pointer->left_node);
	deletion(root_pointer->right_node);
	delete root_pointer;
	root_pointer = nullptr;
}


Node* Node::reverse(Node*& root_pointer)
{
	if (root_pointer == nullptr) {
		return root_pointer;
	} else {
		reverse(root_pointer->left_node);
		reverse(root_pointer->right_node);

		Node* temp_node = root_pointer->right_node;
		root_pointer->right_node = root_pointer->left_node;
		root_pointer->left_node = temp_node;
	}
	return root_pointer;
}


Node* Node::node_create(int key, std::vector<char> vector)
{
	Node* new_node = new Node;
	new_node->key = key;

	for (size_t i = 0; i < vector.size(); i++) {
		new_node->data.push_back(vector[i]);
	}

	new_node->left_node = nullptr;
		new_node->right_node = nullptr;
	return new_node;
}


void Node::printing(const Node* node)
{
	print_binary_tree("", node, false);
}


void Node::node_info_input(std::vector<char>& vector)
{
	int length = 0;
	while (true) {
		char c = _getch();

		if (c >= 65 && c <= 90 || c >= 97 && c <= 122 || c == 32) {		//	Allow to enter only letters and space 
			vector.push_back(c);
			std::cout << (char)c;
			length++;
		}
		else if (c == '\b' && length > 0) {	// Backspace
			vector.pop_back();
			std::cout << "\b \b";
			length--;
		}
		else if (c == 13 && length != 0) {		// Enter breaks down the loop
			break;
		}
	}
}