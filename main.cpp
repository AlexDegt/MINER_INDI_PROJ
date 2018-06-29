#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Bullet.hpp"
#include "FirstEnemy.hpp"
#include "LevelConfiguration1.hpp"
#include "LevelConfiguration2.hpp"
#include "ManagerUpdate.hpp"

// Создать класс призрак, у призрака, который отнаследуешь от гейм обджект, нужно реализовать
// поведение 1)он умеет проходить сквозь все, 2)Когда игрок попадает в определенный радиус, призрак агрится на игрока. Класс PhysCount содержит в себе две важнейшие фунции: обсчитывание физики и реализацию логики. В реализации логики лежит функция player_in_radius. Внутри нее нужно проверить, находится ли плейер(игрок) в определенном радиусе. Для того, чтобы среди остальных персонажей выделить персонажа определенного типа(Player, FirstEnemy, Bulet и т д) используем флаги is_player, is_first_enemy. Для плейера is_player = 1, остальные = 0. Если игрок все-таки окажется в радиусе врага(призрака), в переменную player_in_radius_event нужно записать 1, что сигнализирует о том, что конкретное событие произошло. Далее в функции update_graph() в  классе PLayer нужно 

int main()
{
    sf::String str0[NUM_OF_ITEMS_ON_SCREEN] =
    {
        "Play",
        "Options",
        "Exit"
    };
    
    sf::String str1[NUM_OF_ITEMS_ON_SCREEN] =
    {
        "Hello",
        "Goodbye",
        "Back"
    };
    sf::String str2[NUM_OF_ITEMS_ON_SCREEN] =
    {
        "Yes",
        "No",
        "Back"
    };
    sf::String str3[NUM_OF_ITEMS_ON_SCREEN] =
    {
        "Diffyri",
        "math",
        "Back"
    };
    sf::String str4[NUM_OF_ITEMS_ON_SCREEN] =
    {
        "Option1",
        "Option2",
        "Back"
    };
    
    sf::String *array[5];
    array[0] = str0;
    array[1] = str1;
    array[2] = str2;
    array[3] = str3;
    array[4] = str4;
    
    
    
    GraphObj **mass_graph;
    PhysicObj **mass_phys;
    sf::String *map_string;
    map Map;
    ManagerLevel1Configuration manager_level1;
    mass_graph = manager_level1.get_graph_obj_array();
    mass_phys = manager_level1.get_phys_obj_array();
    
    map_string = manager_level1.get_tile_map_string();
    Map = manager_level1.get_map();
    ManagerUpdate manager_update(mass_graph, mass_phys, Map);
    manager_update.main_loop(map_string, array);
    
    return 0;
}
