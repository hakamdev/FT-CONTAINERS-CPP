/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:41:32 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/25 07:00:12 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <stack>
#include <map>
#include <iostream>
#include <algorithm>
#include "../src/avl_tree.hpp"

int main() {

	// const int arr[] = {0, 1, 2, 3, 4};
	// const int arr2[] = {0, 1, 32, 3, 4};

	ft::avl_tree<std::string, int> tr;

	tr.insert(std::make_pair<std::string, int>("0", 100));
	tr.insert(std::make_pair<std::string, int>("1", 10));
	tr.insert(std::make_pair<std::string, int>("2", 20));
	tr.insert(std::make_pair<std::string, int>("3", 20));
	tr.insert(std::make_pair<std::string, int>("4", 20));
	tr.insert(std::make_pair<std::string, int>("5", 20));
	tr.insert(std::make_pair<std::string, int>("6", 20));
	tr.insert(std::make_pair<std::string, int>("7", 20));
	tr.insert(std::make_pair<std::string, int>("8", 20));
	tr.insert(std::make_pair<std::string, int>("9", 20));

	ft::avl_tree<std::string, int> tr2(tr);

	std::cout << "MIN: " << tr.min_node()->content->first << std::endl;

	std::cout << "MAX: " << tr.max_node()->content->first << std::endl;

	tr.printTree();
	tr2.printTree();

	// ft::avl_tree<std::string, int>::node_pointer p = tr.max_node();

	// while ((p = ft::avl_tree<std::string, int>::prev_node(p)) != NULL) {
	// 	std::cout << "PREV: " << p->content->first << std::endl;
	// }

	// p = ft::avl_tree<std::string, int>::next_node(p);
	// std::cout << "NEXT: " << p->content->first << std::endl;



	

	// tr.delete_node("7");

	// tr.printTree();

	// tr.delete_node("8");

	// tr.printTree();

	// tr.delete_node("9");

	// tr.printTree();

	return (0);
}