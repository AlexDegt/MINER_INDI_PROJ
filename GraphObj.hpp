#pragma once

#include "Constants.hpp"
#include "PhysicObj.hpp"
#include "Map.hpp"

class GraphObj
{
protected:
    PhysicObj* phys;
    bool life;
    int HP;
	float speed;
    double coeff; // CurrentFrame += Coeff * time;
    float current_frame;
    int hero_direction;
    
    double coeff_attack;
    bool is_fighting;
    bool is_running;
    sf::Color nature_color_sprite_attack;
    sf::Color nature_color_sprite;
    float current_frame_attack;
    bool interrapted;
    
    std::string file_name;
    float wight, height;
    int number_of_image;
    
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    
    sf::Image image_attack;
    sf::Texture texture_attack;
    sf::Sprite sprite_attack;
    
    std::string file_name_attack;
    float wight_attack, height_attack;
    int number_of_attack_image;
public:
    GraphObj(std::string file_name_, std::string file_name_attack_, float X_, float Y_, float wight_, float height_, float wight_attack_, float height_attack_, int number_of_image_, int number_of_attack_image_, double coeff_, double coeff_attack_);
    GraphObj();
    
    virtual void update_graph(float time, GraphObj *graph_obj_array[], map &Map);

    PhysicObj *get_phys();
    void set_phys(PhysicObj *phys_);
    
    float get_speed();
    void set_speed(float speed_);
	/*int get_HP();
	void set_HP(int HP_);*/
    
    double get_coeff();
    double get_coeff_attack();
    
    int get_hero_direction();
    void set_hero_direction(int hero_direction_);
  
    bool get_life();
    
    void set_life(bool life_);
    bool is_alive();

	bool get_is_staying();
	void set_is_staying(bool is_staying_);
    
    float get_wight();
    float get_height();
    
    sf::Sprite get_sprite();
    
    int get_number_of_image();
    void set_image(sf::Image image_);
    
    void set_texture(sf::Texture texture_);
    
    void set_sprite(sf::Sprite sprite_);
    
    float get_wight_attack();
    float get_height_attack();
    sf::Sprite get_sprite_attack();
    
    int get_number_of_attack_image();
    
    void set_image_attack(sf::Image image_attack_);
    void set_texture_attack(sf::Texture texture_attack_);

	void set_HP(int HP_);
};

