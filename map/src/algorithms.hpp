/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:05:35 by ehakam            #+#    #+#             */
/*   Updated: 2022/07/06 19:25:10 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ALGORITHMS_HPP__
#define __ALGORITHMS_HPP__

namespace ft
{
	template <class InputIterator1, class InputIterator2>
  	bool lexicographical_compare ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2 ) {
		while ( first1 != last1 ) {
			if ( first2 == last2 || *first2 < *first1 ) return false;
			else if ( *first1 < *first2 ) return true;
			++first1;
			++first2;
		}
		return ( first2 != last2 );
	}

	template <class InputIterator1, class InputIterator2>
  	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 ) {
		while ( first1 != last1 ) {
			if ( !( *first1 == *first2 ))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
  	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred ) {
		while ( first1!=last1 ) {
			if ( !pred( *first1, *first2 ))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

} // namespace ft

#endif // __ALGORITHMS_HPP__
