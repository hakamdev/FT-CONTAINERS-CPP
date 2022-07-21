/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:54:07 by ehakam            #+#    #+#             */
/*   Updated: 2022/07/21 15:16:13 by ehakam           ###   ########.fr       */
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
			node_pointer		_base;
			const node_pointer*	_root;
			node_pointer		_past_end;

		public:
			// Constructors / Destructor
			bidir_iterator( void ) : _base(NULL), _root(NULL), _past_end(NULL) {
				//std::cout << "def constr" << std::endl;
			}

			bidir_iterator( node_pointer base, node_pointer const* root ) : _base(NULL), _root(root), _past_end(NULL) {
				//std::cout << "param constr" << std::endl;
				// _past_end is to be pointed to as end()
				if (base == NULL) {
					this->_base = _past_end;
				} else {
					this->_base = base;
				}
			}

			template <typename T2, typename N2>
			bidir_iterator( const bidir_iterator<T2, N2>& copy ) : _base(NULL), _root(NULL), _past_end(NULL) {
				//std::cout << "copy constr T" << std::endl;
				this->_root = copy._root;
				// If copy.base pointing at end, you need to point to _past_end
				// that's created in this instance, because the copy.past_end might
				// be destroyed and also you can't check equality with this->_past_end
				if (copy.base() == copy.past_end())
					this->_base = this->_past_end;
				else
					this->_base = copy.base();
			}

			bidir_iterator( const bidir_iterator& copy ) : _base(NULL), _root(NULL), _past_end(NULL) {
				//std::cout << "copy constr" << std::endl;
				*this = copy;
			}

			bidir_iterator& operator = ( const bidir_iterator& copy ) {
				//std::cout << "= operator" << std::endl;
				this->_root = copy._root;
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
				return _past_end;
			}

			// Overloaded operators
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
				node_pointer _next =
					iterator_type::next_node(_base != _past_end ? _base : NULL);
				if (_next == NULL) {
					_base = _past_end;
				} else {
					_base = _next;
				}
				return (*this);
			}

			bidir_iterator operator ++ ( int ) {
				bidir_iterator<Iter, Node> old(*this);
				operator++();
				return (old);
			}

			bidir_iterator& operator -- () {
				if (this->_base == iterator_type::min_node(*_root))
					this->_base = iterator_type::prev_node(NULL);
				else if (_base == _past_end)
					this->_base = iterator_type::max_node(*_root);
				else
					this->_base = iterator_type::prev_node(_base);
				return (*this);
			}

			bidir_iterator operator -- ( int ) {
				bidir_iterator<Iter, Node> old(_base != _past_end ? _base : NULL, _root);
				operator--();
				return (old);
			}

	};

} // namespace ft

#endif // __BIDIR_ITER_HPP__
