#include "LevelConfiguration2.hpp"

ManagerLevel2Configuration::ManagerLevel2Configuration()
{
    snake = FirstEnemy("snake.png","snake.png", 400, 50, 64, 64, 64, 64, 4, 0, COEFF_SPEED, COEFF_ATTACK_SPEED);
    gorilla = FirstEnemy("image.png","image.png", 600, 50, 80, 78, 80, 78, 3, 3, COEFF_SPEED, COEFF_ATTACK_SPEED);
    player = Player("gorilla.png", "gorilla_fight.png", 50, 50, 80, 80, 80, 80, 4, 4, COEFF_SPEED, COEFF_ATTACK_SPEED);
    bullet = Bullet();
    Map = map("map.png", WIDHT_MAP_1, HEIGHT_MAP_1);
    graph_obj_array[0] = &player;
    graph_obj_array[1] = &snake;
    graph_obj_array[2] = &gorilla;
    //graph_obj_array[3] = &bullet;
    
    bullet_phys = PhysicObj();
    phys_obj_array[0] = &bullet_phys;
    bullet.set_phys(phys_obj_array[0]);
}

GraphObj** ManagerLevel2Configuration::get_graph_obj_array()
{
    return graph_obj_array;
}

PhysicObj** ManagerLevel2Configuration::get_phys_obj_array()
{
    return phys_obj_array;
}

sf::String* ManagerLevel2Configuration::get_tile_map_string()
{
    return TileMap;
}

map ManagerLevel2Configuration::get_map()
{
    return Map;
}
