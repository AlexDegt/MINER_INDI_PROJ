//
//  View.cpp
//  newProject
//
//  Created by Илья Башаров on 08.05.2018.
//  Copyright © 2018 MIPT. All rights reserved.
//

#include "View.hpp"

int dimensionScreenX = 680;
int dimensionScreenY = 480;
sf::Vector2f positionScreen(0, 0);

void view_treatment(float X, float Y, float wight, float height, sf::View &view)
{
    positionScreen.x = X + wight - (dimensionScreenX / 2);
    positionScreen.y = Y + height - (dimensionScreenY / 2);
    
    //Checking the exit of the character for half the screen
    if (positionScreen.x < 0)
        positionScreen.x = 0;
    if (positionScreen.y < 0)
        positionScreen.y = 0;
    //Change the appearance of the screen
    view.reset(sf::FloatRect(positionScreen.x, positionScreen.y, dimensionScreenX, dimensionScreenY));
}
void zoom_treatment(int ZoomValue, sf::View &view)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))
        view.setSize(dimensionScreenX += ZoomValue, dimensionScreenY += ZoomValue);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
        view.setSize(dimensionScreenX -= ZoomValue, dimensionScreenY -= ZoomValue);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
    {
        dimensionScreenX = int(DIMENSION_SCREEN_X);
        dimensionScreenY = int(DIMENSION_SCREEN_Y);
        view.setSize(dimensionScreenX, dimensionScreenY);
    }
    
    //Check to not increase the image too much
    if (dimensionScreenX < DIMENSION_SCREEN_X - DELTA_DIMENSION_INC)
    {
        dimensionScreenX = DIMENSION_SCREEN_X - DELTA_DIMENSION_INC;
        dimensionScreenY = DIMENSION_SCREEN_Y - DELTA_DIMENSION_INC;
    }
    
    //Check to not too reduce the image
    if (dimensionScreenX > DIMENSION_SCREEN_X + DELTA_DIMENSION_DEC)
    {
        dimensionScreenX = DIMENSION_SCREEN_X + DELTA_DIMENSION_DEC;
        dimensionScreenY = DIMENSION_SCREEN_Y + DELTA_DIMENSION_DEC;
    }
}
