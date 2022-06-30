/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:21:45 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/30 21:30:08 by ehakam           ###   ########.fr       */
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
# include "bidirectional_iterator.hpp"
# include "reverse_bidirectional_iterator.hpp"

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
			typedef std::bidirectional_iterator_tag			iterator_category;
			typedef std::pair<const Key, T>					value_type;
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef Alloc									allocator_type;
			typedef NodeAlloc								node_allocator_type;
			typedef Compare									key_compare;
			typedef node<const Key, T, Alloc>				node_type;
			typedef typename allocator_type::pointer		pointer;
			typedef typename allocator_type::reference		reference;
			typedef typename node_allocator_type::pointer	node_pointer;
			typedef size_t									size_type;

		private:
			node_pointer		_root;
			allocator_type 		_alloc;
			node_allocator_type	_node_alloc;
			key_compare			_comp;
			size_type			_size;

			// Private helping methods (implementation details).
			void _printTree(node_pointer root, std::string indent, bool last) {
				if (root != NULL) {
					std::cout << indent;
					if (last) {
					std::cout << "R ";
					indent += "     ";
					} else {
					std::cout << "L ";
					indent += "|    ";
					}
					std::cout << "(" << root->content->first << ")->(" << root->content->second << ")" << std::endl;
					_printTree(root->left, indent, false);
					_printTree(root->right, indent, true);
				}
			}

			node_pointer _insert(node_pointer parent, const value_type& val, node_pointer *where) {
				if (parent == NULL) {
					++_size;
					*where = _make_node(val);
					return *where;
				}
				if (_comp(val.first, parent->content->first)) {
					// val smaller than parent
					parent->left = _insert(parent->left, val, where);
					parent->left->parent = parent;
				} else if (_comp(parent->content->first, val.first)) {
					// val greater to parent
					parent->right = _insert(parent->right, val, where);
					parent->right->parent = parent;
				} else {
					// == replace previous value
					parent->set_content(val);
					*where = parent;
				}

				// Calculate node hieght for balancing.
				_calculate_height(parent);

				parent = _balance_tree(parent);

				return parent;
			}

			node_pointer _delete_node(node_pointer parent, const key_type& key) {
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
						--_size;
						if (parent == NULL) return NULL;
					} else {
						// Both left and right are NOT NULL
						// Find max_node in the left subtree
						node_pointer max = max_node(parent->left);
						// replace current node content with max->content
						parent->set_content(*max->content);
						// find and delete the max_node from its old position
						parent->left = _delete_node(parent->left, parent->content->first);
					}
				}
				// reset height of parent and rebalance the parent subtree.
				_calculate_height(parent);
				parent = _balance_tree(parent);
				return (parent);
			}

			node_pointer _find(node_pointer parent, const key_type& key) {
				if (parent == NULL) return NULL;
				if (_comp(key, parent->content->first)) {
					// val smaller than parent
					return _find(parent->left, key);
				} else if (_comp(parent->content->first, key)) {
					// val greater to parent
					return _find(parent->right, key);
				} else {
					return parent;
				}
				return parent;
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

			node_pointer _make_node(const value_type& val = value_type()) {
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

		public:
			// Constructors.
			avl_tree(const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type(),
					const node_allocator_type& node_alloc = node_allocator_type()) : 
					_comp(comp), _alloc(alloc), _node_alloc(node_alloc), _root(NULL), _size(0) {
			}

			avl_tree(const avl_tree& other) {
				*this = other;
			}

			avl_tree& operator = (const avl_tree& other) {
				this->_alloc = other._alloc;
				this->_node_alloc = other._node_alloc;
				this->_comp = other._comp;
				this->_size = 0;
				node_pointer curr = other.min_node();
				do {
					if (curr == NULL) break;
					insert(*curr->content);
				} while((curr = next_node(curr)) != NULL);
				return *this;
			}

			// Public methods for AVL Tree operations.
			node_pointer find(const key_type& key) {
				if (empty()) return NULL;
				return _find(_root, key);
			}

			node_pointer insert(const value_type& val) {
				node_pointer where = NULL;
				_root = _insert(_root, val, &where);
				return where;
			}

			// hint can't be NULL or pointing to _past_end;
			node_pointer insert(node_pointer hint, const value_type& val) {
				node_pointer new_hint = _root;
				while (new_hint != NULL) {
					if (new_hint == hint) {
						break ;
					} else if (_comp(val.first, new_hint->content->first)) {
						if (new_hint->left == NULL) break ;
						new_hint = new_hint->left;
					} else if (_comp(new_hint->content->first, val.first)) {
						if (new_hint->right == NULL) break ;
						new_hint = new_hint->right;
					} else {
						break ;
					}
				}
				node_pointer where = NULL;
				new_hint = _insert(new_hint, val, &where);
				return where;
			}

			size_type delete_node(const key_type& key) {
				if (empty()) return 0;
				size_type old_size = _size;
				_root = _delete_node(_root, key);
				return old_size - _size;
			}

			node_pointer min_node() const {
				if (_root == NULL) return NULL;
				return avl_tree::min_node(_root);
			}

			node_pointer max_node() const {
				if (_root == NULL) return NULL;
				return avl_tree::max_node(_root);
			}

			node_pointer root() const {
				return _root;
			}

			size_type size() const {
				return _size;
			}

			bool empty() const {
				return _size == 0;
			}

			// General static functions to manipulate nodes.
			static node_pointer min_node(node_pointer parent) {
				if (parent->left == NULL) return parent;
				return min_node(parent->left);
			}

			static node_pointer max_node(node_pointer parent) {
				if (parent->right == NULL) return parent;
				return max_node(parent->right);
			}

			static node_pointer next_node(node_pointer node) {
				key_compare	_compare;
				if (node->right == NULL) {
					node_pointer curr = node->parent;
					while (curr != NULL && _compare(curr->content->first, node->content->first)) {
						curr = curr->parent;
					}
					return curr;
				} else {
					return min_node(node->right);
				}
			}

			static node_pointer prev_node(node_pointer node) {
				key_compare	_compare;
				if (node->left == NULL) {
					node_pointer curr = node->parent;
					while (curr != NULL && _compare(node->content->first, curr->content->first)) {
						curr = curr->parent;
					}
					return curr;
				} else {
					return max_node(node->left);
				}
			}

			static node_pointer make_node(const value_type& val = value_type()) {
				allocator_type alloc;
				node_allocator_type node_alloc;
				node_pointer _ptr = NULL;
				try {
					_ptr = node_alloc.allocate(1);
					node_alloc.construct(_ptr, node_type(val, alloc));
				} catch (std::exception& e) {
					std::cerr << e.what() << std::endl;
					exit(1);
				}
				return (_ptr);
			}

			static void destroy_node(node_pointer node) {
				node_allocator_type _node_alloc;
				_node_alloc.destroy(node);
				_node_alloc.deallocate(node, 1);
			}

			// Helper functions.
			void printTree() {
				_printTree(_root, "", false);
			}

	};
} // namespace ft

#endif // __AVL_TREE_HPP__