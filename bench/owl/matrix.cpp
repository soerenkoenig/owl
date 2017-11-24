#include "benchpress/benchpress.hpp"
#include "owl/math/matrix.hpp"


namespace benchpress
{

  
  BENCHMARK("matrix multiplication", ([](benchpress::context* ctx)
  {
    auto m = owl::math::random_matrix<float,100,4>();
    auto v = owl::math::random_matrix<float,4,1>();
  

    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i)
    {
       m*v;
    }
  }))

}

