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
#include "owl/math/euler_angles.hpp"
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
        : data_{0, 0, 0, 1}
      {
      }
    
      quaternion(const Scalar& x, const Scalar& y, const Scalar& z, const Scalar& w)
        : data_{x, y, z, w}
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
    
      quaternion(const euler_angles<Scalar>& other)
      {
        *this = other;
      }
    
      quaternion(const vector<Scalar,3>& axis, const angle<Scalar> &theta)
      {
        set_from_axis_angle(axis, theta);
      }
    
      quaternion& operator=(const euler_angles<Scalar>& other)
      {
        Scalar cy = cos(other.yaw * Scalar(0.5));
        Scalar sy = sin(other.yaw * Scalar(0.5));
        Scalar cz = cos(other.roll * Scalar(0.5));
        Scalar sz = sin(other.roll * Scalar(0.5));
        Scalar cx = cos(other.pitch * Scalar(0.5));
        Scalar sx = sin(other.pitch * Scalar(0.5));
    
        w() = cx*cy*cz - sx*sy*sz;
        x() = sx*cy*cz + cx*sy*sz;
        y() = cx*sy*cz - sx*cy*sz;
        z() = cx*cy*sz + sx*sy*cz;
    
        return *this;
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
          x() = (m(2,1) - m(1,2)) / (4.0 * w());
          y() = (m(0,2) - m(2,0)) / (4.0 * w());
          z() = (m(1,0) - m(0,1)) / (4.0 * w());
        }
        else
        {
          std::size_t j = (i + 1) % 3;
          std::size_t k = (i + 2) % 3;

          data_[i] = sqrt(m(i,i) - m(j,j) - m(k,k) + 1.0) / 2.0;
          data_[j] = (m(i,j) + m(j,i)) / (4.0 * data_[i]);
          data_[k] = (m(i,k) + m(k,i)) / (4.0 * data_[i]);
          w() = (m(k,j) - m(j,k)) / (4.0 * data_[i]);
        }
        return *this;
      }
    
    
      operator matrix<Scalar,3,3>() const
      {
        const Scalar q00 = 2.0 * data_[0] * data_[0];
        const Scalar q11 = 2.0 * data_[1] * data_[1];
        const Scalar q22 = 2.0 * data_[2] * data_[2];
        const Scalar q01 = 2.0 * data_[0] * data_[1];
        const Scalar q02 = 2.0 * data_[0] * data_[2];
        const Scalar q03 = 2.0 * data_[0] * data_[3];
        const Scalar q12 = 2.0 * data_[1] * data_[2];
        const Scalar q13 = 2.0 * data_[1] * data_[3];
        const Scalar q23 = 2.0 * data_[2] * data_[3];
    
        matrix<Scalar,3,3> m;
      
        m <<   1.0 - q11 - q22,       q01 - q23,       q02 + q13,
                     q01 + q23, 1.0 - q22 - q00,       q12 - q03,
                     q02 - q13,       q12 + q03, 1.0 - q11 - q00;
    
        return m;
      }
    
      operator matrix<Scalar,4,4>() const
      {
      
        const Scalar q00 = 2.0 * data_[0] * data_[0];
        const Scalar q11 = 2.0 * data_[1] * data_[1];
        const Scalar q22 = 2.0 * data_[2] * data_[2];
        const Scalar q01 = 2.0 * data_[0] * data_[1];
        const Scalar q02 = 2.0 * data_[0] * data_[2];
        const Scalar q03 = 2.0 * data_[0] * data_[3];
        const Scalar q12 = 2.0 * data_[1] * data_[2];
        const Scalar q13 = 2.0 * data_[1] * data_[3];
        const Scalar q23 = 2.0 * data_[2] * data_[3];
    
        matrix<Scalar,4,4> m;
      
        m << 1.0 - q11 - q22,       q01 - q23,       q02 + q13, 0,
                   q01 + q23, 1.0 - q22 - q00,       q12 - q03, 0,
                   q02 - q13,       q12 + q03, 1.0 - q11 - q00, 0,
                           0,               0,               0, 1;
      
        return m;
      }
    
      operator euler_angles<Scalar>() const
      {
        euler_angles<Scalar> euler;
        auto r11 = -2*(y()*z() - w()*x());
        auto r12 =  w()*w() - x()*x() - y()*y() + z()*z();
        auto r21 =  2*(x()*z() + w()*y());
        auto r31 = -2*(x()*y() - w()*z());
        auto r32 =  w()*w() + x()*x() - y()*y() - z()*z();
        euler.roll = radians<Scalar>(std::atan2( r31, r32 ));
        euler.yaw = radians<Scalar>(std::asin ( r21 ));
        euler.pitch = radians<Scalar>(std::atan2( r11, r12 ));
        return euler;
      }
    
      quaternion inverse() const
      {
        return quaternion(-x(), -y(), -z(), w());
      }
  
      void invert()
      {
        imag() *= -1;
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
    
      const Scalar& real() const
      {
        return data_[3];
      }
    
      Scalar& real()
      {
        return data_[3];
      }
    
      const vector<Scalar,3>& imag() const
      {
        return reinterpret_cast<const vector<Scalar,3>&>(*this);
      }
    
      vector<Scalar,3>& imag()
      {
        return reinterpret_cast<vector<Scalar,3>&>(*this);
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
          return quaternion<S>(a * b[0], a * b[1], a * b[2], a * b[3]);
      }
    
      quaternion& operator*=(const quaternion &q)
      {
        *this = (*this) * q;
        return *this;
      }

      template <typename S1, typename S2>
      friend auto operator*(const quaternion<S1>& a, const quaternion<S2>& b)
      {
        using S3 = decltype(std::declval<S1>() * std::declval<S2>());
        return quaternion<S3>(a[3] * b[0] + b[3] * a[0] + a[1] * b[2] - a[2] * b[1],
                              a[3] * b[1] + b[3] * a[1] + a[2] * b[0] - a[0] * b[2],
                              a[3] * b[2] + b[3] * a[2] + a[0] * b[1] - a[1] * b[0],
                              a[3] * b[3] - b[0] * a[0] - a[1] * b[1] - a[2] * b[2]);
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
          Scalar factor = sin(theta / 2.0);
          imag() = factor * axis;
          real() = cos(theta / 2.0);
          normalize();
      }

    private:
      vector<Scalar, 4> data_;
    };
  
    template <typename Scalar>
    std::ostream& operator<<(std::ostream& out,const quaternion<Scalar>& q)
    {
      return out << q.w() << " + " << q.x() << "i + "<< q.y() << "j + " << q.z() << "k";
    }
  
    template <typename Scalar>
    bool compare_equal(const quaternion<Scalar>& lhs, const quaternion<Scalar>& rhs, double margin, double epsilon, double scale)
    {
      return compare_equal(lhs.real(), rhs.real(), margin, epsilon, scale) &&
        compare_equal(lhs.imag(), rhs.imag(), margin, epsilon, scale);
    
    }
  
    using quaternionf = quaternion<float>;
    using quaterniond = quaternion<double>;
  
  }
}

