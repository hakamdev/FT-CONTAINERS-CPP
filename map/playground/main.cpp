/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:41:32 by ehakam            #+#    #+#             */
/*   Updated: 2022/07/04 18:00:06 by ehakam           ###   ########.fr       */
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

	// ft::avl_tree<std::string, int>::node_pointer p1 = tr.insert(ft::make_pair<std::string, int>("0", 100));
	// ft::avl_tree<std::string, int>::node_pointer p2 = tr.insert(ft::make_pair<std::string, int>("1", 10));
	// ft::avl_tree<std::string, int>::node_pointer p3 = tr.insert(ft::make_pair<std::string, int>("2", 20));
	// ft::avl_tree<std::string, int>::node_pointer p4 = tr.insert(ft::make_pair<std::string, int>("4", 555));
	// //tr.insert(ft::make_pair<std::string, int>("3", 20));
	// tr.insert(ft::make_pair<std::string, int>("4", 34));
	// tr.insert(ft::make_pair<std::string, int>("5", 6));
	// tr.insert(ft::make_pair<std::string, int>("6", 13));
	// tr.insert(ft::make_pair<std::string, int>("7", 44));
	// tr.insert(ft::make_pair<std::string, int>("8", 67));
	// // tr.insert(ft::make_pair<std::string, int>("9", 11));

	// ft::avl_tree<std::string, int>::node_pointer lb = tr.lower_bound("9");
	// ft::avl_tree<std::string, int>::node_pointer ub = tr.upper_bound("9");

	// std::cout << "LB: => " << (lb != NULL ? lb->content->first : "NULL") << std::endl;
	// std::cout << "UB: => " << (ub != NULL ? ub->content->first : "NULL") << std::endl;

	// ft::avl_tree<std::string, int> tr2(tr);

	// std::cout << "MIN: " << tr.min_node()->content->first << std::endl;

	// std::cout << "MAX: " << tr.max_node()->content->first << std::endl;

	// std::cout << "P1: " << p1->content->first << " -> " << p1->content->second << std::endl;
	// std::cout << "P2: " << p2->content->first << " -> " << p2->content->second << std::endl;
	// std::cout << "P3: " << p3->content->first << " -> " << p3->content->second << std::endl;
	// std::cout << "P4: " << p4->content->first << " -> " << p4->content->second << std::endl;

	//tr.printTree();
	// tr2.printTree();

	// ft::avl_tree<std::string, int>::node_pointer p = tr.max_node();

	// while ((p = ft::avl_tree<std::string, int>::prev_node(p)) != NULL) {
	// 	std::cout << "PREV: " << p->content->first << std::endl;
	// }

	// p = ft::avl_tree<std::string, int>::next_node(p);
	// std::cout << "NEXT: " << p->content->first << std::endl;

	// std::map<std::string, int> ma;

	// ma.insert(ft::pair<std::string, int>("0", 0));
	// ma.insert(ft::pair<std::string, int>("1", 1));
	// ma.insert(ft::pair<std::string, int>("2", 2));

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

	// ma.insert(ft::pair<std::string, int>("0", 0));

	// std::cout << ma.size() << std::endl;
	// std::cout << ma.empty() << std::endl;
	
	// ma.insert(ft::pair<std::string, int>("1", 1));

	// std::cout << ma.size() << std::endl;
	// std::cout << ma.empty() << std::endl;
	
	// ma.insert(ft::pair<std::string, int>("2", 2));

	// std::cout << ma.size() << std::endl;
	// std::cout << ma.empty() << std::endl;

	// ma.insert(ft::pair<std::string, int>("2", 24));

	// std::cout << ma.size() << std::endl;
	// std::cout << ma.empty() << std::endl;

	// std::cout << "ER: " << ma.erase("1") << std::endl;
	// std::cout << "ER: " << ma.erase("0") << std::endl;
	// std::cout << "ER: " << ma.erase("100") << std::endl;

	// std::cout << ma.size() << std::endl;
	// std::cout << ma.empty() << std::endl;

	// ma.print();

	#define NS ft

	NS::map<int, int> ma;

	ma.insert(NS::pair<int, int>(10, 22));
	ma.insert(NS::pair<int, int>(5, 11));
	ma.insert(NS::pair<int, int>(15, 55));
	ma.insert(NS::pair<int, int>(3, 77));
	ma.insert(NS::pair<int, int>(7, 88));
	ma.insert(NS::pair<int, int>(12, 88));
	ma.insert(NS::pair<int, int>(20, 88));
	ma.insert(NS::pair<int, int>(6, 88));
	ma.insert(NS::pair<int, int>(9, 88));
	ma.insert(NS::pair<int, int>(2, 88));
	ma.insert(NS::pair<int, int>(4, 88));

	//NS::map<std::string, int> ma2(it, eit);

	//ma.print();

	NS::map<int, int>::iterator it = ma.lower_bound(20);
	NS::map<int, int>::iterator it2 = ma.upper_bound(20);

	std::cout << "LB: " << (*it).first << std::endl;
	std::cout << "LB: " << (*it2).second << std::endl;

	// size_t it = ma.count(-5);

	// std::cout << "IT: " << it << std::endl;

	//ma.print();

	// NS::map<int, int>::iterator it = ma.begin();
	// NS::map<int, int>::iterator eit = ma.end();

	// //std::cout << "IT 1: " << (*it).first << std::endl;
	// NS::map<int, int>::iterator beg = ma.begin();

	// ++it; ++it; ++it;
	// NS::map<int, int>::iterator tmp = it;

	// ma.print();

	// ma.erase(5);

	// ma.print();

	// NS::map<int, int>::iterator it2 = ma.begin();
	// std::cout << ma[15] << std::endl;
	// ma.erase(it2);

	// ma.print();

	//std::cout << "IT 2: " << (*it).first << std::endl;

	//std::cout << ma2["0"] << std::endl;

	// ma.print();

	//ft::map<std::string, int> ma2(it, eit);

	// ma2.insert(eit, it);

 	// std::cout << ma2["9"] << std::endl;
 	// std::cout << ma2["1"] << std::endl;

	//ma2.print();

	// std::cout << (*it).first << std::endl;
	// std::cout << (*eit).first << std::endl;

	// std::map<std::string, int> ma2;

	// ma.erase(eit);

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
