
//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include "owl/color/color.hpp"

namespace owl
{
  namespace color
  {
    namespace gamma_correction_model
    {
      struct s_rgb {};
      struct adobe_rgb {};
    };
  
  
    double linear_2_gamma_corrected(double u, gamma_correction_model::s_rgb cm);
  
    double gamma_corrected_2_linear(double u, gamma_correction_model::s_rgb cm);
  
    double linear_2_gamma_corrected(double u, gamma_correction_model::adobe_rgb cm);
  
    double gamma_corrected_2_linear(double u, gamma_correction_model::adobe_rgb cm);
  
  
    template <typename T, std::size_t N, bool HasAlpha, template <typename, bool> typename Derived>
    auto linear_2_gamma_corrected(const color<T, N, HasAlpha, Derived>& col, gamma_correction_model::s_rgb cm)
    {
      Derived<T, HasAlpha> res(static_cast<const math::vector<T,N>&>(col));
    
      for(auto& ch : res)
        ch = linear_2_gamma_corrected(ch, cm);
        return res;
    }
  }
}
