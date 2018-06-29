//
//  Map.cpp
//  newProject
//
//  Created by Илья Башаров on 08.05.2018.
//  Copyright © 2018 MIPT. All rights reserved.
//

#include "Map.hpp"

map::map(sf::String file, int widthOfMap_, int heightOfMap_)
{
    mapFile = file;
    widthOfMap = widthOfMap_;
    heightOfMap = heightOfMap_;
}

map::map()
{}

void map::DrawingMap(sf::RenderWindow &window, sf::String *TileMap)
{
    //If we put this into the constructor, then everything breaks down
    if (mapImage.loadFromFile("map.jpeg") == false)
        assert(!"Class map was crashed(loadFormFile mapImage)");
    
    mapTexture.loadFromImage(mapImage);
    mapSprite.setTexture(mapTexture);
    
    for (int i = 0; i < heightOfMap; i++)
    {
        for (int j = 0; j < widthOfMap; j++)
        {
            mapSprite.setTextureRect(sf::IntRect((TileMap[i][j] - 'a')*MAP_TILESET_WIDHT, 0, MAP_TILESET_WIDHT, MAP_TILESET_WIDHT));
            
            mapSprite.setPosition(j * MAP_TILESET_WIDHT, i * MAP_TILESET_WIDHT);
            window.draw(mapSprite);
        }
    }
}

map::~map()
{}
