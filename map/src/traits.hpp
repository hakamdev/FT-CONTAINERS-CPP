/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traits.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehakam <ehakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:47:05 by ehakam            #+#    #+#             */
/*   Updated: 2022/06/27 05:24:22 by ehakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __TRAITS_HPP__
# define __TRAITS_HPP__

# include <iterator>

namespace ft
{
	// for class iterators
	template <typename Iter>
	struct iterator_traits
	{
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
	};

	// pointers specialization
	template <typename Ptr>
	struct iterator_traits<Ptr*>
	{
		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef Ptr								value_type;
		typedef Ptr*							pointer;
		typedef Ptr&							reference;
	};

	// const pointers specialization
	template <typename Ptr>
	struct iterator_traits<const Ptr*>
	{
		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef Ptr								value_type;
		typedef const Ptr*						pointer;
		typedef const Ptr&						reference;
	};

	// general template
	template< bool Cond, typename T = void >
	struct enable_if;

	// true specialization
	template< typename T >
	struct enable_if<true, T> {
		typedef T type;
	};

	// general template for all non-integral types
	template< typename T >
	struct is_integral {
		static const bool value = false;
	};

	// integral specializations
	template<>
	struct is_integral<int> { static const bool value = true; };
	template<>
	struct is_integral<long> { static const bool value = true; };
	template<>
	struct is_integral<short> { static const bool value = true; };
	template<>
	struct is_integral<char> { static const bool value = true; };
	template<>
	struct is_integral<bool> { static const bool value = true; };
	template<>
	struct is_integral<wchar_t> { static const bool value = true; };
	template<>
	struct is_integral<long long> { static const bool value = true; };
	template<>
	struct is_integral<unsigned char> { static const bool value = true; };
	template<>
	struct is_integral<unsigned short> { static const bool value = true; };
	template<>
	struct is_integral<unsigned int> { static const bool value = true; };
	template<>
	struct is_integral<unsigned long> { static const bool value = true; };
	template<>
	struct is_integral<unsigned long long> { static const bool value = true; };

} // namespace ft

#endif // __TRAITS_HPP__