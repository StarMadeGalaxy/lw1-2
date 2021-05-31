#include "stdafx.h"
 

int main()
{
	Node tree;
	Node* tree_pointer = nullptr;
 

	while (true) {
		ClearScreen();

		std::cout << "Binary search tree\n\n"
			<< "1. Insert nodes\n"
			<< "2. Delete nodes\n"
			<< "3. Inverse tree\n"
			<< "4. Balance tree\n"
			<< "5. View tree\n"
			<< "6. Individual task\n"
			<< "7. Find information by key\n"
			<< "0, ELSE. Exit.\n\n"
			<< "Type here: ";


		switch (_getch() - 48) {
		case 1:		// Insertion
		{
			ClearScreen();

			std::cout << "How many nodes you would like to insert ?\n\n"
				<< "Type here: ";

			int key(0);	// it must be initialized here, because we use it outside the loop
			int nodes_amount = static_cast<int>(number_input(TEST_LIMIT));
			int pizza = 1;	// i want a pizza

			for (int i = 0; i < nodes_amount; i++)
			{
				ClearScreen();
				tree.printing(tree_pointer);

				while (true) {
					bool break_loop = true;
					std::cout << "\nEnter a number: ";
					key = static_cast<int>(number_input(TEST_LIMIT));

					for (size_t i = 0; i < tree.keys.size(); i++) {
						if (tree.keys[i] == key) {
							ClearScreen();
							tree.printing(tree_pointer);
							std::cout << "\nElement '" << key << "' is already in tree.\n";
							break_loop = false;
							break;
						}
					} if (break_loop) {
						ClearScreen();
						std::cout << "\nEnter the data for the node with key '" 
							<< key << "'" << "\n\nType here: ";
						std::vector<char>node_info;
						tree.node_info_input(node_info);	// store information to the vector
						tree.node_insert(tree_pointer, key, node_info);
						node_info.clear();	
						tree.keys.push_back(key);
						tree.printing(tree_pointer);
						break;
					}
				}
			}
			ClearScreen();
			tree.printing(tree_pointer);
			std::cout << "\n\nInsertion is complete.\n\nPress any to button to continue...";
			_getch();
			break;
		}
		case 2:		// Deletion
		{
			ClearScreen();

			if (tree_pointer == nullptr) {
				std::cout << "Tree is empty.\n"
					<< "\n\nPress any to button to continue...";
				_getch();
				break;
			}

			ClearScreen();

			tree.printing(tree_pointer);
			std::cout << "\nWhat you would like to delete ?\n\n"
				<< "1. The whole tree\n"
				<< "2. Some nodes from tree\n"
				<< "0, ELSE. Back\n\n"
				<< "Type here: ";


			switch (_getch() - 48)
			{
			case 1:		// Delete the whole tree
			{
				ClearScreen();

				if (tree_pointer == nullptr) {
					std::cout << "Tree is empty.\n"
						<< "\n\nPress any to button to continue...";
					_getch();
					break;
				}

				tree.deletion(tree_pointer);
				tree.keys.clear();
				std::cout << "\nNow tree is empty"
						<< "\n\nPress any to button to continue...";
				_getch();
				break;
			}
			case 2:		// Delete some nodes
			{
				ClearScreen();

				tree.printing(tree_pointer);
				std::cout << "\nHow many nodes you would to delete ?\n\n"
					<< "Type here: ";

				int nodes_amount(0);

				while (true) {
					ClearScreen();

					tree.printing(tree_pointer);
					std::cout << "\nHow many node you would to delete ?\n\nType here: ";
					nodes_amount = static_cast<int>(number_input(TEST_LIMIT));

					if (nodes_amount > static_cast<int>(tree.keys.size())) {
						ClearScreen();
						std::cout << "Number of elements is too high.\n\nPress any to button to continue...";
						_getch();
					} else if (nodes_amount < 0) {
						ClearScreen();
						std::cout << "Number of elements is too low.\n\nPress any to button to continue...";
						_getch();
					} else {
						break;
					}
				}

				for (int i = 0; i < nodes_amount; i++)
				{
					bool print_warning = false;
					while (true) {
						ClearScreen();
						tree.printing(tree_pointer);

						if (print_warning)
							std::cout << "\nThere is no element like that. Try again.\n";

						std::cout << "\nEnter a number: ";
						int number = static_cast<int>(number_input(TEST_LIMIT));

						std::vector<int>::iterator iterator = std::find(tree.keys.begin(), tree.keys.end(), number);

						// If the iterator reach the last index + 1 => there is no element
						if (iterator != tree.keys.end()) {
							ClearScreen();

							/*We cannot delete an element from vector directrly, but we can use remove/erase idiom.
							What happens is that std::remove compacts the elements that differ from the value to be 
							removed at the end of the vector and returns the iterator to the first element 
							AFTER that range, which is underlined below. Container's size remains the same as before.
							Then erase removes these elements (whose value is unspecified).
							For example we have:
							vector<int> v = {1, 2, 3, 1, 2, 3, 1, 2, 3}; 
							Then we call remove from <algorithm>:
							std::remove(v.begin(), v.end(), 2); // remove all 2 from a container
							we get:
							1, 3, 1, 3, 1, 3, ?, ?, ?, where ? is some kind of rubbish
							and  call v.erase to delete these ???. That's called remove/erase idiom in c++.
							*/

							tree.keys.erase(std::remove(tree.keys.begin(), tree.keys.end(), number), tree.keys.end());
							tree.node_delete(tree_pointer, number);
							tree.printing(tree_pointer);
							print_warning = false;
							break;
						} else {
							print_warning = true;
						}
					}
				}

				std::cout << "\n\nDeletion is complete.\n\nPress any to button to continue...";
				_getch();
				break;
			}
			default:
			{
				break;
			}
			}
			break;
		}
		case 3:		// Reverse tree
		{
			ClearScreen();

			if (tree_pointer == nullptr) {
				std::cout << "Tree is empty.\n"
					<< "\n\nPress any to button to continue...";
				_getch();
				break;
			}

			std::cout << "Not reversed:\n\n";
			tree.printing(tree_pointer);
			std::cout << "\nReversed:\n\n";
			tree.reverse(tree_pointer);

			if (tree.is_reversed == false) tree.is_reversed = true;
			else tree.is_reversed = false;

			tree.printing(tree_pointer);

			std::cout << "\n\nPress any to button to continue...";
			_getch();
			break;
		}
		case 4:		// Balance tree
		{
			ClearScreen();

			if (tree_pointer == nullptr) {
				std::cout << "Tree is empty.\n"
					<< "\n\nPress any to button to continue...";
				_getch();
				break;
			}

			std::cout << "Not balanced:\n\n";
			tree.printing(tree_pointer);
			// Do an in-order traverse to get sorted elements
			tree.get_sorted_nodes(tree_pointer);
			// Delete previous tree
			tree.deletion(tree_pointer);
			std::cout << "\nBalanced:\n\n";

			tree.balanced_build(tree_pointer, 0, tree.sorted_keys.size() - 1);	// 0 - Index of the vector beginning
			tree.printing(tree_pointer);
			// Then clear sorted keys and data
			tree.sorted_keys.clear();
			tree.sorted_data.clear();

			std::cout << "\n\nTree's balanced.\n\nPress any to button to continue...";
			_getch();
			break;
		}
		case 5:		// Print tree
		{
			ClearScreen();

			if (tree_pointer == nullptr)
				std::cout << "Tree is empty.\n";
			else
				tree.printing(tree_pointer);

			std::cout << "\n\nPress any to button to continue...";
			_getch();
			break;
		}
		case 6:	// indidual task
		{
			ClearScreen();

			if (tree_pointer == nullptr) {
				std::cout << "Tree is empty.\n"
					<< "\n\nPress any to button to continue...";
				_getch();
				break;
			}

			int two_children_nodes_amount = 0;
			tree.two_children_nodes(tree_pointer, two_children_nodes_amount);

			tree.printing(tree_pointer);
			std::cout << "\n\nIndividual task is: "
				<< "\n\n'Find amount of nodes with two children'\n"
				<< "\nAmount is equal to " << two_children_nodes_amount;

			std::cout << "\n\nPress any to button to continue...";
			_getch();
			break;
		}
		case 7:
		{
			ClearScreen();

			if (tree_pointer == nullptr) {
				std::cout << "Tree is empty.\n"
					<< "\n\nPress any to button to continue...";
				_getch();
				break;
			}
			
			int find_info_key(0);
			bool key_found = false;

			while (!key_found)
			{
				tree.printing(tree_pointer);
				std::cout << "\n\nEnter the key of the data you would like to find.\n"
					<< "\nType here: ";
				find_info_key = static_cast<int>(number_input(TEST_LIMIT));

				for (size_t i = 0; i < tree.keys.size(); i++)
				{
					if (tree.keys[i] == find_info_key)
					{
						ClearScreen();

						Node* found_node = tree.node_find(tree_pointer, find_info_key);

						std::cout << "Node with key '" << find_info_key << "' has been found."
							<< "\n\nData: ";
						
						
						for (size_t i = 0; i < found_node->data.size(); i++)
							std::cout << found_node->data[i];

						std::cout << "\nAddress: " << found_node;
						std::cout << "\nKey: " << found_node->key;

						key_found = true;
						break;
					}
				}
				if (!key_found) {
					ClearScreen();
					std::cout << "Key's not found. Try again.\n\n";
				}
			}


			std::cout << "\n\nPress any to button to continue...";
			_getch();
			break;
		}
		default:
		{
			std::cout << "\n\n\n";	// just for beautiful output
			return 0;
		}
		}
	}
	return 0;
}




