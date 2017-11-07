//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include "owl/utils/file_utils.hpp"


#define STBI_NO_STDIO

#define STB_IMAGE_IMPLEMENTATION
//#define STB_IMAGE_STATIC
#define STB_IMAGE_INLINE
#include "stb/stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
//#define STB_IMAGE_RESIZE_STATIC
#define STB_IMAGE_RESIZE_INLINE
#include "stb/stb_image_resize.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
//#define STB_IMAGE_WRITE_STATIC
#define STB_IMAGE_WRITE_INLINE
#include "stb/stb_image_write.h"


namespace owl
{
  namespace graphics
  {
    class image_error : public std::exception
    {
    public:
      explicit image_error(const std::string &msg)
        : msg_(msg)
      {}
    
      const char *what() const throw() override
      {
       return msg_.c_str();
      }

    private:
    std::string msg_;
  };

/*
namespace detail {

template <typename T>
typename std::enable_if<std::is_unsigned<T>::value, T>::type saturated_sub(
  T s1, T s2) {
  return s1 > s2 ? static_cast<T>(s1 - s2) : 0;
}

template <typename T>
typename std::enable_if<!std::is_unsigned<T>::value, T>::type saturated_sub(
  T s1, T s2) {
  return static_cast<T>(s1 - s2);
}



inline void resize_image_core(const uint8_t *src,
                              int srcw,
                              int srch,
                              uint8_t *dst,
                              int dstw,
                              int dsth,
                              int channels) {
  stbir_resize_uint8(src, srcw, srch, 0, dst, dstw, dsth, 0, channels);
}

inline void resize_image_core(const float *src,
                              int srcw,
                              int srch,
                              float *dst,
                              int dstw,
                              int dsth,
                              int channels) {
  stbir_resize_float(src, srcw, srch, 0, dst, dstw, dsth, 0, channels);
}

}  // namespace detail*/

enum class image_type
    {
  grayscale,  ///< load image and convert automatically to 8-bit grayscale
  rgb,        ///< load image and keep original color channels
  bgr
};

/**
 * Simple image utility class
 */
template <typename T = unsigned char>
class image {
 public:
  typedef T intensity_t;
  typedef typename std::vector<intensity_t>::iterator iterator;
  typedef typename std::vector<intensity_t>::const_iterator const_iterator;

  image() : width_(0), height_(0), depth_(1) {}

  /**
   * create image from raw pointer
   */
  image(const intensity_t *data, size_t width, size_t height, image_type type = image_type::rgb)
    : width_(width),
      height_(height),
      depth_(type == image_type::grayscale ? 1 : 3),
      type_(type),
      data_(depth_ * width_ * height_, 0)
  {
    std::copy(data, data + width * height * depth_, data_.data());
  }

  template <typename U>
  image(const image<U> &rhs)
    : width_(rhs.width()),
      height_(rhs.height()),
      depth_(rhs.depth()),
      type_(rhs.type()),
      data_(rhs.shape().size())
  {
    std::transform(rhs.begin(), rhs.end(), data_.begin(),
                   [](T src) { return static_cast<intensity_t>(src); });
  }

  
  image(const std::string &path, image_type type = image_type::rgb)
  {
    std::vector<unsigned char> buffer;
    if(!owl::utils::file_exists(path))
      throw image_error("image file does not exist: " + path);
    
    if(!owl::utils::read_file(path, buffer))
      throw image_error("failed to load image from file: " + path);
    
    int w;
    int h;
    int d;
    
    stbi_uc *input_pixels = stbi_load_from_memory(buffer.data(),(int)buffer.size(), &w, &h, &d, STBI_rgb);
   
    if(input_pixels == nullptr)
    {
      throw image_error("failed to open image:" +
                     std::string(stbi_failure_reason()));
    }

    width_  = w;
    height_ = h;
    depth_  = type == image_type::grayscale ? 1 : 3;
    type_   = type;

    data_.resize(width_ * height_ * depth_);

    // reorder to HxWxD -> DxHxW
    from_rgb(input_pixels, input_pixels + data_.size());

    stbi_image_free(input_pixels);
  }

  void save(const std::string &path) const
  {
  /*  int ret;
    std::vector<uint8_t> buf = to_rgb<uint8_t>();
    std::string extension = owl::utils::file_extension(path);
    if (extension == "png")
    {
      ret = stbi_write_png(path.c_str(), static_cast<int>(width_),
                           static_cast<int>(height_), static_cast<int>(depth_),
                           (const void *)&buf[0], 0);
    }
    else if(extension =="bmp")
    {
      ret = stbi_write_bmp(path.c_str(), static_cast<int>(width_),
                           static_cast<int>(height_), static_cast<int>(depth_),
                           (const void *)&buf[0]);
    }
    
    if (ret == 0)
     {
      throw image_error("failed to save image:" + path);
    }*/
  }
  
  

  void resize(size_t width, size_t height)
  {
    data_.resize(width * height * depth_);
    width_  = width;
    height_ = height;
    // depth_ = depth;
  }

  void fill(intensity_t value) { std::fill(data_.begin(), data_.end(), value); }
  
  intensity_t operator()(size_t x, size_t y, size_t z = 0)
  {
    return data_[z * width_ * height_ + y * width_ + x];
  }

  intensity_t &at(size_t x, size_t y, size_t z = 0)
  {
    return data_.at(z * width_ * height_ + y * width_ + x);
  }

  const intensity_t &operator()(size_t x, size_t y, size_t z = 0) const
  {
    return data_[z * width_ * height_ + y * width_ + x];
  }
  
  const intensity_t &at(size_t x, size_t y, size_t z = 0) const
  {
    return data_.at(z * width_ * height_ + y * width_ + x);
  }

  bool empty() const { return data_.empty(); }
  iterator begin() { return data_.begin(); }
  iterator end() { return data_.end(); }
  const_iterator begin() const { return data_.begin(); }
  const_iterator end() const { return data_.end(); }

  intensity_t &operator[](std::size_t idx) { return data_[idx]; }
  const intensity_t &operator[](std::size_t idx) const { return data_[idx]; }

  size_t width() const { return width_; }
  size_t height() const { return height_; }
  size_t depth() const { return depth_; }
  image_type type() const { return type_; }
  size_t size() const { return width_ * height_ *depth_; }
 
  const std::vector<intensity_t> &data() const { return data_; }

  template <typename U>
  std::vector<U> to_rgb() const
  {
    if (depth_ == 1) {
      return std::vector<U>(data_.begin(), data_.end());
    } else {
      std::vector<U> buf(size());
      auto order = depth_order(type_);
      auto dst   = buf.begin();

      for (size_t y = 0; y < height_; y++)
        for (size_t x = 0; x < width_; x++)
          for (size_t i = 0; i < depth_; i++)
            *dst++ = static_cast<U>(at(x, y, order[i]));
      return buf;
    }
  }

  template <typename Iter>
  void from_rgb(Iter begin, Iter end)
  {
    if (depth_ == 1) {
      std::copy(begin, end, data_.begin());
    } else {
      auto order = depth_order(type_);
      assert(std::distance(begin, end) == static_cast<int>(data_.size()));

      for (size_t y = 0; y < height_; y++)
        for (size_t x = 0; x < width_; x++)
          for (size_t i = 0; i < depth_; i++)
            at(x, y, order[i]) = static_cast<intensity_t>(*begin++);
    }
  }

 private:
  std::array<size_t, 3> depth_order(image_type img) const
  {
    if (img == image_type::rgb) {
      return {{0, 1, 2}};
    } else {
      assert(img == image_type::bgr);
      return {{2, 1, 0}};
    }
  }
  size_t width_;
  size_t height_;
  size_t depth_;
  image_type type_;
  std::vector<intensity_t> data_;
};



/**
 * resize image into width x height
 * This function use Mitchell-Netrevalli filter with B=1/3, C=1/3 for
 * downsampling, and
 * and cubic spline algorithm for upsampling.
 
template <typename T>
inline image<T> resize_image(const image<T> &src, int width, int height) {
  image<T> resized(shape3d(width, height, src.depth()), src.type());
  std::vector<T> src_rgb = src.template to_rgb<T>();
  std::vector<T> dst_rgb(resized.shape().size());

  detail::resize_image_core(&src_rgb[0], static_cast<int>(src.width()),
                            static_cast<int>(src.height()), &dst_rgb[0], width,
                            height, static_cast<int>(src.depth()));

  resized.from_rgb(dst_rgb.begin(), dst_rgb.end());

  return resized;
}

// dst[x,y,d] = lhs[x,y,d] - rhs[x,y,d]
template <typename T>
image<T> subtract_image(const image<T> &lhs, const image<T> &rhs) {
  if (lhs.shape() != rhs.shape()) {
    throw nn_error("Shapes of lhs/rhs must be same. lhs:" +
                   to_string(lhs.shape()) + ",rhs:" + to_string(rhs.shape()));
  }

  image<T> dst(lhs.shape(), lhs.type());

  auto dstit = dst.begin();
  auto lhsit = lhs.begin();
  auto rhsit = rhs.begin();

  for (; dstit != dst.end(); ++dstit, ++lhsit, ++rhsit)
  {
    *dstit = detail::saturated_sub(*lhsit, *rhsit);
  }
  return dst;
}

template <typename T>
image<T> subtract_scalar(const image<T> &lhs, const image<T> &rhs) {
  if (lhs.depth() != rhs.depth()) {
    throw nn_error("Depth of lhs/rhs must be same. lhs:" +
                   to_string(lhs.depth()) + ",rhs:" + to_string(rhs.depth()));
  }
  if (rhs.width() != 1 || rhs.height() != 1) {
    throw nn_error("rhs must be 1x1xN");
  }

  image<T> dst(lhs.shape(), lhs.type());

  auto dstit = dst.begin();
  auto lhsit = lhs.begin();
  auto rhsit = rhs.begin();

  for (size_t i = 0; i < lhs.depth(); i++, ++rhsit) {
    for (size_t j = 0; j < lhs.width() * lhs.height(); j++, ++dstit, ++lhsit) {
      *dstit = detail::saturated_sub(*lhsit, *rhsit);
    }
  }

  return dst;
}*/

  }
}

