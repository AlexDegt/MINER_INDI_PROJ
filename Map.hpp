//
//  Map.hpp
//  newProject
//
//  Created by Илья Башаров on 08.05.2018.
//  Copyright © 2018 MIPT. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include <assert.h>
#include "Constants.hpp"

class map
{
public:
    sf::Image mapImage;
    sf::Texture mapTexture;
    sf::Sprite mapSprite;
    std::string mapFile;
    int widthOfMap;
    int heightOfMap;
    
    void DrawingMap(sf::RenderWindow &window, sf::String *TileMap);
    
    map();
    map(sf::String file, int widthOfMap_, int heightOfMap_);
    ~map();
};


#endif /* Map_hpp */
