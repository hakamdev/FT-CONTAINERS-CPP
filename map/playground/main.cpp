/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:41:32 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/29 19:32:32 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <stack>
#include <map>
#include <iostream>
#include <algorithm>
#include "../src/avl_tree.hpp"
#include "../src/map.hpp"

int main() {

	// const int arr[] = {0, 1, 2, 3, 4};
	// const int arr2[] = {0, 1, 32, 3, 4};

	// ft::avl_tree<std::string, int> tr;

	// ft::avl_tree<std::string, int>::node_pointer p1 = tr.insert(std::make_pair<std::string, int>("0", 100));
	// ft::avl_tree<std::string, int>::node_pointer p2 = tr.insert(std::make_pair<std::string, int>("1", 10));
	// ft::avl_tree<std::string, int>::node_pointer p3 = tr.insert(std::make_pair<std::string, int>("2", 20));
	// ft::avl_tree<std::string, int>::node_pointer p4 = tr.insert(std::make_pair<std::string, int>("2", 555));
	// tr.insert(std::make_pair<std::string, int>("3", 20));
	// tr.insert(std::make_pair<std::string, int>("4", 34));
	// tr.insert(std::make_pair<std::string, int>("5", 6));
	// tr.insert(std::make_pair<std::string, int>("6", 13));
	// tr.insert(std::make_pair<std::string, int>("7", 44));
	// tr.insert(std::make_pair<std::string, int>("8", 67));
	// tr.insert(std::make_pair<std::string, int>("9", 11));

	// ft::avl_tree<std::string, int> tr2(tr);

	// std::cout << "MIN: " << tr.min_node()->content->first << std::endl;

	// std::cout << "MAX: " << tr.max_node()->content->first << std::endl;

	// std::cout << "P1: " << p1->content->first << " -> " << p1->content->second << std::endl;
	// std::cout << "P2: " << p2->content->first << " -> " << p2->content->second << std::endl;
	// std::cout << "P3: " << p3->content->first << " -> " << p3->content->second << std::endl;
	// std::cout << "P4: " << p4->content->first << " -> " << p4->content->second << std::endl;

	// tr.printTree();
	// tr2.printTree();

	// ft::avl_tree<std::string, int>::node_pointer p = tr.max_node();

	// while ((p = ft::avl_tree<std::string, int>::prev_node(p)) != NULL) {
	// 	std::cout << "PREV: " << p->content->first << std::endl;
	// }

	// p = ft::avl_tree<std::string, int>::next_node(p);
	// std::cout << "NEXT: " << p->content->first << std::endl;

	// std::map<std::string, int> ma;

	// ma.insert(std::pair<std::string, int>("0", 0));
	// ma.insert(std::pair<std::string, int>("1", 1));
	// ma.insert(std::pair<std::string, int>("2", 2));

	// std::map<std::string, int>::iterator it = ma.begin();
	// std::map<std::string, int>::iterator eit = ma.end();
	
	// std::map<std::string, int>::reverse_iterator rit = ma.rbegin();
	// std::map<std::string, int>::reverse_iterator reit = ma.rend();

	// (*(it));

	// std::cout << (*(++it)).second << std::endl;

	// std::cout << std::boolalpha;

	// ft::map<std::string, int> ma;

	// std::cout << ma.size() << std::endl;
	// std::cout << ma.empty() << std::endl;

	// ma.insert(std::pair<std::string, int>("0", 0));

	// std::cout << ma.size() << std::endl;
	// std::cout << ma.empty() << std::endl;
	
	// ma.insert(std::pair<std::string, int>("1", 1));

	// std::cout << ma.size() << std::endl;
	// std::cout << ma.empty() << std::endl;
	
	// ma.insert(std::pair<std::string, int>("2", 2));

	// std::cout << ma.size() << std::endl;
	// std::cout << ma.empty() << std::endl;

	// ma.insert(std::pair<std::string, int>("2", 24));

	// std::cout << ma.size() << std::endl;
	// std::cout << ma.empty() << std::endl;

	// std::cout << "ER: " << ma.erase("1") << std::endl;
	// std::cout << "ER: " << ma.erase("0") << std::endl;
	// std::cout << "ER: " << ma.erase("100") << std::endl;

	// std::cout << ma.size() << std::endl;
	// std::cout << ma.empty() << std::endl;

	// ma.print();

	std::map<std::string, int> ma;

	ma.insert(std::pair<std::string, int>("2", 24));
	ma.insert(std::pair<std::string, int>("0", 30));
	ma.insert(std::pair<std::string, int>("5", 55));
	ma.insert(std::pair<std::string, int>("9", 55));
	ma.insert(std::pair<std::string, int>("7", 55));

	std::map<std::string, int>::iterator it = ma.begin();

	++it; ++it;

	ma.insert(it, std::pair<std::string, int>("1", 11111));

	//ma.print();

	std::cout << ma["1"] << std::endl;

	// std::map<std::string, int>::iterator it = ma.begin();
	// std::map<std::string, int>::reverse_iterator rit = ma.rbegin();

	// std::cout << (*it++).first << std::endl;
	// //rit++;
	// std::cout << (*it++).first << std::endl;
	// //rit++;
	// std::cout << (*it++).first << std::endl;
	// it++;
	//std::cout << (*it++).first << std::endl;
	//++rit;
	//std::cout << (*rit).first << std::endl;
	//std::cout << (*it).first << std::endl;

	return (0);
}
