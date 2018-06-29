//
//  Bullet.hpp
//  newProject
//
//  Created by Илья Башаров on 08.05.2018.
//  Copyright © 2018 MIPT. All rights reserved.
//

#pragma once

#include "GraphObj.hpp"

class Bullet : public GraphObj
{
    public:
    
    //Constructor:
    Bullet(std::string file_name_, std::string file_name_attack_, float X_, float Y_, float wight_, float height_, float wight_attack_, float height_attack_, int number_of_image_, int number_of_attack_image_, double coeff_, double coeff_attack_);
    Bullet();
    
    //Acceleration
    void life(float time, int player_state, float coordinate_hero_x, float coordinate_hero_y);
    
    virtual void update_graph(float time, GraphObj *graph_obj_array[], map &Map) override;

};

