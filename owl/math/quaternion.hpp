//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include "owl/math/matrix.hpp"
#include "owl/math/angle.hpp"

namespace owl
{
  namespace math
  {
    template <typename Scalar>
    class quaternion
    {
    public:
      quaternion()
        : data_{0,0,0,1}
      {
      }
    
      quaternion(const Scalar& x, const Scalar& y, Scalar& z, const Scalar& w)
        : data_{x,y,z,w}
      {
      }
    
      quaternion(const matrix<Scalar,3,3>& m)
      {
        *this = m;
      }
    
      quaternion(const matrix<Scalar,4,4>& m)
      {
        *this = m;
      }
    
      quaternion(const vector<Scalar,3>& axis, const angle<Scalar> &theta)
      {
        set_from_axis_angle(axis,theta);
      }
    
      template <typename Matrix, typename = std::enable_if_t<Matrix::is_square(3) || Matrix::is_square(4)> >
      quaternion& operator=(const Matrix& m)
      {
        std::size_t i = 2;
        if(m(0,0) > m(1,1))
        {
          if(m(0,0) > m(2,2))
            i = 0;
        }
        else
        {
          if(m(1,1) > m(2,2))
            i = 1;
        }
  
        if (m(0,0) + m(1,1) + m(2,2) > m(i,i))
        {
          w() = sqrt(m(0,0) + m(1,1) + m(2,2) + 1.0) / 2.0;
          x() = (m(2,1) - m(1,2))/(4.0 * w());
          y() = (m(0,2) - m(2,0))/(4.0 * w());
          z() = (m(1,0) - m(0,1))/(4.0 * w());
        }
        else
        {
          std::size_t j = (i + 1) % 3;
          std::size_t k = (i + 2) % 3;

          data_[i] = sqrt(m(i,i) - m(j,j) - m(k,k) + 1.0)/2.0;
          data_[j] = (m(i,j) + m(j,i)) / (4.0 * data_[i]);
          data_[k] = (m(i,k) + m(k,i)) / (4.0 * data_[i]);
          w() = (m(k,j) - m(j,k)) / (4.0 * data_[i]);
        }
        return *this;
      }
    
    
      operator matrix<Scalar,3,3>() const
      {
      
        const Scalar q00 = 2.0l * data_[0] * data_[0];
        const Scalar q11 = 2.0l * data_[1] * data_[1];
        const Scalar q22 = 2.0l * data_[2] * data_[2];
        const Scalar q01 = 2.0l * data_[0] * data_[1];
        const Scalar q02 = 2.0l * data_[0] * data_[2];
        const Scalar q03 = 2.0l * data_[0] * data_[3];
        const Scalar q12 = 2.0l * data_[1] * data_[2];
        const Scalar q13 = 2.0l * data_[1] * data_[3];
        const Scalar q23 = 2.0l * data_[2] * data_[3];
    
        matrix<Scalar,3,3> m;
      
        m << 1.0l - q11 - q22,        q01 - q23,        q02 + q13,
                    q01 + q23, 1.0l - q22 - q00,        q12 - q03,
                    q02 - q13,        q12 + q03, 1.0l - q11 - q00;
    
        return m;
      }
    
      operator matrix<Scalar,4,4>() const
      {
      
        const Scalar q00 = 2.0l * data_[0] * data_[0];
        const Scalar q11 = 2.0l * data_[1] * data_[1];
        const Scalar q22 = 2.0l * data_[2] * data_[2];
        const Scalar q01 = 2.0l * data_[0] * data_[1];
        const Scalar q02 = 2.0l * data_[0] * data_[2];
        const Scalar q03 = 2.0l * data_[0] * data_[3];
        const Scalar q12 = 2.0l * data_[1] * data_[2];
        const Scalar q13 = 2.0l * data_[1] * data_[3];
        const Scalar q23 = 2.0l * data_[2] * data_[3];
    
        matrix<Scalar,4,4> m;
      
        m << 1.0l - q11 - q22,        q01 - q23,        q02 + q13, 0,
                    q01 + q23, 1.0l - q22 - q00,        q12 - q03, 0,
                    q02 - q13,        q12 + q03, 1.0l - q11 - q00, 0,
                            0,                0,                   1;
      
        return m;
      }
    
      quaternion inverse() const
      {
        return quaternion(-x(), -y(), -z(), w());
      }
  
      void invert()
      {
       x() *= -1;
       y() *= -1;
       z() *= -1;
      }
    
      void negate()
      {
        data_ *= -1;
      }
    
      quaternion operator-() const
      {
        quaternion q = *this;
        q.negate();
        return q;
      }
    
      const Scalar& operator()(std::size_t index) const
      {
        return data_[index];
      }
    
      Scalar& operator()(std::size_t index)
      {
        return data_[index];
      }
    
      const Scalar& operator[](std::size_t index) const
      {
        return data_[index];
      }
    
      Scalar& operator[](std::size_t index)
      {
        return data_[index];
      }
      
  
      const Scalar& x() const
      {
        return data_[0];
      }
    
      Scalar& x()
      {
        return data_[0];
      }
    
      const Scalar& y() const
      {
        return data_[1];
      }
    
      Scalar& y()
      {
        return data_[1];
      }
    
      const Scalar& z() const
      {
        return data_[2];
      }
    
      Scalar& z()
      {
        return data_[2];
      }
    
      const Scalar& w() const
      {
        return data_[3];
      }
    
      Scalar& w()
      {
        return data_[3];
      }
    
      template< typename S>
      friend bool operator==(const quaternion<S>& lhs, const quaternion<S>& rhs)
      {
        return lhs.data_ == rhs.data_;
      }
    
      template< typename S>
      friend bool operator!=(const quaternion<S>& lhs, const quaternion<S>& rhs)
      {
        return lhs.data_ != rhs.data_;
      }
    
      template< typename S>
      friend bool operator<(const quaternion<S>& lhs, const quaternion<S>& rhs)
      {
        return lhs.data_ < rhs.data_;
      }
    
      template<typename S>
      friend bool operator<=(const quaternion<S>& lhs, const quaternion<S>& rhs)
      {
        return lhs.data_ <= rhs.data_;
      }
    
      template<typename S>
      friend bool operator>(const quaternion<S>& lhs, const quaternion<S>& rhs)
      {
        return lhs.data_ > rhs.data_;
      }
    
      template <typename S>
      friend bool operator>=(const quaternion<S>& lhs, const quaternion<S>& rhs)
      {
        return lhs.data_ >= rhs.data_;
      }
    
      template <typename S>
      friend quaternion<S> operator*(const S& a, const quaternion<S>& b)
      {
          return quaternion<S>(a*b[0],a*b[1],a*b[2],a*b[3]);
      }
    
      quaternion& operator*=(const quaternion &q)
      {
        *this = (*this) * q;
        return *this;
      }

      template <typename S1, typename S2>
      friend auto operator*(const quaternion<S1>& a, const quaternion<S2>& b)
      {
        using S3 = decltype(std::declval<S1>()*std::declval<S2>());
        return quaternion<S3>(a[3]*b[0] + b[3]*a[0] + a[1]*b[2] - a[2]*b[1],
                              a[3]*b[1] + b[3]*a[1] + a[2]*b[0] - a[0]*b[2],
                              a[3]*b[2] + b[3]*a[2] + a[0]*b[1] - a[1]*b[0],
                              a[3]*b[3] - b[0]*a[0] - a[1]*b[1] - a[2]*b[2]);
      }
    
      void normalize()
      {
        data_.normalize();
      }
    
      void set(const Scalar& x, const Scalar& y, const Scalar& z, const Scalar& w)
      {
        data_[0] = x;
        data_[1] = y;
        data_[2] = z;
        data_[3] = w;
      }
    
      void set_from_axis_angle(const vector<Scalar,3>& axis, const angle<Scalar> &theta)
      {
          Scalar factor = sin( theta / 2.0 );

          x() = axis.x() * factor;
          y() = axis.y() * factor;
          z() = axis.z() * factor;
          w() = cos(theta / 2.0);
          
          normalize();
      }

    private:
      vector<Scalar, 4> data_;
    };
  
    using quaternionf = quaternion<float>;
    using quaterniond = quaternion<double>;
  
  }
}

