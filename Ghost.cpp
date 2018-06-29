#include "Ghost.hpp"

Ghost::Ghost(std::string file_name_, std::string file_name_attack_, float X_, float Y_, float wight_, float height_, float wight_attack_, float height_attack_, int number_of_image_, int number_of_attack_image_, double coeff_, double coeff_attack_):GraphObj(file_name_, file_name_attack_, X_, Y_, wight_, height_, wight_attack_, height_attack_, number_of_image_, number_of_attack_image_, coeff_, coeff_attack_)
{
    interrapted = false;
    phys->set_is_ghost(true);
}

Ghost::Ghost():GraphObj()
{}

void Ghost::standart_movement(float time, map &Map)
{
    sprite.setTexture(texture);
    
    float curr_X = sprite.getPosition().x;
    float curr_Y = sprite.getPosition().y;
    
    phys -> set_X(curr_X);
    phys -> set_Y(curr_Y);
    
    speed = CHAR_SPEED;
    
    if ((curr_Y <= MAP_TILESET_WIDHT * (Map.heightOfMap - 2 - 3)) && (curr_Y >= 0+40) && (hero_direction == DOWN))
    {
        hero_direction = DOWN;
        current_frame += coeff * time;
        if (current_frame > number_of_image) current_frame -= number_of_image;
        sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 0 * height, wight, height));
        sprite.move(0, speed * time);
    }
    else if ((curr_Y <= MAP_TILESET_WIDHT * (Map.heightOfMap - 2 - 3)) && (curr_Y >= 0+40) && (hero_direction == UP))
    {
        hero_direction = UP;
        current_frame += coeff * time;
        if (current_frame > number_of_image) current_frame -= number_of_image;
        sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 3 * height, wight, height));
        sprite.move(0, -speed * time);
        
    }
    else if (curr_Y > MAP_TILESET_WIDHT * (Map.heightOfMap - 2 - 3))
    {
        hero_direction = UP;
        current_frame += coeff * time;
        if (current_frame > number_of_image) current_frame -= number_of_image;
        sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 3 * height, wight, height));
        sprite.move(0, -2 * speed * time);
    }
    else if (curr_Y < 0 + 40)
    {
        hero_direction = DOWN;
        current_frame += coeff * time;
        if (current_frame > number_of_image) current_frame -= number_of_image;
        sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 0 * height, wight, height));
        sprite.move(0, 2 * speed * time);
    }
}

void Ghost::move_to_aim(float time, float START_X, float START_Y, float FINISH_X, float FINISH_Y)
{
    sprite.setTexture(texture);
    
    float curr_X = sprite.getPosition().x;
    float curr_Y = sprite.getPosition().y;
    
    phys -> set_X(curr_X);
    phys -> set_Y(curr_Y);
    speed = CHAR_SPEED;
    
    if (int(START_X) > int(FINISH_X) + wight - DISTANCE)
    {
        hero_direction = LEFT;
        current_frame += coeff * time;
        if (current_frame > number_of_image) current_frame -= number_of_image;
        sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, height, wight, height));
        sprite.move(-speed * time, 0);
        
    }
    
    else if (int(START_X) < int(FINISH_X) - wight + DISTANCE)
    {
        hero_direction = RIGHT;
        current_frame += coeff * time;
        if (current_frame > number_of_image) current_frame -= number_of_image;
        sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 2 * height, wight, height));
        sprite.move(speed*time, 0);
    }
    
    else if (int(START_Y) < int(FINISH_Y) - height + DISTANCE)
    {
        hero_direction = DOWN;
        current_frame += coeff * time;
        if (current_frame > number_of_image) current_frame -= number_of_image;
        sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 0 * height, wight, height));
        sprite.move(0, speed*time);
    }
    
    else if (int(START_Y) > int(FINISH_Y) + height - DISTANCE)
    {
        hero_direction = UP;
        current_frame += coeff * time;
        if (current_frame > number_of_image) current_frame -= number_of_image;
        sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 3 * height, wight, height));
        sprite.move(0, -speed * time);
      
    }
}

void Ghost::behaviour(float time, sf::Sprite player_sprite, map &Map)
{
    if (get_phys() -> get_player_in_radius_event())
    move_to_aim(time, get_sprite().getPosition().x, get_sprite().getPosition().y, player_sprite.getPosition().x, player_sprite.getPosition().y);
    else
        standart_movement(time, Map);
}

/*
void Ghost::close_in_fight_enemy(float time)
{
    
}

void Ghost::fight_if_close(float time, sf::Sprite player_sprite)
{
    
}
*/

void Ghost::update_graph(float time, GraphObj *graph_obj_array[], map &Map)
{
    behaviour(time, graph_obj_array[0] -> get_sprite(), Map);
}

