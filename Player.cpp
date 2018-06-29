#include "Player.hpp"

Player::Player(std::string file_name_, std::string file_name_attack_, float X_, float Y_, float wight_, float height_, float wight_attack_, float height_attack_, int number_of_image_, int number_of_attack_image_, double coeff_, double coeff_attack_) :
GraphObj(file_name_, file_name_attack_, X_, Y_, wight_, height_, wight_attack_, height_attack_, number_of_image_, number_of_attack_image_, coeff_, coeff_attack_)
{
    phys->set_is_player(true);
	phys->set_mass(50);
}

Player::Player():
GraphObj()
{}


void Player::keyboard(float time)
{
    sprite.setTexture(texture);
	sprite.setPosition(phys->get_X(), phys->get_Y());
	float speed_x = phys->get_speed_x();
	float speed_y = phys->get_speed_y();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		hero_direction = LEFT;
		current_frame += coeff * time;
		if (current_frame > number_of_image) current_frame -= number_of_image;
		sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 1 * height, wight, height));
		if (speed_x > -CHAR_SPEED)
			phys->set_speed_x(speed_x - ACCELERATION * time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		hero_direction = RIGHT;
		current_frame += coeff * time;
		if (current_frame > number_of_image) current_frame -= number_of_image;
		sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 3 * height, wight, height));
		if (speed_x <= CHAR_SPEED)
			phys->set_speed_x(speed_x + ACCELERATION * time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		hero_direction = UP;
		current_frame += coeff * time;
		if (current_frame > number_of_image) current_frame -= number_of_image;
		sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 0 * height, wight, height));
		if (speed_y > -CHAR_SPEED)
			phys->set_speed_y(speed_y - ACCELERATION * time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		hero_direction = DOWN;
		current_frame += coeff * time;
		if (current_frame > number_of_image) current_frame -= number_of_image;
		sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 2 * height, wight, height));
		if (speed_y <= CHAR_SPEED)
			phys->set_speed_y(speed_y + ACCELERATION * time);
	}
	if ((!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
		phys->set_speed_x(0);
	if ((!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
		phys->set_speed_y(0);
	/*printf("speed_x = %lf\n", phys->get_speed_x());
	printf("speed_y = %lf\n", phys->get_speed_y());
	printf("X = %lf\n", phys->get_X());
	printf("Y = %lf\n", phys->get_Y());*/
	//sprite.move(phys->get_speed_x()* time, phys->get_speed_y() *time);



	//sprite.setPosition(phys->get_X(), phys->get_Y());



    /*if (speed == 0)
        speed = CHAR_SPEED;*/
}
//Acceleration
void Player::acceleration(float time)
{
	float speed_x = phys->get_speed_x();
	float speed_y = phys->get_speed_y();
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && (abs(phys->get_speed_x()) <= 2*CHAR_SPEED) && (abs(phys->get_speed_y()) <= 2*CHAR_SPEED))
	{
		if ((hero_direction == LEFT) && (speed_x))
			phys->set_speed_x(speed_x - time*ACCELERATION);
		if ((hero_direction == RIGHT) && (speed_x))
			phys->set_speed_x(speed_x + time * ACCELERATION);
		if ((hero_direction == UP) && (speed_y))
			phys->set_speed_y(speed_y - time * ACCELERATION);
		if ((hero_direction == DOWN) && (speed_y))
			phys->set_speed_y(speed_y + time * ACCELERATION);
	}
}
// Collection of gold
void Player::gold_collect_communic_circle(sf::CircleShape &shape)
{
    //Data of character
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    
    //Data of a coin
    sf::FloatRect shapeBounds = shape.getGlobalBounds();
    
    if (spriteBounds.intersects(shapeBounds))
    {
        ////////////Test
        if (shape.getFillColor() == sf::Color::Red)
            phys->set_HP(phys->get_HP() - 50);
        ////////////////
        shape.setFillColor(sf::Color::Transparent);
    }
}
// Ability to pass through teleporters
void Player::teleport_communic(sf::RectangleShape &gate_in, sf::RectangleShape &gate_out)
{
    //Data of character
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    
    //Data of entry teleport
    sf::FloatRect gate_in_bounds = gate_in.getGlobalBounds();
    
    //Data of ext teleport
    sf::FloatRect gate_out_bounds = gate_out.getGlobalBounds();
    
    if ((spriteBounds.intersects(gate_in_bounds)) && ((hero_direction == RIGHT) || (hero_direction == DOWN)))
    {
        sprite.setPosition(gate_out.getPosition().x, gate_out.getPosition().y);
    }
    else if ((spriteBounds.intersects(gate_out_bounds)) && ((hero_direction == LEFT) || (hero_direction == UP)))
    {
        sprite.setPosition(gate_in.getPosition().x, gate_in.getPosition().y);
    }
}
//Close in fighting
void Player::close_in_fight(float time)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        switch (hero_direction)
    {
        case LEFT:
        {
            sprite.setTexture(texture_attack);
            current_frame_attack += coeff_attack * time;
            if (current_frame_attack > number_of_attack_image) current_frame_attack -= number_of_attack_image;
            sprite.setTextureRect(sf::IntRect(int(current_frame_attack) * wight_attack, height_attack, wight_attack, height_attack));
            break;
        }
        case RIGHT:
        {
            sprite.setTexture(texture_attack);
            current_frame_attack += coeff_attack * time;
            if (current_frame_attack > number_of_attack_image) current_frame_attack -= number_of_attack_image;
            sprite.setTextureRect(sf::IntRect(int(current_frame_attack) * wight_attack, 2 * height_attack, wight_attack, height_attack));
            break;
        }
        case UP:
        {
            sprite.setTexture(texture_attack);
            current_frame_attack += coeff_attack * time;
            if (current_frame_attack > number_of_attack_image) current_frame_attack -= number_of_attack_image;
            sprite.setTextureRect(sf::IntRect(int(current_frame_attack) * wight_attack, 3 * height_attack, wight_attack, height_attack));
            break;
        }
        case DOWN:
        {
            sprite.setTexture(texture_attack);
            current_frame_attack += coeff_attack * time;
            if (current_frame_attack > number_of_attack_image) current_frame_attack -= number_of_attack_image;
            sprite.setTextureRect(sf::IntRect(int(current_frame_attack) * wight_attack, 0 * height_attack, wight_attack, height_attack));
            break;
        }
    }
}
void Player::make_standart_speed()
{
    if ((abs(phys->get_speed_x()) >= CHAR_SPEED) && (!sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
       if (hero_direction == LEFT)	phys->set_speed_x(-CHAR_SPEED);
	   else if (hero_direction == RIGHT) phys->set_speed_x(CHAR_SPEED);
	if ((abs(phys->get_speed_y()) >= CHAR_SPEED) && (!sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
		if (hero_direction == UP)	phys->set_speed_y(-CHAR_SPEED);
		else if (hero_direction == DOWN) phys->set_speed_y(CHAR_SPEED);
}

// The hero walks only on the map
void Player::map_limit(int width_of_map_, int height_of_map_)
{
    float curr_X = sprite.getPosition().x;
    float curr_Y = sprite.getPosition().y;
    
	if ((curr_X < 0) && (curr_Y < 0 + 64))
	{
		phys->set_X(0);
		phys->set_Y(0 + 64);
	}
	else if (curr_X < 0)
	{
		phys->set_X(0);
		phys->set_Y(curr_Y);
	}
	else if (curr_Y < 0 + 64)
	{
		phys->set_X(curr_X);
		phys->set_Y(0 + 64);
	}
	if ((curr_X > MAP_TILESET_WIDHT * (width_of_map_ - 2)) && (curr_Y > MAP_TILESET_WIDHT * (height_of_map_ - 2 - 2)))
	{
		phys->set_X(MAP_TILESET_WIDHT * (width_of_map_ - 2));
		phys->set_Y(MAP_TILESET_WIDHT * (height_of_map_ - 2 - 2));
	}
	else if (curr_X > MAP_TILESET_WIDHT * (width_of_map_ - 2))
	{
		phys->set_X(MAP_TILESET_WIDHT * (width_of_map_ - 2));
		phys->set_Y(curr_Y);
	}
    else if (curr_Y > MAP_TILESET_WIDHT * (height_of_map_ - 2 - 2))
    
	{
		phys->set_X(curr_X);
		phys->set_Y(MAP_TILESET_WIDHT * (height_of_map_ - 2 - 2));
	}
}
void Player::no_way_communic_rectangle(sf::RectangleShape shape, float time)
{
    //Data of character
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    
    //Data of rectangle
    sf::FloatRect shapeBounds = shape.getGlobalBounds();
    
    if (spriteBounds.intersects(shapeBounds))
    {
        if (hero_direction == LEFT)
            sprite.move(speed*time, 0);
        if (hero_direction == RIGHT)
            sprite.move(-speed * time, 0);
        if (hero_direction == UP)
            sprite.move(0, speed*time);
        if (hero_direction == DOWN)
            sprite.move(0, -speed * time);
    }
}
void Player::no_way_communic_circle(sf::CircleShape shape, float time)
{
    //Data of character
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    //Data of rectangle
    sf::FloatRect shapeBounds = shape.getGlobalBounds();
    
    if (spriteBounds.intersects(shapeBounds))
    {
        if (hero_direction == LEFT)
            sprite.move(speed*time, 0);
        if (hero_direction == RIGHT)
            sprite.move(-speed * time, 0);
        if (hero_direction == UP)
            sprite.move(0, speed*time);
        if (hero_direction == DOWN)
            sprite.move(0, -speed * time);
    }
}
// Move rectangles
sf::RectangleShape Player::move_rectangle_communic(sf::RectangleShape shape, float time)
{
    //Data of character
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    
    //Data of rectangle
    sf::FloatRect shapeBounds = shape.getGlobalBounds();
    
    if (spriteBounds.intersects(shapeBounds))
    {
        if (hero_direction == LEFT)
            shape.move(-speed * time, 0);
        if (hero_direction == RIGHT)
            shape.move(speed * time, 0);
        if (hero_direction == UP)
            shape.move(0, -speed * time);
        if (hero_direction == DOWN)
            shape.move(0, speed * time);
    }
    return shape;
}

void Player::update_graph(float time, GraphObj *graph_obj_array[], map &Map)
{
    make_standart_speed();
    keyboard(time);
    acceleration(time);
    close_in_fight(time);
    map_limit(Map.widthOfMap, Map.heightOfMap);
}
