//
//  FirstEnemy.cpp
//  newProject
//
//  Created by Илья Башаров on 08.05.2018.
//  Copyright © 2018 MIPT. All rights reserved.
//

#include "FirstEnemy.hpp"

//Constructor:
FirstEnemy::FirstEnemy(std::string file_name_, std::string file_name_attack_, float X_, float Y_, float wight_, float height_, float wight_attack_, float height_attack_, int number_of_image_, int number_of_attack_image_, double coeff_, double coeff_attack_) :
GraphObj(file_name_, file_name_attack_, X_, Y_, wight_, height_, wight_attack_, height_attack_, number_of_image_, number_of_attack_image_, coeff_, coeff_attack_)
{
    interrapted = 0;// прерванный логичеким событием
    phys->set_is_first_enemy(true);
	phys->set_mass(500);
}

FirstEnemy::FirstEnemy(): GraphObj()
{}
void FirstEnemy::move_to_aim(float time, float START_X, float START_Y, float FINISH_X, float FINISH_Y)
{
	//sprite.setTexture(texture);
	sprite.setPosition(phys->get_X(), phys->get_Y());
	float speed_x = phys->get_speed_x();
	float speed_y = phys->get_speed_y();
	
    if (int(START_X) > int(FINISH_X) + wight - DISTANCE)
    {
        hero_direction = LEFT;
        current_frame += coeff * time;
        if (current_frame > number_of_image) current_frame -= number_of_image;
        sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, height, wight, height));
		if (speed_x > -CHAR_SPEED)
			phys->set_speed_x(speed_x - ACCELERATION * time);
    }
    
    else if (int(START_X) < int(FINISH_X) - wight + DISTANCE)
    {
        hero_direction = RIGHT;
        current_frame += coeff * time;
        if (current_frame > number_of_image) current_frame -= number_of_image;
        sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 2 * height, wight, height));
		if (speed_x <= CHAR_SPEED)
			phys->set_speed_x(speed_x + ACCELERATION * time);
    }
    
    else if (int(START_Y) < int(FINISH_Y) - height + DISTANCE)
    {
        hero_direction = DOWN;
        current_frame += coeff * time;
        if (current_frame > number_of_image) current_frame -= number_of_image;
        sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 0 * height, wight, height));
		if (speed_y <= CHAR_SPEED)
			phys->set_speed_y(speed_y + ACCELERATION * time);
    }
    
    else if (int(START_Y) > int(FINISH_Y) + height - DISTANCE)
    {
        hero_direction = UP;
        current_frame += coeff * time;
        if (current_frame > number_of_image) current_frame -= number_of_image;
        sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 3 * height, wight, height));
		if (speed_y > -CHAR_SPEED)
			phys->set_speed_y(speed_y - ACCELERATION * time);
    }
	//sprite.move(phys->get_speed_x()* time, phys->get_speed_y() *time);
}

void FirstEnemy::behaviour(float time, sf::Sprite player_sprite, map &Map)
{
    sprite.setTexture(texture);
    
	sprite.setTexture(texture);
	float curr_X = phys->get_X();
	float curr_Y = phys->get_Y();
	sprite.setPosition(curr_X, curr_Y);
	float speed_x = phys->get_speed_x();
	float speed_y = phys->get_speed_y();
    //float curr_X = sprite.getPosition().x;
    //float curr_Y = sprite.getPosition().y;
    
    /*phys -> set_X(curr_X);
    phys -> set_Y(curr_Y);*/
    
    sf::FloatRect sprite_bounds = sprite.getGlobalBounds();
    sf::FloatRect player_sprite_bounds = player_sprite.getGlobalBounds();
    
    if ((!interrapted) && (!sprite_bounds.intersects(player_sprite_bounds)))
    {
        if ((curr_Y <= MAP_TILESET_WIDHT * (Map.heightOfMap - 2 - 3)) && (curr_Y >= 0 + 50) && (hero_direction == DOWN))
        {
            hero_direction = DOWN;
            current_frame += coeff * time;
            if (current_frame > number_of_image) current_frame -= number_of_image;
            sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 0 * height, wight, height));
			if (speed_y <= CHAR_SPEED)
				phys->set_speed_y(speed_y + ACCELERATION * time);
        }
        else if ((curr_Y <= MAP_TILESET_WIDHT * (Map.heightOfMap - 2 - 3)) && (curr_Y >= 0 + 50) && (hero_direction == UP))
        {
            hero_direction = UP;
            current_frame += coeff * time;
            if (current_frame > number_of_image) current_frame -= number_of_image;
            sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 3 * height, wight, height));
			if (speed_y > -CHAR_SPEED)
				phys->set_speed_y(speed_y - ACCELERATION * time);
        }
        else if (curr_Y > MAP_TILESET_WIDHT * (Map.heightOfMap - 2 - 3 ))
        {
            hero_direction = UP;
            current_frame += coeff * time;
            if (current_frame > number_of_image) current_frame -= number_of_image;
            sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 3 * height, wight, height));
			if (speed_y > -CHAR_SPEED)
				phys->set_speed_y(speed_y - ACCELERATION * time);
        }
        else if (curr_Y < 0 + 50)
        {
            hero_direction = DOWN;
            current_frame += coeff * time;
            if (current_frame > number_of_image) current_frame -= number_of_image;
            sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 0 * height, wight, height));
			if (speed_y <= CHAR_SPEED)
				phys->set_speed_y(speed_y + ACCELERATION * time);
        }
		//sprite.move(phys->get_speed_x()* time, phys->get_speed_y() *time);
    }
    else
    {
        if ((sprite_bounds.intersects(player_sprite_bounds)) && (!interrapted))
            interrapted = 1;
        move_to_aim(time, sprite.getPosition().x, sprite.getPosition().y, player_sprite.getPosition().x, player_sprite.getPosition().y);
    }
}

// Ability to pass through teleporters
void FirstEnemy::teleport_communic(sf::RectangleShape gate_in, sf::RectangleShape gate_out)
{
    //Data of character
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    
    //Data of entry teleport
    sf::FloatRect gate_in_bounds = gate_in.getGlobalBounds();
    
    //Data of ext teleport
    sf::FloatRect gate_out_bounds = gate_out.getGlobalBounds();
    
    if ((spriteBounds.intersects(gate_in_bounds)) && (hero_direction == RIGHT))
        sprite.setPosition(gate_out.getPosition().x, gate_out.getPosition().y);
    
    if ((spriteBounds.intersects(gate_out_bounds)) && (hero_direction == LEFT))
        sprite.setPosition(gate_in.getPosition().x, gate_in.getPosition().y);
}

void FirstEnemy::close_in_fight_enemy(float time)
{
    sprite_attack.setTexture(texture_attack);
    
    if (!is_running)
    {
        is_fighting = IS_FIGHTING;
        //sprite has nature color, we need to make it transparent
        sprite.setColor(sf::Color::Transparent);
        
        //sprite_attack has Transparent color. We need to return the nature color
        sprite_attack.setColor(nature_color_sprite_attack);
        
        sprite_attack.setPosition(sprite.getPosition().x, sprite.getPosition().y);
        switch (hero_direction)
        {
            case LEFT:
                current_frame_attack += coeff_attack * time;
                if (current_frame_attack > number_of_attack_image) current_frame_attack -= number_of_attack_image;
                sprite_attack.setTextureRect(sf::IntRect(int(current_frame_attack) * wight_attack, height_attack, wight_attack, height_attack));
                break;
            case RIGHT:
                current_frame_attack += coeff_attack * time;
                if (current_frame_attack > number_of_attack_image) current_frame_attack -= number_of_attack_image;
                sprite_attack.setTextureRect(sf::IntRect(int(current_frame_attack) * wight_attack, 2 * height_attack, wight_attack, height_attack));
                break;
            case UP:
                current_frame_attack += coeff_attack * time;
                if (current_frame_attack > number_of_attack_image) current_frame_attack -= number_of_attack_image;
                sprite_attack.setTextureRect(sf::IntRect(int(current_frame_attack) * wight_attack, 3 * height_attack, wight_attack, height_attack));
                break;
            case DOWN:
                current_frame_attack += coeff_attack * time;
                if (current_frame_attack > number_of_attack_image) current_frame_attack -= number_of_attack_image;
                sprite_attack.setTextureRect(sf::IntRect(int(current_frame_attack) * wight_attack, 0 * height_attack, wight_attack, height_attack));
                break;
        }
    }
    else
    {
        is_fighting = !IS_FIGHTING;
        sprite_attack.setColor(sf::Color::Transparent);
    }
}

// Calling private functions
void FirstEnemy::fight_if_close(float time, sf::Sprite player_sprite)
{
    //Data of player character
    sf::FloatRect player_sprite_bounds = player_sprite.getGlobalBounds();
    
    //Data of enemy character
    sf::FloatRect enemy_sprite_bounds = sprite.getGlobalBounds();
    
    if (player_sprite_bounds.intersects(enemy_sprite_bounds))
        close_in_fight_enemy(time);
}

void FirstEnemy::update_graph(float time, GraphObj *graph_obj_array[], map &Map)
{
	/*if (!phys->get_is_staying())
	{*/
		behaviour(time, graph_obj_array[0]->get_sprite(), Map);
	//}
		fight_if_close(time, graph_obj_array[0]->get_sprite());
}

