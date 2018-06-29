#include "LevelConfiguration1.hpp"

ManagerLevel1Configuration::ManagerLevel1Configuration()
{
    //snake = FirstEnemy();
    snake = FirstEnemy("snake.png", "snake.png", 400, 50, 64, 64, 64, 64, 4, 0, COEFF_SPEED, COEFF_ATTACK_SPEED);
    gorilla = FirstEnemy("snake.png", "snake.png", 400, 50, 64, 64, 64, 64, 4, 0, COEFF_SPEED, COEFF_ATTACK_SPEED);
    player = Player("main_hero.png", "main_hero.png", 50, 80, 64, 64, 64, 64, 9, 9, COEFF_SPEED, COEFF_ATTACK_SPEED);
    ghost = Ghost("standart_ghost.png", "attack_ghost.png", 600, 200, 45, 45, 45, 45, 3, 3, COEFF_SPEED, COEFF_ATTACK_SPEED);
	bullet = Bullet("bullet.png", "bullet.png", 50, 100, 16, 16, 16, 16, 1, 1, COEFF_SPEED, COEFF_ATTACK_SPEED);

	for (int i = 5; i < 45; i++)
	{
		array_block[i-5] = Block("rock.png", "rock.png", 32 * (i - 5), 32, 32, 32, 0, 0, 1, 0, 0, 0);
		graph_obj_array[i] = &array_block[i-5];
		phys_obj_array[i] = graph_obj_array[i]->get_phys();
	}
	for (int i = 45; i < PHYS_OBJ_ARRAY_CAPACITY; i++)
	{
		array_block[i-5] = Block("rock.png", "rock.png", 32 * (i - 45), 263, 32, 32, 0, 0, 1, 0, 0, 0);
		graph_obj_array[i] = &array_block[i-5];
		phys_obj_array[i] = graph_obj_array[i]->get_phys();
	}
    
    Map = map("map.png", WIDHT_MAP_1, HEIGHT_MAP_1);
    
	graph_obj_array[0] = &player;
	graph_obj_array[1] = &snake;
	graph_obj_array[2] = &gorilla;
	graph_obj_array[3] = &ghost;
	graph_obj_array[4] = &bullet;
    
    // Initialize the physics pointer for the bullet
    
    phys_obj_array[0] = graph_obj_array[0]->get_phys();
    phys_obj_array[1] = graph_obj_array[1]->get_phys();
    phys_obj_array[2] = graph_obj_array[2]->get_phys();
    phys_obj_array[3] = graph_obj_array[3]->get_phys();
	phys_obj_array[4] = graph_obj_array[4]->get_phys();

}

// A function that returns an array of objects at a given level
GraphObj** ManagerLevel1Configuration::get_graph_obj_array()
{
    return graph_obj_array;
}

PhysicObj** ManagerLevel1Configuration::get_phys_obj_array()
{
    return phys_obj_array;
}

sf::String* ManagerLevel1Configuration::get_tile_map_string()
{
    return TileMap;
}

map ManagerLevel1Configuration::get_map()
{
    return Map;
}

