#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include "Map.h"
#include "Constants.h"


// To return the screen resolution to its original state, the "0"
// For the acceleration of the player's character, the button "A"
// For the player's character attack, the "X"

int dimensionScreenX = 640;
int dimensionScreenY = 480;
sf::Vector2f positionScreen(0, 0);



//create a scroll screen
sf::View view(sf::FloatRect(0, 0, dimensionScreenX, dimensionScreenY));
//Creating a class object "CircleShape"
sf::CircleShape shape(20, 70);
sf::CircleShape gold1(10, 50);
sf::CircleShape gold2(10, 50);
//Creating a class objectа "RenderWindow"
sf::RenderWindow window;
//Creating a class object "RectangleShape"
sf::RectangleShape rectangle(sf::Vector2f(150, 40));
//teleports
sf::RectangleShape gate_in(sf::Vector2f(3, 100));
sf::RectangleShape gate_out(sf::Vector2f(3, 100));

//Used functions
sf::View VIEW_TREATMENT(float X, float Y, float wight, float height, sf::View view);
sf::View ZOOM_TREATMENT(int ZoomValue);

class ObjectStatic
{
protected:
	float X, Y, wight, height;
	double coeff; // CurrentFrame += Coeff * time;
	int number_of_image;
	std::string file_name;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	bool life;
	float current_frame;
public:

	//Constructor:
	ObjectStatic(std::string file_name_, float X_, float Y_, float wight_, float height_, int number_of_image_, double coeff_)
	{
		file_name = file_name_;
		X = X_;
		Y = Y_;
		wight = wight_;
		height = height_;
		coeff = coeff_;
		number_of_image = number_of_image_;
		current_frame = 0;
		life = true;
		//Uploading a character picture
		image.loadFromFile(file_name_);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setPosition(X_, Y_);
		sprite.setTextureRect(sf::IntRect(0, 0, wight_, height_));
	}
	//Receiving and setting coordinates
	float get_coord_X()
	{
		//X = sprite.getPosition().x;
		return X;
	}
	float get_coord_Y()
	{
		//Y = sprite.getPosition().y;
		return Y;
	}
	void put_coord_X(float X_)
	{
		X = X_;
	}
	void put_coord_Y(float Y_)
	{
		Y = Y_;
	}
	// Get the hero's linear sizes
	float get_wight()
	{
		return wight;
	}
	float get_height()
	{
		return height;
	}
	// Getting the character's sprite
	sf::Sprite get_sprite()
	{
		return sprite;
	}
};

class ObjectDinamic : public ObjectStatic
{
protected:
	float speed;
	int hero_direction;
	int HP;
public:
	//Constructor:
	ObjectDinamic(std::string file_name_, float X_, float Y_, float wight_, float height_, int number_of_image_, double coeff_) :ObjectStatic(file_name_, X_, Y_, wight_, height_, number_of_image_, coeff_)
	{
		speed = 0;
		hero_direction = 3;
		HP = 100;
	}
	// Shows the amount of HP
	int get_HP()
	{
		//std::cout << HP;
		return HP;
	}
	void set_HP(int HP_)
	{
		HP = HP_;
	}
	// Is the character alive?
	int is_alive()
	{
		if (HP <= 0)
			return 0;
		else return 1;
	}
	// Get the speed
	float get_speed()
	{
		return speed;
	}
	// The hero walks only on the map
	void map_limit()
	{
		X = sprite.getPosition().x;
		Y = sprite.getPosition().y;
		if ((X < 0) && (Y < 0))
			sprite.setPosition(0, 0);
		else if (X < 0)
			sprite.setPosition(0, Y);
		else if (Y < 0)
			sprite.setPosition(X, 0);

		if ((X > MAP_TILESET_WIDHT * (WIDHT_MAP - 2)) && (Y > MAP_TILESET_WIDHT * (HEIGHT_MAP - 2)))
			sprite.setPosition(MAP_TILESET_WIDHT * (WIDHT_MAP - 2), MAP_TILESET_WIDHT * (HEIGHT_MAP - 2));
		else if (X > MAP_TILESET_WIDHT * (WIDHT_MAP - 2))
			sprite.setPosition(MAP_TILESET_WIDHT * (WIDHT_MAP - 2), Y);
		else if (Y > MAP_TILESET_WIDHT * (HEIGHT_MAP - 2))
			sprite.setPosition(X, MAP_TILESET_WIDHT * (HEIGHT_MAP - 2));
	}
};

class Character : public ObjectDinamic
{
protected:
	float wight_attack, height_attack;
	double coeff_attack;
	int number_of_attack_image;
	std::string file_name_attack;
	sf::Image image_attack;
	sf::Texture texture_attack;
	sf::Sprite sprite_attack;

	float current_frame_attack;
public:
	//Constructor:
	Character(std::string file_name_, std::string file_name_attack_, float X_, float Y_, float wight_, float height_, float wight_attack_, float height_attack_, int number_of_image_, int number_of_attack_image_, double coeff_, double coeff_attack_) : ObjectDinamic(file_name_, X_, Y_, wight_, height_, number_of_image_, coeff_)
	{
		file_name_attack = file_name_attack_;
		wight_attack = wight_attack_;
		height_attack = height_attack_;
		coeff_attack = coeff_attack_;
		number_of_attack_image = number_of_attack_image_;
		current_frame_attack = 0;
		//Загрузка картинки дерущегося персонажа
		image_attack.loadFromFile(file_name_attack_);
		texture_attack.loadFromImage(image_attack);
		sprite_attack.setTexture(texture_attack);
		sprite_attack.setPosition(X_, Y_);
		sprite_attack.setTextureRect(sf::IntRect(0, 0, wight_attack_, height_attack_));
	}
	// Interactions
	// Neutrality through circles and rectangles
	void no_way_communic_rectangle(sf::RectangleShape shape, float time)
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
	void no_way_communic_circle(sf::CircleShape shape, float time)
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
	sf::RectangleShape move_rectangle_communic(sf::RectangleShape shape, float time)
	{
		//CharSpeed = CHAR_SPEED;	
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
	sf::Sprite get_attack_sprite()
	{
		return sprite_attack;
	}
};

class Player : public Character
{
private:

	//Keyboard:
	void update(float time)
	{
		if (speed == 0)
			speed = CHAR_SPEED;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			hero_direction = LEFT;
			current_frame += coeff * time;
			if (current_frame > number_of_image) current_frame -= number_of_image;
			sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, height, wight, height));
			sprite.move(-speed * time, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			hero_direction = RIGHT;
			current_frame += coeff * time;
			if (current_frame > number_of_image) current_frame -= number_of_image;
			sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 2 * height, wight, height));
			sprite.move(speed * time, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			hero_direction = DOWN;
			current_frame += coeff * time;
			if (current_frame > number_of_image) current_frame -= number_of_image;
			sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 0 * height, wight, height));
			sprite.move(0, speed * time);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			hero_direction = UP;
			current_frame += coeff * time;
			if (current_frame > number_of_image) current_frame -= number_of_image;
			sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 3 * height, wight, height));
			sprite.move(0, -speed * time);
		}
	}
	//Acceleration
	void acceleration(float time)
	{
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && (speed <= CHAR_SPEED))
			speed = 2 * speed;
	}
	// Collection of gold
	sf::CircleShape gold_collect_communic_circle(sf::CircleShape shape)
	{
		//Data of character
		sf::FloatRect spriteBounds = sprite.getGlobalBounds();
		//Data of a coin
		sf::FloatRect shapeBounds = shape.getGlobalBounds();

		if (spriteBounds.intersects(shapeBounds))
		{
			////////////Test
			if (shape.getFillColor() == sf::Color::Red)
				HP -= 50;
			////////////////
			shape.setFillColor(sf::Color::Transparent);
		}
		return shape;
	}
	// Ability to pass through teleporters
	void teleport_communic(sf::RectangleShape gate_in, sf::RectangleShape gate_out)
	{
		//Data of character
		sf::FloatRect spriteBounds = sprite.getGlobalBounds();
		//Data of entry teleport
		sf::FloatRect gate_in_bounds = gate_in.getGlobalBounds();
		//Data of ext teleport
		sf::FloatRect gate_out_bounds = gate_out.getGlobalBounds();

		if ((spriteBounds.intersects(gate_in_bounds)) && (hero_direction == RIGHT))
		{
			sprite.setPosition(gate_out.getPosition().x, gate_out.getPosition().y);
		}

		if ((spriteBounds.intersects(gate_out_bounds)) && (hero_direction == LEFT))
		{
			sprite.setPosition(gate_in.getPosition().x, gate_in.getPosition().y);
		}
	}
public:
	//Constructor:
	Player(std::string file_name_, std::string file_name_attack_, float X_, float Y_, float wight_, float height_, float wight_attack_, float height_attack_, int number_of_image_, int number_of_attack_image_, double coeff_, double coeff_attack_) : Character(file_name_, file_name_attack_, X_, Y_, wight_, height_, wight_attack_, height_attack_, number_of_image_, number_of_attack_image_, coeff_, coeff_attack_)
	{}
	//Close in fighting
	void close_in_fight(float time)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			sprite_attack.setPosition(sprite.getPosition().x, sprite.getPosition().y);
			switch (hero_direction)
			{
			case LEFT:
				current_frame_attack += coeff_attack * time;
				if (current_frame_attack > number_of_attack_image) current_frame_attack -= number_of_attack_image;
				sprite_attack.setTextureRect(sf::IntRect(int(current_frame_attack) * wight_attack, height_attack, wight_attack, height_attack));
			case RIGHT:
				current_frame_attack += coeff_attack * time;
				if (current_frame_attack > number_of_attack_image) current_frame_attack -= number_of_attack_image;
				sprite_attack.setTextureRect(sf::IntRect(int(current_frame_attack) * wight_attack, 2 * height_attack, wight_attack, height_attack));
			case UP:
				current_frame_attack += coeff_attack * time;
				if (current_frame_attack > number_of_attack_image) current_frame_attack -= number_of_attack_image;
				sprite_attack.setTextureRect(sf::IntRect(int(current_frame_attack) * wight_attack, 3 * height_attack, wight_attack, height_attack));
			case DOWN:
				current_frame_attack += coeff_attack * time;
				if (current_frame_attack > number_of_attack_image) current_frame_attack -= number_of_attack_image;
				sprite_attack.setTextureRect(sf::IntRect(int(current_frame_attack) * wight_attack, 0 * height_attack, wight_attack, height_attack));
			}
		}
		//else
		//{
		//sprite_attack.setColor(sf::Color::Transparent);
		//}
	}
	//Using private and protected functions and variables
	void get_update(float time)
	{
		update(time);
	}
	void get_acceleration(float time)
	{
		acceleration(time);
	}
	sf::CircleShape get_private_gold_collect_communic_circle(sf::CircleShape shape)
	{
		return gold_collect_communic_circle(shape);
	}
	void get_private_teleport_communic(sf::RectangleShape gate_in, sf::RectangleShape gate_out)
	{
		teleport_communic(gate_in, gate_out);
	}
	void make_standart_speed()
	{
		if ((speed) && (!sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
			speed = CHAR_SPEED;
	}
};

class FirstEnemy : public Character
{
protected:
	//If the character is flaunted from a fascinating hike back and forth
	int interrapted;
	// Character movement function at the given start and end points
	void move_to_aim(float time, float START_X, float START_Y, float FINISH_X, float FINISH_Y)
	{
		if (int(START_X) > int(FINISH_X) + wight - DISATANCE)
		{
			hero_direction = LEFT;
			current_frame += coeff * time;
			if (current_frame > number_of_image) current_frame -= number_of_image;
			sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, height, wight, height));
			sprite.move(-speed * time, 0);
		}
		if (int(START_X) < int(FINISH_X) - wight + DISATANCE)
		{
			hero_direction = RIGHT;
			current_frame += coeff * time;
			if (current_frame > number_of_image) current_frame -= number_of_image;
			sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 2 * height, wight, height));
			sprite.move(speed*time, 0);
			//std::cout << "!!!!!!!!";
		}
		if (int(START_Y) < int(FINISH_Y) - height + DISATANCE)
		{
			hero_direction = DOWN;
			current_frame += coeff * time;
			if (current_frame > number_of_image) current_frame -= number_of_image;
			sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 0 * height, wight, height));
			sprite.move(0, speed*time);
		}
		if (int(START_Y) > int(FINISH_Y) + height - DISATANCE)
		{
			hero_direction = UP;
			current_frame += coeff * time;
			if (current_frame > number_of_image) current_frame -= number_of_image;
			sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 3 * height, wight, height));
			sprite.move(0, -speed * time);
		}
	}
private:
	void enemy_update(float time, sf::Sprite player_sprite)
	{
		X = sprite.getPosition().x;
		Y = sprite.getPosition().y;
		speed = CHAR_SPEED;
		sf::FloatRect sprite_bounds = sprite.getGlobalBounds();
		sf::FloatRect player_sprite_bounds = player_sprite.getGlobalBounds();
		if ((!interrapted) && (!sprite_bounds.intersects(player_sprite_bounds)))
		{
			if ((Y <= MAP_TILESET_WIDHT * (HEIGHT_MAP - 2)) && (Y >= 0) && (hero_direction == DOWN))
			{
				hero_direction = DOWN;
				current_frame += coeff * time;
				if (current_frame > number_of_image) current_frame -= number_of_image;
				sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 0 * height, wight, height));
				sprite.move(0, speed * time);
			}
			else if ((Y <= MAP_TILESET_WIDHT * (HEIGHT_MAP - 2)) && (Y >= 0) && (hero_direction == UP))
			{
				hero_direction = UP;
				current_frame += coeff * time;
				if (current_frame > number_of_image) current_frame -= number_of_image;
				sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 3 * height, wight, height));
				sprite.move(0, -speed * time);
			}
			else if (Y > MAP_TILESET_WIDHT * (HEIGHT_MAP - 2))
			{
				hero_direction = UP;
				current_frame += coeff * time;
				if (current_frame > number_of_image) current_frame -= number_of_image;
				sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 3 * height, wight, height));
				sprite.move(0, -2 * speed * time);
			}
			else if (Y < 0)
			{
				hero_direction = DOWN;
				current_frame += coeff * time;
				if (current_frame > number_of_image) current_frame -= number_of_image;
				sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 0 * height, wight, height));
				sprite.move(0, 2 * speed * time);
			}

		}
		else
		{
			if ((sprite_bounds.intersects(player_sprite_bounds)) && (!interrapted))
				interrapted = 1;
			//time = float(timer.getElapsedTime().asSeconds());
			//if (time > 3)
			move_to_aim(time, sprite.getPosition().x, sprite.getPosition().y, player_sprite.getPosition().x, player_sprite.getPosition().y);
			//timer.restart();
			///////////////////////////////////////////////////////
		}

	}
public:
	//Constructor:
	FirstEnemy(std::string File_name_, std::string File_name_attack_, float X_, float Y_, float wight_, float height_, float wight_attack_, float height_attack_, int NumOfImg_, int NumOfAttackImg_, double Coeff_, double Coeff_attack_) : Character(File_name_, File_name_attack_, X_, Y_, wight_, height_, wight_attack_, height_attack_, NumOfImg_, NumOfAttackImg_, Coeff_, Coeff_attack_)
	{
		interrapted = 0;
	}
	// Calling private functions
	void get_enemy_update(float time, sf::Sprite player_sprite)
	{
		enemy_update(time, player_sprite);
	}
};

int main()
{
	//Character Creation
	Player Player1("gorilla.png", "gorilla_fight.png", 50, 50, 80, 80, 80, 80, 4, 4, COEFF_SPEED, COEFF_ATTACK_SPEED);
	FirstEnemy Snake1("snake.png", "snake.png", 400, 50, 64, 64, 64, 64, 4, 0, COEFF_SPEED, COEFF_ATTACK_SPEED);
	FirstEnemy Gorilla1("image.png", "image.png", 600, 50, 80, 78, 80, 78, 3, 3, COEFF_SPEED, COEFF_ATTACK_SPEED);

	//Creating a font
	sf::Font font;
	if (!font.loadFromFile("zelda.ttf"))
		std::cout << "Mistake";
	sf::Text text;

	text.setFont(font);
	text.setCharacterSize(18);
	text.setColor(sf::Color::Red);
	text.setOutlineThickness(4);
	text.setOutlineColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold/* | sf::Text::Underlined*/);


	//Drawing a map
	std::string File_name_map = "image_map.png";
	sf::Image image_map;
	sf::Texture texture_map;
	sf::Sprite sprite_map;
	image_map.loadFromFile(File_name_map);
	texture_map.loadFromImage(image_map);
	sprite_map.setTexture(texture_map);

	//Description of the figure(circle)
	shape.rotate(45);
	shape.setPosition(520, 80);
	shape.setOutlineThickness(10);
	shape.setOutlineColor(sf::Color::Black);
	shape.setFillColor(sf::Color::Magenta);

	gold1.setPosition(300, 240);
	gold1.setOutlineThickness(3);
	gold1.setOutlineColor(sf::Color::Black);
	gold1.setFillColor(sf::Color::Red);

	gold2.setPosition(400, 240);
	gold2.setOutlineThickness(3);
	gold2.setOutlineColor(sf::Color::Black);
	gold2.setFillColor(sf::Color::Red);

	//Description of the rectangle
	//rectangle.rotate(45);
	rectangle.setPosition(120, 300);
	rectangle.setOutlineThickness(10);
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setFillColor(sf::Color::Blue);

	////////////////////Teleport///////////////////////
	gate_in.setPosition(100, 10);
	gate_in.setOutlineThickness(2);
	gate_in.setOutlineColor(sf::Color::Black);
	gate_in.setFillColor(sf::Color::Red);

	gate_out.setPosition(530, 370);
	gate_out.setOutlineThickness(2);
	gate_out.setOutlineColor(sf::Color::Black);
	gate_out.setFillColor(sf::Color::Red);
	///////////////////////////////////////////////////

	//Creating a Window 640 х 480
	window.create(sf::VideoMode(640, 480), "Screen");
	//Number of frames per second
	window.setFramerateLimit(60);

	//Create a timer for real - time synchronization
	sf::Clock clock;

	while (window.isOpen())
	{
		//Installing HP
		std::ostringstream playerHPstring;
		playerHPstring << Player1.get_HP();
		text.setString("HP number:" + playerHPstring.str());

		float time = float(clock.getElapsedTime().asMicroseconds());
		//Updating the timer
		clock.restart();
		time = time / 16000;

		//Create and wait for an event
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		//In case the acceleration button is not pressed, the speed returns to the CHAR_SPEED state
		Player1.make_standart_speed();
		Player1.get_acceleration(time);

		Player1.get_update(time);
		Snake1.get_enemy_update(time, Player1.get_sprite());
		Gorilla1.get_enemy_update(time, Player1.get_sprite());

		Player1.close_in_fight(time);

		view = ZOOM_TREATMENT(ZOOM_VALUE);
		Player1.map_limit();
		Player1.get_private_teleport_communic(gate_in, gate_out);

		Player1.no_way_communic_circle(shape, time);
		Snake1.no_way_communic_circle(shape, time);
		Gorilla1.no_way_communic_circle(shape, time);

		rectangle = Player1.move_rectangle_communic(rectangle, time);
		rectangle = Snake1.move_rectangle_communic(rectangle, time);
		rectangle = Gorilla1.move_rectangle_communic(rectangle, time);

		gold1 = Player1.get_private_gold_collect_communic_circle(gold1);
		gold2 = Player1.get_private_gold_collect_communic_circle(gold2);

		view = VIEW_TREATMENT(Player1.get_coord_X(), Player1.get_coord_Y(), Player1.get_wight(), Player1.get_height(), view);

		window.clear(sf::Color::Yellow);

		//Drawing cycle of the map
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDHT_MAP; j++)
			{
				if (TileMap[i][j] == ' ')
				{
					sprite_map.setTextureRect(sf::IntRect(0, 0, MAP_TILESET_WIDHT, MAP_TILESET_WIDHT));
				}
				if (TileMap[i][j] == 's')
				{
					sprite_map.setTextureRect(sf::IntRect(MAP_TILESET_WIDHT, 0, MAP_TILESET_WIDHT, MAP_TILESET_WIDHT));
				}
				if (TileMap[i][j] == '0') sprite_map.setTextureRect(sf::IntRect(2 * MAP_TILESET_WIDHT, 0, MAP_TILESET_WIDHT, MAP_TILESET_WIDHT));


				sprite_map.setPosition(j * MAP_TILESET_WIDHT, i * MAP_TILESET_WIDHT);
				window.draw(sprite_map);
			}

		window.setView(view);
		window.draw(gate_in);
		window.draw(gate_out);
		window.draw(gold1);
		window.draw(gold2);
		window.draw(shape);
		window.draw(Snake1.get_sprite());
		window.draw(Gorilla1.get_sprite());
		window.draw(Player1.get_sprite());
		window.draw(Player1.get_attack_sprite());
		window.draw(rectangle);

		//Draw the text
		text.setPosition(view.getCenter().x + 40, view.getCenter().y - 200);
		window.draw(text);

		window.display();
	}

	return 0;
}
/////////////////////////Working with the screnn////////////////////////////
sf::View VIEW_TREATMENT(float X, float Y, float wight, float height, sf::View view)
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
	return view;
}

sf::View ZOOM_TREATMENT(int ZoomValue)
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
	return view;
}