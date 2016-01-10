#ifndef TEXTURE_POOL_INCLUDED_6CFB6B90_56F8_408D_B068_9EB867B41233
#define TEXTURE_POOL_INCLUDED_6CFB6B90_56F8_408D_B068_9EB867B41233


#include <renderer/graphics_api/ogl/ogl_texture.hpp>
#include <cstddef>


#define SIZE_OF_TEXTURE_POOL 64


namespace Data {


struct Texture_pool
{
  std::size_t         id[SIZE_OF_TEXTURE_POOL];
  Ogl::Texture        texture[SIZE_OF_TEXTURE_POOL];
  
  const std::size_t   size = SIZE_OF_TEXTURE_POOL;
}; // struct


/*!
  Initializes the pool, such that the ids will be in sequence.
*/
void
texture_pool_init(Texture_pool *pool);


/*!
  Find the texture for the given id.
*/
Ogl::Texture*
texture_pool_find(Texture_pool *pool, const std::size_t id);


} // ns


#endif // inc guard