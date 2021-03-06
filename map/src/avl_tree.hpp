/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:21:45 by ehakam            #+#    #+#             */
/*   Updated: 2022/07/24 03:21:56 by ehakam           ###   ########.fr       */
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
# include "pair.hpp"

namespace ft
{
	template < typename Key,											// map::key_type
           typename T,													// map::mapped_type
           typename Compare = std::less<Key>,							// map::key_compare
           typename Alloc = std::allocator<ft::pair<const Key, T> >		// map::allocator_type
           >
	class avl_tree {
		public:
			typedef std::bidirectional_iterator_tag										iterator_category;
			typedef ft::pair<const Key, T>												value_type;
			typedef Key																	key_type;
			typedef T																	mapped_type;
			typedef Compare																key_compare;
			typedef node<const Key, T, Alloc>											node_type;
			typedef Alloc																allocator_type;
			typedef typename Alloc::template rebind<node<const Key, T, Alloc> >::other	node_allocator_type;
			typedef typename allocator_type::pointer									pointer;
			typedef typename allocator_type::const_pointer								const_pointer;
			typedef typename allocator_type::reference									reference;
			typedef typename node_allocator_type::pointer								node_pointer;
			typedef typename node_allocator_type::const_pointer							const_node_pointer;
			typedef size_t																size_type;

		private:
			node_pointer		_root;
			allocator_type 		_alloc;
			node_allocator_type	_node_alloc;
			key_compare			_comp;
			size_type			_size;

			// private helping methods (implementation details).
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
					std::cout << "(" << root->content->first << ")" /*->(" << root->content->second << ")"*/;
					if (root->parent != NULL)
						std::cout << " [" << (root->parent != NULL ? root->parent->content->first : 0) << "]";
					std::cout << "{" << root->height << "}" << std::endl;
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
					if (parent->left != NULL)
						parent->left->parent = parent;
				} else if (_comp(parent->content->first, val.first)) {
					// val greater to parent
					parent->right = _insert(parent->right, val, where);
					if (parent->right != NULL)
						parent->right->parent = parent;
				} else {
					*where = parent;
				}

				// calculate node hieght for balancing.
				_calculate_height(parent);

				parent = _balance_tree(parent);

				return parent;
			}

			node_pointer _insert_all(node_pointer parent, node_pointer from) {
				// from->parent is a leaf node.
				if (from == NULL) return NULL;
				
				// copy "from" content and height.
				parent = _make_node(*from->content);
				parent->height = from->height;

				// rerun recursively for left child.
				parent->left = _insert_all(parent->left, from->left);

				// asign the parent for left child.
				if (parent->left != NULL) parent->left->parent = parent;

				// rerun recursively for right child.
				parent->right = _insert_all(parent->right, from->right);

				// asign the parent for right child.
				if (parent->right != NULL) parent->right->parent = parent;
				
				return parent;
			}

			node_pointer _delete_found_node(node_pointer node) {
				// key found, now start deletion
				if (node->left == NULL || node->right == NULL) {
					// now we replace parent by left/right depend. on which is not NULL
					node_pointer new_node = node->left != NULL ? node->left : node->right;
					// destroy the node
					_node_alloc.destroy(node);
					_node_alloc.deallocate(node, 1);
					// asign the new parent left/right/NULL
					node = new_node;
				} else {
					// both left and right are NOT NULL
					// find max_node in the left subtree
					node_pointer max = max_node(node->left);
					// disconnect max from its parent
					if (max == node->left)
						max->parent->left = max->left;
					else
						max->parent->right = max->left;
					if (max->left != NULL)
						max->left->parent = max->parent;
					// give max the children of node
					max->left = node->left;
					max->right = node->right;
					if (max->left != NULL)
						max->left->parent = max;
					if (max->right != NULL)
						max->right->parent = max;
					// destory node
					_node_alloc.destroy(node);
					_node_alloc.deallocate(node, 1);
					// asign max to node to return it
					node = max;
				}
				--_size;
				return (node);
			}

			node_pointer _delete_node_key(node_pointer parent, const key_type& key) {
				if (parent == NULL) return NULL;
				if (_comp(key, parent->content->first)) {
					// val smaller than parent
					parent->left = _delete_node_key(parent->left, key);
					if (parent->left != NULL)
						parent->left->parent = parent;
				} else if (_comp(parent->content->first, key)) {
					// val greater to parent
					parent->right = _delete_node_key(parent->right, key);
					if (parent->right != NULL)
						parent->right->parent = parent;
				} else {
					parent = _delete_found_node(parent);
					if (parent == NULL) return NULL;
					parent->parent = NULL;
				}
				// reset height of parent and rebalance the parent subtree.
				_calculate_height(parent);
				parent = _balance_tree(parent);
				return (parent);
			}

			node_pointer _delete_node(node_pointer parent, node_pointer node) {
				if (parent == NULL) return NULL;
				if (_comp(node->content->first, parent->content->first)) {
					// val smaller than parent
					parent->left = _delete_node(parent->left, node);
					if (parent->left != NULL)
						parent->left->parent = parent;
				} else if (_comp(parent->content->first, node->content->first)) {
					// val greater to parent
					parent->right = _delete_node(parent->right, node);
					if (parent->right != NULL)
						parent->right->parent = parent;
				} else {
					parent = _delete_found_node(parent);
					if (parent == NULL) return NULL;
					parent->parent = NULL;
				}
				// reset height of parent and rebalance the parent subtree.
				_calculate_height(parent);
				parent = _balance_tree(parent);
				return (parent);
			}

			node_pointer _delete_all(node_pointer parent) {
				if (parent == NULL) return NULL;

				// get pointers to left and right children before
				// delete the parent node.
				parent->left = _delete_all(parent->left);
				parent->right = _delete_all(parent->right);

				// now delete parent node safely.
				_node_alloc.destroy(parent);
				_node_alloc.deallocate(parent, 1);

				// decrease size
				--_size;
				return (NULL);
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
			}

			node_pointer _const_find(node_pointer parent, const key_type& key) const {
				if (parent == NULL) return NULL;
				if (_comp(key, parent->content->first)) {
					// val smaller than parent
					return _const_find(parent->left, key);
				} else if (_comp(parent->content->first, key)) {
					// val greater to parent
					return _const_find(parent->right, key);
				} else {
					return parent;
				}
			}

			void _calculate_height(node_pointer node) {
				// calculate node hieght for balancing.
				node->height = std::max(_height(node->left), _height(node->right)) + 1;
			}

			int _height(node_pointer node) {
				// get node height or -1 if null.
				return node == NULL ? -1 : node->height;
			}

			int _get_balance_factor(node_pointer node) {
				// balance factor if diff between left and right subtrees.
				// if it's not (-1 <= bf <= 1) the tree is not balanced. 
				return _height(node->left) - _height(node->right);
			}

			bool _is_left_heavy(node_pointer node) {
				// the tree is not balanced on the left subtree
				return _get_balance_factor(node) > 1;
			}

			bool _is_right_heavy(node_pointer node) {
				// the tree is not balanced on the right subtree
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
				// perform rotation
				node_pointer new_parent = parent->right;
				parent->right = new_parent->left;
				new_parent->left = parent;

				// reset parents
				new_parent->parent = parent->parent;
				parent->parent = new_parent;
				if (parent->right != NULL)
					parent->right->parent = parent;
				if (new_parent->left != NULL)
					new_parent->left->parent = new_parent;

				// reset heights
				_calculate_height(parent);
				_calculate_height(new_parent);
				
				return (new_parent);
			}

			node_pointer _right_rotate(node_pointer parent) {
				// perform rotation
				node_pointer new_parent = parent->left;
				parent->left = new_parent->right;
				new_parent->right = parent;

				// reset parents
				new_parent->parent = parent->parent;
				parent->parent = new_parent;
				if (parent->left != NULL)
					parent->left->parent = parent;
				if (new_parent->right != NULL)
					new_parent->right->parent = new_parent;

				// reset heights
				_calculate_height(parent);
				_calculate_height(new_parent);

				return (new_parent);
			}

			node_pointer _make_node(const value_type& val = value_type()) {
				// allocate and construct a new node with val and return it
				// using map's instance of Alloc
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
			// constructors/destructor.
			avl_tree(const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type(),
					const node_allocator_type& node_alloc = node_allocator_type()) : 
					_root(NULL), _alloc(alloc), _node_alloc(node_alloc),  _comp(comp), _size(0) {
			}

			avl_tree(const avl_tree& other) : _root(NULL), _size(0) {
				*this = other;
			}

			avl_tree& operator = (const avl_tree& other) {
				delete_all();
				this->_alloc = other._alloc;
				this->_node_alloc = other._node_alloc;
				this->_comp = other._comp;
				this->_root = _insert_all(this->_root, other._root);
				this->_size = other._size;
				return *this;
			}

			~avl_tree() {
				delete_all();
			}

			// public methods for AVL Tree operations.
			node_pointer find(const key_type& key) {
				if (empty()) return NULL;
				return _find(_root, key);
			}

			node_pointer const_find(const key_type& key) const {
				if (empty()) return NULL;
				return _const_find(_root, key);
			}

			node_pointer insert(const value_type& val) {
				node_pointer where = NULL;
				_root = _insert(_root, val, &where);
				return where;
			}

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

			size_type delete_node(const key_type& key, bool is_key) {
				size_type old_size = _size;
				if (empty() || !is_key) return 0;
				_root = _delete_node_key(_root, key);
				if (_root != NULL) _root->parent = NULL;
				return old_size - _size;
			}

			void delete_node(node_pointer node) {
				if (empty()) return ;
				_root = _delete_node(_root, node);
				if (_root != NULL) _root->parent = NULL;
			}

			void delete_all() {
				_root = _delete_all(_root);
			}

			node_pointer min_node() {
				if (_root == NULL) return NULL;
				return avl_tree::min_node(_root);
			}

			const_node_pointer min_node() const {
				if (_root == NULL) return NULL;
				return avl_tree::min_node(_root);
			}

			node_pointer max_node() {
				if (_root == NULL) return NULL;
				return avl_tree::max_node(_root);
			}

			const_node_pointer max_node() const {
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

			node_pointer lower_bound(const key_type& k) {
				if (empty()) return NULL;
				node_pointer start = min_node();
				while (start != NULL && _comp(start->content->first, k)) {
					start = next_node(start);
				}
				return start;
			}

			const_node_pointer lower_bound(const key_type& k) const {
				if (empty()) return NULL;
				const_node_pointer start = min_node();
				while (start != NULL && _comp(start->content->first, k)) {
					start = next_node(start);
				}
				return start;
			}

			node_pointer upper_bound(const key_type& k) {
				if (empty()) return NULL;
				node_pointer start = min_node();
				while (start != NULL && _comp(start->content->first, k)) {
					start = next_node(start);
				}
				if (start == NULL) return NULL;
				if (_comp(k, start->content->first)) return start;
				return next_node(start);
			}

			const_node_pointer upper_bound(const key_type& k) const {
				if (empty()) return NULL;
				const_node_pointer start = min_node();
				while (start != NULL && _comp(start->content->first, k)) {
					start = next_node(start);
				}
				if (start == NULL) return NULL;
				if (_comp(k, start->content->first)) return start;
				return next_node(start);
			}

			void swap(avl_tree& rhs) {
				node_pointer		temp_root = rhs._root;
				allocator_type 		temp_alloc = rhs._alloc;
				node_allocator_type	temp_node_alloc = rhs._node_alloc;
				key_compare			temp_comp = rhs._comp;
				size_type			temp_size = rhs._size;

				rhs._root = this->_root;
				rhs._alloc = this->_alloc;
				rhs._node_alloc = this->_node_alloc;
				rhs._comp = this->_comp;
				rhs._size = this->_size;

				this->_root = temp_root;
				this->_alloc = temp_alloc;
				this->_node_alloc = temp_node_alloc;
				this->_comp = temp_comp;
				this->_size = temp_size;
			}

			// general static functions to manipulate nodes.
			static node_pointer min_node(node_pointer parent) {
				if (parent->left == NULL) return parent;
				return min_node(parent->left);
			}

			static const_node_pointer min_node(const_node_pointer parent) {
				if (parent->left == NULL) return parent;
				return min_node(parent->left);
			}

			static node_pointer max_node(node_pointer parent) {
				if (parent->right == NULL) return parent;
				return max_node(parent->right);
			}

			static const_node_pointer max_node(const_node_pointer parent) {
				if (parent->right == NULL) return parent;
				return max_node(parent->right);
			}

			static node_pointer next_node(node_pointer node) {
				key_compare	_compare = key_compare();

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

			static const_node_pointer next_node(const_node_pointer node) {
				key_compare	_compare = key_compare();

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
				key_compare	_compare = key_compare();
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

			static const_node_pointer prev_node(const_node_pointer node) {
				key_compare	_compare = key_compare();
	
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

			// helper functions.
			void printTree() {
				std::cout << std::endl;
				_printTree(_root, "", false);
			}

	};

} // namespace ft

#endif // __AVL_TREE_HPP__