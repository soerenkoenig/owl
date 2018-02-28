#include "owl/render/raytracer.hpp"
#include "owl/scene/view.hpp"
#include "owl/graphics/image.hpp"
#include "owl/color/color.hpp"
#include "catch/catch.hpp"


namespace test
{
  TEST_CASE( "raytracer", "[render]" )
  {
    using namespace owl;
  
    graphics::rgb8u_image img(640, 480);
    auto graph = scene::make_graph<float>();
    auto view = scene::make_view(img, graph);
  
    render::raytracer r;
    r.render(view);
 
  
  }
}

