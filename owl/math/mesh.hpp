//
//           .___.
//           {o,o}
//          ./)_)
//      owl --"-"---
//
//  Copyright © 2017 Sören König. All rights reserved.
//

#pragma once

#include "owl/utils/handle.hpp"
#include "owl/utils/dynamic_properties.hpp"
#include "owl/utils/count_iterator.hpp"
#include "owl/utils/iterator_range.hpp"
#include "owl/utils/map_iterator.hpp"
#include "owl/utils/adjacent_iterator.hpp"
#include "owl/utils/range_algorithm.hpp"
#include "owl/math/matrix.hpp"
#include "owl/math/angle.hpp"
#include "owl/math/interval.hpp"
#include "owl/math/constants.hpp"

namespace owl
{
  namespace math
  {
  
    struct vertex_tag{};
    using vertex_handle = owl::utils::handle<vertex_tag>;
  
    struct halfedge_tag{};
    using halfedge_handle = owl::utils::handle<halfedge_tag>;
  
    struct edge_tag{};
    using edge_handle = owl::utils::handle<edge_tag>;
  
    struct face_tag{};
    using face_handle = owl::utils::handle<face_tag>;
 
  
    template <typename T>
    using mesh_property_handle = owl::utils::property_handle<T>;
  
    template <typename T>
    using vertex_property_handle = owl::utils::indexed_property_handle<T,vertex_tag>;
    template <typename T>
    using edge_property_handle = owl::utils::indexed_property_handle<T,edge_tag>;
    template <typename T>
    using halfedge_property_handle = owl::utils::indexed_property_handle<T,halfedge_tag>;
    template <typename T>
    using face_property_handle = owl::utils::indexed_property_handle<T,face_tag>;
  

  
    class status_flags
    {
    public:
      status_flags()
        : bits_(0)
      {}
  
    
      bool is_selected() const
      {
        return bits_.test(0);
      }
  
      void select()
      {
        bits_.set(0, true);
      }
  
      void deselect()
      {
        bits_.set(0, false);
      }
  
      void invert_selection()
      {
        if(is_selected())
          deselect();
        else
          select();
      }
    
      bool is_modified() const
      {
        return bits_.test(1);
      }
    
      void modify()
      {
        bits_.set(1, true);
      }
    
      void unmodify()
      {
        bits_.set(0, false);
      }
    
    
    
    
    
  
       /*  bool is_removed() const
      {
        return bits_.test(0);
      }
  
      void remove()
      {
        bits_.set(0, true);
      }
    
      void restore()
      {
        bits_.set(0, false);
      }*/
    
    private:
      std::bitset<8> bits_;
    };
  
    template <typename Scalar>
    class mesh
    {
    public:
      using scalar = Scalar;
    
      template <std::size_t Dim>
      using vector = vector<Scalar,Dim>;
    
      using face_iterator = owl::utils::count_iterator<face_handle>;
      using vertex_iterator = owl::utils::count_iterator<vertex_handle>;
      using edge_iterator = owl::utils::count_iterator<edge_handle>;
      using halfedge_iterator = owl::utils::count_iterator<halfedge_handle>;
    
      template <typename Range>
      using is_vertex_handle_range = std::is_same<typename utils::container_traits<std::decay_t<Range>>::value_type, vertex_handle>;
    
      template <typename Range>
      using is_halfedge_handle_range = std::is_same<typename utils::container_traits<std::decay_t<Range>>::value_type, halfedge_handle>;
    
      template <typename Range>
      using is_edge_handle_range = std::is_same<typename utils::container_traits<std::decay_t<Range>>::value_type, edge_handle>;
    
      template <typename Range>
      using is_face_handle_range = std::is_same<typename utils::container_traits<std::decay_t<Range>>::value_type, face_handle>;
    
      template <typename Range, std::size_t N = 3>
      using is_vector_range = std::is_same<typename utils::container_traits<std::decay_t<Range>>::value_type, vector<N>>;
    
    
      mesh()
      {
        add_property(vertex_position_handle_,"vertex_position");
        add_property(face_normal_handle_,"face_normal");
        add_property(halfedge_normal_handle_,"halfedge_normal");
        add_property(halfedge_texcoord_handle_,"halfedge_texcoord");
      }
    
    
      auto faces() const
      {
       return make_iterator_range(
         face_iterator(face_handle(0)),
         face_iterator(face_handle(num_faces())));
      }

      auto vertices() const
      {
       return make_iterator_range(
         vertex_iterator(vertex_handle(0)),
         vertex_iterator(vertex_handle(num_vertices())));
      }

      auto edges() const
      {
       return make_iterator_range(
         edge_iterator(edge_handle(0)),
         edge_iterator(edge_handle(num_edges())));
      }

      auto halfedges() const
      {
       return make_iterator_range(
         halfedge_iterator(halfedge_handle(0)),
         halfedge_iterator(halfedge_handle(num_halfedges())));
      }
    
      auto vertices(face_handle f, vertex_handle v_start) const
      {
        auto step = [this](halfedge_handle he)
        {
          return next(he);
        };

        auto deref = [this](halfedge_handle he)
        {
          return target(he);
        };
      
        halfedge_handle he = halfedge(f);
        while(target(he) != v_start)
          he = next(he);
      
        return make_iterator_range(
          make_handle_iterator(he, step, deref, he.is_valid() ? 0 : 1),
          make_handle_iterator(he, step, deref, 1));
      }

      auto vertices(face_handle f) const
      {
        return vertices(f,target(halfedge(f)));
      }

      auto vertices(vertex_handle v) const
      {
        auto step = [this](halfedge_handle he)
        {
          return opposite(next(he));
        };

        auto deref = [this](halfedge_handle he)
        {
          return target(he);
        };
      
        halfedge_handle he = halfedge(v);
        return make_iterator_range(
          make_handle_iterator(he, step, deref, he.is_valid() ? 0 : 1),
          make_handle_iterator(he, step, deref, 1));
      }
    
      auto incoming_halfedges(vertex_handle v) const
      {
        auto step = [this](halfedge_handle he)
        {
          return opposite(next(he));
        };

        auto deref = [this](halfedge_handle he)
        {
          return he;
        };

        halfedge_handle he = halfedge(v);

        return make_iterator_range(
          make_handle_iterator(he, step, deref, he.is_valid() ? 0 : 1),
          make_handle_iterator(he, step, deref, 1));
      }

      auto outgoing_halfedges(vertex_handle v) const
      {
        auto step = [this](halfedge_handle he)
        {
          return opposite(next(he));
        };

        auto deref = [this](halfedge_handle he)
        {
          return opposite(he);
        };
        halfedge_handle he = halfedge(v);
        return make_iterator_range(
          make_handle_iterator(he, step, deref, he.is_valid() ? 0 : 1),
          make_handle_iterator(he, step, deref, 1));
      }

      auto edges(face_handle f) const
      {
        auto step = [this](halfedge_handle he)
        {
          return next(he);
        };
     
        auto deref = [this](halfedge_handle he)
        {
          return edge(he);
        };
        halfedge_handle he = halfedge(f);
        return make_iterator_range(
          make_handle_iterator(he, step, deref,he.is_valid() ? 0 : 1),
          make_handle_iterator(he, step, deref, 1));
      }
    
      auto halfedges(face_handle f) const
      {
        return halfedges(f, halfedge(f));
      }
    
      auto halfedges(face_handle f, halfedge_handle he_start) const
      {
        auto step = [this](halfedge_handle he)
        {
          return next(he);
        };
     
        auto deref = [this](halfedge_handle he)
        {
          return he;
        };
        halfedge_handle he = halfedge(f);
        while(he != he_start)
          he = next(he);
        return make_iterator_range(
          make_handle_iterator(he, step, deref, he.is_valid() ? 0 : 1),
          make_handle_iterator(he, step, deref, 1));
      }
    
      auto halfedges(halfedge_handle he) const
      {
        auto step = [this](halfedge_handle he)
        {
          return next(he);
        };
     
        auto deref = [this](halfedge_handle he)
        {
          return he;
        };
        return make_iterator_range(
          make_handle_iterator(he, step, deref, he.is_valid() ? 0 : 1),
          make_handle_iterator(he, step, deref, 1));
      }
    
      auto outer_halfedges(face_handle f) const
      {
        auto step = [this](halfedge_handle he)
        {
          return next(he);
        };
     
        auto deref = [this](halfedge_handle he)
        {
          return opposite(he);
        };
        halfedge_handle he = halfedge(f);
        return make_iterator_range(
          make_handle_iterator(he, step, deref, he.is_valid() ? 0 : 1),
          make_handle_iterator(he, step, deref, 1));
      }

      const math::vector<Scalar,3>& position(vertex_handle v) const
      {
        return vertex_properties_[vertex_position_handle_][v.index()];
      }

      math::vector<Scalar,3>& position(vertex_handle v)
      {
        return vertex_properties_[vertex_position_handle_][v.index()];
      }

      const math::vector<Scalar,2>& texcoord(halfedge_handle he) const
      {
        return halfedge_properties_[halfedge_texcoord_handle_][he.index()];
      }

      math::vector<Scalar,2>& texcoord(halfedge_handle he)
      {
        return halfedge_properties_[halfedge_texcoord_handle_][he.index()];
      }

      const math::vector<Scalar,3>& normal(face_handle f) const
      {
        return face_properties_[face_normal_handle_][f.index()];
      }
    
      math::vector<Scalar,3>& normal(face_handle f)
      {
        return face_properties_[face_normal_handle_][f.index()];
      }
    
      const math::vector<Scalar,3>& normal(halfedge_handle he) const
      {
        return halfedge_properties_[halfedge_normal_handle_][he.index()];
      }
    
      math::vector<Scalar,3>& normal(halfedge_handle he)
      {
        return halfedge_properties_[halfedge_normal_handle_][he.index()];
      }

    
      template<typename Handle>
      status_flags& status(Handle h)
      {
        return operator[](h);
      }
    
      const vertex_handle& target(halfedge_handle he) const
      {
        return operator[](he).target;
      }
    
      vertex_handle& target(halfedge_handle he)
      {
        return operator[](he).target;
      }
    
      const vertex_handle& origin(halfedge_handle he) const
      {
        return operator[](opposite(he)).target;
      }
    
      vertex_handle& origin(halfedge_handle he)
      {
        return operator[](opposite(he)).target;
      }
    
      const vertex_handle& target(edge_handle e) const
      {
        return operator[](halfedge(e)).target;
      }
    
      vertex_handle& target(edge_handle e)
      {
        return operator[](halfedge(e)).target;
      }
    
      const vertex_handle& origin(edge_handle e) const
      {
        return operator[](opposite(halfedge(e))).target;
      }
    
      vertex_handle& origin(edge_handle e)
      {
        return operator[](opposite(halfedge(e))).target;
      }
    
      template<typename Handle>
      void selected(Handle h)
      {
        return status(h).select();
      }
    
      template<typename Handle>
      void deselected(Handle h)
      {
        return status(h).deselect();
      }
    
      template<typename Handle>
      void invert_selection(Handle h)
      {
        return status(h).invert_selection();
      }
    
      template<typename Handle>
      bool is_selected(Handle h) const
      {
        return status(h).is_selected();
      }
    
      template <typename VertexRange, typename = std::enable_if_t<is_vertex_handle_range<VertexRange>::value>>
      auto positions(VertexRange&& vertices) const
      {
        return utils::map_range([this](vertex_handle v)->const auto&{ return position(v);},
          std::forward<VertexRange>(vertices));
      }

      template <typename VertexRange, typename = std::enable_if_t<is_vertex_handle_range<VertexRange>::value>>
      auto positions(VertexRange&& vertices)
      {
        return utils::map_range([this](vertex_handle v)->auto&{ return position(v);},
          std::forward<VertexRange>(vertices));
      }

      template <typename FaceHandleRange, typename = std::enable_if_t<is_face_handle_range<FaceHandleRange>::value>>
      auto normals(FaceHandleRange&& faces) const
      {
        return utils::map_range([this](face_handle f)-> auto&{ return normal(f);},
          std::forward<FaceHandleRange>(faces));
      }

      template <typename FaceHandleRange, typename = std::enable_if_t<is_face_handle_range<FaceHandleRange>::value>>
      auto normals(FaceHandleRange&& faces)
      {
        return utils::map_range([this](face_handle f)->const auto&{ return normal(f);},
          std::forward<FaceHandleRange>(faces));
      }

      template <typename VertexHandleRange, typename = std::enable_if_t<is_vertex_handle_range<VertexHandleRange>::value>, typename = void>
      auto normals(VertexHandleRange&& vertices) const
      {
        return utils::map_range([this](vertex_handle v)->const auto&{ return normal(v);},
          std::forward<VertexHandleRange>(vertices));
      }

      template <typename VertexHandleRange, typename = std::enable_if_t<is_vertex_handle_range<VertexHandleRange>::value>, typename = void>
      auto normals(VertexHandleRange&& vertices)
      {
        return utils::map_range([this](vertex_handle v)->auto&{ return normal(v);},
          std::forward<VertexHandleRange>(vertices));
      }
    
      template <typename HalfEdgeHandleRange, typename = std::enable_if_t<is_halfedge_handle_range<HalfEdgeHandleRange>::value>, typename = void, typename = void>
      auto normals(HalfEdgeHandleRange&& halfedges) const
      {
        return utils::map_range([this](halfedge_handle he)->const auto&{ return normal(he);},
          std::forward<HalfEdgeHandleRange>(halfedges));
      }
    
      template <typename HalfEdgeHandleRange, typename = std::enable_if_t<is_halfedge_handle_range<HalfEdgeHandleRange>::value>, typename = void, typename = void>
      auto normals(HalfEdgeHandleRange&& halfedges)
      {
        return utils::map_range([this](halfedge_handle he)->auto&{ return normal(he);},
          std::forward<HalfEdgeHandleRange>(halfedges));
      }
    
      template <typename HalfEdgeHandleRange, typename = std::enable_if_t<is_halfedge_handle_range<HalfEdgeHandleRange>::value>>
      auto texcoords(HalfEdgeHandleRange&& halfedges) const
      {
        return utils::map_range([this](halfedge_handle he)->const auto&{ return texcoord(he);},
          std::forward<HalfEdgeHandleRange>(halfedges));
      }

      template <typename HalfEdgeHandleRange, typename = std::enable_if_t<is_halfedge_handle_range<HalfEdgeHandleRange>::value>, typename = void>
      auto texcoords(HalfEdgeHandleRange&& halfedges)
      {
        return utils::map_range([this](halfedge_handle he)->auto&{ return texcoord(he);},
          std::forward<HalfEdgeHandleRange>(halfedges));
      }
    
      std::size_t num_vertices() const
      {
        return vertices_.size();
      }
    
      std::size_t num_edges() const
      {
        return edges_.size();
      }

      std::size_t num_halfedges() const
      {
        return num_edges() << 1;
      }
    
      std::size_t num_faces() const
      {
        return faces_.size();
      }
    
      std::size_t num_triangles() const
      {
        auto fs =  faces();
        return std::count_if(fs.begin(), fs.end(),
         [this](face_handle f)
         {
           return is_triangle(f);
         });
      }
    
      std::size_t num_quads() const
      {
        auto fs =  faces();
        return std::count_if(fs.begin(), fs.end(),
         [this](face_handle f)
         {
           return is_quad(f);
         });
      }
    
      bool is_non_manifold(vertex_handle v) const
      {
        std::size_t n = 0;
        for(auto he : incoming_halfedges(v))
          if(is_boundary(he))
          {
            if(++n > 1)
              return true;
          }
        return false;
      }

      bool is_boundary(vertex_handle v) const
      {
        return is_boundary(halfedge(v));
      }

      bool is_boundary(halfedge_handle he) const
      {
        return !face(he).is_valid();
      }

      bool is_boundary(edge_handle e) const
      {
        auto hes = halfedges(e);
        return is_boundary(hes[0]) || is_boundary(hes[1]);
      }
 
      bool is_boundary(face_handle f, bool check_vertices = false) const
      {
        if(check_vertices)
        {
          for(auto v : vertices(f))
            if(is_boundary(v))
              return true;
          return false;
        }
        for(auto he : outer_halfedges(f))
          if(is_boundary(he))
            return true;
        return false;
      }
    
      bool is_isolated(vertex_handle v) const
      {
        return !halfedge(v).is_valid();
      }
    
      bool is_sharp(edge_handle e, const angle<Scalar>& max_angle = degrees<Scalar>(44)) const
      {
        return is_sharp(halfedge(e), max_angle);
      }
  
      bool is_sharp(halfedge_handle he, const angle<Scalar>& max_angle = degrees<Scalar>(44)) const
      {
        auto angle = std::abs(dihedral_angle(he));
        return angle >= max_angle;
      }
    
      vector<3> direction(halfedge_handle he) const
      {
        return position(target(he)) - position(origin(he));
      }
    
      Scalar length(halfedge_handle he) const
      {
        return direction(he).length();
      }
    
      Scalar length(edge_handle e) const
      {
        return length(halfedge(e));
      }
    
      edge_handle split(edge_handle e, const vector<3>& position)
      {
         return edge(split(halfedge(e), position));
      }
    
      edge_handle split(edge_handle e, vertex_handle v)
      {
        return edge(split(halfedge(e), v));
      }
    
      halfedge_handle split(halfedge_handle he, const vector<3>& position)
      {
        auto v = add_vertex(position);
        return split(he, v);
      }
    
    
      //returns first halfedge of new edge pointing to new vertices
      halfedge_handle split(halfedge_handle he, vertex_handle v)
      {
        auto he_opp = opposite(he);
        auto he_opp_prev = prev(he_opp);
        auto vold = target(he);
      
        auto e = add_edge(vold, v);
        auto he_new = halfedge(e);
        auto he_new_opp = opposite(he_new);
      
         if(halfedge(vold) == he)
          halfedge(vold) = he_new_opp;
      
        next(he_opp_prev) = he_new;
        next(he_new_opp) = next(he);
        next(he) = he_new_opp;
        next(he_new) = he_opp;
      
        target(he) = v;
        face(he_new) = face(he_opp);
        face(he_new_opp) = face(he);
        if(!face(he_new).is_valid())
         halfedge(v) = he_new;
        else
          halfedge(v) = he;
        
        return he_new;
      }
    
      auto split_edges()
      {
        auto first = edge_handle{num_edges()};
        for(auto e : edges())
        {
          auto pos = centroid(e);
          split(e, pos);
        }
        return make_iterator_range(
         edge_iterator(first),
         edge_iterator(edge_handle{num_edges()}));
      }
    
      void reserve_vertices(std::size_t n)
      {
        vertices_.reserve(n);
        vertex_properties_.reserve(n);
      }
    
      void reserve_edges(std::size_t n)
      {
        edges_.reserve(n);
        edge_properties_.reserve(n);
        halfedge_properties_.reserve(2*n);
      }
    
      void reserve_faces(std::size_t n)
      {
        faces_.reserve(n);
        face_properties_.reserve(n);
      }
    
      void subdivide_quad_split()
      {
        assert(is_quad_mesh());
        reserve_vertices(num_vertices() + num_faces());
        reserve_edges(2 * num_edges() + 4 * num_faces());
        reserve_faces(4 * num_faces());
      
        std::size_t num_vertices_old = vertices_.size();
        split_edges();
      
        auto is_old_vertex = [&](vertex_handle v)
          {
            return v.index() < num_vertices_old;
          };
      
        for(auto f : faces())
        {
          auto he_prev = halfedge(f);
          if(is_old_vertex(target(he_prev)))
            he_prev = next(he_prev);
        
          auto he_next = next(next(next(he_prev)));
          auto e = insert_edge(he_prev, he_next);
          auto v = target(split_edge(e, centroid(f)));
          he_prev = next(he_prev);
          he_next = next(next(he_next));
          while(he_next != he_prev)
          {
            insert(edge(he_prev,he_next));
            he_next = next(next(he_next));
          }
          insert_edge(he_prev,he_next);
        }
      }
    
      void subdivide_triangle_split()
      {
        assert(is_triangle_mesh());
      
        reserve_vertices(num_vertices() + num_edges());
        reserve_faces(4 * num_faces());
        reserve_edges(2 * num_edges() + 3 * num_faces());
  
        std::size_t num_vertices_old = vertices_.size();
        split_edges();
      
        auto is_old_vertex = [&](vertex_handle v)
          {
            return v.index() < num_vertices_old;
          };
      
        for(auto f : faces())
        {
          auto he_prev = halfedge(f);
          if(is_old_vertex(target(he_prev)))
            he_prev = next(he_prev);
          
          auto he_next = next(next(next(he_prev)));
          insert_edge(he_prev, he_next);
          he_prev = next(he_prev);
          he_next = next(next(he_next));
          insert_edge(he_prev, he_next);
          he_prev = next(he_prev);
          he_next = next(next(he_next));
          insert_edge(he_prev, he_next);
        }
      }
    
      face_handle create_face(halfedge_handle he)
      {
      
        faces_.emplace_back(he);
        return face_properties_.add_elem();
      
      }
    
     /* void subdivide_vertex_split()
      {
      
      }*/
    
      // inserts an edge between target(he_prev) and origin(he_next).
      // returns the halfedge containing the new face
      //assumes he and he_next belong to the same face
      halfedge_handle insert_edge(halfedge_handle he_prev, halfedge_handle he_next)
      {
        auto e = add_edge(target(he_prev), origin(he_next));
        auto he = halfedge(e);
        auto he_opp = opposite(he);
        auto fold =  face(he_prev);
        face(he_opp) = face(he_prev);
        halfedge(fold) = he_opp;
        next(he_opp) = next(he_prev);
        next(he_prev) = he;
        next(he) = he_next;
        next(prev(he_next)) = he_opp;
        auto f_new = create_face(he);
        face(he) = f_new;
        halfedge(f_new) = he;
        auto he2 = next(he);
        while(he2 != he)
        {
          face(he2) = f_new;
          he2 = next(he2);
        }
        normal(f_new) = compute_normal(f_new);
        return he;
      }
    
      void split(face_handle f, const vector<3>& pos)
      {
        split(f, add_vertex(pos));
      }
    
      vector<3> centroid(halfedge_handle he) const
      {
        return (position(target(he)) + position(origin(he)))/2;
      }
    
      vector<3> centroid(edge_handle e) const
      {
        return centroid(halfedge(e));
      }
    
      vector<3> centroid(face_handle f) const
      {
        auto points = positions(vertices(f));
        vector<3> mp = vector<3>::zero();
        std::size_t n = 0;
        for(auto p : points)
        {
          mp += p;
          ++n;
        }
        return mp / n;
      }
    
      void split(face_handle f, vertex_handle v)
      {
        auto hes = halfedges(f);
        std::vector<halfedge_handle> hes_old(hes.begin(), hes.end());
        std::vector<edge_handle> edges_new;
        for(auto he : hes_old)
        {
          split(he, centroid(he));
          auto e = add_edge(target(he), v);
          edges_new.push_back(e);
          next(opposite(halfedge(e))) = next(he);
          next(he) = halfedge(e);
        }
      
        for(auto e : utils::make_adjacent_range(edges_new))
        {
          auto he2 = halfedge(e.current);
          if(f == faces_.size())
            create_face(he2);
          else
            halfedge(f) = he2;
          auto he_start = he2;
          next(he2) = opposite(halfedge(e.prev));
          do
          {
            face(he2) = f;
            he2 = next(he2);
          }
          while(he2 != he_start);
        
          f = faces_.size();
        
        }
        halfedge(v) = halfedge(edges_new.front());
      }
    
      angle<Scalar> sector_angle(halfedge_handle he) const
      {
        auto v0 = direction(next(he));
        auto v1 = direction(opposite(he));
        auto denom = v0.length() * v1.length();
        
        if(denom == Scalar(0))
          return 0;
    
        Scalar cos_a = dot(v0 , v1) / denom;
        cos_a = std::clamp(cos_a, -1, 1);
        if(is_boundary(he))
        {
          vector<3> f_n(compute_loop_normal(opposite(he)));
          Scalar sign_a = dot(cross(v0, v1), f_n);
          return radians<Scalar>(sign_a >= 0 ? acos(cos_a) : -acos(cos_a));
        }
        else
        {
          return radians<Scalar>(acos(cos_a));
        }
      }

      angle<Scalar> dihedral_angle(halfedge_handle he) const
      {
        return dihedral_angle(edge(he));
      }
    
      angle<Scalar> dihedral_angle(edge_handle e) const
      {
        if(is_boundary(e))
          return radians<Scalar>(0);

        vector<3> n0, n1;
        halfedge_handle he = halfedge(e);
        n0 = compute_sector_normal(he);
        n1 = compute_sector_normal(opposite(he));
        auto he_dir = direction(he);
        Scalar denom = n0.length() * n1.length();
        if(denom == 0)
          return 0;
        Scalar da_cos = dot(n0, n1) / denom;
        da_cos = std::clamp(da_cos, -1, 1);
        Scalar da_sin_sign = dot(cross(n0, n1), he_dir);
        return angle<Scalar>(da_sin_sign >= 0 ? acos(da_cos) : -acos(da_cos));
      }
    
      vector<3> compute_sector_normal(halfedge_handle he, bool normalize = true) const
      {
        auto nml = cross(direction(next(he)), direction(opposite(he)));
        if(normalize)
          nml.normalize();
        return nml;
      }
    
      vector<3> compute_loop_normal(halfedge_handle he) const
      {
        auto nml = vector<3>::zero();
      
        for(auto he : halfedges(he))
          nml += compute_sector_normal(he, false);
      
        nml.normalize();
        return nml;
      }
    
      vector<3> compute_normal(face_handle f) const
      {
        return compute_loop_normal(halfedge(f));
      }
    
      vector<3> compute_normal(vertex_handle v) const
      {
        auto nml = vector<3>::zero();
      
        for(auto he : incoming_halfedges(v))
          nml += compute_sector_normal(he, false);
      
        nml.normalize();
        return nml;
      }
    
      void update_face_normals()
      {
        for(auto f : faces())
          normal(f) = compute_normal(f);
      }
    
      template <typename Handle>
      std::size_t valence(Handle h) const
      {
        return std::size(vertices(h));
      }

      bool is_ngon_mesh(std::size_t n) const
      {
        for(auto face: faces())
          if(valence(face) != n)
            return false;
        return true;
      }

      bool is_quad_mesh() const
      {
        return is_ngon_mesh(4);
      }

      bool is_triangle_mesh() const
      {
        return is_ngon_mesh(3);
      }
    
      bool is_triangle(face_handle f) const
      {
        auto  he = halfedge(f);
        return he == next(next(next(he)));
      }
    
      bool is_quad(face_handle f) const
      {
        auto  he = halfedge(f);
        return he == next(next(next(next(he))));
      }
    
      bool is_convex(face_handle f) const
      {
        std::size_t n = valence(f);
        if(n < 4)
          return true;
      
        auto [u,v] = min_abs_components(normal(f));

        math::interval<Scalar> zrange;
        for(auto he : halfedges(f))
        {
          vector<3> d1 = position(target(next(he))) - position(target(he));
          vector<3> d2 = position(target(opposite(he))) - position(target(he));
          Scalar z = d1[u] * d2[v] - d1[v] * d2[u];
          zrange.insert(z);
        }
        return (zrange.lower_bound >= 0 && zrange.upper_bound >= 0) ||
               (zrange.lower_bound <= 0 && zrange.upper_bound <= 0);
      }
    
      math::box<Scalar> bounds() const
      {
        box<Scalar> bbox;
        for(auto p : positions(vertices()))
          bbox.insert(p);
        return bbox;
      }
    
      bool is_open() const
      {
        for(auto he: halfedges())
          if(is_boundary(he))
            return true;
        return false;
      }
    
      bool is_closed() const
      {
        return !is_open();
      }
    
      void clear()
      {
        faces_.clear();
        face_properties_.clear();
        edges_.clear();
        edge_properties_.clear();
        halfedge_properties_.clear();
        vertices_.clear();
        vertex_properties_.clear();
      }
    
      bool empty() const
      {
        return faces_.empty() && vertices_.empty() && edges_.empty();
      }
    
    
      auto add_vertex(const vector<3>& pos)
      {
        vertices_.emplace_back();
        auto v = vertex_properties_.add_elem();
        position(v) = pos;
        return v;
      }
    
      template <typename VectorRange, typename = std::enable_if_t<is_vector_range<VectorRange>::value>>
      auto add_vertices(VectorRange&& points)
      {
        auto n = std::size(points);
        vertices_.resize(num_vertices() + n);
        auto verts = vertex_properties_.add_elems(n);
        owl::utils::copy(points, positions(verts).begin());
        return verts;
      }
    
      template <typename... VertexHandles, typename = std::enable_if_t<(... && std::is_same<std::decay_t<VertexHandles>,vertex_handle>::value)>>
      face_handle add_face(VertexHandles&&... vertices)
      {
         return add_face(std::array<vertex_handle, sizeof...(vertices)> { std::forward<VertexHandles>(vertices)... });
      }
    
    
      //ensures the first vertex of returned face is the vertices.front()
      //adding a face which results in a non-manifold vertex is not allowed
      template <typename VertexHandleRange, typename = std::enable_if_t<is_vertex_handle_range<VertexHandleRange>::value>>
      face_handle add_face(VertexHandleRange&& vertices)
      {
        face_handle f = face_handle{faces_.size()};
      
        std::vector<halfedge_handle> hes;
        hes.reserve(std::size(vertices));
      
        for(auto v : owl::utils::make_adjacent_range(vertices))
        {
          auto he = find_halfedge(v.prev, v.current);
          if (!he.is_valid())
            he = halfedge(add_edge(v.prev, v.current));
          else
            assert(is_boundary(he));
          face(he) = f;
          hes.push_back(he);
        }
        create_face(hes.back());
      
        for(auto he : owl::utils::make_adjacent_range(hes))
        {
          if(next(he.current) != he.next)
          {
            auto he_outer = opposite(he.next);
            auto he_outer_next = next(he_outer);
            if(he_outer_next.is_valid())
            {
              while(he_outer_next != he.next || he_outer == he.current)
              {
                he_outer = opposite(he_outer_next);
                he_outer_next = next(he_outer);
              }
              if(he_outer == he.current)
              {
                auto he_a = opposite(he.next);
                while(!is_boundary(he_a))
                  he_a = opposite(next(he_a));
                auto he_b = prev(he.next);
                next(he_b) = next(he_a);
                next(he_a) = next(he_outer);
                next(he_outer) = he.next;
              }
              else
               next(he_outer) = opposite(he.current);
            }
            else
            {
              if(next(he.current).is_valid())
                next(he_outer) = next(he.current);
              else
              {
                auto he_p = halfedge(target(he.current));
                if(he_p.is_valid() && is_boundary(he_p))
                {
                 next(he_outer) = next(he_p);
                 next(he_p) = opposite(he.current);
                }
                else
                  next(he_outer) = opposite(he.current);
              }
            }
            next(he.current) = he.next;
            auto v = target(he.current);
            if(is_isolated(v))
              halfedge(v) = he.current;
            adjust_halfedge(v);
          }
        }
      
        normal(f) = compute_normal(f);
        for(auto he : halfedges(f))
          normal(he) = normal(f);
        return f;
      }
    
      template <typename TexCoordRange, typename = std::enable_if_t<is_vector_range<TexCoordRange,2>::value>>
      void set_face_texcoords(face_handle f, TexCoordRange&& texcoords)
      {
        owl::utils::copy(texcoords,this->texcoords(halfedges(f)).begin());
      }
    
      template <typename NormalRange, typename = std::enable_if_t<is_vector_range<NormalRange,3>::value>>
      void set_face_normals(face_handle f, NormalRange&& normals)
      {
        owl::utils::copy(normals, this->normals(halfedges(f)).begin());
      }
    
      //ensure halfedge of v is a boundary halfedge if v is on boundary
      void adjust_halfedge(vertex_handle v)
      {
        for(auto he : incoming_halfedges(v))
        {
          if(is_boundary(he))
          {
            halfedge(v) = he;
            break;
          }
        }
      }
    
      template <typename T>
      void add_property(vertex_property_handle<T>& ph, const std::string& name = "")
      {
        return vertex_properties_.add_property(ph, name);
      }
    
      template <typename T>
      void add_property(edge_property_handle<T>& ph, const std::string& name = "")
      {
        return edge_properties_.add_property(ph, name);
      }
    
      template <typename T>
      void add_property(halfedge_property_handle<T>& ph, const std::string& name = "")
      {
        return halfedge_properties_.add_property(ph, name);
      }
    
      template <typename T>
      void add_property(face_property_handle<T>& ph, const std::string& name = "")
      {
        face_properties_.add_property(ph, name);
      }
    
      template <typename T>
      void add_property(mesh_property_handle<T>& ph, const std::string& name = "")
      {
        mesh_properties_.add_property(ph, name);
      }
    
      template <typename T>
      void remove_property(vertex_property_handle<T>& ph)
      {
        vertex_properties_.remove_property(ph);
      }
    
      template <typename T>
      void remove_property(edge_property_handle<T>& ph)
      {
        edge_properties_.remove_property(ph);
      }
    
      template <typename T>
      void remove_property(halfedge_property_handle<T>& ph)
      {
        halfedge_properties_.remove_property(ph);
      }
    
      template <typename T>
      void remove_property(face_property_handle<T>& ph)
      {
        face_properties_.remove_property(ph);
      }
    
      template <typename T>
      void remove_property(mesh_property_handle<T>& ph)
      {
        mesh_properties_.remove_property(ph);
      }
    
      const face_handle& face(halfedge_handle he) const
      {
        return operator[](he).face;
      }
    
    
      halfedge_handle opposite(halfedge_handle he) const
      {
        return he.index() % 2  == 0 ? halfedge_handle{he.index() + 1} : halfedge_handle{he.index() - 1};
      }
    
      const halfedge_handle& halfedge(face_handle f) const
      {
        return operator[](f).halfedge;
      }
    
      const halfedge_handle& next(halfedge_handle he) const
      {
        return operator[](he).next;
      }
    
      const halfedge_handle& halfedge(vertex_handle v) const
      {
        return operator[](v).halfedge;
      }
    
      halfedge_handle prev(halfedge_handle he) const
      {
        auto prev_he = opposite(next(opposite(he)));
        auto prev_next_he = next(prev_he);
        while(prev_next_he != he)
        {
          prev_he = opposite(prev_next_he);
          prev_next_he = next(prev_he);
        }
        return prev_he;
      }
    
      edge_handle edge(halfedge_handle he) const
      {
        return edge_handle(he.index() >> 1);
      }
    
      halfedge_handle halfedge(edge_handle e) const
      {
        return halfedge_handle{e.index() << 1};
      }
    
      std::array<halfedge_handle,2> halfedges(edge_handle e) const
      {
        halfedge_handle he = halfedge_handle{e.index() << 1};
        halfedge_handle he_opp = he + 1;
        return {he, he_opp};
      }

   private:
   
      struct vertex_t
      {
        vertex_t() = default;
        halfedge_handle halfedge;
        status_flags status;
      };
   
      struct halfedge_t
      {
        halfedge_t() = default;
        halfedge_t(vertex_handle to, face_handle f = face_handle{})
          : target{to}
          , face{f}
        {
        }
     
        vertex_handle target;
        halfedge_handle next;
        face_handle face;
        status_flags status;
      };
    
      struct edge_t
      {
        edge_t(vertex_handle from, vertex_handle to)
          : halfedges {halfedge_t(to), halfedge_t(from)}
        {
        }
     
        std::array<halfedge_t,2> halfedges;
        status_flags status;
      };
    
      struct face_t
      {
        face_t() = default;
     
        face_t(halfedge_handle he)
          : halfedge{he}
        {
        }
     
        halfedge_handle halfedge;
        status_flags status;
      };
    
      face_handle& face(halfedge_handle he)
      {
       return operator[](he).face;
      }
    
      halfedge_handle& halfedge(face_handle f)
      {
        return operator[](f).halfedge;
      }
    
      halfedge_handle& halfedge(vertex_handle v)
      {
        return operator[](v).halfedge;
      }
    
      halfedge_handle& next(halfedge_handle he)
      {
        return operator[](he).next;
      }
    
      auto operator[](edge_handle e)
      {
        auto he = halfedge(e);
        return std::tie(operator[](he), operator[](he + 1));
      }
    
      auto operator[](edge_handle e) const
      {
        auto he = halfedge(e);
        return std::tie(operator[](he), operator[](he + 1));
      }

      auto& operator[](halfedge_handle he)
      {
        edge_handle e = edge(he);
        return edges_[e.index()].halfedges[he.index() - (e.index() << 1)];
      }
        
      const auto& operator[](halfedge_handle he) const
      {
        edge_handle e = edge(he);
        return edges_[e.index()].halfedges[he.index() - (e.index() << 1)];
      }

      auto& operator[](face_handle f)
      {
        return faces_[f.index()];
      }

      const auto& operator[](face_handle f) const
      {
        return faces_[f.index()];
      }
    
      auto& operator[](vertex_handle v)
      {
        return vertices_[v.index()];
      }

      const auto& operator[](vertex_handle v) const
      {
        return vertices_[v.index()];
      }
    
      halfedge_handle find_halfedge(vertex_handle from, vertex_handle to) const
      {
        auto hes = outgoing_halfedges(from);
          for(auto he : hes)
            if(target(he) == to)
              return he;
        return halfedge_handle{};
      }

      edge_handle find_edge(vertex_handle from, vertex_handle to) const
      {
        halfedge_handle he = find_halfedge(from,to);
        if(he.is_valid())
          return edge(he);

       return edge_handle{};
      }
    
      edge_handle add_edge(vertex_handle from, vertex_handle to)
      {
        edges_.emplace_back(from, to);
        halfedge_properties_.add_elems(2);
        return edge_properties_.add_elem();
      }

      template <typename S>
      friend std::size_t check_mesh(const mesh<S>& m);
    
    
      std::vector<edge_t> edges_;
      std::vector<vertex_t> vertices_;
      std::vector<face_t> faces_;

      vertex_property_handle<vector3<Scalar>> vertex_position_handle_;
      face_property_handle<vector3<Scalar>> face_normal_handle_;
      halfedge_property_handle<vector3<Scalar>> halfedge_normal_handle_;
      halfedge_property_handle<vector2<Scalar>> halfedge_texcoord_handle_;
    
      utils::indexed_property_container<vertex_tag> vertex_properties_;
      utils::indexed_property_container<edge_tag> edge_properties_;
      utils::indexed_property_container<halfedge_tag> halfedge_properties_;
      utils::indexed_property_container<face_tag> face_properties_;
      utils::property_container mesh_properties_;
    };
  
  
   template <typename Scalar>
   std::size_t check_mesh(const mesh<Scalar>& m)
   {
     std::size_t count_error = 0;
     for(auto v: m.vertices())
     {
       if(m.is_isolated(v))
       {
         std::cout << "mesh contains isolated vertex "<< v << std::endl;
         ++count_error;
       }
     }
   
     for(auto f: m.faces())
     {
       for(auto he : m.halfedges(f))
       {
         if(m.face(he) != f)
         {
           std::cout << "face " << f << "contains inconsistent halfedge "<< he <<std::endl;
            ++count_error;
         }
       }
     }
     for(auto he: m.halfedges())
     {
        if(m.next(m.prev(he)) != he)
        {
          std::cout << "next halfedge of halfedge " << m.prev(he) << "is "<<m.next(m.prev(he)) << "instead of "<< he <<std::endl;
          ++count_error;
        }
         
     }
   
     return count_error;
   }
  
   /*
   
   Y is above
    
    Y
    2 -- 3
   /.   /|
  6 -- 7 |
  | 0..|.1  X
  |.   |/
  4 -- 5
 Z
 */
    template <typename Scalar>
    mesh<Scalar> create_box()
    {
     std::array<math::vector<Scalar,3>,8> positions = {math::vector<Scalar,3>{0,0,0},
     math::vector<Scalar,3>{1,0,0},
     math::vector<Scalar,3>{0,1,0},
     math::vector<Scalar,3>{1,1,0},
     math::vector<Scalar,3>{0,0,1},
     math::vector<Scalar,3>{1,0,1},
     math::vector<Scalar,3>{0,1,1},
     math::vector<Scalar,3>{1,1,1}};
     mesh<float> m;
     auto vertices = m.add_vertices(positions);
    
     std::array<math::vector<Scalar,2>,4> texcoord_right =
     {
      math::vector<Scalar,2>{0.5,0.25},
      math::vector<Scalar,2>{0.5,0.5},
      math::vector<Scalar,2>{0.75,0.5},
      math::vector<Scalar,2>{0.75,0.25}
     };
     m.set_face_texcoords(m.add_face(vertices[1],vertices[3],vertices[7],vertices[5]), texcoord_right);

    
    
     std::array<math::vector<Scalar,2>,4> texcoord_left =
     {
      math::vector<Scalar,2>{0,0.5},
      math::vector<Scalar,2>{0.25,0.5},
      math::vector<Scalar,2>{0.25,0.25},
      math::vector<Scalar,2>{0,0.25}
     };
    m.set_face_texcoords(m.add_face(vertices[0],vertices[4],vertices[6],vertices[2]),texcoord_left);
    
    
     std::array<math::vector<Scalar,2>,4> texcoord_top =
     {
      math::vector<Scalar,2>{0.25,0.0},
      math::vector<Scalar,2>{0.25,0.25},
      math::vector<Scalar,2>{0.5,0.25},
      math::vector<Scalar,2>{0.5,0.0}
     };
     m.set_face_texcoords(m.add_face(vertices[2], vertices[6], vertices[7], vertices[3]), texcoord_top);
    
     std::array<math::vector<Scalar,2>,4> texcoord_bottom =
     {
      math::vector<Scalar,2>{0.25,0.75},
      math::vector<Scalar,2>{0.5,0.75},
      math::vector<Scalar,2>{0.5,0.5},
      math::vector<Scalar,2>{0.25,0.5}
     };
     m.set_face_texcoords(m.add_face(vertices[0], vertices[1], vertices[5], vertices[4]), texcoord_bottom);
    
      std::array<math::vector<Scalar,2>,4> texcoord_front =
     {
      math::vector<Scalar,2>{0.25,0.5},
      math::vector<Scalar,2>{0.5,0.5},
      math::vector<Scalar,2>{0.5,0.25},
      math::vector<Scalar,2>{0.25,0.25}
     };
     m.set_face_texcoords(m.add_face(vertices[4], vertices[5], vertices[7], vertices[6]), texcoord_front);
    
     std::array<math::vector<Scalar,2>,4> texcoord_back =
     {
      math::vector<Scalar,2>{1,0.5},
      math::vector<Scalar,2>{1.0,0.25},
      math::vector<Scalar,2>{0.75,0.25},
      math::vector<Scalar,2>{0.75,0.5}
     };
     m.set_face_texcoords(m.add_face(vertices[0],vertices[2],vertices[3],vertices[1]), texcoord_back);
    
     return m;
    
    }
  
    template <typename Scalar>
    mesh<Scalar> create_tetradedron()
    {
      std::array<math::vector<Scalar,3>,4> positions = {math::vector<Scalar,3>{0,0,0},
      math::vector<Scalar,3>{1,0,0},
      math::vector<Scalar,3>{0,1,0},
      math::vector<Scalar,3>{0,0,1}};
   
      mesh<float> m;
      auto vertices = m.add_vertices(positions);
    
      m.add_face(vertices[0], vertices[2], vertices[1]);
      m.add_face(vertices[0], vertices[3], vertices[2]);
      m.add_face(vertices[0], vertices[1], vertices[3]);
      m.add_face(vertices[1], vertices[2], vertices[3]);
  
      return m;
    }
  
    template <typename Scalar>
    mesh<Scalar> create_icosaeder(const Scalar& radius = Scalar(1))
    {
      mesh<Scalar> m;
  
      Scalar a  = (Scalar)(radius * 4.0/sqrt(10.0 + 2.0 * sqrt(5.0)));
      Scalar h = (Scalar)cos(2.0 * asin(a/(2.0 * radius))) * radius;
      Scalar r2 = (Scalar)sqrt(radius * radius - h * h);
    
      std::array<vector<Scalar,3>, 12> points;
      int k = 0;
      points[k++] =  vector<Scalar,3>(0,radius,0);
      for(int i = 0; i < 5; i++)
        points[k++] = vector<Scalar,3>(cos(i * degrees<Scalar>(72)) * r2, h, -sin(i * degrees<Scalar>(72)) * r2);
      for(int i = 0; i < 5; i++)
       points[k++] = vector<Scalar,3>(cos(degrees<Scalar>(36) + i * degrees<Scalar>(72)) * r2, -h, -sin(degrees<Scalar>(36) + i * degrees<Scalar>(72)) * r2);
      points[k] = vector<Scalar,3>(0, -radius, 0);

      auto vhandles = m.add_vertices(points);
    
      for(std::size_t i = 0; i < 5; i++)
      {
        m.add_face(vhandles[0], vhandles[i + 1], vhandles[(i + 1) % 5 + 1]);
        m.add_face(vhandles[11], vhandles[(i + 1) % 5 + 6], vhandles[i + 6]);
        m.add_face(vhandles[i + 1], vhandles[i + 6], vhandles[(i + 1) % 5 + 1]);
        m.add_face(vhandles[(i + 1) % 5 + 1], vhandles[i + 6], vhandles[(i + 1) % 5 + 6]);
      }
      return m;
    }
  
     template <typename Scalar>
    mesh<Scalar> create_triangle()
    {
      mesh<Scalar> m;
    
      std::array<vector3<Scalar>,3> positions =
      {vector3<Scalar>{0, 0,  0},
       vector3<Scalar>{1, 0,  0},
       vector3<Scalar>{(Scalar)0.5,(Scalar) 1,  0}};
      auto vhandles = m.add_vertices(positions);

      m.add_face(vhandles[0], vhandles[1], vhandles[2]);
    
      return m;
    }
  
  template <typename Scalar, typename Scalar2>
  mesh<Scalar> create_geodesic_sphere(Scalar2 radius = 1, std::size_t levels = 2)
  {
    mesh<Scalar> m = create_icosaeder<Scalar>(radius);
  
    for(std::size_t i = 0; i < levels; ++i)
    {
      auto n_old  = m.vertices().size();
      m.subdivide_triangle_split();
      auto verts = m.vertices();
    
      for(auto& pos: m.positions(make_iterator_range(verts).advance_begin(n_old)))
        pos = radius * normalize(pos);
    }
    for(auto v: m.vertices())
    {
      for(auto& nml : m.normals(m.incoming_halfedges(v)))
        nml = normalize(m.position(v));
    }
    return m;
  }
  
  //create a sphere mesh
  template <typename Scalar, typename Scalar2>
  mesh<Scalar> create_sphere(Scalar2 radius, std::size_t slices = 48, std::size_t stacks = 48)
  {
    assert(slices >= 3 && stacks >= 3);
  
    mesh<Scalar> m;
  
    std::size_t n = slices * (stacks - 1) + 2;
    std::vector<vector<Scalar,3>> positions;
    positions.reserve(n);

    positions.emplace_back(0, radius, 0);
  
    int k = 1;
    for(int i = 1; i < stacks; i++)
    {
      Scalar angle1 = constants::pi_2<Scalar> - (Scalar)(i * constants::pi<Scalar>)/(Scalar)stacks;
      Scalar r = cos(angle1) * radius;
      Scalar height = sin(angle1) * radius;

      for(int j = 0; j < slices; j++)
      {
        Scalar angle2 = (Scalar)(j * constants::two_pi<Scalar>) / (Scalar)(slices);
        positions.emplace_back(cos(angle2) * r, height, sin(angle2) * r);
        ++k;
      }
    }
  
    positions.emplace_back(0, -radius, 0);
    auto vhandles = m.add_vertices(positions);
  
    for(int i = 0; i < slices; i++)
    {
      m.add_face(vhandles[0], vhandles[1 + (1 + i) % slices], vhandles[1 + i % slices]);
    
      for(std::size_t j = 0; j < stacks-2; ++j)
      {
        std::size_t a,b,c,d;
        a = 1 + j * slices + i % slices;
        b = 1 + j * slices + (1 + i) % slices;
        c = 1 + (j + 1) * slices + (1 + i) % slices;
        d = 1 + (j + 1) * slices + i % slices;
        m.add_face(vhandles[a], vhandles[b], vhandles[c], vhandles[d]);
      }
      m.add_face(vhandles[1 + slices * (stacks - 1)],
          vhandles[1 + (stacks - 2) * slices + i % slices],
          vhandles[1 + (stacks - 2) * slices + (1 + i) % slices]);
    }
  
    for(auto v: m.vertices())
    {
      for(auto& nml : m.normals(m.incoming_halfedges(v)))
        nml = normalize(m.position(v));
    }

    return m;
  }
  
  template <typename Scalar, typename Scalar2, typename Scalar3>
  mesh<Scalar> create_cylinder(Scalar2 radius, Scalar3 height, std::size_t stacks, std::size_t slices)
  {
    assert(slices >= 3 && stacks >= 1);

    mesh<Scalar> m;
  
    std::size_t n = 2 + slices * (stacks + 1);
    std::vector<vector<Scalar,3> > positions;
    positions.reserve(n);
  
    positions.emplace_back(0, height, 0);

 
    for(std::size_t i = 0; i < stacks + 1; i++)
    {
      Scalar h = (stacks - i) * height / stacks;

      for(std::size_t j = 0; j < slices; j++)
      {
        Scalar angle2 = (Scalar)(j*constants::two_pi<Scalar>)/(Scalar)(slices);
        positions.emplace_back(cos(angle2)*radius, h, sin(angle2)*radius);
      }
    }

    positions.emplace_back(0,0,0);
    auto vhandles = m.add_vertices(positions);

    for(std::size_t i = 0; i < slices; ++i)
    {
      m.add_face(vhandles[0], vhandles[1 + (1 + i) % slices], vhandles[1 + i % slices]);
  
      for(int j = 0; j < stacks; ++j)
      {
        std::size_t a,b,c,d;
        a = 1 + j * slices + i%slices;
        b = 1 + j * slices + (1 + i) % slices;
        c = 1 + (j + 1) * slices + (1+i) % slices;
        d = 1 + (j + 1) * slices + i % slices;
        m.add_face(vhandles[a], vhandles[b], vhandles[c], vhandles[d]);
      }
      m.add_face(vhandles[vhandles.size() - 1],
      vhandles[1 + stacks * slices + i % slices],
      vhandles[1 + stacks * slices + (1 + i) % slices]);
    }
    return m;
  }
  
  template <typename Scalar>
  mesh<Scalar> create_torus(Scalar r, Scalar R, std::size_t nsides, std::size_t rings)
  {
    assert(nsides >= 3 && rings >= 3);
    mesh<Scalar> m;

    std::size_t n = rings * nsides;
    std::vector<vector<Scalar,3>> positions;
    positions.reserve(n);
    std::size_t k = 0;
    for(std::size_t i = 0; i < rings; ++i)
    {
      Scalar angle1 = (Scalar)(i * constants::two_pi<Scalar> / rings);
      vector<Scalar,3> center(cos(angle1) * R, 0, sin(angle1) * R);
      vector<Scalar,3> t1(cos(angle1), 0, sin(angle1));
      vector<Scalar,3> t2(0, 1, 0);

      for(std::size_t j = 0; j < nsides; ++j)
      {
        Scalar angle2 = (Scalar)(j*constants::two_pi<Scalar>/nsides);
        positions.push_back(center + (Scalar)(sin(angle2) * r) * t1+(Scalar)(cos(angle2) * r) * t2);
      //  m.texcoord(vhandles[k]).set(angle1/(2*3.14159f),angle2/(2*3.14159f)) ;
        k++;
      }
    }
    auto vhandles = m.add_vertices(positions);

    for(std::size_t i = 0; i < rings; ++i)
    {
      for(std::size_t j = 0; j < nsides; ++j)
      {
        std::size_t a,b,c,d;
        a = (i+1)%(rings)*(nsides)+j;
        b = (i+1)%(rings)*(nsides)+(j+1)%(nsides);
        c = i*(nsides)+(j+1)%(nsides);
        d = i*(nsides)+j;
        m.add_face(vhandles[a], vhandles[b], vhandles[c], vhandles[d]);
      }
    }
    return m;
  }
  
  template <typename Scalar, typename Scalar2>
  mesh<Scalar> create_disk(Scalar2 radius, std::size_t slices)
  {
    mesh<Scalar> m;
    std::vector<vector<Scalar,3>> positions;
    positions.reserve(slices + 1);
    positions.emplace_back(0, 0, 0);
  
    for(std::size_t i = 0; i < slices; ++i)
    {
      Scalar angle= -i * constants::two_pi<Scalar>/slices;
      positions.emplace_back(cos(angle) * radius, 0, sin(angle) * radius);
    }
    auto vhandles = m.add_vertices(positions);
    for(std::size_t i = 0; i < slices; ++i)
    {
      m.add_face(vhandles[0], vhandles[1 + i % slices], vhandles[1 + (1 + i) % slices]);
    }
  
    return m;
  }
  
  template <typename Scalar, typename Scalar2>
  mesh<Scalar> create_octaeder(Scalar2 radius)
  {
    mesh<Scalar> m;
  
    std::vector<vector<Scalar,3>> positions;
    positions.reserve(6);
  
    positions.emplace_back(0, radius, 0);
  
    for(std::size_t i = 0; i < 4; ++i)
      positions.emplace_back((Scalar)cos(i * constants::pi_2<Scalar>) * radius, 0, -(Scalar)sin(i * constants::pi_2<Scalar>) * radius);

    positions.emplace_back(0, -radius, 0);
    auto vhandles = m.add_vertices(positions);

    for(std::size_t i = 0; i < 4; i++)
    {
      m.add_face(vhandles[0], vhandles[i + 1], vhandles[(i + 1) % 4 + 1]);
      m.add_face(vhandles[5], vhandles[(i + 1) % 4 + 1], vhandles[i + 1]);
    }
    return m;
  }
  
  


  
  
    //sphere
    //radius
    //segment count
  
  
  
    //tube
  
  
    //pyramid
    // width x, height y, length z
    //width/height/length segment count
  
    //torus
    //ring radius / pipe radius
    //ring /pipe segment count
  
    //cone
    //radius /height
    //radial/height segment count
  
    //plane
     // width, height
     //radial /height segment count
  
   //cone
   // top, bottom  radius , height
  
    //todo capsule
    // radius, height (ydir)
    //radial-,  cap-, height segment count
  
  
  /*
  
   template <typename mesh>
mesh create_triangle()
{
  typedef typename primitive_traits<mesh>::scalar scalar;
  mesh m;
  std::vector<vertex_handle> vhandles = m.add_vertices(3);
  m.position(vhandles[0]).set(0, 0,  0);
  m.position(vhandles[1]).set((scalar)1, 0,  0);
  m.position(vhandles[2]).set((scalar)0.5,(scalar) 1,  0);
  m.add_face(vhandles);
  m.complete();
  compute_missing_normals(m);
  return m;
}

template <typename mesh>
mesh create_quad()
{
  typedef typename primitive_traits<mesh>::scalar scalar;

  mesh m;
  std::vector<vertex_handle> vhandles = m.add_vertices(4);
  m.position(vhandles[0]).set((scalar)-0.5, (scalar)-0.5,  0);
  m.position(vhandles[1]).set((scalar) 0.5, (scalar)-0.5,  0);
  m.position(vhandles[2]).set((scalar) 0.5, (scalar) 0.5,  0);
  m.position(vhandles[3]).set((scalar)-0.5, (scalar) 0.5,  0);
  
  m.add_face(vhandles);
  m.complete();
  compute_missing_normals(m);
  return m;
}



//create a unit arrow
template <typename mesh>
mesh create_unit_arrow(const typename primitive_traits<mesh>::scalar& stem_radius,
             const typename primitive_traits<mesh>::scalar& head_radius,
             const typename primitive_traits<mesh>::scalar& stem_height,
             int slices, int stem_stacks)
{
  typedef typename primitive_traits<mesh>::scalar scalar;
  typedef typename primitive_traits<mesh>::vec3 vec3;
  assert(slices >= 3 && stem_stacks >= 1&&stem_height <= 1 && stem_height >= 0);

  scalar head_height=(scalar)1-stem_height;
  mesh m;
  
  int n  = 2+slices*(stem_stacks+2);
  std::vector<vertex_handle> vhandles = m.add_vertices(n);
  
  scalar height = stem_height+ head_height;
  m.position(vhandles[0]).set(0,height,0);
  
  int k=1;
  for(int j = 0; j < slices; j++)
  {
    scalar angle2 = (scalar)(j*2.0*3.14159)/(scalar)(slices);
    m.position(vhandles[k]).set(cos(angle2)*head_radius,stem_height,sin(angle2)*head_radius);
    k++;
  }

  for(int i = 0; i < stem_stacks+1; i++)
  {
    scalar  h = (stem_stacks-i)*stem_height/(stem_stacks);

    for(int j = 0; j < slices; j++)
    {
      scalar angle2 = (scalar)(j*2.0*3.14159)/(scalar)(slices);
      m.position(vhandles[k]).set(cos(angle2)*stem_radius,h,sin(angle2)*stem_radius);
      k++;
    }
  }
  m.position(vhandles[k]).set(0,0,0);
  
  for(int i = 0; i < slices; i++)
  {
    m.add_triangle(vhandles[0],vhandles[1+(1+i)%slices],vhandles[1+i%slices]);
   
    for(int j = 0; j < stem_stacks+1;j++)
    {
      int a,b,c,d;
      a = 1+j*slices+(i)%slices;
      b = 1+j*slices+(1+i)%slices;
      c = 1+(j+1)*slices+(1+i)%slices;
      d = 1+(j+1)*slices+(i)%slices;
      m.add_quad(vhandles[a],vhandles[b],vhandles[c],vhandles[d]);
    }
    m.add_triangle(vhandles[vhandles.size()-1],
      vhandles[1+(stem_stacks+1)*slices+(i)%slices],
      vhandles[1+(stem_stacks+1)*slices+(1+i)%slices]);
  }
  m.complete();
  compute_missing_normals(m);
  return m;
}

template <typename mesh>
mesh create_saddle(int stacks, int slices, const typename primitive_traits<mesh>::scalar& xmin,
           const typename primitive_traits<mesh>::scalar& xmax,
           const typename primitive_traits<mesh>::scalar& ymin,
           const typename primitive_traits<mesh>::scalar& ymax)
{
  typedef typename primitive_traits<mesh>::scalar scalar;
  typedef typename primitive_traits<mesh>::vec3 vec3;
  assert(slices >= 2 && stacks >= 2);
  mesh m;
  int n  = slices*stacks;
  std::vector<vertex_handle> vhandles = m.add_vertices(n);
  for(int i = 0; i < n; ++i)
  {
    int x = i%slices;
    int y = i/slices;
    scalar xf = (xmax-xmin)*x/(scalar)(slices-1)+xmin;
    scalar yf = (ymax-ymin)*y/(scalar)(stacks-1)+ymin;
    m.position(vhandles[i]).set(xf,xf*xf - yf*yf,yf);
    if(x < slices-1 && y < stacks-1)
      m.add_quad(vhandles[i],vhandles[i+slices],vhandles[i+slices+1],vhandles[i+1]);
  }
  m.complete();
  compute_missing_normals(m);
  return m;

}


  */
  
    template <typename Scalar>
    void print_vertex_positions(const mesh<Scalar>& m)
    {
      for(auto pos: m.positions(m.vertices()))
      {
        std::cout << pos << std::endl;
      }
    }
  }
}
