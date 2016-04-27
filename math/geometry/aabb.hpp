#ifndef AABB_INCLUDED_0C5E26F6_BFB1_422A_948B_0E4861927EEE
#define AABB_INCLUDED_0C5E26F6_BFB1_422A_948B_0E4861927EEE


#include "geometry_types.hpp"
#include "../vec/vec3.hpp"
#include "../general/general.hpp"
#include <stddef.h>
#include <assert.h>


namespace math {


// ** Interface ** //

inline aabb         aabb_init(const vec3 max, const vec3 min);
inline aabb         aabb_init_from_xyz_data(const float vertex[], const size_t number_of_floats);

inline vec3         aabb_get_extents(const aabb &a);
inline vec3         aabb_get_half_extents(const aabb &a);
inline vec3         aabb_get_min(const aabb &a);
inline vec3         aabb_get_max(const aabb &a);
inline vec3         aabb_get_origin(const aabb &a);

inline void         aabb_scale(aabb &aabb_to_scale, const vec3 scale);
inline void         aabb_scale(aabb &aabb_to_scale, const float scale);

inline bool         aabb_intersection_test(const aabb &a, const aabb &b);


// ** Impl ** //


aabb
aabb_init(const vec3 max,
          const vec3 min)
{
  aabb return_aabb;
  return_aabb.max = max;
  return_aabb.min = min;
  
  return return_aabb;
}


aabb
aabb_init_from_xyz_data(const float vertex[],
                        const size_t number_of_floats)
{
  aabb out_aabb;

  // Check is valid.
  assert((number_of_floats % 3) == 0);
  if((number_of_floats % 3) != 0)
  {
    return out_aabb;
  }

  // Calculate min, max
  float max_x(vertex[0]);
  float max_y(vertex[1]);
  float max_z(vertex[2]);

  float min_x(vertex[0]);
  float min_y(vertex[1]);
  float min_z(vertex[2]);

  for(size_t i = 0; i < number_of_floats / 3; ++i)
  {
    size_t index = i * 3;

    max_x = max(vertex[index + 0], max_x);
    min_x = min(vertex[index + 0], min_x);

    max_y = max(vertex[index + 1], max_y);
    min_y = min(vertex[index + 1], min_y);

    max_z = max(vertex[index + 2], max_z);
    min_z = min(vertex[index + 2], min_z);
  }

  out_aabb.max = vec3_init(max_x, max_y, max_z);
  out_aabb.min = vec3_init(min_x, min_y, min_z);

  return out_aabb;
}


vec3
aabb_get_extents(const aabb &a)
{
  return vec3_subtract(a.max, a.min);
}


vec3
aabb_get_half_extents(const aabb &a)
{
  return vec3_scale(aabb_get_extents(a), 0.5f);
}


vec3
aabb_get_min(const aabb &a)
{
  return a.min;
}


vec3
aabb_get_max(const aabb &a)
{
  return a.max;
}


vec3
aabb_get_origin(const aabb &a)
{
  const vec3 half_extent = aabb_get_half_extents(a);

  return vec3_add(a.min, half_extent);
}


void
aabb_scale(aabb &aabb_to_scale, const vec3 scale)
{
  aabb_to_scale.max = math::vec3_multiply(aabb_to_scale.max, scale);
  aabb_to_scale.min = math::vec3_multiply(aabb_to_scale.min, scale);
}


void
aabb_scale(aabb &aabb_to_scale, const float scale)
{
  return aabb_scale(aabb_to_scale, vec3_init(scale));
}


namespace detail
{
  // Simple Single Axis Therom test.
  // We assume we are dealing with just AABB boxes.
  inline bool
  sat_test(const float origin_a,
           const float origin_b,
           const float combined_length)
  {
    return math::abs(origin_b - origin_a) < combined_length;
  }
} // ns


bool
aabb_intersection_test(const aabb &a,
                       const aabb &b)
{
  return (detail::sat_test(math::vec3_get_x(aabb_get_origin(a)), math::vec3_get_x(aabb_get_origin(b)), (math::vec3_get_x(aabb_get_half_extents(a)) + math::vec3_get_x(aabb_get_half_extents(b)))) &&
          detail::sat_test(math::vec3_get_y(aabb_get_origin(a)), math::vec3_get_y(aabb_get_origin(b)), (math::vec3_get_y(aabb_get_half_extents(a)) + math::vec3_get_y(aabb_get_half_extents(b)))) &&
          detail::sat_test(math::vec3_get_z(aabb_get_origin(a)), math::vec3_get_z(aabb_get_origin(b)), (math::vec3_get_z(aabb_get_half_extents(a)) + math::vec3_get_z(aabb_get_half_extents(b)))));
}


} // ns


#endif // inc guard
