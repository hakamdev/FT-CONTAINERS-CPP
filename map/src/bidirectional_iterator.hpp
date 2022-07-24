/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:54:07 by ehakam            #+#    #+#             */
/*   Updated: 2022/07/24 03:22:26 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BIDIR_ITER_HPP__
# define __BIDIR_ITER_HPP__

# include <iterator>
# include <iostream>
# include "iterator.hpp"

namespace ft
{
	template <typename Iter, typename Node>
	struct bidir_iterator : public ft::iterator<std::bidirectional_iterator_tag, Iter> {

		typedef Iter									iterator_type;
		typedef Node									node_pointer;
		typedef typename iterator_type::node_type		node_type;
		typedef typename iterator_type::value_type		value_type;
		typedef typename iterator_type::pointer			pointer;
		typedef typename iterator_type::const_pointer	const_pointer;
		typedef typename iterator_type::reference		reference;

		private:
			node_pointer		 	_base;
			const iterator_type*	_tree;
			node_pointer			_past_end;

		public:
			// constructors / destructor
			bidir_iterator( void ) : _base(NULL), _tree(NULL), _past_end(NULL) { }

			bidir_iterator( node_pointer base, const iterator_type& tree ) : _base(NULL), _tree(&tree), _past_end(NULL) {
				// _past_end is to be pointed to as end()
				if (base == NULL) {
					this->_base = _past_end;
				} else {
					this->_base = base;
				}
			}

			template <typename T2, typename N2>
			bidir_iterator( const bidir_iterator<T2, N2>& copy ) : _base(NULL), _past_end(NULL) {
				this->_tree = copy.tree();
				// If copy.base pointing at end, you need to point to _past_end
				// that's created in this instance, because the copy.past_end might
				// be destroyed and also you can't check equality with this->_past_end
				if (copy.base() == copy.past_end())
					this->_base = this->_past_end;
				else
					this->_base = copy.base();
			}

			bidir_iterator( const bidir_iterator& copy ) : _base(NULL), _tree(NULL), _past_end(NULL) {
				*this = copy;
			}

			bidir_iterator& operator = ( const bidir_iterator& copy ) {
				this->_tree = copy.tree();
				// If copy.base pointing at end, you need to point to _past_end
				// that's created in this instance, because the copy.past_end might
				// be destroyed and also you can't check equality with this->_past_end
				if (copy.base() == copy.past_end())
					this->_base = this->_past_end;
				else
					this->_base = copy.base();
				return (*this);
			}

			~bidir_iterator() { }

			node_pointer base() const {
				return this->_base;
			}

			node_pointer past_end() const {
				return this->_past_end;
			}

			const iterator_type* tree() const {
				return this->_tree;
			}

			// overloaded operators
			bool operator == ( const bidir_iterator& other ) {
				return (this->_base == other._base || (this->_base == this->_past_end && other._base == other._past_end));
			}

			bool operator != ( const bidir_iterator& other ) {
				return !(*this == other);
			}

			reference operator * () {
				return (*this->_base->content);
			}

			pointer operator-> () {
				return (this->_base->content);
			}

			const_pointer operator-> () const {
				return (this->_base->content);
			}

			bidir_iterator& operator ++ () {
				_base = iterator_type::next_node(_base);
				return (*this);
			}

			bidir_iterator operator ++ ( int ) {
				bidir_iterator<Iter, Node> old(*this);
				operator++();
				return (old);
			}

			bidir_iterator& operator -- () {
				if (this->_base == iterator_type::min_node(_tree->root())) {
					this->_base = iterator_type::prev_node(_past_end);
				} else if (_base == NULL) {
					this->_base = iterator_type::max_node(_tree->root());
				} else {
					this->_base = iterator_type::prev_node(_base);
				}
				return (*this);
			}

			bidir_iterator operator -- ( int ) {
				bidir_iterator<Iter, Node> old(*this);
				operator--();
				return (old);
			}

	};

} // namespace ft

#endif // __BIDIR_ITER_HPP__
