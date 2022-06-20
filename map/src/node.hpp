/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:21:45 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/20 22:29:15 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __NODE_HPP__
# define __NODE_HPP__

# include <memory>
# include <utility>
# include <functional>

namespace ft
{
	template <typename T, typename Alloc>
	struct node {
		// Memeber types
		typedef T		value_type;
		typedef Alloc	allocator_type;

		private:
			allocator_type		_alloc;
			
		public:
		// Member variables
			value_type			*content;
			node<T, Alloc>		*left;
			node<T, Alloc>		*right;
			node<T, Alloc>		*parent;
			int					height_factor;

			node(const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
				_alloc(alloc), parent(NULL), left(NULL), right(NULL), height_factor(-1) {
				this->content =	alloc.allocate(1);
				this->_alloc.construct(content, val);
			}

			node(const node<T, Alloc>& parent, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
				_alloc(alloc), parent(parent), left(NULL), right(NULL), height_factor(-1) {
				this->content =	alloc.allocate(1);
				this->_alloc.construct(content, val);
			}

			node(const node<T, Alloc>& other) {
				*this = other;
			}

			node& operator = (const node<T, Alloc>& other) {
				parent = other.parent;
				content = other.content;
				left = other.left;
				right = other.right;
				height_factor = other.height_factor;
				_alloc = other._alloc;
			}

			~node() {
				this->_alloc.destroy(content);
				this->_alloc.deallocate(content, 1);
			}
	};

} // namespace ft

#endif // __NODE_HPP__