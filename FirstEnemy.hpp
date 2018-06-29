#pragma once
#include "GraphObj.hpp"

class FirstEnemy: public GraphObj
{
public:
    //Constructor:
    FirstEnemy(std::string file_name_, std::string file_name_attack_, float X_, float Y_, float wight_, float height_, float wight_attack_, float height_attack_, int number_of_image_, int number_of_attack_image_, double coeff_, double coeff_attack_);
    FirstEnemy();
    
    void move_to_aim(float time, float START_X, float START_Y, float FINISH_X, float FINISH_Y);
    
    void behaviour(float time, sf::Sprite player_sprite, map &Map);
    
    // Ability to pass through teleporters
    void teleport_communic(sf::RectangleShape gate_in, sf::RectangleShape gate_out);
    
    void close_in_fight_enemy(float time);
    
    // Calling private functions
    void fight_if_close(float time, sf::Sprite player_sprite);
    
    virtual void update_graph(float time, GraphObj *graph_obj_array[], map &Map) override;
};

