#include "PhysicObj.hpp"

PhysicObj::PhysicObj()
{
	is_staying = 0;
	visible = 0;
	mass = 50;
	speed_x = 0;
	speed_y = 0;
	HP = 100;
    intersect_bullet_event = 0;
    player_in_radius_event = 0;
    is_player = 0;
    is_ghost = 0;
    is_first_enemy = 0;
    is_bullet = 0;
	is_block = 0;
}

float PhysicObj::get_X()
{
    return X;
}

float PhysicObj::get_Y()
{
    return Y;
}

float PhysicObj::get_mass()
{
	return mass;
}

void PhysicObj::set_mass(float mass_)
{
	mass = mass_;
}


void PhysicObj::set_X(float X_)
{
    X = X_;
}

void PhysicObj::set_Y(float Y_)
{
    Y = Y_;
}

void PhysicObj::set_is_player(bool is_player_)
{
    is_player = is_player_;
}

void PhysicObj::set_is_first_enemy(bool is_first_enemy_)
{
    is_first_enemy = is_first_enemy_;
}

void PhysicObj::set_is_bullet(bool is_bullet_)
{
    is_bullet = is_bullet_;
}

bool PhysicObj::get_is_player()
{
    return is_player;
}

bool PhysicObj::get_is_first_enemy()
{
    return is_first_enemy;
}

bool PhysicObj::get_is_bullet()
{
    return is_bullet;
}

float PhysicObj::get_wight()
{
    return wight;
}

float PhysicObj::get_height()
{
    return height;
}

void PhysicObj::set_wight(float wight_)
{
    wight = wight_;
}

void PhysicObj::set_height(float height_)
{
    height = height_;
}

void PhysicObj::set_is_block(bool is_block_)
{
	is_block = is_block_;
}

bool PhysicObj::get_is_block()
{
	return is_block;
}

bool PhysicObj::get_is_ghost()
{
    return is_ghost;
}

void PhysicObj::set_is_ghost(bool is_ghost_)
{
    is_ghost = is_ghost_;
}

bool PhysicObj::get_player_in_radius_event()
{
    return player_in_radius_event;
}

void PhysicObj::set_player_in_radius_event(bool player_in_radius_event_)
{
    player_in_radius_event = player_in_radius_event_;
}

void PhysicObj::set_intersect_bullet_event(bool intersect_bullet_event_)
{
    intersect_bullet_event = intersect_bullet_event_;
}

bool PhysicObj::get_intersect_bullet_event()
{
    return intersect_bullet_event;
}

float PhysicObj::get_speed_x()
{
	return speed_x;
}

void PhysicObj::set_speed_x(float speed_x_)
{
	speed_x = speed_x_;
}

float PhysicObj::get_speed_y()
{
	return speed_y;
}

void PhysicObj::set_speed_y(float speed_y_)
{
	speed_y = speed_y_;
}

void PhysicObj::set_HP(int HP_)
{
	HP = HP_;
}

int PhysicObj::get_HP()
{
	return HP;
}

float PhysicObj::get_hit_radius()
{
	return hit_radius;
}

void PhysicObj::set_hit_radius(float hit_radius_)
{
	hit_radius = hit_radius_;
}

bool PhysicObj::get_is_staying()
{
	return is_staying;
}

void PhysicObj::set_is_staying(bool is_staying_)
{
	is_staying = is_staying_;
}

bool PhysicObj::get_life()
{
	if (get_HP() > 0) return true;
	else return false;
}
