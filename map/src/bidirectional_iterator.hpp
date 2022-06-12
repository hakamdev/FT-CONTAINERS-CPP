/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:54:07 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/12 23:04:11 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BIDIR_ITER_HPP__
# define __BIDIR_ITER_HPP__

# include <iterator>
# include "iterator.hpp"
# include "traits.hpp"

namespace ft
{
	template <typename Iter>
	struct bidir_iterator : public ft::iterator<std::bidirectional_iterator_tag, Iter> {
		
		typedef Iter															iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
		typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
		typedef typename ft::iterator_traits<iterator_type>::reference			reference;

		private:
			iterator_type _base;

		// Constructors / Destructor
		bidir_iterator( void ) : _base() {}
		bidir_iterator( iterator_type base ) : _base(base) {}
		bidir_iterator( bidir_iterator<iterator_type> const & copy ) { *this = copy; }
		template <typename T2>
		bidir_iterator( bidir_iterator<T2> const & copy ) { this->_base = copy.base(); }
		bidir_iterator& operator = ( bidir_iterator<Iter> const & copy ) { this->_base = copy.base(); return (*this); }
		~bidir_iterator() {}

		iterator_type base() const { return _base; }

		// Overloaded operators
		bool operator == ( racc_iterator const & other ) {
			return (this->_base == other._base);
		}
		bool operator != ( racc_iterator const & other ) {
			return (this->_base != other._base);
		}
		reference operator * () {
			return (*this->_base);
		}
		racc_iterator& operator ++ () {
			++this->_base;
			return (*this);
		}
		racc_iterator operator ++ ( int ) {
			racc_iterator<Iter> old(*this);
			++this->_base;
			return (old);
		}
		racc_iterator& operator -- () {
			--this->_base;
			return (*this);
		}
		racc_iterator operator -- ( int ) {
			racc_iterator<Iter> old(*this);
			--this->_base;
			return (old);
		}
	}
} // namespace ft

#endif // __BIDIR_ITER_HPP__