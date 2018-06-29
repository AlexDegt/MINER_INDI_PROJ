#pragma once

#include "GraphObj.hpp"

class Player : public GraphObj
{
public:
    //Constructor:
    Player(std::string file_name_, std::string file_name_attack_, float X_, float Y_, float wight_, float height_, float wight_attack_, float height_attack_, int number_of_image_, int number_of_attack_image_, double coeff_, double coeff_attack_);
    Player();
    
    //Keyboard:
    void keyboard(float time);
    
    //Acceleration
    void acceleration(float time);
    
    // Collection of gold
    void gold_collect_communic_circle(sf::CircleShape &shape);
    
    // Ability to pass through teleporters
    void teleport_communic(sf::RectangleShape &gate_in, sf::RectangleShape &gate_out);
    
    //Close in fighting
    void close_in_fight(float time);
    
    void make_standart_speed();
    
    // The hero walks only on the map
    void map_limit(int width_of_map_, int height_of_map_);
    
    void no_way_communic_rectangle(sf::RectangleShape shape, float time);
    
    void no_way_communic_circle(sf::CircleShape shape, float time);
    
    // Move rectangles
    sf::RectangleShape move_rectangle_communic(sf::RectangleShape shape, float time);
    
    virtual void update_graph(float time, GraphObj *graph_obj_array[], map &Map) override;
};

