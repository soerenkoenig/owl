#include "owl/render/raytracer.hpp"
#include "owl/scene/view.hpp"
#include "owl/scene/mesh.hpp"
#include "owl/graphics/image.hpp"
#include "owl/scene/look_at_constraint.hpp"
#include "owl/scene/grid.hpp"
#include "owl/color/color.hpp"
#include "catch/catch.hpp"



namespace test
{
  TEST_CASE( "raytracer", "[render]" )
  {
    using namespace owl;
  
  
    scene::graph<float> scene;
  
    auto& grid_node = scene.root.add_child();
    grid_node.geometry = std::make_shared<scene::grid<float>>();
  
  
    auto& sphere_node = scene.root.add_child();
    sphere_node.geometry = std::make_shared<scene::mesh<float>>(math::create_sphere<float>(1));
  
    auto& camera_node = scene.root.add_child();

    camera_node.position << 10, 10, 10;
  
    camera_node.constraints.push_back(scene::look_at_constraint<float>(sphere_node));
  
    graphics::rgb8u_image img(640, 480);
    scene::view<color::rgb8u, float> view(img, scene);
  
    render::raytracer r;
  
   /* scene.start()
    scene.apply_actions();
    scene.apply_animation();
    scene.simulate_physics();
    */
  //  scene.evaluate_constraints();
  
  
    r.render(view);
 
  
  }
}

