#pragma once

#include "FirstEnemy.hpp"
#include "Player.hpp"
#include "Bullet.hpp"

class ManagerLevel2Configuration
{
public:
    GraphObj * graph_obj_array[OBJ_ARRAY_CAPACITY];
    PhysicObj * phys_obj_array[PHYS_OBJ_ARRAY_CAPACITY];
    sf::String TileMap[HEIGHT_MAP_1] =
    {
        "0000000000000000000000000000000000000000",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0                                      0",
        "0             sssss                    0",
        "0         ssss    ssss                 0",
        "0      sss            sss              0"
    };
    map Map;
    
    Player player;
    FirstEnemy snake;
    FirstEnemy gorilla;
    PhysicObj bullet_phys;
    Bullet bullet;
    ManagerLevel2Configuration();
    
    GraphObj **get_graph_obj_array();
    
    PhysicObj **get_phys_obj_array();
    
    sf::String *get_tile_map_string();
    
    map get_map();
};

