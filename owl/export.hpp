//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#if defined( OWL_SHARED_BUILD )
  #define OWL_API __declspec(dllexport)
#elif defined( OWL_SHARED )
  #define OWL_API __declspec(dllimport)
#else
  #define OWL_API
#endif
