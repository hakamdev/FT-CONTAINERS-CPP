/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:57:01 by ehakam            #+#    #+#             */
/*   Updated: 2022/07/07 04:47:47 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PAIR_HPP__
# define __PAIR_HPP__

namespace ft
{
	template <typename T1, typename T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair() : first(), second() {
		}

		template<typename U, typename V>
		pair(const pair<U, V>& pr) : first(static_cast<first_type>(pr.first)), second(static_cast<second_type>(pr.second)) { }

		pair(const first_type& a, const second_type& b) : first(a), second(b) {}

		pair& operator= (const pair& pr) {
			first = pr.first;
			second = pr.second;
			return *this;
		}

	};

	template <typename T1, typename T2>
	bool operator== (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <typename T1, typename T2>
	bool operator!= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return !(lhs == rhs);
	}

	template <typename T1, typename T2>
	bool operator<  (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template <typename T1, typename T2>
	bool operator<= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return !(rhs < lhs);
	}

	template <typename T1, typename T2>
	bool operator>  (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return rhs < lhs;
	}

	template <typename T1, typename T2>
	bool operator>= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return !(lhs < rhs);
	}

	// make_pair
	template <typename T1, typename T2>
	pair<T1, T2> make_pair(T1 a, T2 b)
	{
		return (pair<T1, T2>(a, b));
	}

} // namespace ft

#endif // __PAIR_HPP__
