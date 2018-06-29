//
//  View.hpp
//  newProject
//
//  Created by Илья Башаров on 08.05.2018.
//  Copyright © 2018 MIPT. All rights reserved.
//

#ifndef View_hpp
#define View_hpp

#include "Constants.hpp"

extern int dimensionScreenX;
extern int dimensionScreenY;
extern sf::Vector2f positionScreen;

void view_treatment(float X, float Y, float wight, float height, sf::View &view);
void zoom_treatment(int ZoomValue, sf::View &view);

#endif /* View_hpp */
