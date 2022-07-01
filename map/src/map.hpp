/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:45:19 by ehakam            #+#    #+#             */
/*   Updated: 2022/07/01 01:06:23 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_HPP__
# define __MAP_HPP__

# include <memory>
# include <utility>
# include <functional>
# include "bidirectional_iterator.hpp"
# include "reverse_bidirectional_iterator.hpp"
# include "avl_tree.hpp"

namespace ft
{
	template < typename Key,                                     		// map::key_type
           typename T,                                       			// map::mapped_type
           typename Compare = std::less<Key>,                     		// map::key_compare
           typename Alloc = std::allocator<std::pair<const Key,T> >    // map::allocator_type
           >
	class map {
		public:
			typedef std::pair<const Key, T> 					value_type;
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef Compare										key_compare;
			typedef Alloc										allocator_type;
			typedef ft::avl_tree<Key, T, Compare, Alloc>		tree;
			typedef typename allocator_type::reference			reference;
            typedef typename allocator_type::const_reference	const_reference;
            typedef typename allocator_type::pointer			pointer;
            typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename tree::node_pointer					node_pointer;
			typedef ft::bidir_iterator<tree>   					iterator;
			typedef ft::bidir_iterator<const tree> 				const_iterator;
			typedef ft::rbidir_iterator<iterator>				reverse_iterator;
			typedef ft::rbidir_iterator<const_iterator>			const_reverse_iterator;
			typedef size_t										size_type;

			class value_compare;

		private:
			allocator_type		_alloc;
			tree				_tree;
			key_compare			_comp;
			value_compare		_v_comp;

		public:
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: _comp(comp), _alloc(alloc) { }
	
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: _comp(comp), _alloc(alloc) {
				insert<InputIterator>(first, last);
			}

			map (const map& x) {
				*this = x;
			}

			map& operator = (const map& x) {
				_comp = x._comp;
				_alloc = x._alloc;
				_tree = x._tree;
			}

			~map() { }

			iterator begin() {
				return iterator(_tree.min_node(), _tree.root());
			}

			const_iterator begin() const {
				return const_iterator(_tree.min_node(), _tree.root());
			}

			iterator end() {
				return iterator(NULL, _tree.root());
			}

			const_iterator end() const {
				return const_iterator(NULL, _tree.root());
			}

			reverse_iterator rbegin() {
				return reverse_iterator(end());
			}

			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(end());
			}

			reverse_iterator rend() {
				return reverse_iterator(begin());
			}

			const_reverse_iterator rend() const {
				return const_reverse_iterator(begin());
			}

			bool empty() const {
				return _tree.empty();
			}
			
			size_type size() const {
				return _tree.size();
			}
			
			size_type max_size() const {
				return this->_alloc.max_size();
			}
			
			mapped_type& operator[] (const key_type& k) {
				node_pointer _p = _tree.find(k);
				if (_p == NULL) {
					_p = _tree.insert(std::make_pair(k, mapped_type()));
				}
				return _p->content->second;
			}

			// TMEPORARY
			iterator findNode (const key_type& k) {
				node_pointer _p = _tree.find(k);
				return iterator(_p, _tree.root());
			}

			allocator_type get_allocator() const {
				return _alloc;
			}

			std::pair<iterator, bool> insert (const value_type& val) {
				size_type old_size = _tree.size();
				node_pointer _p = _tree.insert(val);
				return std::make_pair(iterator(_p, _tree.root()), _tree.size() > old_size);
			}

			iterator insert (iterator position, const value_type& val) {
				node_pointer p = NULL;
				if (position.base() == position.past_end()
					|| position.base()->parent == NULL) {
					p = _tree.insert(val);
				} else {
					p = _tree.insert(position.base(), val);
				}
				return iterator(p, _tree.root());
			}

			// Test
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last) {
				while (first != last) {
					insert(*(first++));
				}
			}

			// Test
			void erase (iterator position) {
				if (position.base() == NULL || position.base == position.past_end()) {
					_tree.delete_node(NULL);
				} else {
					_tree.delete_node(position.base());
				}
			}

			size_type erase (const key_type& k) {
				return _tree.delete_node(k);
			}

			// Test
     		void erase (iterator first, iterator last) {
				while (first != last) {
					erase(*(first++));
				}
			}

			// Test
			void swap (map& x) {
				// allocator_type	_alloc;
				// tree				_tree;
				// key_compare		_comp;
				tree& temp_tree = x._tree.get_reference();
				allocator_type& temp_alloc = x._alloc;
				key_compare& temp_comp = x._comp;

				x._tree = this->_tree.get_reference();
				x._alloc = this->_alloc;
				x._comp = this->_comp;

				this->_tree = temp_tree;
				this->_alloc = temp_alloc;
				this->_comp = temp_comp;
			}

			// Test
			void clear() {
				// TODO:
				while (!empty()) {
					node_pointer p = _tree.max_node();
					_tree.delete_node(p);
				}
			}

			key_compare key_comp() const {
				return _comp;
			}

			value_compare value_comp() const {
				return _v_comp;
			}

			// Test
			iterator find (const key_type& k) {
				node_pointer found = _tree.find(k);
				return iterator(found, _tree.root());
			}

			// Test
			const_iterator find (const key_type& k) const {
				node_pointer found = _tree.find(k);
				return const_iterator(found, _tree.root());
			}

			// Test
			size_type count (const key_type& k) const {
				node_pointer found = _tree.find(k);
				return (found != NULL ? 1 : 0);
			}

			// Test
			iterator lower_bound (const key_type& k) {
				node_pointer lbp = _tree.lower_bound(k);
				return iterator(lbp, _tree.root());
			}

			// Test
			const_iterator lower_bound (const key_type& k) const {
				node_pointer lbp = _tree.lower_bound(k);
				return const_iterator(lbp, _tree.root());
			}

			// Test
			iterator upper_bound (const key_type& k) {
				node_pointer lbp = _tree.upper_bound(k);
				return iterator(lbp, _tree.root());
			}

			// Test
			const_iterator upper_bound (const key_type& k) const {
				node_pointer lbp = _tree.upper_bound(k);
				return const_iterator(lbp, _tree.root());
			}

			// Test
			std::pair<const_iterator, const_iterator> equal_range (const key_type& k) const {
				return std::make_pair(lower_bound(k), upper_bound(k));
			}

			// Test
			std::pair<iterator, iterator> equal_range (const key_type& k) {
				return std::make_pair(lower_bound(k), upper_bound(k));
			}

			//////
			void print() {
				_tree.printTree();
			}
	};

	template <class Key, class T, class Compare, class Alloc>
	class map<Key, T, Compare, Alloc>::value_compare : binary_function<value_type, value_type, bool>
	{
		friend class map;
		protected:
			Compare _comp;
			value_compare (Compare c) : _comp(c) {}
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const
			{
				return _comp(x.first, y.first);
			}
	};

	template <class Key, class T, class Compare, class Alloc>
  	bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

	template <class Key, class T, class Compare, class Alloc>
	bool operator<  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );
		
	template <class Key, class T, class Compare, class Alloc>
	bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );
		
	template <class Key, class T, class Compare, class Alloc>
	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

	template <class Key, class T, class Compare, class Alloc>
  	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y);

} // namespace ft

#endif // __MAP_HPP__
