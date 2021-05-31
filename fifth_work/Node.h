#pragma once

#ifndef _NODE_H_
#define _NODE_H_

#include "stdafx.h"


class Node
{
public:
	Node* right_node, * left_node;
	int key = 0;
	bool is_reversed = false;
	std::vector<int> keys; // elements in order they've been entered
	std::vector<int> sorted_keys;	// store tree-keys after in-order traverse
	std::vector<char> data;	
	std::vector<std::vector<char>> sorted_data;


	void two_children_nodes(Node*& root_pointer, int& amount_variable);
	void balanced_build(Node*& root_pointer, int start, int end);
	Node* node_delete(Node*& root_pointer, int key);
	Node* node_insert(Node*& root_pointer, int key, std::vector<char> vector);
	Node* node_find(Node*& root_pointer, int key);
	void get_sorted_nodes(Node* root_pointer);
	Node* reverse(Node*& root_pointer);
	void deletion(Node*& root_pointer);
	void printing(const Node* node);
	void node_info_input(std::vector<char>& vector);
private:
	void print_binary_tree(const std::string& prefix, const Node* node, bool is_left);
	Node* node_find_min(Node* root_pointer);
	Node* node_create(int key, std::vector<char> vector);
};


#endif	// _NODE_H_