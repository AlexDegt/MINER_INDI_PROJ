#pragma once

#include "FirstEnemy.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Ghost.hpp"
#include "Block.hpp"

class ManagerLevel1Configuration
{
public:
    GraphObj * graph_obj_array[OBJ_ARRAY_CAPACITY];
    PhysicObj * phys_obj_array[PHYS_OBJ_ARRAY_CAPACITY];
    //
    /*sf::String TileMap[HEIGHT_MAP_1] =
    {
        "ghghghghghghghgooooooooooooooo",
        "cccccccccccccchghghghghghghghg",
        "ccccccccccccccccccnnnnnnncccc",
        "ccccccccccccccccccnnmemnncccc",
        "ccccccccccccccccccnnmemnncccc",
        "ccccccccccccccccccnnnnnnncccc",
        "cccccccccccccchghghghghghghghg",
        "ghghghghghghghgoooooooooooooo",
        "oooooooooooooo",
        
    };*/
    
    sf::String TileMap[HEIGHT_MAP_1] =
    {
        "pppppppppppppppppppppppppppppppppppppppp",
        "pppppppppppppppppppppppppppppppppppppppp",
        "aooaaooohggooaoofhfooooaaooggoefeooehhhh",
        "cccccccckkkcjcccckccccccccjkkccccccckkkk",
        "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkbkkkbkkkkk",
        "kkkkkkbkkkkkbkkkkkkkkkkkkbkkkkkkkkkkkkkk",
        "kkkbkkkkkkkkkkkkkkkkbkkkbkkkkbkkbkkkkkkk",
        "kkkkkbkkkkkkkkkkkkkkkkkkkkbkkkkkkkkkkkkk",
        "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm",
        "pppppppppppppppppppppppppppppppppppppppp",
        "pppppppppppppppppppppppppppppppppppppppp",
    };
    
    map Map;
    
    Player player;
    FirstEnemy snake;
    FirstEnemy gorilla;
    Bullet bullet;
    Ghost ghost;
	Block *array_block = new Block[80];

    ManagerLevel1Configuration();
    
    // A function that returns an array of objects at a given level
    GraphObj **get_graph_obj_array();
    
    PhysicObj **get_phys_obj_array();
    
    sf::String *get_tile_map_string();
    
    map get_map();
};
