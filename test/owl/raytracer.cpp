#include "owl/render/raytracer.hpp"
#include "owl/scene/view.hpp"
#include "owl/graphics/image.hpp"
#include "owl/color/color.hpp"
#include "catch/catch.hpp"
#include  "owl/scene/look_at_constraint.hpp"


namespace test
{
  TEST_CASE( "raytracer", "[render]" )
  {
    using namespace owl;
  
  
    auto scene = scene::make_graph<float>();
  
    auto camera_node = scene::make_node<float>();
    scene->root->add_child(camera_node);
    camera_node->position << 10, 10, 10;
  
  
    auto sphere_node = scene::make_node<float>();
    camera_node->constraints.push_back(scene::look_at_constraint<float>(sphere_node));
  
   // sphere_node->geometry =
    scene->root->add_child(sphere_node);
  
    graphics::rgb8u_image img(640, 480);
    auto view = scene::make_view(img, scene);
  
    render::raytracer r;
    r.render(view);
 
  
  }
}

