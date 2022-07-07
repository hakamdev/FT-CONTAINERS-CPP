/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 23:20:08 by ehakam            #+#    #+#             */
/*   Updated: 2022/07/07 03:48:54 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/vector.hpp"
#include "Human.hpp"
#include <vector>

int main() {

	std::cout << "===== Testing Empty Vector =====" << std::endl;

	std::string str, ft_str;
	ft::vector<std::string>::size_type s, ft_s;
	ft::vector<std::string>::size_type c, ft_c;
	ft::vector<std::string>::iterator ft_it;
	std::vector<std::string>::iterator it;

	{
            std::vector<std::string> v;
            ft::vector<std::string> ft_v;
            it = v.insert(v.begin(), "hello");
            ft_it = ft_v.insert(ft_v.begin(), "hello");

            (*ft_it).length();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
			std::cout << std::boolalpha;
            std::cout << ((str == ft_str) && (s == ft_s) && (c == ft_c) && (*ft_it == *it)) << std::endl;

    }

	// std::vector<Human> hv;
	
	// std::vector<int> iv2(10, 44);

	// ft::vector<int> iv(iv2.begin(), iv2.end());
	// ft::vector<int> iv3(4, 33);

	//std::vector<int>::iterator it = iv.end();

	//std::cout << *it << std::endl;

	//iv.clear();

	//iv.insert(iv.begin(), 30, 66);

	// std::cout << "sz: " << iv.size() << std::endl;
	// std::cout << "cp: " << iv.capacity() << std::endl;

	// std::cout << "[ ";
	// for (size_t i = 0; i < iv.size(); ++i) {
	// 	std::cout << iv[i] << ", ";
	// }
	// std::cout << "]" << std::endl;

	// std::cout << "[ ";
	// for (size_t i = 0; i < iv3.size(); ++i) {
	// 	std::cout << iv3[i] << ", ";
	// }
	// std::cout << "]" << std::endl;

	std::cout << "===== Testing Fill Empty Vector =====" << std::endl;
	
	
	return (0);
}