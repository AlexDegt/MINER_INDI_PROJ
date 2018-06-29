//
//  Bullet.cpp
//  newProject
//
//  Created by Илья Башаров on 08.05.2018.
//  Copyright © 2018 MIPT. All rights reserved.
//

#include "Bullet.hpp"

Bullet::Bullet()
{}

Bullet::Bullet(std::string file_name_, std::string file_name_attack_, float X_, float Y_, float wight_, float height_, float wight_attack_, float height_attack_, int number_of_image_, int number_of_attack_image_, double coeff_, double coeff_attack_) :
GraphObj(file_name_, file_name_attack_, X_, Y_, wight_, height_, wight_attack_, height_attack_, number_of_image_, number_of_attack_image_, coeff_, coeff_attack_)
{
    phys->set_HP(0);
    phys->set_is_bullet(true);
	phys->set_mass(1000000);
	phys->set_hit_radius(16);
}

void Bullet::life(float time, int player_state, float coordinate_hero_x, float coordinate_hero_y)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) /*&& !get_life()*/)
    {
        set_hero_direction(player_state);
        phys->set_HP(100);
		phys->set_X(coordinate_hero_x +25);
		phys->set_Y(coordinate_hero_y +25);
    }
    
    if (phys->get_life())
    {
		sprite.setTexture(texture);
		sprite.setPosition(phys->get_X(), phys->get_Y());
		float speed_x = phys->get_speed_x();
		float speed_y = phys->get_speed_y();
        /*sprite.setTexture(texture);
        
        float curr_X = sprite.getPosition().x;
        float curr_Y = sprite.getPosition().y;
        
        phys -> set_X(curr_X);
        phys -> set_Y(curr_Y);
        
        if (speed == 0)
            speed = CHAR_SPEED;*/
        
        switch (get_hero_direction())
        {
            case LEFT:
				if (speed_x > -6*CHAR_SPEED)
					phys->set_speed_x(speed_x - ACCELERATION * time);
                //sprite.move((-3)*speed * time, 0);
                break;
            case RIGHT:
				if (speed_x <= 6*CHAR_SPEED)
					phys->set_speed_x(speed_x + ACCELERATION * time);
                //sprite.move(3*speed * time, 0);
                break;
            case UP:
				if (speed_y > -6*CHAR_SPEED)
					phys->set_speed_y(speed_y - ACCELERATION * time);
                //sprite.move(0, (-3)*speed * time);
                break;
            case DOWN:
				if (speed_y <= 6*CHAR_SPEED)
					phys->set_speed_y(speed_y + ACCELERATION * time);
                //sprite.move(0, 3*speed * time);
                break;
        }
    }
}

void Bullet::update_graph(float time, GraphObj *graph_obj_array[], map &Map)
{
    life(time, graph_obj_array[0] -> get_hero_direction(),graph_obj_array[0]->get_phys()->get_X(),graph_obj_array[0]->get_phys()->get_Y());
}
