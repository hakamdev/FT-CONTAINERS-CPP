/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:21:45 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/21 20:13:41 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __AVL_TREE_HPP__
# define __AVL_TREE_HPP__


# include <memory>
# include <utility>
# include <functional>
# include <iostream>
# include "node.hpp"

// this->_alloc.construct(&_new_begin[i], this-> _begin[i]);
// pointer _new_begin = this->_alloc.allocate(new_capacity);
// this->_alloc.destroy(&this->_begin[i]);
// this->_alloc.deallocate(this->_begin, this->_capacity);

namespace ft
{
	template < typename Key,                                     		// map::key_type
           typename T,                                       			// map::mapped_type
           typename Compare = std::less<Key>,                     		// map::key_compare
           typename Alloc = std::allocator<std::pair<const Key,T> >,    // map::allocator_type
		   typename NodeAlloc = std::allocator<node<std::pair<const Key,T>, Alloc> >
           >
	class avl_tree {
		public:
			typedef std::pair<const Key,T>	value_type;
			typedef Key						key_type;
			typedef T						mapped_type;
			typedef Alloc					allocator_type;
			typedef NodeAlloc				node_allocator_type;
			typedef Compare					key_compare;
			typedef node<value_type, Alloc>	node_type;

		private:
			node_type*			_root;
			allocator_type 		_alloc;
			node_allocator_type	_node_alloc;
			key_compare			_comp_less;

			node_type* _make_node(const value_type& val) {
				node_type* _ptr = NULL;
				try {
					_ptr = _node_alloc.allocate(1);
					_node_alloc.construct(_ptr, node_type(val, _alloc));
				} catch (std::exception& e) {
					std::cerr << e.what() << std::endl;
					exit(1);
				}
				return (_ptr);
			}

			node_type* _insert(node_type* parent, const value_type& val) {
				node_type* _new_node = _make_node(val);
				if (parent == NULL)
					return _new_node;

				if (_comp_less(val.first, parent->content.first)) {
					// val smaller than parent
					
				} else if (_comp_less(parent->content.first, val.first))
					// val greater to parent
				else {
					// val equal to parent
				}
			}

		public:
			avl_tree() {
				// TODO:
			}

			void insert(const value_type& val) {
				_root = _insert(_root, val);
			}
	};
} // namespace ft

#endif // __AVL_TREE_HPP__