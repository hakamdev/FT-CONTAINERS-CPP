/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:21:45 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/24 20:57:49 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __AVL_TREE_HPP__
# define __AVL_TREE_HPP__


# include <memory>
# include <utility>
# include <functional>
# include <iostream>
# include <algorithm>
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
		   typename NodeAlloc = std::allocator<node<Key, T, Alloc> >
           >
	class avl_tree {
		public:
			typedef std::pair<Key,T>		value_type;
			typedef Key						key_type;
			typedef T						mapped_type;
			typedef Alloc					allocator_type;
			typedef NodeAlloc				node_allocator_type;
			typedef Compare					key_compare;
			typedef node<Key, T, Alloc>		node_type;

			typedef typename allocator_type::pointer			pointer;
			typedef typename node_allocator_type::pointer		node_pointer;

		private:
			node_pointer		_root;
			allocator_type 		_alloc;
			node_allocator_type	_node_alloc;
			key_compare			_comp;

			// Print the tree
			void _printTree(node_pointer root, std::string indent, bool last) {
				if (root != NULL) {
					std::cout << indent;
					if (last) {
					std::cout << "R----";
					indent += "   ";
					} else {
					std::cout << "L----";
					indent += "|  ";
					}
					std::cout << root->content->first << std::endl;
					_printTree(root->left, indent, false);
					_printTree(root->right, indent, true);
				}
			}

			node_pointer _make_node(const value_type& val) {
				node_pointer _ptr = NULL;
				try {
					_ptr = _node_alloc.allocate(1);
					_node_alloc.construct(_ptr, node_type(val, _alloc));
				} catch (std::exception& e) {
					std::cerr << e.what() << std::endl;
					exit(1);
				}
				return (_ptr);
			}

			node_pointer _insert(node_pointer parent, const value_type& val) {
				std::cout << "-- Inserting " << val.first << std::endl;

				if (parent == NULL) {
					std::cout << "Parent is NULL, INSERT" << std::endl;
					return _make_node(val);
				}

				if (_comp(val.first, parent->content->first)) {
					std::cout << "Val < Parent" << std::endl;
					// val smaller than parent
					parent->left = _insert(parent->left, val);
					parent->left->parent = parent;
				} else if (_comp(parent->content->first, val.first)) {
					std::cout << "Val > Parent" << std::endl;
					// val greater to parent
					parent->right = _insert(parent->right, val);
					parent->right->parent = parent;
				} else {
					std::cout << "Val == Parent" << std::endl;
					// == replace previous value
					parent->set_content(val);
				}

				parent->height = std::max(_height(parent->left), _height(parent->right)) + 1;

				std::cout << "Height = " << parent->height << std::endl;
			
				return parent;
			}

			int _height(node_pointer node) {
				return node == NULL ? -1 : node->height;
			}

			void _balance_tree() {
				// TODO: 
			}

		public:
			avl_tree() {
				// TODO:
			}

			void insert(const value_type& val) {
				_root = _insert(_root, val);
			}

			void printTree() {
				_printTree(_root, "", false);
			}

	};
} // namespace ft

#endif // __AVL_TREE_HPP__