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
#include "owl/utils/count_iterator.hpp"
#include "owl/utils/iterator_range.hpp"
#include "owl/utils/map_iterator.hpp"
#include "owl/utils/adjacent_iterator.hpp"
#include "owl/math/matrix.hpp"
#include "owl/math/angle.hpp"

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
      using face_iterator = owl::utils::count_iterator<face_handle>;
      using vertex_iterator = owl::utils::count_iterator<vertex_handle>;
      using edge_iterator = owl::utils::count_iterator<edge_handle>;
      using halfedge_iterator = owl::utils::count_iterator<halfedge_handle>;
    
      template <typename Range>
      using is_vertex_range = std::is_same<typename utils::container_traits<std::decay_t<Range>>::value_type, vertex_handle>;
    
      template <typename Range>
      using is_halfedge_range = std::is_same<typename utils::container_traits<std::decay_t<Range>>::value_type, halfedge_handle>;
    
      template <typename Range>
      using is_face_range = std::is_same<typename utils::container_traits<std::decay_t<Range>>::value_type, face_handle>;
    
      template <typename Range>
      using is_point_range = std::is_same<typename utils::container_traits<std::decay_t<Range>>::value_type, vector<Scalar,3>>;
    
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
    

      auto vertices(face_handle f) const
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
        return make_iterator_range(
          make_handle_iterator(he, step, deref, he.is_valid() ? 0 : 1),
          make_handle_iterator(he, step, deref, 1));
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
          make_handle_iterator(he,step,deref,he.is_valid() ? 0 : 1),
          make_handle_iterator(he,step,deref,1));
      }
    
      auto halfedges(face_handle f) const
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
        return make_iterator_range(
          make_handle_iterator(he,step,deref,he.is_valid() ? 0 : 1),
          make_handle_iterator(he,step,deref,1));
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
          make_handle_iterator(he,step,deref,he.is_valid() ? 0 : 1),
          make_handle_iterator(he,step,deref,1));
      }

      const math::vector<Scalar,3>& position(vertex_handle v) const
      {
        return operator[](v).position;
      }

      math::vector<Scalar,3>& position(vertex_handle v)
      {
        return operator[](v).position;
      }

      const math::vector<Scalar,2>& texcoord(halfedge_handle he) const
      {
        return operator[](he).texcoord;
      }

      math::vector<Scalar,2>& texcoord(halfedge_handle he)
      {
        return operator[](he).texcoord;
      }


      template<typename Handle>
      const math::vector<Scalar,3>& normal(Handle h) const
      {
        return operator[](h).normal;
      }

      template<typename Handle>
      math::vector<Scalar,3>& normal(Handle h)
      {
        return operator[](h).normal;
      }

    
    
      template<typename Handle>
      const status_flags& status(Handle h) const
      {
        return operator[](h);
      }
    
      template<typename Handle>
      status_flags& status(Handle h)
      {
        return operator[](h);
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
    
    

      template <typename VertexRange, typename = std::enable_if_t<is_vertex_range<VertexRange>::value>>
      auto positions(VertexRange&& vertices) const
      {
        return utils::map_range([this](vertex_handle v){ return position(v);},
          std::forward<VertexRange>(vertices));
      }

      template <typename VertexRange, typename = std::enable_if_t<is_vertex_range<VertexRange>::value>>
      auto positions(VertexRange&& vertices)
      {
        return utils::map_range([this](vertex_handle v){ return position(v);},
          std::forward<VertexRange>(vertices));
      }

      template <typename FaceRange, typename = std::enable_if_t<is_face_range<FaceRange>::value>>
      auto normals(FaceRange&& faces) const
      {
        return utils::map_range([this](face_handle f){ return normal(f);},
          std::forward<FaceRange>(faces));
      }

      template <typename FaceRange, typename = std::enable_if_t<is_face_range<FaceRange>::value>>
      auto normals(FaceRange&& faces)
      {
        return utils::map_range([this](face_handle f){ return normal(f);},
          std::forward<FaceRange>(faces));
      }

      template <typename VertexRange, typename = std::enable_if_t<is_vertex_range<VertexRange>::value>, typename = void>
      auto normals(VertexRange&& vertices) const
      {
        return utils::map_range([this](vertex_handle v){ return normal(v);},
          std::forward<VertexRange>(vertices));
      }

      template <typename VertexRange, typename = std::enable_if_t<is_vertex_range<VertexRange>::value>, typename = void>
      auto normals(VertexRange&& vertices)
      {
        return utils::map_range([this](vertex_handle v){ return normal(v);},
          std::forward<VertexRange>(vertices));
      }
    
     template <typename HalfEdgeRange, typename = std::enable_if_t<is_halfedge_range<HalfEdgeRange>::value>>
      auto texcoords(HalfEdgeRange&& halfedges) const
      {
        return utils::map_range([this](halfedge_handle he){ return texcoord(he);},
          std::forward<HalfEdgeRange>(halfedges));
      }

      template <typename HalfEdgeRange, typename = std::enable_if_t<is_halfedge_range<HalfEdgeRange>::value>, typename = void>
      auto texcoords(HalfEdgeRange&& halfedges)
      {
        return utils::map_range([this](halfedge_handle he){ return texcoord(he);},
          std::forward<HalfEdgeRange>(halfedges));
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

      bool is_isolated(vertex_handle v) const
      {
        return !halfedge(v).is_valid();
      }
    
      vector<Scalar,3> direction(halfedge_handle he) const
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
    
      vertex_handle split(edge_handle e, const vector<Scalar,3>& position)
      {
        return split(halfedge(e), position);
      }
      void split(edge_handle e, vertex_handle v)
      {
        return split(halfedge(e), v);
      }
      void split(halfedge_handle he, const vector<Scalar,3>& position)
      {
        auto v = add_vertex(position);
        split(he, v);
      }
    
      void split(halfedge_handle he, vertex_handle v)
      {
        auto he_prev = opposite(next(he));
        while(next(he_prev) != opposite(he))
          he_prev = opposite(next(he_prev));
    
        auto e = add_edge(v,target(he));
        auto he_next = halfedge(e);
        auto he_next_opp = opposite(he_next);
        next(he_prev) = he_next_opp;
        next(he_next) = next(he);
        next(he) = he_next;
        auto he_opp = opposite(he);
        next(he_next_opp) = he_opp;
        target(he_next_opp) = v;
        target(he) = v;
        face(he_next) = face(he);
        face(he_next_opp) = face(he_opp);
      }
    
      void split(face_handle f, const vector<Scalar,3>& pos)
      {
        split(f, add_vertex(pos));
      }
    
      vector<Scalar, 3> centroid(halfedge_handle he) const
      {
        return (position(target(he)) + position(origin(he)))/2;
      }
    
      vector<Scalar, 3> centroid(edge_handle e) const
      {
        return mid_point(halfedge(e));
      }
    
      vector<Scalar, 3> centroid(face_handle f) const
      {
        auto points = positions(vertices(f));
        vector<Scalar, 3> mp = vector<Scalar,3>::zero();
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
            faces_.emplace_back_back(he2);
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
    
    
      /*
      angle<Scalar> sector_angle(halfedge_handle he) const
      {
        auto v0 = direction(next(he));
        auto v1 = direction(opposite(he));
        auto denom = v0.length()*v1.length();
        
        if(denom == Scalar(0))
          return 0;
    
        Scalar cos_a = dot(v0 , v1) / denom;
        if(is_boundary(he))
        {//determine if the boundary sector is concave or convex
          auto fh = face(opposite(he));
          vector<Scalar,3> f_n(calc_face_normal(fh));//this normal is (for convex fh) OK
          Scalar sign_a = dot(cross(v0, v1), f_n);
          cos_a = std::clamp(cos_a, -1, 1);
          
          return (Scalar) sign_a >= 0 ? acos(cos_a) : -acos(cos_a);


        }
        else
        {
          cos_a = std::clamp(cos_a, -1, 1);
          return acos(cos_a);
        }
      }

  
      angle<Scalar> dihedral_angle(halfedge_handle he) const
      {
      }
    */
    
      vector<Scalar, 3> compute_sector_normal(halfedge_handle he, bool normalize = true) const
      {
        auto nml = cross(direction(next(he)), direction(opposite(he)));
        if(normalize)
          nml.normalize();
        return nml;
      }
    
      vector<Scalar, 3> compute_normal(face_handle f) const
      {
        auto nml = vector<Scalar,3>::zero();
      
        for(auto he : halfedges(f))
          nml += compute_sector_normal(he, false);
      
        
        nml.normalize();
        return nml;
      }
    
      vector<Scalar, 3> compute_normal(vertex_handle v) const
      {
        auto nml = vector<Scalar,3>::zero();
      
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
        edges_.clear();
        vertices_.clear();
      }
    
      bool empty() const
      {
        return faces_.empty() && vertices_.empty() && edges_.empty();
      }
    
      template <typename PointRange, typename = std::enable_if_t<is_point_range<PointRange>::value>>
      auto add_vertices(PointRange&& points)
      {
        std::size_t n = vertices_.size();
        vertices_.insert(vertices_.end(), std::begin(points),std::end(points));
        return make_iterator_range(vertex_iterator(vertex_handle(n)), vertex_iterator(vertex_handle(vertices_.size())));
      }
    
      template <typename... VertexHandles, typename = std::enable_if_t<(... && std::is_same<std::decay_t<VertexHandles>,vertex_handle>::value)>>
      face_handle add_face(VertexHandles&&... vertices)
      {
         return add_face(std::array<vertex_handle, sizeof...(vertices)> { std::forward<VertexHandles>(vertices)... });
      }
    
      template <typename VertexRange, typename = std::enable_if_t<is_vertex_range<VertexRange>::value>>
      face_handle add_face(VertexRange&& vertices)
      {
        face_handle f = face_handle{faces_.size()};
      
        std::vector<halfedge_handle> hes;
        hes.reserve(std::size(vertices));
      
        for(auto v : owl::utils::make_adjacent_range(vertices))
        {
          auto he = find_halfedge(v.current, v.next);
          if (!he.is_valid())
            he = halfedge(add_edge(v.current, v.next));
          else
            assert(is_boundary(he));
          hes.push_back(he);
        }
      
        for(auto he : owl::utils::make_adjacent_range(hes))
        {
          face(he.current) = f;
          if(next(he.current) != he.next)
          {
            auto he_outer = opposite(he.next);
            auto he_outer_next = next(he_outer);
            if(he_outer_next.is_valid())
            {
              while(he_outer_next != he.next)
              {
                he_outer = opposite(he_outer_next);
                he_outer_next = next(he_outer);
              }
              next(he_outer) = opposite(he.current);
            }
            else
            {
              if(next(he.current).is_valid())
                next(he_outer) = next(he.current);
              else
                next(he_outer) = opposite(he.current);
            }
            next(he.current) = he.next;
            auto v = target(he.current);
            adjust_halfedge(v, he.current);
          }
        }
        faces_.emplace_back(hes.front());
        return f;
      }
    
      //set halfedge of v to he and ensure halfedge of v is on boundary if v is on boundary
      void adjust_halfedge(vertex_handle v, halfedge_handle he)
      {
        halfedge(v) = he;
        for(auto h : incoming_halfedges(v))
        {
          if(is_boundary(h))
          {
            halfedge(v) = h;
            break;
          }
        }
      }

   private:
   
     struct vertex_t
     {
       vertex_t() = default;
       vertex_t(const vector<Scalar,3>& p) : position{p} {}
     
       halfedge_handle halfedge;
       vector<Scalar,3> position;
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
        vector<Scalar,3> normal;
        vector<Scalar,2> texcoord;
     };
    
     struct edge_t
     {
       edge_t(vertex_handle from, vertex_handle to)
        : halfedges {halfedge_t(to)
        , halfedge_t(from)}
       {
       }
     
       std::array<halfedge_t,2> halfedges;
       status_flags status;
     };
    
     struct face_t
     {
       face_t() = default;
     
       face_t(halfedge_handle he, const vector<Scalar,3>& nml = vector<Scalar,3>::zero())
        : halfedge{he}
        , normal{nml}
       {
       }
     
       halfedge_handle halfedge;
       vector<Scalar,3> normal;
       status_flags status;
     };
    
     halfedge_handle& halfedge(face_handle f)
     {
       return operator[](f).halfedge;
     }
     
     const halfedge_handle& halfedge(face_handle f) const
     {
       return operator[](f).halfedge;
     }
    
     halfedge_handle& halfedge(vertex_handle v)
     {
       return operator[](v).halfedge;
     }
    
     const halfedge_handle& halfedge(vertex_handle v) const
     {
       return operator[](v).halfedge;
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
    
     const halfedge_handle& next(halfedge_handle he) const
     {
        return operator[](he).next;
     }
    
     halfedge_handle& next(halfedge_handle he)
     {
        return operator[](he).next;
     }
    
     const face_handle& face(halfedge_handle he) const
     {
        return operator[](he).face;
     }
    
     face_handle& face(halfedge_handle he)
     {
        return operator[](he).face;
     }
    
     edge_handle edge(halfedge_handle he) const
     {
      return edge_handle(he.index() >> 1);
     }
    
     halfedge_handle halfedge(edge_handle e) const
     {
       return halfedge_handle{e.index() << 1};
     }
    
     halfedge_handle opposite(halfedge_handle he) const
     {
       return he.index() % 2  == 0 ? halfedge_handle{he.index() + 1} : halfedge_handle{he.index() - 1};
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
        edge_handle e = edge_handle{edges_.size()};
        edges_.emplace_back(from, to);
        return e;
     }
    
    
    
     std::vector<edge_t> edges_;
     std::vector<vertex_t> vertices_;
     std::vector<face_t> faces_;
   };
  
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
    
     auto f = m.add_face(vertices[1],vertices[3],vertices[7],vertices[5]); //right
     std::array<math::vector<Scalar,2>,4> texcoord_right =
     {
      math::vector<Scalar,2>{0.5,0.25},
      math::vector<Scalar,2>{0.5,0.5},
      math::vector<Scalar,2>{0.75,0.5},
      math::vector<Scalar,2>{0.75,0.25}
     };
    
    
    
    
    
    
    
    
   
     auto it = texcoord_right.begin();
     for(auto he : m.halfedges(f))
     {
       m.texcoord(he) = *it++;
     }
    
     f = m.add_face(vertices[0],vertices[4],vertices[6],vertices[2]); //left
     std::array<math::vector<Scalar,2>,4> texcoord_left =
     {
      math::vector<Scalar,2>{0,0.5},
      math::vector<Scalar,2>{0.25,0.5},
      math::vector<Scalar,2>{0.25,0.25},
      math::vector<Scalar,2>{0,0.25}
     };
     it = texcoord_left.begin();
     for(auto he : m.halfedges(f))
     {
       m.texcoord(he) = *it++;
     }
    
     f = m.add_face(vertices[2],vertices[6],vertices[7],vertices[3]); //top
     std::array<math::vector<Scalar,2>,4> texcoord_top =
     {
      math::vector<Scalar,2>{0.25,0.0},
      math::vector<Scalar,2>{0.25,0.25},
      math::vector<Scalar,2>{0.5,0.25},
      math::vector<Scalar,2>{0.5,0.0}
     };
     it = texcoord_top.begin();
     for(auto he : m.halfedges(f))
     {
       m.texcoord(he) = *it++;
     }
    
     f = m.add_face(vertices[0],vertices[1],vertices[5],vertices[4]); //bottom
      std::array<math::vector<Scalar,2>,4> texcoord_bottom =
     {
      math::vector<Scalar,2>{0.25,0.75},
      math::vector<Scalar,2>{0.5,0.75},
      math::vector<Scalar,2>{0.5,0.5},
      math::vector<Scalar,2>{0.25,0.5}
     };
     it = texcoord_bottom.begin();
     for(auto he : m.halfedges(f))
     {
       m.texcoord(he) = *it++;
     }
    
     f = m.add_face(vertices[4],vertices[5],vertices[7],vertices[6]); //front
      std::array<math::vector<Scalar,2>,4> texcoord_front =
     {
      math::vector<Scalar,2>{0.25,0.5},
      math::vector<Scalar,2>{0.5,0.5},
      math::vector<Scalar,2>{0.5,0.25},
      math::vector<Scalar,2>{0.25,0.25}
     };
     it = texcoord_front.begin();
     for(auto he : m.halfedges(f))
     {
       m.texcoord(he) = *it++;
     }
    
     f = m.add_face(vertices[0],vertices[2],vertices[3],vertices[1]); //back
      std::array<math::vector<Scalar,2>,4> texcoord_back =
     {
      math::vector<Scalar,2>{1,0.5},
      math::vector<Scalar,2>{1.0,0.25},
      math::vector<Scalar,2>{0.75,0.25},
      math::vector<Scalar,2>{0.75,0.5}
     };
     it = texcoord_back.begin();
     for(auto he : m.halfedges(f))
     {
       m.texcoord(he) = *it++;
     }
     m.update_face_normals();
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
     m.update_face_normals();
     return m;
    
    }
  
    //sphere
    //radius
    //segment count
  
  
    //geodesic_sphere
    //subdivided icosahedron
  
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

template <typename mesh>
mesh create_box(const typename primitive_traits<mesh>::vec3&  pmin, const typename primitive_traits<mesh>::vec3 &pmax)
{
   
  mesh m;
  
  std::vector<vertex_handle> vhandles = m.add_vertices(8);

  m.position(vhandles[0]).set(pmin[0], pmin[1], pmax[2]);
  m.position(vhandles[1]).set(pmax[0], pmin[1], pmax[2]);
  m.position(vhandles[2]).set(pmax[0], pmax[1], pmax[2]);
  m.position(vhandles[3]).set(pmin[0], pmax[1], pmax[2]);
  m.position(vhandles[4]).set(pmin[0], pmin[1], pmin[2]);
  m.position(vhandles[5]).set(pmax[0], pmin[1], pmin[2]);
  m.position(vhandles[6]).set(pmax[0], pmax[1], pmin[2]);
  m.position(vhandles[7]).set(pmin[0], pmax[1], pmin[2]);
  
  std::vector<vertex_handle>  face_vhandles;
  face_vhandles.clear();
  face_vhandles.push_back(vhandles[0]);
  face_vhandles.push_back(vhandles[1]);
  face_vhandles.push_back(vhandles[2]);
  face_vhandles.push_back(vhandles[3]);
  m.add_face(face_vhandles);
 
  face_vhandles.clear();
  face_vhandles.push_back(vhandles[7]);
  face_vhandles.push_back(vhandles[6]);
  face_vhandles.push_back(vhandles[5]);
  face_vhandles.push_back(vhandles[4]);
  m.add_face(face_vhandles);

  face_vhandles.clear();
  face_vhandles.push_back(vhandles[1]);
  face_vhandles.push_back(vhandles[0]);
  face_vhandles.push_back(vhandles[4]);
  face_vhandles.push_back(vhandles[5]);
  m.add_face(face_vhandles);

  face_vhandles.clear();
  face_vhandles.push_back(vhandles[2]);
  face_vhandles.push_back(vhandles[1]);
  face_vhandles.push_back(vhandles[5]);
  face_vhandles.push_back(vhandles[6]);
  m.add_face(face_vhandles);

  face_vhandles.clear();
  face_vhandles.push_back(vhandles[3]);
  face_vhandles.push_back(vhandles[2]);
  face_vhandles.push_back(vhandles[6]);
  face_vhandles.push_back(vhandles[7]);
  m.add_face(face_vhandles);

  face_vhandles.clear();
  face_vhandles.push_back(vhandles[0]);
  face_vhandles.push_back(vhandles[3]);
  face_vhandles.push_back(vhandles[7]);
  face_vhandles.push_back(vhandles[4]);
  m.add_face(face_vhandles);
  m.complete();
  compute_missing_normals(m);
  return m;
}


template <typename mesh>
mesh create_cube()
{
  typedef typename primitive_traits<mesh>::vec3 vec3;
  typedef typename primitive_traits<mesh>::scalar scalar;
  return create_box<mesh>(vec3((scalar)-0.5,(scalar)-0.5,(scalar)-0.5),vec3((scalar)0.5,(scalar)0.5,(scalar)0.5));
}

template <typename mesh>
mesh create_tetrahedron(const typename primitive_traits<mesh>::scalar& a)
{
  typedef typename primitive_traits<mesh>::scalar scalar;
  mesh m;
  
  std::vector<vertex_handle> vhandles = m.add_vertices(4);
   
  m.position(vhandles[0]).set( sqrt((scalar)3)*a/(scalar)3,           0, 0);
  m.position(vhandles[1]).set(-sqrt((scalar)3)*a/(scalar)6,-a/(scalar)2, 0);
  m.position(vhandles[2]).set(-sqrt((scalar)3)*a/(scalar)6, a/(scalar)2, 0);
  m.position(vhandles[3]).set(     0,      0, sqrt((scalar)6)*a/(scalar)3);
  
  std::vector<vertex_handle>  face_vhandles;
  face_vhandles.clear();
  face_vhandles.push_back(vhandles[0]);
  face_vhandles.push_back(vhandles[1]);
  face_vhandles.push_back(vhandles[2]);
  m.add_face(face_vhandles);

  face_vhandles.clear();
  face_vhandles.push_back(vhandles[0]);
  face_vhandles.push_back(vhandles[2]);
  face_vhandles.push_back(vhandles[3]);
  m.add_face(face_vhandles);

  face_vhandles.clear();
  face_vhandles.push_back(vhandles[0]);
  face_vhandles.push_back(vhandles[3]);
  face_vhandles.push_back(vhandles[1]);
  m.add_face(face_vhandles);

  face_vhandles.clear();
  face_vhandles.push_back(vhandles[3]);
  face_vhandles.push_back(vhandles[2]);
  face_vhandles.push_back(vhandles[1]);
  m.add_face(face_vhandles);
  m.complete();
  compute_missing_normals(m);
  
  return m;
}

template <typename mesh>
mesh create_disk(const typename primitive_traits<mesh>::scalar radius, int slices)
{
  typedef typename primitive_traits<mesh>::scalar scalar;
  mesh m;
  std::vector<vertex_handle> vhandles = m.add_vertices(slices+1);
  m.position(vhandles[0]).set(0.0f,0.0f,0.0f);
  
  for(int i = 0; i < slices;i++)
  {
    scalar angle= -i*2*(scalar)3.14159/slices;
    m.position(vhandles[i+1]).set(cos(angle)*radius, 0.0f, sin(angle)*radius);
  }
  for(int i = 0; i < slices;i++)
  {
    m.add_triangle(vhandles[0],vhandles[1+i%slices],vhandles[1+(1+i)%slices]);
  }
  m.complete();
  compute_missing_normals(m);
  return m;
}

//create a cylinder mesh
template <typename mesh>
mesh create_cylinder(const typename primitive_traits<mesh>::scalar radius, const typename primitive_traits<mesh>::scalar height,int stacks, int slices)
{
  typedef typename primitive_traits<mesh>::scalar scalar;
  assert(slices >= 3 && stacks >= 1);

  mesh m;
  
  int n = 2+slices*(stacks+1);
  std::vector<vertex_handle> vhandles = m.add_vertices(n);
  
  m.position(vhandles[0]).set((scalar)0,height,(scalar)0);

  int k=1;
  for(int i = 0; i < stacks+1; i++)
  {
    float h = (stacks-i)*height/(stacks);

    for(int j = 0; j < slices; j++)
    {
      scalar angle2 = (scalar)(j*2.0*3.14159)/(scalar)(slices);
      m.position(vhandles[k]).set(cos(angle2)*radius,h,sin(angle2)*radius);
      k++;
    }
  }

  m.position(vhandles[k]).set((scalar)0,(scalar)0,(scalar)0);

  for(int i = 0; i < slices; i++)
  {
    m.add_triangle(vhandles[0],vhandles[1+(1+i)%slices],vhandles[1+i%slices]);
   
    for(int j = 0; j < stacks;j++)
    {
      int a,b,c,d;
      a = 1+j*slices+(i)%slices;
      b = 1+j*slices+(1+i)%slices;
      c = 1+(j+1)*slices+(1+i)%slices;
      d = 1+(j+1)*slices+(i)%slices;
      m.add_quad(vhandles[a],vhandles[b],vhandles[c],vhandles[d]);
    }
    m.add_triangle(vhandles[vhandles.size()-1],
      vhandles[1+(stacks)*slices+(i)%slices],
      vhandles[1+(stacks)*slices+(1+i)%slices]);
  }
  m.complete();
  compute_missing_normals(m);
  return m;
}

//create a sphere mesh
template <typename mesh>
mesh create_sphere(const typename primitive_traits<mesh>::scalar radius, int slices, int stacks)
{
  typedef typename primitive_traits<mesh>::scalar scalar;
  assert(slices >= 3 && stacks >= 3);
  
  mesh m;
   
  int n = slices*(stacks-1) + 2;
  std::vector<vertex_handle> vhandles = m.add_vertices(n);

  m.position(vhandles[0]).set(0.0f,radius,0.0f);
  
  int k = 1;
  for(int i = 1; i < stacks; i++)
  {
    scalar angle1 = (scalar)(3.14159/2.0)-(scalar)(i*3.14159)/(scalar)stacks;
    scalar r = cos(angle1)*radius;
    scalar height =sin(angle1)*radius;

    for(int j = 0; j < slices; j++)
    {
      scalar angle2 = (scalar)(j*2.0*3.14159)/(scalar)(slices);
      m.position(vhandles[k]).set(cos(angle2)*r,height,sin(angle2)*r);
      k++;
    }
  }
   
  m.position(vhandles[k]).set(0.0f,-radius,0.0f);
  
  for(int i = 0; i < slices; i++)
  {
    m.add_triangle(vhandles[0],vhandles[1+(1+i)%slices],vhandles[1+i%slices]);
   
    for(int j = 0; j < stacks-2;j++)
    {
      int a,b,c,d;
      a = 1+j*slices+(i)%slices;
      b = 1+j*slices+(1+i)%slices;
      c = 1+(j+1)*slices+(1+i)%slices;
      d = 1+(j+1)*slices+(i)%slices;
      m.add_quad(vhandles[a],vhandles[b],vhandles[c],vhandles[d]);
    }
    m.add_triangle(vhandles[1+slices*(stacks-1)],
        vhandles[1+(stacks-2)*slices+(i)%slices],
        vhandles[1+(stacks-2)*slices+(1+i)%slices]);
  }
  m.complete();
  compute_missing_normals(m);
  return m;
}

template <typename mesh>
mesh create_sphere(const typename primitive_traits<mesh>::vec3& center,
           const typename primitive_traits<mesh>::scalar radius,
           int slices, int stacks)
{
  typedef typename primitive_traits<mesh>::scalar scalar;
  assert(slices >= 3 && stacks >= 3);
  
  mesh m;
   
  
  int n = slices*(stacks-1) + 2;
  std::vector<vertex_handle> vhandles = m.add_vertices(n);

  m.position(vhandles[0]).set(center[0],center[1]+radius,center[2]);
  
  int k = 1;
  for(int i = 1; i < stacks; i++)
  {
    scalar angle1 = (scalar)(3.14159/2.0)-(scalar)(i*3.14159)/(scalar)stacks;
    scalar r = cos(angle1)*radius;
    scalar height =sin(angle1)*radius;

    for(int j = 0; j < slices; j++)
    {
      scalar angle2 = (scalar)(j*2.0*3.14159)/(scalar)(slices);
      m.position(vhandles[k]).set(center[0]+cos(angle2)*r,center[1]+height,center[2]+sin(angle2)*r);
      k++;
    }
  }
   
  m.position(vhandles[k]).set(center[0],center[1]-radius,center[2]);
  
  for(int i = 0; i < slices; i++)
  {
    m.add_triangle(vhandles[0],vhandles[1+(1+i)%slices],vhandles[1+i%slices]);
   
    for(int j = 0; j < stacks-2;j++)
    {
      int a,b,c,d;
      a = 1+j*slices+(i)%slices;
      b = 1+j*slices+(1+i)%slices;
      c = 1+(j+1)*slices+(1+i)%slices;
      d = 1+(j+1)*slices+(i)%slices;
      m.add_quad(vhandles[a],vhandles[b],vhandles[c],vhandles[d]);
    }
    m.add_triangle(vhandles[1+slices*(stacks-1)],
        vhandles[1+(stacks-2)*slices+(i)%slices],
        vhandles[1+(stacks-2)*slices+(1+i)%slices]);
  }
  m.complete();
  compute_missing_normals(m);
  return m;
}


//create a torus mesh
template <typename mesh>
mesh create_torus(const typename primitive_traits<mesh>::scalar&  r,const typename primitive_traits<mesh>::scalar& R,int nsides,int rings)
{
  typedef  typename primitive_traits<mesh>::scalar scalar;
  typedef  typename primitive_traits<mesh>::vec3 vec3;
  assert(nsides >= 3 && rings >= 3);
  mesh m;

  int n = rings*nsides;
  std::vector<vertex_handle> vhandles = m.add_vertices(n);
  int k = 0;
  for(int i = 0; i < rings; i++)
  {
    scalar angle1=(scalar)(i*2.0*3.14159/(rings));
    vec3 center(cos(angle1)*R,0,sin(angle1)*R);
    vec3 t1(cos(angle1),0.0,sin(angle1));
    vec3 t2(0.0f,1.0f,0.0f);

    for(int j = 0; j < nsides; j++)
    {
      scalar angle2=(scalar)(j*2.0*3.14159/(nsides));
      m.position(vhandles[k])=center+(scalar)(sin(angle2)*r)*t1+(scalar)(cos(angle2)*r)*t2 ;
      m.texcoord(vhandles[k]).set(angle1/(2*3.14159f),angle2/(2*3.14159f)) ;
      k++;
    }
  }

  for(int i = 0; i < rings; i++)
  {
    for(int j = 0; j < nsides; j++)
    {
      int a,b,c,d;
      a = (i+1)%(rings)*(nsides)+j;
      b = (i+1)%(rings)*(nsides)+(j+1)%(nsides);
      c = i*(nsides)+(j+1)%(nsides);
      d = i*(nsides)+j;
      m.add_quad(
        vhandles[a], vhandles[b],
        vhandles[c], vhandles[d]);
   
   
   
    }
  }
  m.complete();
  compute_missing_normals(m);
  return m;
}


//creates an icosaeder mesh in m
// radius is the radius of the circum sphere
template <typename mesh>
mesh create_icosaeder(const typename primitive_traits<mesh>::scalar& radius)
{
  
  typedef typename primitive_traits<mesh>::scalar scalar;
  mesh m;
  
  scalar a  = (scalar)(radius*4.0/sqrt(10.0+2.0*sqrt(5.0)));
  scalar h = (scalar)cos(2.0*asin(a/(2.0*radius)))*radius;
  scalar r2 = (scalar)sqrt(radius*radius-h*h);

  std::vector<vertex_handle> vhandles = m.add_vertices(12);
  int k = 0;
  m.position(vhandles[k++]).set(0,radius,0);

  for(int i = 0; i < 5;i++)
    m.position(vhandles[k++]).set((float)cos(i*72.0*3.14159/180.0)*r2,h,-(float)sin(i*72.0*3.14159/180.0)*r2);
  
  for(int i = 0; i < 5;i++)
    m.position(vhandles[k++]).set((float)cos(36.0*3.14159/180.0+i*72.0*3.14159/180.0)*r2,-h,-(float)sin(36.0*3.14159/180.0+i*72.0*3.14159/180.0)*r2);
   
  m.position(vhandles[k]).set(0,-radius,0);
  
  for(int i = 0;i < 5;i++)
  {
    m.add_triangle(vhandles[0],vhandles[i+1],vhandles[(i+1)%5+1]);
    m.add_triangle(vhandles[11],vhandles[(i+1)%5+6],vhandles[i+6]);
    m.add_triangle(vhandles[i+1],vhandles[i+6],vhandles[(i+1)%5+1]);
    m.add_triangle(vhandles[(i+1)%5+1],vhandles[i+6],vhandles[(i+1)%5+6]);
  }
  m.complete();
  compute_missing_normals(m);
  return m;
}


//creates an octaeder mesh
// radius is the radius of the circum sphere
template <typename mesh>
mesh create_octaeder(const typename primitive_traits<mesh>::scalar& radius)
{
  typedef typename primitive_traits<mesh>::scalar scalar;
  typedef typename primitive_traits<mesh>::vec3 vec3;
  mesh m;
   
  std::vector<vertex_handle> vhandles = m.add_vertices(6);
  int k = 0;
  m.position(vhandles[k++]).set(0,radius,0);
  
   
  for(int i = 0; i < 4; i++)
    m.position(vhandles[k++])= vec3((scalar)cos(i*3.14159/2.0)*radius,0,-(scalar)sin(i*3.14159/2.0)*radius);


  m.position(vhandles[k++])=vec3(0,-radius,0);


  for(int i = 0; i < 4; i++)
  {
    m.add_triangle(vhandles[0],vhandles[i+1],vhandles[(i+1)%4+1]);
    m.add_triangle(vhandles[5],vhandles[(i+1)%4+1],vhandles[i+1]);
  }
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
  }
}
