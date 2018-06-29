#include "ManagerUpdate.hpp"

ManagerUpdate::ManagerUpdate(GraphObj *graph_obj_array_[], PhysicObj *phys_obj_array_[],map &Map_)
{
    for (int i = 0; i < OBJ_ARRAY_CAPACITY; i++)
    {
        graph_obj_array[i] = graph_obj_array_[i];
    }
    for (int i = 0; i < PHYS_OBJ_ARRAY_CAPACITY; i++)
    {
        phys_count.phys_obj_array[i] = phys_obj_array_[i];
    }
    Map = Map_;
    level_complited = 0;
}

ManagerUpdate::ManagerUpdate()
{}

void ManagerUpdate::run_update_graph(float time, sf::Clock &clock, sf::View &view)
{
    time = clock.getElapsedTime().asMicroseconds();
    clock.restart();
    time = time / DECREMENT;
    for (int i = 0; i < OBJ_ARRAY_CAPACITY; i++)
    {
        graph_obj_array[i]->update_graph(time, graph_obj_array, Map);
    }
    zoom_treatment(ZOOM_VALUE, view);
    view_treatment(graph_obj_array[0]->get_sprite().getPosition().x, graph_obj_array[0]->get_sprite().getPosition().y,
                   graph_obj_array[0]->get_wight(), graph_obj_array[0]->get_height(), view);
}

void ManagerUpdate::draw_all(float time)
{
    game_window.draw_game_window(time);
    if (game_window.number_of_window == LAUNCH_WINDOW)
    {
        for (int i = 0; i < OBJ_ARRAY_CAPACITY; i++)
           if (graph_obj_array[i]->is_alive())
                game_window.window.draw(graph_obj_array[i]->get_sprite());
    }
}

int ManagerUpdate::main_loop(sf::String *map1_string_, sf::String **array_of_string)
{
    
    sf::View view(sf::FloatRect(0, 0, DIMENSION_SCREEN_X, DIMENSION_SCREEN_Y));
    sf::Clock clock;
    
    game_window.main_music.play();
    game_window.main_music.setLoop(true);
    
    while (game_window.window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / DECREMENT;
        
        sf::Event event;
        while (game_window.window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                game_window.window.close();
                return EXIT_SUCCESS;
            }
            
            game_window.interaction_with_buttons(array_of_string, event);
        }
        
        if (game_window.number_of_window > 0)
        {
            game_window.window.clear();
            
            draw_all(time);
            game_window.window.display();
        }
        else if (game_window.number_of_window == LAUNCH_WINDOW)
        {
            game_window.main_music.stop();
            game_window.window.clear();
            
            Map.DrawingMap(game_window.window, map1_string_);
			//game_window.window.draw(graph_obj_array[6]->get_sprite());
			//game_window.window.draw(graph_obj_array[7]->get_sprite());
			//game_window.window.draw(graph_obj_array[46]->get_sprite());

            phys_count.physic_count(time, Map);
            phys_count.logic_realisation();
            run_update_graph(time, clock, view);
            draw_all(time/*, game_window*/);
            game_window.window.setView(view);
            
            game_window.window.display();
        }
    }
}
