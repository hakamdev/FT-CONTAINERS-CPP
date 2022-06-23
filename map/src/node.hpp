/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:21:45 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/23 02:59:02 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __NODE_HPP__
# define __NODE_HPP__

# include <memory>
# include <utility>
# include <functional>

namespace ft
{
	template < typename Key,                                     		// map::key_type
           typename T,                                       			// map::mapped_type
           typename Alloc = std::allocator<std::pair<const Key,T> >     // map::allocator_type
           >
	struct node {
			

			public:
				// Memeber types
				typedef std::pair<Key,T>		value_type;
				typedef Key						key_type;
				typedef T						mapped_type;
				typedef Alloc					allocator_type;
				typedef node<Key, T, Alloc>		node_type;
				typedef typename allocator_type::pointer			pointer;

			private:
				allocator_type		_alloc;

			public:
				// Member variables
				pointer				content;
				node_type			*left;
				node_type			*right;
				node_type			*parent;
				int					height;

				node(const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
						_alloc(alloc), parent(NULL), left(NULL), right(NULL), height(0) {
					this->content =	this->_alloc.allocate(1);
					this->_alloc.construct(content, val);
				}

				node(const node_type& parent, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
						_alloc(alloc), parent(parent), left(NULL), right(NULL), height(0) {
					this->content =	this->_alloc.allocate(1);
					this->_alloc.construct(content, val);
				}

				node(const node_type& other) {
					*this = other;
				}

				node& operator = (const node_type& other) {
					this->parent = other.parent;
					this->content = other.content;
					this->left = other.left;
					this->right = other.right;
					this->height_factor = other.height_factor;
					this->_alloc = other._alloc;
				}

				~node() {
					//this->_alloc.destroy(content);
					//this->_alloc.deallocate(content, 1);
				}

				void set_content(const value_type& val) {
				if (content != NULL) {
					this->_alloc.destroy(content);
				} else {
					this->content =	this->_alloc.allocate(1);
				}
				this->_alloc.construct(content, val);
			}

	};

} // namespace ft

#endif // __NODE_HPP__