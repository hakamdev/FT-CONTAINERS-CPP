/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 23:05:18 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/12 23:30:29 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STACK_HPP__
# define __STACK_HPP__

#include "../../vector/src/vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack {

		public:
			typedef T											value_type;
			typedef Container									container_type;
			typedef size_t										size_type;

		protected:
			ft::vector<T> _c;

		public:
			explicit stack (const container_type& ctnr = container_type()) {
				// TODO:
			}

			bool empty() const {
				return _c.empty();
			}

			size_type size() const {
				return _c.size();
			}

			value_type& top() {
				return _c.back();
			}
		
			const value_type& top() const {
				return _c.back();
			}

			void push (const value_type& val) {
				_c.push_back(val);
			}

			void pop() {
				_c.pop_back();
			}

			friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
			friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
			friend bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
			friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
			friend bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
			friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	};

	template <class T, class Container>
  	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs._c == rhs._c; }

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs._c != rhs._c; }

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs._c < rhs._c; }

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs._c <= rhs._c; }

	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs._c > rhs._c; }

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs._c >= rhs._c; }

} // namespace ft

#endif
