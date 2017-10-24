//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include <array>
#include <cmath>
#include <numeric>
#include <iostream>
#include <algorithm>

#include "owl/utils/linear_index.hpp"
#include "owl/utils/iterator_range.hpp"
#include "owl/utils/step_iterator.hpp"
#include "owl/utils/container_utils.hpp"

namespace owl
{
  namespace math
  {
    namespace detail
    {
      
      template <typename T, std::size_t N>
      constexpr T delta(std::size_t i)
      {
          return i  == N ? (T)1 : 0;
      }
  
      template <typename T>
      constexpr T zero(std::size_t i)
      {
          return 0;
      }
  
      template <typename T>
      constexpr T one(std::size_t i)
      {
          return (T)1;
      }

      template <typename T, std::size_t N>
      constexpr T eye(std::size_t i)
      {
          return (i % (N+1)) == 0 ? (T)1 : 0;
      }
    }
  
    template <typename Scalar, std::size_t Rows, std::size_t Cols>
    class matrix
    {
    public:
    
    using container_type = std::array<Scalar,Rows*Cols>;
    using size_type = typename container_type::size_type;
    using difference_type = typename container_type::difference_type;
    using iterator = typename container_type::iterator;
    using const_iterator = typename container_type::const_iterator;
    using reverse_iterator = typename container_type::reverse_iterator;
    using const_reverse_iterator = typename container_type::const_reverse_iterator;
    using value_type = typename container_type::value_type;
    using reference = typename container_type::reference;
    using const_reference = typename container_type::const_reference;
    using pointer = typename container_type::pointer;
    using const_pointer = typename container_type::const_pointer;
    
    using row_iterator = utils::step_iterator<iterator,Rows>;
    using const_row_iterator =  utils::step_iterator<const_iterator,Rows>;
    
    using column_iterator = iterator;
    using const_column_iterator = const_iterator;
    
    using row_range = owl::utils::iterator_range<row_iterator>;
    using const_row_range = owl::utils::iterator_range<const_row_iterator>;
    
    using column_range = owl::utils::iterator_range<column_iterator>;
    using const_column_range = owl::utils::iterator_range<const_column_iterator>;
    
    template <typename S1, typename S2 = value_type>
    using enable_if_scalar_t = std::enable_if_t<std::is_convertible<S1,S2>::value >;
    
    constexpr static size_type size()
    {
        return Rows*Cols;
    }
    
    constexpr static size_type ncols()
    {
        return Cols;
    }
    
    constexpr static size_type nrows()
    {
        return Rows;
    }
    
    constexpr static bool is_square()
    {
        return Rows == Cols;
    }
   
    constexpr static bool is_square(std::size_t n)
    {
        return Rows == n && Cols == n;
    }
    
    constexpr static bool is_vector()
    {
        return Rows == 1 || Cols == 1;
    }
    
    constexpr static bool is_vector(std::size_t n)
    {
        return (Rows == 1 && Cols == n) || (Rows == n && Cols == 1);
    }
    
    constexpr static size_type linear_index(size_type row_index, size_type column_index)
    {
        return utils::linear_index<Rows,Cols>(row_index, column_index);
    }
    
    template <size_t I, typename = std::enable_if_t<(I < size()) && is_vector()> >
    static constexpr matrix ident()
    {
      return matrix{owl::utils::make_array<size()>(detail::delta<Scalar,I>)};
    }
    
    template <bool Dummy = true, typename = std::enable_if_t<Dummy && is_vector() && (size() > 0)>  >
    static constexpr matrix identity_x()
    {
        return ident<0>();
    }
    
    template <bool Dummy = true, typename = std::enable_if_t<Dummy && is_vector() && (size() > 1)>  >
    static constexpr matrix identity_y()
    {
        return ident<1>();
    }
    
    template <bool Dummy = true, typename = std::enable_if_t<Dummy && is_vector() && (size() > 2)>  >
    static constexpr matrix identity_z()
    {
        return ident<2>();
    }
    
    template <bool Dummy = true, typename = std::enable_if_t<Dummy && is_vector() && (size() > 3)>  >
    static constexpr matrix identity_w()
    {
        return ident<3>();
    }
    
    static constexpr matrix zero()
    {
      return matrix{owl::utils::make_array<size()>(detail::zero<Scalar>)};
    }
    
    static constexpr matrix one()
    {
        return matrix{owl::utils::make_array<size()>(detail::one<Scalar>)};
    }
    
     static constexpr matrix identity()
    {
        return matrix{owl::utils::make_array<size()>(detail::eye<Scalar,Rows>)};
    }
    
    //iterator interface
    
    iterator begin() { return _data.begin(); }
    iterator end() { return _data.end(); }
    
    const_iterator begin() const { return _data.begin(); }
    const_iterator end() const { return _data.end(); }
    
    const_iterator cbegin() const { return _data.cbegin(); }
    const_iterator cend() const { return _data.cend(); }
    
    reverse_iterator rbegin() { return _data.rbegin(); }
    reverse_iterator rend() { return _data.rend(); }
    
    const_reverse_iterator rbegin() const { return _data.crbegin(); }
    const_reverse_iterator rend() const { return _data.crend(); }
    
    const_reverse_iterator crbegin() const { return _data.crbegin(); }
    const_reverse_iterator crend() const { return _data.crend(); }
    

    iterator iterator_at(size_type row_index, size_type column_index)
    {
        return begin() + linear_index(row_index, column_index);
    }
    
    const_iterator iterator_at(size_type row_index, size_type column_index) const
    {
        return cbegin() + linear_index(row_index,column_index);
    }
    
    row_iterator row_begin(size_type row_index)
    {
        return row_iterator{iterator_at(row_index,0)};
    }
    
    row_iterator row_end(size_type row_index)
    {
        return row_iterator{iterator_at(row_index,ncols())};
    }
    
    const_row_iterator row_begin(size_type r) const
    {
        return const_row_iterator{iterator_at(r,0)};
    }
    
    const_row_iterator row_end(size_type r) const
    {
        return const_row_iterator{iterator_at(r,ncols())};
    }
    
    const_row_iterator row_cbegin(size_type r) const
    {
        return const_row_iterator{iterator_at(r,0)};
    }
    
    const_row_iterator row_cend(size_type r) const
    {
        return const_row_iterator{iterator_at(r,ncols())};
    }
    
    column_iterator column_begin(size_type c)
    {
        return column_iterator{iterator_at(0,c)};
    }
    
    row_iterator column_end(size_type c)
    {
        return column_iterator{iterator_at(nrows(),c)};
    }
    
    const_column_iterator column_begin(size_type c) const
    {
        return const_column_iterator{iterator_at(0,c)};
    }
    
    const_column_iterator column_end(size_type c) const
    {
        return const_column_iterator{iterator_at(nrows(),c)};
    }
    
    const_column_iterator column_cbegin(size_type c) const
    {
        return const_column_iterator{iterator_at(0,c)};
    }
    
    const_column_iterator column_cend(size_type c) const
    {
        return const_column_iterator{iterator_at(nrows(),c)};
    }
    
    // range interface
    row_range row(size_type r)
    {
        return owl::utils::make_iterator_range(row_begin(r), row_end(r));
    }
    
    const_row_range row(size_type r) const
    {
        return owl::utils::make_iterator_range(row_begin(r), row_end(r));
    }
    
    column_range column(size_type c)
    {
        return owl::utils::make_iterator_range(column_begin(c), column_end(c));
    }
    
    const_column_range column(size_type c) const
    {
        return owl::utils::make_iterator_range(column_begin(c), column_end(c));
    }
    
    //constructors
    
    constexpr matrix() = default;
    
    matrix(std::initializer_list<Scalar> list)
    {
        std::copy(list.begin(),list.end(),_data.begin());
    }

    
    constexpr matrix(std::array<Scalar,Rows*Cols> arr)
        : _data{arr}
    {
    }
    
    template<typename S, typename... Args>
    explicit matrix(S&& a, Args&&... args)
        : _data{static_cast<value_type>(std::forward<S>(a)),static_cast<value_type>(std::forward<Args>(args))...}
    {
        static_assert(sizeof...(Args) == 0 || sizeof...(Args)+1 == size(), "incorrect number of arguments");
    }
    
    matrix(matrix& other) = default;
    
    matrix(const matrix& other) = default;
    
    matrix(matrix&& other) = default;
    
    template <typename S2>
    matrix(const matrix<S2,Rows,Cols>& other)
    {
        for(size_type i = 0; i < Rows;++i)
            for(size_type j = 0; j < Cols; ++j)
                operator()(i,j) = other(i,j);
    }
    
    //assignment operators
    
    matrix& operator=(const matrix& other) = default;
    
    matrix& operator=(matrix&& other) = default;
    
    template <typename S2>
    matrix& operator=(const matrix<S2,Rows,Cols>& other)
    {
        for(size_type i = 0; i < Rows;++i)
            for(size_type j = 0; j < Cols; ++j)
                operator()(i,j) = other(i,j);
        return *this;
    }
    
    //component accessors
     template<typename M = matrix,
        typename = std::enable_if_t<M::is_vector() && (size() > 0) > >
    value_type& x()
    {
        return _data[0];
    }
    
    template<typename M = matrix,
        typename = std::enable_if_t<M::is_vector() && (size() > 0) > >
    const value_type& x() const
    {
    return _data[0];
    }
    
    template<typename M = matrix,
        typename = std::enable_if_t<M::is_vector() && (size() > 1) > >
    value_type& y()
    {
        return _data[1];
    }
    
    template<typename M = matrix,
        typename = std::enable_if_t<M::is_vector() && (size() > 1) > >
    const value_type& y() const
    {
        return _data[1];
    }
    
    template<typename M = matrix,
    typename = std::enable_if_t<M::is_vector() && (size() > 2) > >
    value_type& z()
    {
        return _data[2];
    }
    
    template<typename M = matrix,
    typename = std::enable_if_t<M::is_vector() && (size() > 2) > >
    const value_type& z() const
    {
        return _data[2];
    }
    
    template<typename M = matrix,
    typename = std::enable_if_t<M::is_vector() && (size() > 3) > >
    value_type& w()
    {
        return _data[3];
    }
    
    template<typename M = matrix,
    typename = std::enable_if_t<M::is_vector() && (size() > 3) > >
    const value_type& w() const
    {
        return _data[3];
    }
    
    reference operator[](size_type pos)
    {
        return _data[pos];
    }
    
    const_reference operator[](size_type pos) const
    {
        return _data[pos];
    }
    
    reference operator()(size_type pos)
    {
    return _data[pos];
    }
    
    const_reference operator()(size_type pos) const
    {
    return _data[pos];
    }
    
    reference operator()(size_type r, size_type c)
    {
        return _data[linear_index(r,c)];
    }
    
    const_reference operator()(size_type r, size_type c) const
    {
        return _data[linear_index(r,c)];
    }
    
    //comparison operators
    
    template< typename  S, std::size_t N, std::size_t M>
    friend bool operator==( const matrix<S,N,M>& lhs, const matrix<S,N,M>& rhs )
    {
        return lhs._data == rhs._data;
    }
    
    template< typename  S, std::size_t N, std::size_t M>
    friend bool operator!=( const matrix<S,N,M>& lhs, const matrix<S,N,M>& rhs )
    {
        return lhs._data != rhs._data;
    }
    
    template< typename  S, std::size_t N, std::size_t M>
    friend bool operator<( const matrix<S,N,M>& lhs, const matrix<S,N,M>& rhs )
    {
        return lhs._data < rhs._data;
    }
    
    template< typename  S, std::size_t N, std::size_t M>
    friend bool operator<=( const matrix<S,N,M>& lhs, const matrix<S,N,M>& rhs )
    {
        return lhs._data <= rhs._data;
    }
    
    template< typename  S, std::size_t N, std::size_t M>
    friend bool operator>( const matrix<S,N,M>& lhs, const matrix<S,N,M>& rhs )
    {
        return lhs._data > rhs._data;
    }
    
    template< typename  S, std::size_t N, std::size_t M, typename T>
    friend bool operator>=( const matrix<S,N,M>& lhs, const matrix<S,N,M>& rhs )
    {
        return lhs._data >= rhs._data;
    }
    
    constexpr static bool empty()
    {
        return container_type::empty();
    }
    
    pointer data()
    {
        return _data.data();
    }
    
    const_pointer data() const
    {
        return _data.data();
    }
    
    template <typename S, typename = enable_if_scalar_t<S> >
    matrix& operator*=(S&& s)
    {
        for(auto& elem : _data)
            elem *= s;
        return *this;
    }
    
    template <typename S,typename = enable_if_scalar_t<S> >
    matrix operator*(S&& s)
    {
        auto ans = *this;
        ans *= s;
        return ans;
    }
    
    template <typename S2>
    matrix& operator+=(const matrix<S2,Rows,Cols>& other)
    {
        std::transform (begin(), end(), other.begin(), begin(), std::plus<value_type>());
        return *this;
    }
    
    template< typename  S, typename T, std::size_t N, std::size_t M>
    friend matrix operator+( matrix<S,N,M> lhs, const matrix<T,N,M>& rhs )
    {
        lhs += rhs;
        return lhs;
    }
    
    template <typename S2>
    matrix& operator-=(const matrix<S2,Rows,Cols>& other)
    {
        std::transform (begin(), end(), other.begin(), begin(), std::minus<value_type>());
        return *this;
    }
    
    template< typename  S, typename T, std::size_t N, std::size_t M>
    friend matrix operator-( matrix<S,N,M> lhs, const matrix<T,N,M>& rhs )
    {
        lhs -= rhs;
        return lhs;
    }
    
    matrix operator-() const
    {
        return *this * value_type{-1};
    }
    
    matrix operator+() const
    {
     return *this;
    }
    
    template <typename S2, std::size_t Cols2>
    matrix<decltype(std::declval<Scalar>()*std::declval<S2>()),Rows,Cols2>
    operator*(const matrix<S2,Cols,Cols2>& other) const
    {
        matrix<decltype(std::declval<Scalar>()*std::declval<S2>()),Rows,Cols2> prod{};
    
        for(size_type i = 0; i < Rows;++i)
            for(size_type k = 0; k < Cols2; ++k)
                for(size_type j = 0; j < Cols; ++j)
                    prod(i,k) += operator()(i,j) * other(j,k);
    
        return prod;
    }
    
    template<typename S1, typename  S2, std::size_t N, std::size_t M,
        typename = enable_if_scalar_t< S1,S2> >
    friend matrix<S2,N,M> operator*( S1&& lhs, matrix<S2,N,M> rhs )
    {
        return rhs *= lhs;
    }
    
    template <typename S, typename = enable_if_scalar_t<S> >
    matrix& operator/=(S&& s)
    {
        for(auto& elem: _data)
            elem /= s;
        return *this;
    }
    
    template <typename S, typename = enable_if_scalar_t<S> >
    matrix operator/(S&& s)
    {
        auto ans = *this;
        ans /= s;
        return ans;
    }
    
    template<typename M = matrix, typename = std::enable_if_t<M::is_vector()> >
    value_type sqr_length() const
    {
        return std::inner_product(cbegin(),cend(),cbegin(),value_type{});
    }
    
    template<typename M = matrix, typename = std::enable_if_t<M::is_vector()> >
    value_type length() const
    {
        return std::sqrt(sqr_length());
    }
    
    template<typename M = matrix, typename = std::enable_if_t<M::is_vector()> >
    void normalize()
    {
        value_type l = length();
        if(l != 0)
        {
            l = 1.0/l;
            *this *= l;
        }
    }
    template<typename M = matrix, typename = std::enable_if_t<M::is_vector()> >
    matrix  normalized() const
    {
        value_type l = length();
        if(l != 0)
        {
            l = (value_type)1/l;
            *this *= l;
        }
    }
    
    matrix<Scalar,Cols,Rows> transposed() const
    {
        matrix<Scalar,Cols,Rows> ans;
        for(size_type i = 0; i < Rows;++i)
            for(size_type j = 0; j < Cols; ++j)
                ans(j,i) = operator()(i,j);
    
        return ans;
    }
    
    private:
        container_type _data;
    
    };
  
    template <typename Scalar, std::size_t Dim>
    using square_matrix = matrix<Scalar, Dim, Dim>;
  
    template <typename Scalar, std::size_t Dim>
    using vector = matrix<Scalar, Dim,1>;
  
    template <typename Scalar, std::size_t Dim>
    using row_vector = matrix<Scalar,1, Dim>;
  
    template <typename Scalar>
    using vector2 = vector<Scalar, 2>;
  
    template <typename Scalar>
    using vector3 = vector<Scalar, 3>;
  
    template <typename Scalar>
    using vector4 = vector<Scalar, 4>;
  
    using vector2f = vector2<float>;
    using vector3f = vector3<float>;
    using vector4f = vector4<float>;
  
    using matrix22f = square_matrix<float,2>;
  
    using matrix23f = matrix<float,2,3>;
    using matrix32f = matrix<float,3,2>;
  
    using matrix33f = square_matrix<float,3>;

    using matrix34f = matrix<float,3,4>;
    using matrix43f = matrix<float,4,3>;
  
  
    using matrix44f = square_matrix<float,4>;


    //implementation
  
    template< typename  S, std::size_t N, std::size_t M,
    typename = std::enable_if_t< matrix<S,N,M>::is_vector()> >
    matrix<S,N,M> normalize(matrix<S,N,M>& v)
    {
        v.normalize();
        return v;
    }
  
    template< typename  S, std::size_t N, std::size_t M,
        typename = std::enable_if_t< matrix<S,N,M>::is_vector()> >
    S sqr_length(const matrix<S,N,M>& v)
    {
        return v.sqr_length();
    }
  
  
    template< typename  S, std::size_t N, std::size_t M,
        typename = std::enable_if_t< matrix<S,N,M>::is_vector()> >
    S length(const matrix<S,N,M>& v)
    {
        return v.length();
    }
  
  
    template< typename  S, std::size_t N, std::size_t M,
        typename = std::enable_if_t< matrix<S,N,M>::is_vector()> >
    S dot( const matrix<S,N,M>& lhs, const matrix<S,N,M>& rhs)
    {
        return std::inner_product(lhs.cbegin(),lhs.cend(),rhs.cbegin(),S{0});
    }
  
    template< typename  S, std::size_t N, std::size_t M>
    matrix<S,M,N> transpose(const matrix<S,N,M>& rhs)
    {
        using size_type = typename matrix<S,M,N>::size_type;
        matrix<S,M,N> ans;
        for(size_type i = 0; i < N;++i)
            for(size_type j = 0; j < M; ++j)
                ans(j,i) = operator()(i,j);
    
        return ans;
    }
  
    template< typename  S, std::size_t N, std::size_t M,
        typename = std::enable_if_t< matrix<S,N,M>::is_vector(3)> >
    matrix<S,N,M> cross( const matrix<S,N,M>& lhs, const matrix<S,N,M>& rhs)
    {
        return matrix<S,N,M>{lhs.y()*rhs.z() - lhs.z()*rhs.y(),
                lhs.z()*rhs.x() - lhs.x()*rhs.z(),
                lhs.x()*rhs.y() - lhs.y()*rhs.x()};
    }
  
    template <typename S, std::size_t N, std::size_t M>
    std::ostream& operator<<(std::ostream& out, const matrix<S,N,M>& m)
    {
        for(std::size_t i = 0; i < N; ++i)
            for(std::size_t j = 0; j < M; ++j)
                out << m(i,j) << ((j == M-1) ? "\n" : " ");
        return out;
    }
  
    template <typename S, std::size_t M, std::size_t N>
    std::istream& operator>>(std::istream& in,  matrix<S,M,N>& m)
    {
        for(std::size_t i = 0; i < M; ++i)
        {
            for(std::size_t j = 0; j < N; ++j)
                in >> m(i,j);
        
        }
        return in;
    }
  
  
    ///determinant of 2x2 matrix
    template <typename S>
    S det(const square_matrix<S,2>& m)
    {
        return m(0,0)*m(1,1) - m(0,1)*m(1,0);
    }
  
    ///determinant of 3x3 matrix
    template <typename S>
    S det(const square_matrix<S,3>& m)
    {
        return m(0,0)*m(1,1)*m(2,2)
        +m(0,1)*m(1,2)*m(2,0)
        +m(0,2)*m(1,0)*m(2,1)
        -m(0,0)*m(1,2)*m(2,1)
        -m(0,1)*m(1,0)*m(2,2)
        -m(0,2)*m(1,1)*m(2,0);
    }
  
    ///determinant of 4x4 matrix
    template <typename S>
    S det(const square_matrix<S,4>& m)
    {
        return m(0,0)*m(1,1)*m(2,2)*m(3,3) - m(0,0)*m(1,1)*m(3,2)*m(2,3) - m(0,0)*m(1,2)*m(2,1)*m(3,3) + m(0,0)*m(1,2)*m(2,3)*m(3,1) +
        m(0,0)*m(1,3)*m(2,1)*m(3,2) + m(0,0)*m(1,3)*m(3,1)*m(2,2) - m(0,1)*m(1,0)*m(2,2)*m(3,3) + m(0,1)*m(1,0)*m(3,2)*m(2,3) +
        m(0,1)*m(1,2)*m(2,0)*m(3,3) - m(0,1)*m(1,2)*m(3,0)*m(2,3) - m(0,1)*m(1,3)*m(2,0)*m(3,2) + m(0,1)*m(1,3)*m(3,0)*m(2,2) +
        m(0,2)*m(1,0)*m(2,1)*m(3,3) - m(0,2)*m(1,0)*m(3,1)*m(2,3) - m(0,2)*m(1,1)*m(2,0)*m(3,2) + m(0,2)*m(1,1)*m(3,0)*m(2,2) +
        m(0,2)*m(1,3)*m(2,0)*m(3,1) - m(0,2)*m(1,3)*m(3,0)*m(2,1) - m(0,3)*m(1,0)*m(2,1)*m(3,2) + m(0,3)*m(1,0)*m(3,1)*m(2,2) +
        m(0,3)*m(1,1)*m(2,0)*m(3,2) - m(0,3)*m(1,1)*m(3,0)*m(2,2) - m(0,3)*m(1,2)*m(2,0)*m(3,1) + m(0,3)*m(1,2)*m(3,0)*m(2,1);
    }
  
  
    ///compute inverse of 2x2 matrix
    template <typename S>
    square_matrix<S,2> invert(const square_matrix<S,2>& m)
    {
        S t4 = (S)1.0 / (-m(0,0) * m(1,1) + m(0,1) * m(1,0));
        return{ -m(1,1) * t4, m(1,0) * t4, m(0,1) * t4, -m(0,0) * t4 };
    }
  
    ///compute inverse of 3x3 matrix
    template <typename T>
    square_matrix<T,3> invert(const square_matrix<T,3>& m)
    {
    
        T t4 = m(2,0) * m(0,1);
        T t6 = m(2,0) * m(0,2);
        T t8 = m(1,0) * m(0,1);
        T t10 = m(1,0) * m(0,2);
        T t12 = m(0,0) * m(1,1);
        T t14 = m(0,0) * m(1,2);
        T t17 = (T)1.0 / (t4 * m(1,2) - t6 * m(1,1) - t8 * m(2,2) + t10 * m(2,1) + t12 * m(2,2) - t14 * m(2,1));
        return square_matrix<T,3>{ (m(1,1) * m(2,2) - m(1,2) * m(2,1)) * t17,
                -(-m(2,0) * m(1,2) + m(1,0) * m(2,2)) * t17,
                (-m(2,0) * m(1,1) + m(1,0) * m(2,1)) * t17,
                -(m(0,1) * m(2,2) - m(0,2) * m(2,1)) * t17,
                (-t6 + m(0,0) * m(2,2)) * t17,
                -(-t4 + m(0,0) * m(2,1)) * t17,
                (m(0,1) * m(1,2) - m(0,2) * m(1,1)) * t17,
                -(-t10 + t14) * t17,
                (-t8 + t12) * t17 };
    }
  
    //compute inverse of 4x4 matrix
    template <typename T>
    square_matrix<T,4> invert(const square_matrix<T,4>& m)
    {
        T t1 = m(3,3) * m(1,1);
        T t3 = m(3,2) * m(1,1);
        T t7 = m(3,1) * m(1,2);
        T t9 = m(3,1) * m(1,3);
        T t11 = m(3,2) * m(2,1);
        T t14 = m(0,0) * m(1,1);
        T t19 = m(0,0) * m(3,3);
        T t20 = m(1,2) * m(2,1);
        T t22 = m(3,1) * m(0,0);
        T t23 = m(1,2) * m(2,3);
        T t25 = m(1,3) * m(2,2);
        T t27 = m(3,2) * m(0,0);
        T t28 = m(2,1) * m(1,3);
        T t30 = m(1,1) * m(3,0);
        T t31 = m(0,3) * m(2,2);
        T t33 = m(2,0) * m(0,3);
        T t35 = m(0,2) * m(2,3);
        T t37 = m(2,0) * m(0,2);
        T t39 = m(3,0) * m(0,2);
        T t41 = m(3,1) * m(1,0);
        T t43 = t14 * m(3,3) * m(2,2) - t14 * m(3,2) * m(2,3) - t19 * t20 +
        t22 * t23 - t22 * t25 + t27 * t28 - t30 * t31 + t3 * t33 + t30 * t35
        - t1 * t37 - t39 * t28 - t41 * t35;
        T t45 = m(3,0) * m(0,1);
        T t47 = m(1,0) * m(3,3);
        T t50 = m(2,0) * m(3,3);
        T t51 = m(0,1) * m(1,2);
        T t53 = m(3,2) * m(1,0);
        T t56 = m(0,2) * m(2,1);
        T t58 = m(3,0) * m(0,3);
        T t63 = m(3,2) * m(2,0);
        T t64 = m(0,1) * m(1,3);
        T t66 = m(1,0) * m(0,3);
        T t68 = -t7 * t33 - t45 * t23 - t47 * m(0,1) * m(2,2) + t50 * t51 + t53 *
        m(0,1) * m(2,3) + t47 * t56 + t58 * t20 + t9 * t37 + t41 * t31 + t45 *
        t25 - t63 * t64 - t11 * t66;
        T t70 = (T)1.0 / (t43 + t68);
        T t72 = m(3,3) * m(0,1);
        T t74 = m(3,2) * m(0,1);
        T t78 = m(0,3) * m(3,1);
        T t108 = m(2,0) * m(1,2);
        T t111 = m(1,3) * m(3,0);
        T t131 = m(0,0) * m(1,2);
        T t135 = m(1,0) * m(0,2);
        T t148 = m(3,1) * m(2,0);
        T t150 = m(1,0) * m(2,1);
        T t156 = m(0,0) * m(2,1);
        T t158 = m(0,0) * m(2,3);
        T t161 = m(2,0) * m(0,1);
        return square_matrix<T,4>{ (t1 * m(2,2) - t3 * m(2,3) - m(3,3) * m(1,2) * m(2,1) +
                   t7 * m(2,3) - t9 * m(2,2) + t11 * m(1,3)) * t70,
        -(t47 * m(2,2) - t53 * m(2,3) + m(1,3) * m(3,2) * m(2,0) - t108 *
                    m(3,3) + t23 * m(3,0) - t111 * m(2,2)) * t70,
         (-m(1,1) * m(2,0) * m(3,3) + m(1,1) * m(2,3) * m(3,0) - t28 *
                   m(3,0) + t148 * m(1,3) + t150 * m(3,3) - m(2,3) * m(3,1) * m(1,0)) * t70,
         -(-t3 * m(2,0) + t30 * m(2,2) + t11 * m(1,0) - m(3,0) * m(1,2) *
                    m(2,1) - t41 * m(2,2) + t7 * m(2,0)) * t70,
        
         -(t72 * m(2,2) - t74 * m(2,3) - t56 * m(3,3) + t35 * m(3,1) -
                    t78 * m(2,2) + m(0,3) * m(3,2) * m(2,1)) * t70,
         (t19 * m(2,2) - t27 * m(2,3) - t58 * m(2,2) + t63 * m(0,3) + t39 *
                   m(2,3) - t50 * m(0,2)) * t70,
         -(t156 * m(3,3) - t158 * m(3,1) + t33 * m(3,1) - t161 * m(3,3) - m(2,1) *
                    m(3,0) * m(0,3) + m(2,3) * m(3,0) * m(0,1)) * t70,
         (-t22 * m(2,2) + t27 * m(2,1) - t39 * m(2,1) + t148 * m(0,2) + t45 *
                   m(2,2) - t63 * m(0,1)) * t70,
        
       
         (t72 * m(1,2) - t74 * m(1,3) - t1 * m(0,2) + m(0,2) * m(3,1) *
                   m(1,3) + t3 * m(0,3) - t78 * m(1,2)) * t70,
        
         -(t19 * m(1,2) - t27 * m(1,3) - t47 * m(0,2) - t58 * m(1,2) + t111 *
                    m(0,2) + t66 * m(3,2)) * t70,
        
         (t19 * m(1,1) - t22 * m(1,3) - t58 * m(1,1) - t47 * m(0,1) + t41 *
                   m(0,3) + t45 * m(1,3)) * t70,
        
         -(-t53 * m(0,1) + t27 * m(1,1) - t39 * m(1,1) + t41 * m(0,2) - t22 *
                    m(1,2) + t45 * m(1,2)) * t70,
        
        -(t51 * m(2,3) - t64 * m(2,2) - m(1,1) * m(0,2) * m(2,3) + t56 *
                    m(1,3) + m(1,1) * m(0,3) * m(2,2) - m(0,3) * m(1,2) * m(2,1)) * t70,
       
        
         (t131 * m(2,3) - m(0,0) * m(1,3) * m(2,2) - t135 * m(2,3) - t108 *
                   m(0,3) + m(1,3) * m(2,0) * m(0,2) + t66 * m(2,2)) * t70,
       
       
         -(-m(2,3) * m(1,0) * m(0,1) + t158 * m(1,1) - t33 * m(1,1) + t161 *
                    m(1,3) - t156 * m(1,3) + t150 * m(0,3)) * t70,
       
        
        
        t70 * (t161 * m(1,2) - t37 * m(1,1) - m(1,0) * m(0,1) * m(2,2) + t135 *
               m(2,1) + t14 * m(2,2) - t131 * m(2,1)) };
    
   
    }
  

    template <typename T, std::size_t M, std::size_t N>
    matrix<T,M,N> dyad(const vector<T,M>& v1, const vector<T,N>& v2)
    {
        matrix<T,M,N> m;
        for(std::size_t j = 0; j < N; ++j)
            for(std::size_t i = 0; i < M; ++i)
                m(i,j) = v1(i)*v2(j);
        return m;
    }
  
  
    template <typename T, std::size_t M, std::size_t N>
    T trace(const matrix<T,M,N>& m)
    {
        T tr = (T)0;
        std::size_t o = (std::min)(M,N);
        for(std::size_t i = 0; i < o; ++i)
            tr += m(i,i);
        return tr;
    }
  
    template <typename T, std::size_t M, std::size_t N>
    matrix<T,M,N> eye()
    {
        matrix<T,M,N> r;
        r = (T)0;
        std::size_t o = (std::min)(M,N);
        for(std::size_t i = 0; i < o; i++)
            r(i,i) = (T)1;
        return r;
    }
  
    template <typename T, std::size_t M>
    matrix<T,M,M> eye()
    {
        matrix<T,M,M> r;
        r = (T)0;
    
        for(std::size_t i = 0; i < M; i++)
            r(i,i) = (T)1;
        return r;
    }
  
    template <typename T,std::size_t M, std::size_t N,
        typename Mat = matrix<T,M,N>, typename = std::enable_if_t<Mat::is_vector(3)> >
    square_matrix<T,3> cross_mat(matrix<T,M,N>& v)
    {
        return square_matrix<T,3>{ 0, v(2), -v(1), -v(2), 0, v(0), v(1), -v(0), 0 };
    }
  
    template <typename T, std::size_t M, std::size_t N>
    matrix<T,M,N> ones()
    {
        matrix<T,M,N> r;
        r=T{1};
        return r;
    }
  
    template <typename T, std::size_t N >
    square_matrix<T,N> diag(const vector<T,N>& v)
    {
        square_matrix<T,N> r;
        r = (T)0;
        for(std::size_t i = 0; i < N; i++)
            r(i,i) = v(i);
        return r;
    }

    template<typename S,typename T>
    square_matrix<S,4> perspective(const T& fovy, const T&aspect, const T& znear, const T& zfar)
    {
        S fovyr = (S)(fovy*3.14159/180.0);
        S f = (S)(cos(fovyr/2.0f)/sin(fovyr/2.0f));
        return square_matrix<S,4> {
         f/aspect, 0, 0, 0, 0, f, 0, 0, 0,
         0, (zfar+znear)/(znear-zfar), -1 ,0, 0,
        (2*zfar*znear)/(znear-zfar),0 };
    
    }
  
    template<typename S, typename T>
    square_matrix<S,4> frustrum(const T& left, const T&right,const T& bottom, const T&top, const T& znear, const T& zfar)
    {
        S A = (right+left)/(right-left);
        S B = (top+bottom)/(top-bottom);
        S C = -(zfar+znear)/(zfar-znear);
        S D = -2*zfar*znear/(zfar-znear);
        return square_matrix<S,4>{
            2*znear/(right-left),0,0,0,0,2*znear/(top-bottom), 0,0,A,B, C, -1, 0, 0, D, 0 };
    }
  
    template<typename S>
    square_matrix<S,4> lookat(const vector<S,3>& eye, const vector<S,3>& target, vector<S,3> up)
    {
        vector<S,3>  f = normalize(target - eye);
        up.normalize();
        vector<S,3> s = cross(f,up);
        s.normalize();
        vector<S,3> u = cross(s,f);
        return square_matrix<S,4>{ s(0), u(0), -f(0), 0,
            s(1), u(1), -f(1), 0,
            s(2), u(2), -f(2), 0,
            -dot(s,eye),-dot(u,eye),dot(f,eye),1};
    }
  
  
    ///creates a picking matrix like gluPickMatrix with pixel (0,0) in the lower left corner if flipy=false
    // x,y is the center of the region
    template<typename S, typename T>
    const square_matrix<S,4> pick(const T& x,const T& y,const T& width, const T& height,
                               const std::array<T,4>& viewport,
                               const square_matrix<T,4> &modelviewproj, bool flipy = true)
    {
        S sx, sy;
        S tx, ty;
        sx = viewport[2] / width;
        sy = viewport[3] / height;
        tx = (S)(viewport[2] + 2.0 * (viewport[0] - x)) / width;
        if(flipy)
            ty = (S)(viewport[3] + 2.0 * (viewport[1] - (viewport[3]-y))) / height;
        else
            ty = (S)(viewport[3] + 2.0 * (viewport[1] - y)) / height;
        square_matrix<S,4> m(sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, 1, 0, tx, ty, 0, 1);
        return m*modelviewproj;
    }
  
    template <typename S, typename T>
    square_matrix<S,4> translate(const T& tx, const T& ty, const T& tz)
    {
        return square_matrix<S,4>{1,0,0,0,0,1,0,0,0,0,1,0, tx, ty,tz,1};
    }
  
    template <typename S, typename T>
    square_matrix<S,3> scale(const T& sx,const T& sy,const T& sz)
    {
        return square_matrix<S,4>{sx,0,0,0,
            0,sy,0,0,
            0,0,sz,0,
            0,0,0,1};
    }
  
    template <typename S, typename T>
    square_matrix<S,3> uniform_scale(const T& s)
    {
    return square_matrix<S,4>{s,0,0,0,
        0,s,0,0,
        0,0,s,0,
        0,0,0,1};
    }
  
    template<typename T>
    square_matrix<T,4> rotate(const vector<T, 3> axis, const T& angle)
    {
    
        if(angle == 0)
            return eye<T,4>();
        square_matrix<T,3> R = eye<T,3>();
        vector<T,3> dirn =  axis;
        dirn.normalize();
        square_matrix<T,3> omega = cross_mat(dirn);
        T theta = angle;
    
        R += sin(theta)*omega + (1.0f-cos(theta))*(omega*omega);
    return square_matrix<T,3> {R(0,0),R(1,0),R(2,0),0,
        R(0,1),R(1,1),R(2,1),0,
        R(0,2),R(1,2),R(2,2),0,
        0,0,0,1};
    
    }
  
    template <typename T>
    square_matrix<T,4> rotateX(const T& angle)
    {
        T Cos{cos(angle)};
        T Sin{sin(angle)};
        return square_matrix<T,4>{ 1, 0, 0, 0,
                                   0, Cos, Sin,0,
                                   0, -Sin, Cos, 0,
                                   0, 0, 0, 1};
    }
  
    template <typename T>
    square_matrix<T,4> rotateY(const T& angle)
    {
        T Cos{cos(angle)};
        T Sin{sin(angle)};
        return square_matrix<T,4>{ Cos , 0, -Sin, 0,
            0 ,1, 0,0,
            Sin, 0,  Cos, 0,
            0,0,0,1};
    }
  
    template <typename T>
    square_matrix<T,4> rotateZ(const T& angle)
    {
    T Cos{cos(angle)};
    T Sin{sin(angle)};
    return square_matrix<T,4>{ Cos , Sin, 0, 0,
        -Sin ,Cos,0,0,
        0, 0,1, 0,
        0,0,0,1};
    }
  
    template <typename S,typename T>
    square_matrix<T,4> ortho(T left, T right, T bottom, T top, T zNear, T zFar)
    {
    
        T rl = right -  left;
        T tb = top - bottom;
        T zfn = zFar - zNear;
    
        return square_matrix<T,4> {static_cast<T>(2) / rl,0,0,0,
            0,static_cast<T>(2) / tb,0,0,
            0,0,- static_cast<T>(2) / zfn,0,
            - (right + left) / rl,- (top + bottom) / tb,- (zFar + zNear) / zfn,1};
    }
  
    /*
     template <typename T>
    tiny_mat<T, 4, 4> projection_matrix_from_intrinsics(const math::tiny_mat<T, 3, 3>& K, int img_width, int img_height, T znear, T zfar)
    {
    
    T fx = K(0, 0);
    T fy = K(1, 1);
    //T skew = K(0, 1);
    T u0 = K(0, 2);
    T v0 = K(1, 2);
    
    T l = -znear  * u0/fx;
    
    T r = znear  *(img_width - u0) / fx;
    
    T b = -znear  *v0 / fy;
    
    T t = znear  *( img_height - v0) / fy;
    return frustrum(l, r, b, t, znear, zfar);
    
    }
    
    template <typename T>
    tiny_mat<T,2,2> rotation_2D(T angle)
    {
    angle *= (T)(3.14159/180.0);
    T cosa = cos(angle);
    T sina = sin(angle);
    
    tiny_mat<T,2,2> r;
    r(0,0) = cosa; r(0,1) = -sina;
    r(1,0) = sina; r(1,1) = cosa;
    return r;
    }
    
    template<typename T>
    tiny_mat<T,3,3> rotation_3D(const tiny_vec<T, 3> axis, const T& angle)
    {
    tiny_mat<T,3,3> R;
    R.eye();
    if(angle == 0)
        return R;
    tiny_vec<T,3> dirn =  axis;
    dirn.normalize();
    tiny_mat<T,3,3> omega = cross_mat(dirn);
    T theta = angle;
    //float theta2 = angle*angle;
    R += sin(theta)*omega + (1.0f-cos(theta))*(omega*omega);
    
    return R;
    }
    
    
    template <typename T, std::size_t N>
    tiny_mat<T,N+1,N+1> homog(const tiny_mat<T,N,N>& m)
    {
    tiny_mat<T,N+1,N+1> mh;
    
    for(std::size_t j = 0; j < m.ncols(); j++)
        {
        for(std::size_t i = 0; i < m.nrows(); i++)
            mh(i,j) = m(i,j);
        mh(m.nrows(),j) = 0;
        }
    
    for(std::size_t i = 0; i < m.nrows(); i++)
        mh(i,m.ncols()) = 0;
    mh(m.nrows(),m.ncols()) = 1;
    
    return mh;
    }
    
    template<typename T>
    tiny_mat<T,4,4> rotation_homog_3D(const tiny_vec<T, 3> axis, const T& angle)
    {
    tiny_mat<T,3,3> R = rotation_3D(axis,angle);
    return homog(R);
    }
    
    
    template <typename T>
    tiny_mat<T,3,3> translation_homog_2D(const T& tx,const T& ty)
    {
    tiny_mat<T,3,3> tr = eye<T,3,3>();
    tr(0,2) = tx;
    tr(1,2) = ty;
    return tr;
    }
    
    
    template <typename T>
    tiny_mat<T,3,3> scale_3d(const T& sx,const T& sy,const T& sz)
    {
    tiny_mat<T,3,3> tr = eye<T,3,3>();
    tr(0,0) = sx;
    tr(1,1) = sy;
    tr(2,2) = sz;
    return tr;
    }
    
    template <typename T>
    tiny_mat<T,3,3> scale_3D(const T& s)
    {
    tiny_mat<T,3,3> tr = eye<T,3,3>();
    tr(0,0) = s;
    tr(1,1) = s;
    tr(2,2) = s;
    return tr;
    }
    
    
    template <typename T>
    tiny_mat<T,4,4> translation_homog_3D(const tiny_vec<T,3>& t)
    {
    tiny_mat<T,4,4> tr = eye<T,4,4>();
    tr(0,3) = t[0];
    tr(1,3) = t[1];
    tr(2,3) = t[2];
    return tr;
    }
    
    
    template <typename T>
    tiny_mat<T,4,4> scale_homog_3D(const T& sx,const T& sy,const T& sz)
    {
    
    return homog(scale_3D(sx,sy,sz));
    }
    
    
    template <typename T>
    tiny_mat<T,4,4> scale_homog_3D(const T& s)
    {
    
    return homog(scale_3D(s));
    }
    
    */
  
  }
  
}


