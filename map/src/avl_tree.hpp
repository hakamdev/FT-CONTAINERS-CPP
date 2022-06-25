/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:21:45 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/25 04:12:25 by ehakam           ###   ########.fr       */
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

namespace ft
{
	template < typename Key,                                     		// map::key_type
           typename T,                                       			// map::mapped_type
           typename Compare = std::less<Key>,                     		// map::key_compare
           typename Alloc = std::allocator<std::pair<const Key, T> >,    // map::allocator_type
		   typename NodeAlloc = std::allocator<node<const Key, T, Alloc> >
           >
	class avl_tree {
		public:
			typedef std::pair<Key,T>						value_type;
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef Alloc									allocator_type;
			typedef NodeAlloc								node_allocator_type;
			typedef Compare									key_compare;
			typedef node<const Key, T, Alloc>				node_type;
			typedef typename allocator_type::pointer		pointer;
			typedef typename node_allocator_type::pointer	node_pointer;

		private:
			node_pointer		_root;
			allocator_type 		_alloc;
			node_allocator_type	_node_alloc;
			key_compare			_comp;

			void _printTree(node_pointer root, std::string indent, bool last) {
				if (root != NULL) {
					std::cout << indent;
					if (last) {
					std::cout << "R----";
					indent += "     ";
					} else {
					std::cout << "L----";
					indent += "|    ";
					}
					std::cout << root->content->first << " {" << root->height << "}" << " (" << (root->parent != NULL ? root->parent->content->first : ".")  << ")" << std::endl;
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
				if (parent == NULL) {
					return _make_node(val);
				}

				if (_comp(val.first, parent->content->first)) {
					// val smaller than parent
					parent->left = _insert(parent->left, val);
					parent->left->parent = parent;
				} else if (_comp(parent->content->first, val.first)) {
					// val greater to parent
					parent->right = _insert(parent->right, val);
					parent->right->parent = parent;
				} else {
					// == replace previous value
					parent->set_content(val);
				}

				// Calculate node hieght for balancing.
				_calculate_height(parent);

				parent = _balance_tree(parent);

				return parent;
			}

			node_pointer _min_node(node_pointer parent) {
				if (parent->left == NULL) return parent;
				return _min_node(parent->left);
			}

			node_pointer _max_node(node_pointer parent) {
				if (parent->right == NULL) return parent;
				return _max_node(parent->right);
			}

			node_pointer _delete_node(node_pointer parent, const Key& key) {
				if (parent == NULL) return NULL;
				if (_comp(key, parent->content->first)) {
					// val smaller than parent
					parent->left = _delete_node(parent->left, key);
				} else if (_comp(parent->content->first, key)) {
					// val greater to parent
					parent->right = _delete_node(parent->right, key);
				} else {
					// key found, now start deletion
					if (parent->left == NULL || parent->right == NULL) {
						// Now we replace parent by left/right depend. on which is not NULL
						node_pointer new_parent = parent->left != NULL ? parent->left : parent->right;
						// destroy the parent
						_node_alloc.destroy(parent);
						_node_alloc.deallocate(parent, 1);
						// asign the new parent left/right/NULL
						parent = new_parent;
						if (parent == NULL) return NULL;
					} else {
						// Both left and right are NOT NULL
						// Find max_node in the left subtree
				
						node_pointer max = _max_node(parent->left);
						// replace current node content with max->content
						_alloc.destroy(parent->content);
						_alloc.construct(parent->content, *max->content);
						// find and delete the max_node from its old position
						parent->left = _delete_node(parent->left, parent->content->first);
					}
				}
				// reset height of parent and rebalance the parent subtree.
				_calculate_height(parent);
				parent = _balance_tree(parent);
				return (parent);
			}

			void _calculate_height(node_pointer node) {
				// Calculate node hieght for balancing.
				node->height = std::max(_height(node->left), _height(node->right)) + 1;
			}

			int _height(node_pointer node) {
				return node == NULL ? -1 : node->height;
			}

			int _get_balance_factor(node_pointer node) {
				return _height(node->left) - _height(node->right);
			}

			bool _is_left_heavy(node_pointer node) {
				return _get_balance_factor(node) > 1;
			}

			bool _is_right_heavy(node_pointer node) {
				return _get_balance_factor(node) < -1;
			}

			node_pointer _balance_tree(node_pointer parent) {
				if (_is_right_heavy(parent)) {
					if (_get_balance_factor(parent->right) > 0)
						parent->right = _right_rotate(parent->right);
					return _left_rotate(parent);
				} else if (_is_left_heavy(parent)) {
					if (_get_balance_factor(parent->left) < 0)
						parent->left = _left_rotate(parent->left);
					return _right_rotate(parent);
				}
				return (parent);
			}

			node_pointer _left_rotate(node_pointer parent) {
				// Perform rotation
				node_pointer new_parent = parent->right;
				parent->right = new_parent->left;
				new_parent->left = parent;

				// Reset parents
				new_parent->parent = parent->parent;
				if (parent->right != NULL)
					parent->right->parent = parent;
				if (new_parent->left != NULL)
					new_parent->left->parent = new_parent;

				// Reset height
				_calculate_height(parent);
				_calculate_height(new_parent);
				
				return (new_parent);
			}

			node_pointer _right_rotate(node_pointer parent) {
				// Perform rotation
				node_pointer new_parent = parent->left;
				parent->left = new_parent->right;
				new_parent->right = parent;

				// Reset parents
				new_parent->parent = parent->parent;
				if (parent->left != NULL)
					parent->left->parent = parent;
				if (new_parent->right != NULL)
					new_parent->right->parent = new_parent;

				// Reset height
				_calculate_height(parent);
				_calculate_height(new_parent);

				// Return new_parent to assign it to parent
				return (new_parent);
			}

		public:
			avl_tree() {
				// TODO:
			}

			void insert(const value_type& val) {
				_root = _insert(_root, val);
			}

			void delete_node(const Key& key) {
				_root = _delete_node(_root, key);
			}

			node_pointer min_node() {
				if (_root == NULL) return NULL;
				return _min_node(_root);
			}

			node_pointer max_node() {
				if (_root == NULL) return NULL;
				return _max_node(_root);
			}

			void printTree() {
				_printTree(_root, "", false);
			}

	};
} // namespace ft

#endif // __AVL_TREE_HPP__