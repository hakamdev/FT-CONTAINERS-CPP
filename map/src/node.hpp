/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:21:45 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/25 07:07:43 by ehakam           ###   ########.fr       */
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
           typename Alloc = std::allocator<std::pair<const Key, T> >     // map::allocator_type
           >
	struct node {
		public:
			// Memeber types
			typedef std::pair<const Key, T>				value_type;
			typedef Key									key_type;
			typedef T									mapped_type;
			typedef Alloc								allocator_type;
			typedef node<const Key, T, Alloc>			node_type;
			typedef typename allocator_type::pointer	pointer;
			typedef typename allocator_type::reference	reference;

		private:
			allocator_type		_alloc;

		public:
			// Member variables
			pointer				content;
			node_type			*left;
			node_type			*right;
			node_type			*parent;
			int					height;

			explicit node(const value_type& val, const allocator_type& alloc = allocator_type()) :
					_alloc(alloc), parent(NULL), left(NULL), right(NULL), height(0) {
				this->content =	this->_alloc.allocate(1);
				this->_alloc.construct(content, val);
			}

			explicit node(const node_type& other) {
				*this = other;
			}

			node& operator = (const node_type& other) {
				this->content =	this->_alloc.allocate(1);
				this->_alloc.construct(content, *other.content);
				this->parent = other.parent;
				this->left = other.left;
				this->right = other.right;
				this->height = other.height;
				this->_alloc = other._alloc;
				return *this;
			}

			~node() {
				this->_alloc.destroy(content);
				this->_alloc.deallocate(content, 1);
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