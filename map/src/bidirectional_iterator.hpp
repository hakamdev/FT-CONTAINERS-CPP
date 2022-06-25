/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:54:07 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/25 19:32:38 by ehakam           ###   ########.fr       */
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
		typedef typename Iter::node_pointer										node_pointer;
		typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
		typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
		typedef typename ft::iterator_traits<iterator_type>::reference			reference;

		private:
			node_pointer _base;
			node_pointer _prev;

		// Constructors / Destructor
		bidir_iterator( void ) : _base() {}
		bidir_iterator( const node_pointer& base ) : _base(base) {}
		bidir_iterator( const bidir_iterator& copy ) {
			*this = copy;
		}
		template <typename T2>
		bidir_iterator( const bidir_iterator<T2>& copy ) {
			this->_base = copy.base();
		}
		bidir_iterator& operator = ( const bidir_iterator& copy ) {
			this->_base = copy.base(); return (*this);
		}
		~bidir_iterator() {}

		iterator_type base() const {
			return _base;
		}
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
		bidir_iterator& operator ++ () {
			_prev = _base;
			_base = iterator_type::next_node(_base);
			return (*this);
		}
		bidir_iterator operator ++ ( int ) {
			bidir_iterator<Iter> old(_base);
			_prev = _base;
			_base = iterator_type::next_node(_base);
			return (old);
		}
		bidir_iterator& operator -- () {
			_prev = _base;
			_base = iterator_type::prev_node(_base);
			return (*this);
		}
		bidir_iterator operator -- ( int ) {
			bidir_iterator<Iter> old(_base);
			_prev = _base;
			_base = iterator_type::prev_node(_base);
			return (old);
		}
	};
} // namespace ft

#endif // __BIDIR_ITER_HPP__