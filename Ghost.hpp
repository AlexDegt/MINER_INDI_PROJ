#pragma once

#include "Ghost.hpp"
#include "GraphObj.hpp"

class Ghost: public GraphObj
{
public:
    std::string text;
    Ghost(std::string file_name_, std::string file_name_attack_, float X_, float Y_, float wight_, float height_, float wight_attack_, float height_attack_, int number_of_image_, int number_of_attack_image_, double coeff_, double coeff_attack_);
    Ghost();
    
    void standart_movement(float time, map &Map);
    
    void move_to_aim(float time, float startX, float startY, float finishX, float finishY);
    
    void behaviour(float time, sf::Sprite player_sprite, map &Map);
    
    void close_in_fight_enemy(float time);
    
    // Calling private functions
    void fight_if_close(float time, sf::Sprite player_sprite);
    virtual void update_graph(float time, GraphObj *graph_obj_array[], map &Map) override;
};
