/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 22:54:07 by ehakam            #+#    #+#             */
/*   Updated: 2022/07/02 21:05:50 by ehakam           ###   ########.fr       */
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

		public:
			// Constructors / Destructor
			bidir_iterator( void ) : _root(NULL), _base(NULL) {
				this->_past_end = iterator_type::make_node();
			}

			bidir_iterator( node_pointer base, node_pointer root ) : _root(root) {
				// this->_past_end is to be pointed to as end()
				this->_past_end = iterator_type::make_node();
				if (base == NULL) {
					this->_base = _past_end;
				} else {
					this->_base = base;
				}
			}

			template <typename T2>
			bidir_iterator( const bidir_iterator<T2>& copy ) {
				*this = copy;
			}

			bidir_iterator( const bidir_iterator& copy ) {
				*this = copy;
			}

			bidir_iterator& operator = ( const bidir_iterator& copy ) {
				this->_past_end = iterator_type::make_node();
				this->_root = copy._root;
				// If copy.base pointing at end, you need to point to _past_end
				// that's created in this instance, because the copy.past_end might
				// be destroyed and also you can't check equality with this->_past_end
				if (copy.base() == copy._past_end)
					this->_base = this->_past_end;
				else
					this->_base = copy.base();
				return (*this);
			}

			~bidir_iterator() {
				iterator_type::destroy_node(_past_end);
			}

			node_pointer base() const {
				return this->_base;
			}

			node_pointer past_end() const {
				return _past_end;
			}

			// Overloaded operators
			bool operator == ( const bidir_iterator& other ) {
				return (this->_base == other._base
				|| (this->_base == this->_past_end && other._base == other._past_end));
			}

			bool operator != ( const bidir_iterator& other ) {
				return !(*this == other);
			}

			reference operator * () {
				return (*this->_base->content);
			}

			bidir_iterator& operator ++ () {
				node_pointer _next =
					iterator_type::next_node(_base != _past_end ? _base : NULL);
				if (_next == NULL) {
					_base = _past_end;
				} else {
					_base = _next;
				}
				//std::cout << "NEXT: " << _next->content->first << std::endl;
				return (*this);
			}

			bidir_iterator operator ++ ( int ) {
				bidir_iterator<Iter> old(_base != _past_end ? _base : NULL, _root);
				operator++();
				//std::cout << "NEXT BASE: " << _base->content->first << std::endl;
				return (old);
			}

			bidir_iterator& operator -- () {
				if (_base == _past_end)
					this->_base = iterator_type::max_node(_root);
				else
					this->_base = iterator_type::prev_node(_base);
				return (*this);
			}

			bidir_iterator operator -- ( int ) {
				bidir_iterator<Iter> old(_base != _past_end ? _base : NULL, _root);
				operator--();
				return (old);
			}

	};
} // namespace ft

#endif // __BIDIR_ITER_HPP__
