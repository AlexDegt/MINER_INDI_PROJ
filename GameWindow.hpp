//
//  GameWindow.hpp
//  newProject
//
//  Created by Илья Башаров on 31.05.2018.
//  Copyright © 2018 MIPT. All rights reserved.
//

#pragma once
#include "Constants.hpp"

class GameWindow
{
public:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text *array_of_text = new sf::Text[NUM_OF_ITEMS_ON_SCREEN]; // array of texts
    sf::Sound click;
    sf::Sound clack;
    sf::Texture *array_of_texture = new sf::Texture[NUM_OF_PICTURES_ON_SCREEN];
    sf::Sprite *array_of_sprite = new sf::Sprite[NUM_OF_PICTURES_ON_SCREEN];//pictures which changed on screen
    sf::Image icon;
    sf::SoundBuffer click_buffer;
    sf::SoundBuffer clack_buffer;
    sf::Music main_music;
    
    bool *clamped_on_text = new bool[NUM_OF_ITEMS_ON_SCREEN];
    float number_of_sprite;
    
    // загрузка фото в функции - имя файла
    GameWindow(sf::String &string_font, sf::String &string_music_click, sf::String &string_music_clack, sf::String &string_icon, sf::String *String_texts);
    GameWindow();
    ~GameWindow();
    
    int number_of_window;
    
    sf::Font get_font();
    void set_font(sf::Font &font_);
    
    sf::Text* get_array_of_text();
    void set_array_of_text(sf::Text* array_of_text_);
    
    sf::Sprite* get_array_of_sprite();
    void set_array_of_sprite(sf::Sprite* array_of_sprite_);
    
    void set_array_of_sprite(sf::String* array_of_string);
    
    sf::Image get_icon();
    void set_icon(sf::Image &icon_);
    
    int interaction_with_buttons(sf::String **array_of_string,sf::Event event);
    int pressing_the_button(sf::Event &event, int* number_of_button);
    
    int hash_key(int nesting_level, int number_of_button, int* space_in_array);
    
    void upgrade_text(sf::String ** array, int space_in_array);
    
    int counter(float time);
    
    void draw_game_window(float time);
};
