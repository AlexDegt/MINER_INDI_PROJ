//
//  PhysicObj.hpp
//  newProject
//
//  Created by Илья Башаров on 08.05.2018.
//  Copyright © 2018 MIPT. All rights reserved.
//

#pragma once
#include "Constants.hpp"

class PhysicObj
{
    float X, Y,wight, height, hit_radius;
	int HP;
	float speed_x, speed_y;
	float mass;

	bool visible;
	bool is_staying; // Use if you need to make stop the hero from PhysCount
    
    // flags of done events
    bool intersect_bullet_event;
    bool player_in_radius_event;
    
    // this flags we use while realisations logics(like in function  in class PhusCount)
    bool is_player;
    bool is_first_enemy;
    bool is_bullet;
    bool is_ghost;
	bool is_block;
    
public:
    PhysicObj();
    
    float get_X();
    float get_Y();
	float get_mass();
	void set_mass(float mass_);
    void set_X(float X_);
    void set_Y(float Y_);
    void set_is_player(bool is_player_);
    void set_is_first_enemy(bool is_first_enemy_);
    void set_is_bullet(bool is_bullet_);
	void set_is_block(bool is_block_);
	bool get_is_block();
    bool get_is_player();
    bool get_is_first_enemy();
    bool get_is_bullet();
    bool get_is_ghost();
	bool get_is_staying();
	void set_is_staying(bool is_staying_);
    void set_is_ghost(bool is_ghost_);
    float get_wight();
    float get_height();
    void set_wight(float wight_);
    void set_height(float height_);
    bool get_player_in_radius_event();
    void set_player_in_radius_event(bool player_in_radius_event_);
    void set_intersect_bullet_event(bool intersect_bullet_event_);
    bool get_intersect_bullet_event();

	float get_speed_x();
	float get_speed();
	void set_speed_x(float speed_x_);
	float get_speed_y();
	void set_speed_y(float speed_y_);
	int get_HP();
	void set_HP(int HP_);  
	float get_hit_radius();
	void set_hit_radius(float hit_radius_);
	bool get_life();
};
