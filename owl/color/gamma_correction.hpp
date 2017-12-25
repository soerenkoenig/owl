
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
  }
}
