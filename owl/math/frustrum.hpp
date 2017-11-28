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
  
    template <typename T>
    class frustrum
    {
    public:
      using scalar_type = T;
      using matrix_type = square_matrix<T,4>;
      using plane_type = plane<T,3>;
    
      enum side : std::size_t { right, left, top, bottom, far, near };
    
      plane_type operator(side s) const
      {
      
        switch(s)
        {
        case 0:
          return model_view_projection_.row(3) - model_view_projection_.row(0);
        case 1:
          return model_view_projection_.row(3) + model_view_projection_.row(0);
        case 2:
          return model_view_projection_.row(3) - model_view_projection_.row(1);
        case 3:
          return model_view_projection_.row(3) + model_view_projection_.row(1);
        case 4:
          return model_view_projection_.row(3) - model_view_projection_.row(2);
        case 5:
          return model_view_projection_.row(3) - model_view_projection_.row(2);
        default:
          assert(false);
        };
      }
    
    private:
      matrix_type model_view_projection_;
    };
  
    const mat<T> extract_frustrum_planes(const mat<T>& modelviewprojection)
    {
      mat<T> frustrum_planes(4,6);
    
      frustrum_planes.set_col(0,modelviewprojection.row(3)-modelviewprojection.row(0));//right
      frustrum_planes.set_col(1,modelviewprojection.row(3)+modelviewprojection.row(0));//left
      frustrum_planes.set_col(2,modelviewprojection.row(3)-modelviewprojection.row(1));//top
      frustrum_planes.set_col(3,modelviewprojection.row(3)+modelviewprojection.row(1));//bottom
      frustrum_planes.set_col(4,modelviewprojection.row(3)-modelviewprojection.row(2));//far
      frustrum_planes.set_col(5,modelviewprojection.row(3)+modelviewprojection.row(2));//near

         // Normalize all planes
         for(unsigned i=0;i<6;i++)
           frustrum_planes.set_col(i,frustrum_planes.col(i)/length(frustrum_planes.col(i).sub_vec(0,3)));
       return frustrum_planes;

    }
  }
}
