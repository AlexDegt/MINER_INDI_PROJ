//
//  GameWindow.cpp
//  newProject
//
//  Created by Илья Башаров on 31.05.2018.
//  Copyright © 2018 MIPT. All rights reserved.
//

#include "GameWindow.hpp"

GameWindow::GameWindow()
{
    window.create(sf::VideoMode(DIMENSION_SCREEN_X,DIMENSION_SCREEN_Y), "The Miner");
    
    number_of_window = FIRST_LEVEL_OF_OPTIONS;
    number_of_sprite = 0;
    
    if (main_music.openFromFile("Horror.ogg") == false)
    {
        assert(!"CreateMainWindow is crashed(loadFromFile music)");
    }
    
    if (icon.loadFromFile("icon.png") == false)
    {
        assert(!"CreateMainWindow is crashed(loadFromFile icon)");
    }
    
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    for (int i = 0; i < NUM_OF_PICTURES_ON_SCREEN; i++)
    {
        char number = i + '1';
		sf::String str = {};
        // Load a sprite to display
        if (array_of_texture[i].loadFromFile(str + number + ".jpg") == false)
        {
			std::cout << number + ".jpg" << std::endl;
            assert(!"CreateMainWindow is crashed(loadFromFile texture)");
        }
        array_of_sprite[i].setTexture(array_of_texture[i]);
    }
    
    // Create a graphical text to display
    if (!font.loadFromFile("new_new_font.ttf"))
    {
        assert(!"CreateMainWindow is crashed(loadFromFile font)");
    }
    
    sf::String String_texts[NUM_OF_ITEMS_ON_SCREEN] =
    {
        "Play",
        "Options",
        "Exit"
    };
    
    for (int i = 0; i < NUM_OF_ITEMS_ON_SCREEN; i++)
    {
        clamped_on_text[i] = false;
        array_of_text[i].setFont(font);
        array_of_text[i].setString(String_texts[i]);
        array_of_text[i].setCharacterSize(CHARACTER_SIZE_WORD);
        array_of_text[i].setFillColor(sf::Color::Black);
        
        array_of_text[i].setOrigin(array_of_text[i].getLocalBounds().width/2,array_of_text[i].getLocalBounds().height/2);
        
        array_of_text[i].setPosition(DIMENSION_SCREEN_X / 2, DIMENSION_SCREEN_Y / 2 + i*((DIMENSION_SCREEN_Y/2 - INDENT) / NUM_OF_ITEMS_ON_SCREEN ));
    }
    
    
    if (!click_buffer.loadFromFile("mouserelease1.ogg") || !clack_buffer.loadFromFile("mouseclick1.ogg"))
    {
        assert(!"CreateMainWindow is crashed(loadFromFile music)");
    }
    else
    {
        click.setBuffer(click_buffer);
        clack.setBuffer(clack_buffer);
    }
}

GameWindow::~GameWindow()
{}

GameWindow::GameWindow(sf::String &string_font, sf::String &string_music_click, sf::String &string_music_clack, sf::String &string_icon, sf::String *String_texts):
number_of_window(FIRST_LEVEL_OF_OPTIONS),
number_of_sprite(0)
{
    
    window.create(sf::VideoMode(DIMENSION_SCREEN_X,DIMENSION_SCREEN_Y), "The Miner");
    
    if (icon.loadFromFile(string_font) == false)
    {
        assert(!"CreateMainWindow is crashed(loadFromFile icon)");
    }
    
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    for (int i = 0; i < NUM_OF_PICTURES_ON_SCREEN; i++)
    {
        sf::Texture texture;
        char number = i + '0';
        
        if (texture.loadFromFile(number + ".jpg") == false)
        {
            assert(!"CreateMainWindow is crashed(loadFromFile texture)");
        }
        array_of_sprite[i].setTexture(texture);
    }
    
    // Create a graphical text to display
    if (!font.loadFromFile(string_font))
    {
        assert(!"CreateMainWindow is crashed(loadFromFile font)");
    }
    
    for (int i = 0; i < NUM_OF_ITEMS_ON_SCREEN; i++)
    {
        clamped_on_text[i] = false;
        array_of_text[i].setFont(font);
        array_of_text[i].setString(String_texts[i]);
        array_of_text[i].setCharacterSize(CHARACTER_SIZE_WORD);
        array_of_text[i].setFillColor(sf::Color::White);
        
        array_of_text[i].setOrigin(String_texts[i].getSize()*CHARACTER_SIZE_WORD/2 , String_texts[i].getSize()*CHARACTER_SIZE_WORD/4);//че за хуйня написана
        
        array_of_text[i].setPosition(DIMENSION_SCREEN_X / 2, DIMENSION_SCREEN_Y / 2 + i*(DIMENSION_SCREEN_Y/2 - INDENT) / NUM_OF_ITEMS_ON_SCREEN ); //рандом полнейший
    }
    
    if (!click_buffer.loadFromFile(string_music_click) || !clack_buffer.loadFromFile(string_music_clack))
    {
        assert(!"CreateMainWindow is crashed(loadFromFile music)");
    }
    else
    {
        click.setBuffer(click_buffer);
        clack.setBuffer(clack_buffer);
    }
}

sf::Font GameWindow::get_font()
{
    return font;
}

void GameWindow::set_font(sf::Font &font_)
{
    font = font_;
}

sf::Text* GameWindow::get_array_of_text()
{
    return array_of_text;
}

void GameWindow::set_array_of_text(sf::Text* array_of_text_)
{
    array_of_text = array_of_text_;
}

sf::Sprite* GameWindow::get_array_of_sprite()
{
    return array_of_sprite;
}

void GameWindow::set_array_of_sprite(sf::Sprite* array_of_sprite_)
{
    array_of_sprite = array_of_sprite_;
}

void GameWindow::set_array_of_sprite(sf::String* array_of_string)
{
    for (int i = 0; i < NUM_OF_ITEMS_ON_SCREEN; i++)
    {
        array_of_text[i].setString(array_of_string[i]);
        array_of_text[i].setPosition(DIMENSION_SCREEN_X/2, INDENT +i*(DIMENSION_SCREEN_Y - 2*INDENT)/NUM_OF_ITEMS_ON_SCREEN);
    }
}

sf::Image GameWindow::get_icon()
{
    return icon;
}
void GameWindow::set_icon(sf::Image &icon_)
{
    icon = icon_;
}

int GameWindow::pressing_the_button(sf::Event &event, int* number_of_button)
{
    // Update mouse coordinates
    sf::Vector2i PixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f GamePos = window.mapPixelToCoords(PixelPos);
    
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            for (int i = 0; i < NUM_OF_ITEMS_ON_SCREEN; i ++)
            {
                if (array_of_text[i].getGlobalBounds().contains(GamePos.x, GamePos.y))
                {
                    clamped_on_text[i] = true;
                    array_of_text[i].setCharacterSize(CHARACTER_SIZE_WORD - 3); // 3 - уменьшение
                    array_of_text[i].setFillColor(sf::Color(145,146,146)); // sf::Color(145,146,146) - grey
                    click.play();
                    array_of_text[i].move(2, 2);
                }
            }
        }
    }
    
    if (event.type == sf::Event::MouseButtonReleased)
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            for (int i = 0; i < NUM_OF_ITEMS_ON_SCREEN; i ++)
            {
                if (clamped_on_text[i])
                {
                    clamped_on_text[i] = false;
                    array_of_text[i].setCharacterSize(CHARACTER_SIZE_WORD);
                    array_of_text[i].setFillColor(sf::Color::Black);
                    array_of_text[i].move(-2, -2);
                    if (array_of_text[i].getGlobalBounds().contains(GamePos.x, GamePos.y))
                    {
                        clack.play();
                        *number_of_button = i;
                        return ENDOFLAUNCH_SECCESS;
                    }
                }
            }
        }
        
    // Escape pressed: exit
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        window.close();
        return ENDOFLAUNCH_CLOSED;
    }
    return NOTENDOFLAUNCH;
}

int GameWindow::hash_key(int nesting_level, int number_of_button, int* space_in_array)
{
    number_of_button +=1;
    switch (nesting_level)
    {
        case FIRST_LEVEL_OF_OPTIONS:
        {
            if (number_of_button == PLAY)
            {
                number_of_window = LAUNCH_WINDOW;
                return PLAY;
            }
            else if (number_of_button == EXIT)
            {
                number_of_window = CLOSED_WINDOW;
                window.close();
                return EXIT;
            }
            else if (number_of_button == GO_TO_NEXT_LEVEL_OF_OPTIONS)
            {
                *space_in_array = 1;
                number_of_window = SECOND_LEVEL_OF_OPTIONS;
                return GO_TO_NEXT_LEVEL_OF_OPTIONS;
            }
        }
            break;
            
        case SECOND_LEVEL_OF_OPTIONS:
        {
            if (number_of_button == BACK)
            {
                *space_in_array = 0;
                number_of_window = FIRST_LEVEL_OF_OPTIONS;
                return GO_TO_NEXT_LEVEL_OF_OPTIONS;
            }
            else
            {
                *space_in_array = pow(2, nesting_level - 1) + number_of_button - 1;
                number_of_window = THIRD_LEVEL_OF_OPTIONS;
                return GO_TO_NEXT_LEVEL_OF_OPTIONS;
            }
        }
            break;
         
        case THIRD_LEVEL_OF_OPTIONS:
        {
            if (number_of_button == BACK)
            {
                *space_in_array = 1;
                number_of_window = SECOND_LEVEL_OF_OPTIONS;
                return GO_TO_NEXT_LEVEL_OF_OPTIONS;
            }
        }
            break;
        default:
            break;
    }
}

int GameWindow::interaction_with_buttons(sf::String **array_of_string, sf::Event event)
{
    int number_of_pressed_button = 0;
    int result_button = 0;
    int result_hash = 0;
    int space_in_array = 0;
    result_button = pressing_the_button(event, &number_of_pressed_button);
    if (result_button == ENDOFLAUNCH_SECCESS)
    {
        result_button = NOTENDOFLAUNCH;
        result_hash = hash_key(number_of_window, number_of_pressed_button, &space_in_array);
        
        if (result_hash == GO_TO_NEXT_LEVEL_OF_OPTIONS)
        {
            upgrade_text(array_of_string, space_in_array);
        }
    }
	return 1;
}

void GameWindow::upgrade_text(sf::String ** array, int space_in_array)
{
    for (int i = 0; i < NUM_OF_ITEMS_ON_SCREEN; i++)
    {
        array_of_text[i].setString(array[space_in_array][i]);
        
        array_of_text[i].setOrigin(array_of_text[i].getLocalBounds().width/2,array_of_text[i].getLocalBounds().height/2);
        
      array_of_text[i].setOrigin(array_of_text[i].getLocalBounds().width/2,array_of_text[i].getLocalBounds().height/2);
        
       array_of_text[i].setPosition(DIMENSION_SCREEN_X / 2, DIMENSION_SCREEN_Y / 2 + i*((DIMENSION_SCREEN_Y/2 - INDENT) / NUM_OF_ITEMS_ON_SCREEN));
    }
}

int GameWindow::counter(float time)
{
    number_of_sprite += time/15;
    if (number_of_sprite >= 4)
        number_of_sprite  = 0;
    
    int random = rand()%3;
    int number = (int)number_of_sprite;
    if ((random == number + 1) && (number < 4))
        return random;
    else
        return number;
}

void GameWindow::draw_game_window(float time)
{
    if (number_of_window > 0)
    {
        window.draw(array_of_sprite[counter(time)]);
        for (int i = 0; i < NUM_OF_ITEMS_ON_SCREEN; i ++)
            window.draw(array_of_text[i]);
    }
}
