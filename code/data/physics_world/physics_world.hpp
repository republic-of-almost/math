#ifndef PHYSICS_WORLD_INCLUDED_2B7C3AF5_17F9_49E4_8603_7919D93A39F4
#define PHYSICS_WORLD_INCLUDED_2B7C3AF5_17F9_49E4_8603_7919D93A39F4


#include "physics_fwd.hpp"
#include "rigidbody_properties.hpp"
#include <btBulletCollisionCommon.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>


namespace Physics {


struct World
{
  btDbvtBroadphase                       broadphase;
  btDefaultCollisionConfiguration        collision_config;
  btCollisionDispatcher                  dispatcher = {&collision_config};
  btSequentialImpulseConstraintSolver    solver;
  btDiscreteDynamicsWorld                dynamics_world = {&dispatcher, &broadphase, &solver, &collision_config};
//  Bullet::Detail::Debug_draw             m_debug_draw;
};


void world_init(World *world);
void world_step(World *world, const float dt);
void world_add_rigidbody(World *world, const Rigidbody_properties rb_properties, Rigidbody *dest);
void world_add_rigidbodies(World *world, const Rigidbody_properties rb_properties[], const std::size_t number_of_rbs, Rigidbody destination[], const std::size_t stride);


} // ns


#endif // inc guard