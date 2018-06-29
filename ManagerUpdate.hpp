#pragma once

#include "Player.hpp"
#include "GameWindow.hpp"
#include "PhysicObj.hpp"
#include "GraphObj.hpp"
#include "PhysicCount.hpp"
#include "View.hpp"

class ManagerUpdate
{
public:
    PhysicCount phys_count;
    GraphObj *graph_obj_array[OBJ_ARRAY_CAPACITY] = {};
    map Map;
    sf::Event event;
    GameWindow game_window;
    
    bool level_complited;
    
    ManagerUpdate(GraphObj *graph_obj_array_[], PhysicObj *phys_obj_array_[],map &Map_);
    
    ManagerUpdate();
    
    void run_update_graph(float time, sf::Clock &clock, sf::View &view);
    
    void draw_all(float time);
    
    int main_loop(sf::String *map1_string_, sf::String **array_of_string);
};
