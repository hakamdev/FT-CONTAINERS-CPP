/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:54:07 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/25 23:37:19 by ehakam           ###   ########.fr       */
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
		typedef typename iterator_type::node_pointer							node_pointer;
		typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
		typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
		typedef typename ft::iterator_traits<iterator_type>::reference			reference;

		private:
			node_pointer _base;
			node_pointer _root;
			node_pointer _past_end;

		// Constructors / Destructor
		bidir_iterator( void ) : _base(NULL), _root(NULL) {
			this->_past_end = iterator_type::make_node();
		}
		bidir_iterator( const node_pointer& base, const node_pointer& root ) : _base(base), _root(root) {
			this->_past_end = iterator_type::make_node();
		}
		bidir_iterator( const bidir_iterator& copy ) {
			*this = copy;
			this->_past_end = iterator_type::make_node();
		}
		template <typename T2>
		bidir_iterator( const bidir_iterator<T2>& copy ) {
			this->_base = copy.base();
			this->_root = copy.root();
			this->_past_end = iterator_type::make_node();
		}
		bidir_iterator& operator = ( const bidir_iterator& copy ) {
			this->_base = copy.base();
			this->_root = copy.root();
			return (*this);
		}
		~bidir_iterator() {
			iterator_type::destroy_node(_past_end);
		}

		node_pointer base() const {
			return _base;
		}
		node_pointer root() const {
			return _root;
		}

		// Overloaded operators
		bool operator == ( racc_iterator const & other ) {
			return (this->_base == other._base);
		}
		bool operator != ( racc_iterator const & other ) {
			return (this->_base != other._base);
		}
		reference operator * () {
			if (this->_base == NULL) {
				return (*this->_past_end->content);
			}
			return (*this->_base->content);
		}
		bidir_iterator& operator ++ () {
			_base = iterator_type::next_node(_base);
			return (*this);
		}
		bidir_iterator operator ++ ( int ) {
			bidir_iterator<Iter> old(_base, _root);
			_base = iterator_type::next_node(_base);
			return (old);
		}
		bidir_iterator& operator -- () {
			if (_base == NULL)
				this->_base = iterator_type::max_node(_root);
			else
				this->_base = iterator_type::prev_node(_base);
			return (*this);
		}
		bidir_iterator operator -- ( int ) {
			bidir_iterator<Iter> old(_base, _root);
			if (_base == NULL)
				this->_base = iterator_type::max_node(_root);
			this->_base = iterator_type::prev_node(_base);
			return (old);
		}
	};
} // namespace ft

#endif // __BIDIR_ITER_HPP__