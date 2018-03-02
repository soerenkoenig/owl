//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include <chrono>

namespace owl
{
  namespace scene
  {
    template <typename Scalar>
    class camera
    {
    };
  
    /*
    
template<typename Scalar>
class intrinsic_camera
{
  public:
  intrinsic_camera(const Scalar& focal_length_world = 4.1,
   const vector<Scalar, 2>& sensor_size = {4.89, 3.67},
   const vector<std::size_t, 2>& resolution = {3264, 2448},
   const vector<Scalar, 2>& principal_point = sensor_resolution / Scalar{2})
    : focal_length_pixel_(comp_div(focal_length_world * sensor_resolution, sensor_size)),
      principal_point_(principal_point),
      sensor_resolution_(sensor_resolution),
      pixel_size_(comp_div(sensor_size, sensor_resolution)
  {
  }
  
  vector<Scalar, 2> pixel_size_;
  vector<std::size_t, 2> sensor_resolution_; //sensor resolution
  vector<Scalar, 2> principal_point_; //principal point
  vector<Scalar, 2> focal_length_pixel_; // focal length in pixel units often denoted as fx, fy
};
    */
  }
}

