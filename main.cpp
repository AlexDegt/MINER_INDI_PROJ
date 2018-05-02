#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>
#include "Constants.h"

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

#define OBJ_ARRAY_CAPACITY 3
#define DIMENSION_SCREEN_X 680
#define DIMENSION_SCREEN_Y 480

enum WINDOW
{
	FIRST_WINDOW = 1,
	SECOND_WINDOW
};
enum LAUNCH1
{
	NOTENDOFLAUNCH = 0,
	ENDOFLAUNCH_SECCESS,
	ENDOFLAUNCH_CLOSED,
	ERROR
};


int dimensionScreenX = 680;
int dimensionScreenY = 480;
sf::Vector2f positionScreen(0, 0);

static bool clamped_on_text = false;

//Линейные размеры карты
const int HEIGHT_MAP_1 = 25;
const int WIDHT_MAP_1 = 40;

// ex - пример

//Прототипы
int CreateMainWindow(sf::RenderWindow &window, sf::Texture &texture, sf::Sprite &img_sprite, sf::Font &font, sf::Text &text, sf::Music &music);
int LaunchMainWindow(sf::RenderWindow &window, sf::Text &text, const sf::Event &event);
int CreateRun(sf::Font &font, sf::Text &text);
void view_treatment(float X, float Y, float wight, float height, sf::View &view);
void zoom_treatment(int ZoomValue, sf::View &view);

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
	map(std::string file, int widthOfMap_, int heightOfMap_);
	~map();
};

map::map(std::string file, int widthOfMap_, int heightOfMap_)
{
	mapFile = file;
	widthOfMap = widthOfMap_;
	heightOfMap = heightOfMap_;
}

map::map()
{}

void map::DrawingMap(sf::RenderWindow &window, sf::String *TileMap)
{
	//Если положить это в конструктор, то все ломается
	if (mapImage.loadFromFile(mapFile) == false)
		assert(!"Class map was crashed(loadFormFile mapImage)");
	mapTexture.loadFromImage(mapImage);
	mapSprite.setTexture(mapTexture);

	for (int i = 0; i < heightOfMap; i++)
	{
		for (int j = 0; j < widthOfMap; j++)
		{
			if (TileMap[i][j] == ' ')
			{
				mapSprite.setTextureRect(sf::IntRect(0, 0, MAP_TILESET_WIDHT, MAP_TILESET_WIDHT));
			}
			if (TileMap[i][j] == 's')
			{
				mapSprite.setTextureRect(sf::IntRect(MAP_TILESET_WIDHT, 0, MAP_TILESET_WIDHT, MAP_TILESET_WIDHT));
			}
			if (TileMap[i][j] == '0')
			{
				mapSprite.setTextureRect(sf::IntRect(2 * MAP_TILESET_WIDHT, 0, MAP_TILESET_WIDHT, MAP_TILESET_WIDHT));
			}
			mapSprite.setPosition(j * MAP_TILESET_WIDHT, i * MAP_TILESET_WIDHT);
			window.draw(mapSprite);
		}
	}
	//window.display();
}

map::~map()
{}

//Три приведенных базовых класса не будут иметь одинаковых элементов в отличие от обработчиков уровней
//Обработчики абсолютно идентичны, заисключением того, что в конструкторе присваиваются различные
//начальные значения переменным

class GameLogicObj;
class GameObject;
class PhysicObj;
class GraphObj;
class IncludeFilesObj;

class GraphObj
{
protected:
	double coeff; // CurrentFrame += Coeff * time;
	float current_frame;
	float speed;
	int hero_direction;

	double coeff_attack;
	bool is_fighting;
	bool is_running;
	sf::Color nature_color_sprite_attack;
	sf::Color nature_color_sprite;
	float current_frame_attack;
	int interrapted;
public:
	GraphObj(double coeff_, double coeff_attack_)
	{
		//gr -в конструктор графики, ph -физики, log -логики, in -включаемых файлов,pl -игрока, en -врага, ch -персонажа; 
		speed = 0;//gr
		coeff_attack = coeff_attack_;//gr
		current_frame_attack = 0;//gr

		hero_direction = 3;//gr		
		coeff = coeff_;//gr
		current_frame = 0;//gr
	}
	GraphObj()
	{}

	void update_graph_gen(float time, GameObject * game_obj_array[], map &Map);
	virtual void update_graph_spec(float time, GameObject * game_obj_array[], map &Map);
	void update_graph(float time, GameObject * game_obj_array[], map &Map);
	// Сеттеры и геттеры

	float get_speed()
	{
		return speed;
	}
	void set_speed(float speed_)
	{
		speed = speed_;
	}
	double get_coeff()
	{
		return coeff;
	}
	double get_coeff_attack()
	{
		return coeff_attack;
	}
	int get_hero_direction()
	{
		return hero_direction;
	}
	void set_hero_direction(int hero_direction_)
	{
		hero_direction = hero_direction_;
	}
};

class IncludeFilesObj
{
protected:
	std::string file_name;
	float wight, height;
	int number_of_image;

	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Image image_attack;
	sf::Texture texture_attack;
	sf::Sprite sprite_attack;

	std::string file_name_attack;
	float wight_attack, height_attack;
	int number_of_attack_image;
public:
	IncludeFilesObj(std::string file_name_, std::string file_name_attack_, float wight_, float height_, float wight_attack_, float height_attack_, int number_of_image_, int number_of_attack_image_)
	{
		wight = wight_;
		height = height_;
		wight_attack = wight_attack_;
		height_attack = height_attack_;
		number_of_image = number_of_image_;
		number_of_attack_image = number_of_attack_image_;
		//Uploading a character picture //in
		file_name_attack = file_name_attack_;//in
		file_name = file_name_;//in
							   //in
		if (image_attack.loadFromFile(file_name_attack_) == false)
			assert(!"Class Character is crashed(loadFromFile image_attack)");

		if (texture_attack.loadFromImage(image_attack) == false)
			assert(!"Class Character is crashed(loadFromImage texture_attack)");

		if (image.loadFromFile(file_name_) == false)
			assert(!"Class ObjectStatic is crashed(loadFromFile image)");

		if (texture.loadFromImage(image) == false)
			assert(!"Class ObjectStatic is crashed(loadFromImage texture)");
	}
	IncludeFilesObj()
	{}

	// Сеттеры и геттеры
	float get_wight()
	{
		return wight;
	}
	float get_height()
	{
		return height;
	}
	sf::Sprite get_sprite()
	{
		return sprite;
	}
	int get_number_of_image()
	{
		return number_of_image;
	}
	void set_image(sf::Image image_)
	{
		image = image_;
	}
	void set_texture(sf::Texture texture_)
	{
		texture = texture_;
	}
	void set_sprite(sf::Sprite sprite_)
	{
		sprite = sprite_;
	}

	float get_wight_attack()
	{
		return wight_attack;
	}
	float get_height_attack()
	{
		return height_attack;
	}
	sf::Sprite get_sprite_attack()
	{
		return sprite_attack;
	}
	int get_number_of_attack_image()
	{
		return number_of_attack_image;
	}
	void set_image_attack(sf::Image image_attack_)
	{
		image_attack = image_attack_;
	}
	void set_texture_attack(sf::Texture texture_attack_)
	{
		texture_attack = texture_attack_;
	}
	void set_sprite_attack(sf::Sprite sprite_attack_)
	{
		sprite_attack = sprite_attack_;
	}
};

class PhysicObj
{
protected:
	float X, Y;
public:
	PhysicObj(float X_, float Y_)
	{
		X = X_;//ph
		Y = Y_;//ph
	}
	PhysicObj()
	{}
	//Обновление физики
	//special functions
	virtual void update_phys_spec(float time, GameObject * game_obj_array[], map &Map);
	void update_phys_gen(float time, GameObject * game_obj_array[], map &Map);
	void update_phys(float time, GameObject * game_obj_array[], map &Map);
	// Сеттеры и геттеры
	float get_X()
	{
		//X = sprite.getPosition().x;
		return X;
	}
	float get_Y()
	{
		//Y = sprite.getPosition().y;
		return Y;
	}
	void set_X(float X_)
	{
		X = X_;
	}
	void set_Y(float Y_)
	{
		Y = Y_;
	}
};

class GameLogicObj
{
protected:
	bool life;
	int HP;
public:
	GameLogicObj()
	{
		HP = 100;//log
		life = true;//log
	}

	//special functions
	virtual void update_game_logic_spec(float time, GameObject * game_obj_array[], map &Map);
	//general functions
	void update_game_logic_gen(float time, GameObject * game_obj_array[], map &Map);
	void update_game_logic(float time, GameObject * game_obj_array[], map &Map);
	// Сеттеры и геттеры
	int get_HP()
	{
		//std::cout << HP;
		return HP;
	}
	void set_HP(int HP_)
	{
		HP = HP_;
	}
	bool get_life()
	{
		return life;
	}
	void set_life(bool life_)
	{
		life = life_;
	}
	int is_alive()
	{
		if (HP <= 0)
			return 0;
		else return 1;
	}
};

class GameObject :public IncludeFilesObj, public PhysicObj, public GraphObj, public GameLogicObj
{
public:
	//Здесь ОБЯЗАТЕЛЬНО вызывать апдеты от this, посколкьу если вызывать от PhysicObj и GraphObj,
	//тогда будет вызван тот апдет, который и прописан в этих классах
	GameObject(std::string file_name_, std::string file_name_attack_, float X_, float Y_, float wight_, float height_, float wight_attack_, float height_attack_, int number_of_image_, int number_of_attack_image_, double coeff_, double coeff_attack_) :
		IncludeFilesObj(file_name_, file_name_attack_, wight_, height_, wight_attack_, height_attack_, number_of_image_, number_of_attack_image_),
		GraphObj(coeff_, coeff_attack_),
		PhysicObj(X_, Y_)
	{
		sprite.setPosition(X_, Y_);
		sprite.setTextureRect(sf::IntRect(0, 0, wight_, height_));

		sprite_attack.setPosition(X_, Y_);
		sprite_attack.setTextureRect(sf::IntRect(0, 0, wight_, height_));
	}
	GameObject() :IncludeFilesObj(), PhysicObj(), GraphObj(), GameLogicObj()
	{}

	void update(float time, GameObject *game_obj_array[], map &Map)
	{
		update_phys(time, game_obj_array, Map);
		update_graph(time, game_obj_array, Map);
		update_game_logic(time, game_obj_array, Map);
	}

	//Отрисовать!!!!!!!!!
	//ex
	/*void draw_dinamic_array(sf::RenderWindow &window)
	{
		window.clear();
		for (int i = 0; i < OBJ_ARRAY_CAPACITY; i++)
			window.draw(sprite);
		window.display();
	}*/
};

class Character : public GameObject
{
public:
	//Player::Player(std::string file_name_, std::string file_name_attack_, float X_, float Y_, float wight_, float height_, float wight_attack_, float height_attack_, int number_of_image_, int number_of_attack_image_, double coeff_, double coeff_attack_)
	//FirstEnemy::FirstEnemy(std::string File_name_, std::string File_name_attack_, float X_, float Y_, float wight_, float height_, float wight_attack_, float height_attack_, int NumOfImg_, int NumOfAttackImg_, double Coeff_, double Coeff_attack_)
	Character(std::string file_name_, std::string file_name_attack_, float X_, float Y_, float wight_, float height_, float wight_attack_, float height_attack_, int number_of_image_, int number_of_attack_image_, double coeff_, double coeff_attack_) :
		GameObject(file_name_, file_name_attack_, X_, Y_, wight_, height_, wight_attack_, height_attack_, number_of_image_, number_of_attack_image_, coeff_, coeff_attack_)
	{}
	Character() : GameObject()
	{}
	
	// The hero walks only on the map
	void map_limit(int width_of_map_, int height_of_map_)
	{
		X = sprite.getPosition().x;
		Y = sprite.getPosition().y;
		if ((X < 0) && (Y < 0))
			sprite.setPosition(0, 0);
		else if (X < 0)
			sprite.setPosition(0, Y);
		else if (Y < 0)
			sprite.setPosition(X, 0);

		if ((X > MAP_TILESET_WIDHT * (width_of_map_ - 2)) && (Y > MAP_TILESET_WIDHT * (height_of_map_ - 2)))
			sprite.setPosition(MAP_TILESET_WIDHT * (width_of_map_ - 2), MAP_TILESET_WIDHT * (height_of_map_ - 2));
		else if (X > MAP_TILESET_WIDHT * (width_of_map_ - 2))
			sprite.setPosition(MAP_TILESET_WIDHT * (width_of_map_ - 2), Y);
		else if (Y > MAP_TILESET_WIDHT * (height_of_map_ - 2))
			sprite.setPosition(X, MAP_TILESET_WIDHT * (height_of_map_ - 2));
	}
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
};

class Player : public Character
{
public:
	//Constructor:
	Player(std::string file_name_, std::string file_name_attack_, float X_, float Y_, float wight_, float height_, float wight_attack_, float height_attack_, int number_of_image_, int number_of_attack_image_, double coeff_, double coeff_attack_) :
		Character(file_name_, file_name_attack_, X_, Y_, wight_, height_, wight_attack_, height_attack_, number_of_image_, number_of_attack_image_, coeff_, coeff_attack_)
	{}
	Player() : Character()
	{}
	
	//Keyboard:
	void keyboard(float time)
	{
		sprite.setTexture(texture);
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
	void gold_collect_communic_circle(sf::CircleShape &shape)
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
	}
	// Ability to pass through teleporters
	void teleport_communic(sf::RectangleShape &gate_in, sf::RectangleShape &gate_out)
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
		else
			if ((spriteBounds.intersects(gate_out_bounds)) && ((hero_direction == LEFT) || (hero_direction == UP)))
			{
				sprite.setPosition(gate_in.getPosition().x, gate_in.getPosition().y);
			}
	}
	//Close in fighting
	void close_in_fight(float time)
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
	void make_standart_speed()
	{
		if ((speed) && (!sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
			speed = CHAR_SPEED;
	}

	//Собственно апдейты
	virtual void update_phys_spec(float time, GameObject * game_obj_array[], map &Map) override
	{}

	virtual void update_graph_spec(float time, GameObject * game_obj_array[], map &Map) override
	{
		make_standart_speed();
		keyboard(time);
		acceleration(time);
		close_in_fight(time);
		map_limit(Map.widthOfMap, Map.heightOfMap);
	}

	virtual void update_game_logic_spec(float time, GameObject * game_obj_array[], map &Map) override
	{};
};

class FirstEnemy : public Character
{
public:
	//Constructor:
	FirstEnemy(std::string file_name_, std::string file_name_attack_, float X_, float Y_, float wight_, float height_, float wight_attack_, float height_attack_, int number_of_image_, int number_of_attack_image_, double coeff_, double coeff_attack_) :
		Character(file_name_, file_name_attack_, X_, Y_, wight_, height_, wight_attack_, height_attack_, number_of_image_, number_of_attack_image_, coeff_, coeff_attack_)
	{
		interrapted = 0;// en
	}
	FirstEnemy() : Character()
	{}

	void move_to_aim(float time, float START_X, float START_Y, float FINISH_X, float FINISH_Y)
	{
		if (int(START_X) > int(FINISH_X) + wight - DISTANCE)
		{
			hero_direction = LEFT;
			current_frame += coeff * time;
			if (current_frame > number_of_image) current_frame -= number_of_image;
			sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, height, wight, height));
			sprite.move(-speed * time, 0);
		}
		if (int(START_X) < int(FINISH_X) - wight + DISTANCE)
		{
			hero_direction = RIGHT;
			current_frame += coeff * time;
			if (current_frame > number_of_image) current_frame -= number_of_image;
			sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 2 * height, wight, height));
			sprite.move(speed*time, 0);
			//std::cout << "!!!!!!!!";
		}
		if (int(START_Y) < int(FINISH_Y) - height + DISTANCE)
		{
			hero_direction = DOWN;
			current_frame += coeff * time;
			if (current_frame > number_of_image) current_frame -= number_of_image;
			sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 0 * height, wight, height));
			sprite.move(0, speed*time);
		}
		if (int(START_Y) > int(FINISH_Y) + height - DISTANCE)
		{
			hero_direction = UP;
			current_frame += coeff * time;
			if (current_frame > number_of_image) current_frame -= number_of_image;
			sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 3 * height, wight, height));
			sprite.move(0, -speed * time);
		}
		//if (() && ())
	}
	void behaviour(float time, sf::Sprite player_sprite, map &Map)
	{
		sprite.setTexture(texture);
		X = sprite.getPosition().x;
		Y = sprite.getPosition().y;
		speed = CHAR_SPEED;
		sf::FloatRect sprite_bounds = sprite.getGlobalBounds();
		sf::FloatRect player_sprite_bounds = player_sprite.getGlobalBounds();
		if ((!interrapted) && (!sprite_bounds.intersects(player_sprite_bounds)))
		{
			if ((Y <= MAP_TILESET_WIDHT * (Map.heightOfMap - 2)) && (Y >= 0) && (hero_direction == DOWN))
			{
				hero_direction = DOWN;
				current_frame += coeff * time;
				if (current_frame > number_of_image) current_frame -= number_of_image;
				sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 0 * height, wight, height));
				sprite.move(0, speed * time);
			}
			else if ((Y <= MAP_TILESET_WIDHT * (Map.heightOfMap - 2)) && (Y >= 0) && (hero_direction == UP))
			{
				hero_direction = UP;
				current_frame += coeff * time;
				if (current_frame > number_of_image) current_frame -= number_of_image;
				sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, 3 * height, wight, height));
				sprite.move(0, -speed * time);
			}
			else if (Y > MAP_TILESET_WIDHT * (Map.heightOfMap - 2))
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
	/*void enemy_update(float time, sf::Sprite player_sprite)
	{
	if (!is_fighting)
	{
	printf("%");
	//sprite_attack has nature color, we neew to make it transparent
	sprite_attack.setColor(sf::Color::Transparent);

	//sprite has Transparent color. We need to return the nature color
	sprite.setColor(nature_color_sprite);

	X = sprite.getPosition().x;
	Y = sprite.getPosition().y;
	speed = CHAR_SPEED;
	is_running = IS_RUNNING;
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
	if (sprite_bounds.intersects(player_sprite_bounds))
	{
	printf("#");
	is_fighting = IS_FIGHTING;
	}
	//time = float(timer.getElapsedTime().asSeconds());
	//if (time > 3)
	move_to_aim(time, sprite.getPosition().x, sprite.getPosition().y, player_sprite.getPosition().x, player_sprite.getPosition().y);
	//timer.restart();
	///////////////////////////////////////////////////////
	}
	}
	else
	{
	is_running = !IS_RUNNING;
	printf("$");
	}
	}*/
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
	void close_in_fight_enemy(float time)
	{
		sprite_attack.setTexture(texture_attack);
		//printf("@");
		if (!is_running)
		{
			printf("!");
			is_fighting = IS_FIGHTING;
			//sprite has nature color, we need to make it transparent
			sprite.setColor(sf::Color::Transparent);

			//sprite_attack has Transparent color. We need to return the nature color
			sprite_attack.setColor(nature_color_sprite_attack);

			sprite_attack.setPosition(sprite.getPosition().x, sprite.getPosition().y);
			switch (hero_direction)
			{
			case LEFT:
				current_frame_attack += coeff_attack * time;
				if (current_frame_attack > number_of_attack_image) current_frame_attack -= number_of_attack_image;
				sprite_attack.setTextureRect(sf::IntRect(int(current_frame_attack) * wight_attack, height_attack, wight_attack, height_attack));
				break;
			case RIGHT:
				current_frame_attack += coeff_attack * time;
				if (current_frame_attack > number_of_attack_image) current_frame_attack -= number_of_attack_image;
				sprite_attack.setTextureRect(sf::IntRect(int(current_frame_attack) * wight_attack, 2 * height_attack, wight_attack, height_attack));
				break;
			case UP:
				current_frame_attack += coeff_attack * time;
				if (current_frame_attack > number_of_attack_image) current_frame_attack -= number_of_attack_image;
				sprite_attack.setTextureRect(sf::IntRect(int(current_frame_attack) * wight_attack, 3 * height_attack, wight_attack, height_attack));
				break;
			case DOWN:
				current_frame_attack += coeff_attack * time;
				if (current_frame_attack > number_of_attack_image) current_frame_attack -= number_of_attack_image;
				sprite_attack.setTextureRect(sf::IntRect(int(current_frame_attack) * wight_attack, 0 * height_attack, wight_attack, height_attack));
				break;
			}
		}
		else
		{
			is_fighting = !IS_FIGHTING;
			sprite_attack.setColor(sf::Color::Transparent);
		}
	}
	// Calling private functions
	void fight_if_close(float time, sf::Sprite player_sprite)
	{
		//Data of player character
		sf::FloatRect player_sprite_bounds = player_sprite.getGlobalBounds();
		//Data of enemy character
		sf::FloatRect enemy_sprite_bounds = sprite.getGlobalBounds();
		if (player_sprite_bounds.intersects(enemy_sprite_bounds))
			close_in_fight_enemy(time);
	}

	//Собственно апдейты
	virtual void update_phys_spec(float time, GameObject * game_obj_array[], map &Map) override
	{}

	virtual void update_graph_spec(float time, GameObject * game_obj_array[], map &Map) override
	{
		behaviour(time, game_obj_array[0]->get_sprite(), Map);
		fight_if_close(time, game_obj_array[0]->get_sprite());
	}

	virtual void update_game_logic_spec(float time, GameObject * game_obj_array[], map &Map) override
	{};

};

class ManagerUpdateGameObj
{
public:
	GameObject * game_obj_array[OBJ_ARRAY_CAPACITY] = {};
	map Map;
	ManagerUpdateGameObj(GameObject *game_obj_array_[], map &Map_)
	{
		for (int i = 0; i < OBJ_ARRAY_CAPACITY; i++)
		{
			game_obj_array[i] = game_obj_array_[i];
		}
		Map = Map_;
	}
	//ex
	void run_update(float time, sf::Clock &clock, sf::View &view)
	{
		time = float(clock.getElapsedTime().asMicroseconds());
		clock.restart();
		time = time / 16000;
		for (int i = 0; i < OBJ_ARRAY_CAPACITY; i++)
		{
			game_obj_array[i]->update(time, game_obj_array, Map);
		}
		zoom_treatment(ZOOM_VALUE, view);
		view_treatment(game_obj_array[0]->get_sprite().getPosition().x, game_obj_array[0]->get_sprite().getPosition().y,
			game_obj_array[0]->get_wight(), game_obj_array[0]->get_height(), view);
	}
	void draw_all(sf::RenderWindow &window)
	{
		for (int i = 0; i < OBJ_ARRAY_CAPACITY; i++)
		{
			window.draw(game_obj_array[i]->get_sprite());
		}
	}
};

class ManagerEventLoop
{
public:
	sf::Event event; //ex
	//ex
	int main_loop(GameObject *mass_[], sf::String *map1_string_, map &Map)
	{
		ManagerUpdateGameObj manager_update(mass_, Map);
		//printf("%s\n", Map.mapFile.getData() + 3);
		sf::RenderWindow window(sf::VideoMode(DIMENSION_SCREEN_X, DIMENSION_SCREEN_Y), "MINER_INDI"/*,Style::Fullscreen*/);

		sf::View view(sf::FloatRect(0, 0, DIMENSION_SCREEN_X, DIMENSION_SCREEN_Y));
		sf::Clock clock;
		float time = float(clock.getElapsedTime().asMicroseconds());

		//Вывод картинки и текста в первое окно
		sf::Texture texture;
		sf::Sprite img_sprite;
		sf::Font font;
		sf::Text text;
		sf::Music music;

		//Player Player1("gorilla.png", "gorilla_fight.png", 50, 50, 80, 80, 80, 80, 4, 4, COEFF_SPEED, COEFF_ATTACK_SPEED);
		//FirstEnemy Snake1("snake.png", "snake.png", 400, 50, 64, 64, 64, 64, 4, 0, COEFF_SPEED, COEFF_ATTACK_SPEED);
		//FirstEnemy Gorilla1("image.png", "image.png", 600, 50, 80, 78, 80, 78, 3, 3, COEFF_SPEED, COEFF_ATTACK_SPEED);

		sf::Image image_map;
		sf::Texture texture_map;
		sf::Sprite sprite_map;

		//Для того, чтобы один ращ вызвать функцию CreateRun()
		int current = 0;
		//sf::Clock clock;

		if (CreateMainWindow(window, texture, img_sprite, font, text, music) == EXIT_FAILURE)
		{
			assert(!"CreateMainWindow crashed(exit)");
			return EXIT_FAILURE;
		}
		int window_is = FIRST_WINDOW;

		music.play();
		while (window.isOpen())
		{

			sf::Event event;
			while (window.pollEvent(event))
			{
				// Close window: exit
				if (event.type == sf::Event::Closed)
				{
					window.close();
					return EXIT_SUCCESS;
				}
				if (window_is == FIRST_WINDOW)
				{
					if (ENDOFLAUNCH_SECCESS == LaunchMainWindow(window, text, event))
						window_is++;
				}
				else if (window_is == SECOND_WINDOW)
				{
					if (current == 0)
					{
						CreateRun(font, text);
						current++;
					}
				}
			}

			if (window_is == FIRST_WINDOW)
			{
				window.clear();
				window.draw(img_sprite);
				window.draw(text);
				window.display();
			}
			if (window_is == SECOND_WINDOW)
			{
				music.stop();
				window.clear();

				Map.DrawingMap(window, map1_string_);
				manager_update.run_update(time, clock, view);
				manager_update.draw_all(window);
				window.setView(view);

				//Draw the text
				text.setPosition(view.getCenter().x + 40, view.getCenter().y - 200);
				window.draw(text);
				window.display();
			}
		}
	}
};

//Лучше сделать один базовый класс(а не так что есть ObjectStatic и ObjectDinamic).
//В противном случае придется писать обработчики начала уровня отедльно для каждого,
//потому что они содеожать одинаковые элементы, а если обработчик наследуется сразу от обоих,
//то возникает ошибка компиляции. Не понятно с каким конкретно элементов мы работаем.

//Общее правило: Класс игрока будем класть в первую ячейку массива объектов
class ManagerLevel1Configuration : public GameObject
{
public:
	GameObject * game_obj_array[OBJ_ARRAY_CAPACITY];
	sf::String TileMap[HEIGHT_MAP_1] =
	{ "0000000000000000000000000000000000000000",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0             sssss                    0",
		"0         ssss    ssss                 0",
		"0      sss            sss              0",
		"0     ss    sss  sss     ss            0",
		"0    s       s    s        s           0",
		"0     ss        s       ss             0",
		"0      sss   s    s   sss              0",
		"0        sss  ssss   sss               0",
		"0           sss    ss                  0",
		"0              ssss                    0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0                                      0",
		"0000000000000000000000000000000000000000",
	};
	map Map;
	Player player;
	FirstEnemy snake;
	FirstEnemy gorilla;
	ManagerLevel1Configuration()
	{
		snake = FirstEnemy("snake.png", "snake.png", 400, 50, 64, 64, 64, 64, 4, 0, COEFF_SPEED, COEFF_ATTACK_SPEED);
		gorilla = FirstEnemy("image.png", "image.png", 600, 50, 80, 78, 80, 78, 3, 3, COEFF_SPEED, COEFF_ATTACK_SPEED);
		player = Player("gorilla.png", "gorilla_fight.png", 50, 50, 80, 80, 80, 80, 4, 4, COEFF_SPEED, COEFF_ATTACK_SPEED);
		Map = map("map.png", WIDHT_MAP_1, HEIGHT_MAP_1);
		game_obj_array[0] = &player;
		game_obj_array[1] = &snake;
		game_obj_array[2] = &gorilla;
	}
	//Функция, возвращающая массив объектов на данном уровне
	GameObject **get_game_obj_array()
	{
		return game_obj_array;
	}
	sf::String *get_tile_map_string()
	{
		return TileMap;
	}
	map get_map()
	{
		return Map;
	}
};


// To return the screen resolution to its original state, the "0"
// For the acceleration of the player's character, the button "A"
// For the player's character attack, the "X"f

//ph - физика, gr - графика, log - игр. логика, inc - включаемые файлы

//create a scroll screen

int main()
	{
		GameObject **mass;
		sf::String *map1_string;
		map Map;
		ManagerLevel1Configuration manager_level1;
		mass = manager_level1.get_game_obj_array();
		map1_string = manager_level1.get_tile_map_string();
		Map = manager_level1.get_map();
		ManagerEventLoop manager_event;
		manager_event.main_loop(mass, map1_string, Map);
		//getchar();
		return 0;
	}
/////////////////////////Working with the screnn////////////////////////////

int CreateMainWindow(sf::RenderWindow &window, sf::Texture &texture, sf::Sprite &img_sprite, sf::Font &font, sf::Text &text, sf::Music &music)
	{
		// Set the Icon
		sf::Image icon;
		if (icon.loadFromFile("icon.png") == false)
		{
			assert(!"CreateMainWindow is crashed(loadFromFile icon)");
			return EXIT_FAILURE;
		}

		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

		// Load a sprite to display
		if (texture.loadFromFile("cute_image.jpg") == false)
		{
			assert(!"CreateMainWindow is crashed(loadFromFile texture)");
			return EXIT_FAILURE;
		}

		img_sprite.setTexture(texture);

		// Create a graphical text to display
		if (!font.loadFromFile("sansation.ttf"))
		{
			assert(!"CreateMainWindow is crashed(loadFromFile font)");
			return EXIT_FAILURE;
		}

		text.setFont(font);
		text.setString("Click to play");
		text.setCharacterSize(50);
		text.setFillColor(sf::Color::White);
		text.setPosition(DIMENSION_SCREEN_X / 2 - 70, DIMENSION_SCREEN_Y / 2 - 20);

		// Load a music to play
		if (!music.openFromFile("nice_music.ogg"))
		{
			assert(!"CreateMainWindow is crashed(loadFromFile music)");
			return EXIT_FAILURE;
		}

		return EXIT_SUCCESS;
	}

int LaunchMainWindow(sf::RenderWindow &window, sf::Text &text, const sf::Event &event)
	{
		// Update mouse coordinates
		sf::Vector2i PixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f GamePos = window.mapPixelToCoords(PixelPos);

		if (event.type == sf::Event::MouseButtonPressed)
		{
			std::cout << "isClicked1!/n";
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (text.getGlobalBounds().contains(GamePos.x, GamePos.y))
				{
					std::cout << "isClicked1!/n";
					clamped_on_text = true;
					text.setCharacterSize(46);
					text.setFillColor(sf::Color::Green);
					text.move(2, 2);
				}
			}
		}
		else if (event.type == sf::Event::MouseButtonReleased)
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (text.getGlobalBounds().contains(GamePos.x, GamePos.y) || clamped_on_text)
				{
					text.setCharacterSize(50);
					text.setFillColor(sf::Color::White);
					text.move(-2, -2);
					clamped_on_text = false;
					if (text.getGlobalBounds().contains(GamePos.x, GamePos.y))
						return ENDOFLAUNCH_SECCESS;
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

int CreateRun(sf::Font &font, sf::Text &text)
	{
		//Creating a font
		if (font.loadFromFile("sansation.ttf") == false)
		{
			assert(!"CreateRun is crashed(loadFromFile Font)");
			return EXIT_FAILURE;
		}

		text.setFont(font);
		text.setCharacterSize(18);
		text.setColor(sf::Color::Red);
		text.setOutlineThickness(4);
		text.setOutlineColor(sf::Color::Black);
		text.setStyle(sf::Text::Bold);

		return EXIT_SUCCESS;
	}

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

//Определния апдейтов:

//Для физики:
void PhysicObj::update_phys_spec(float time, GameObject * game_obj_array[], map &Map)
{}
void PhysicObj::update_phys_gen(float time, GameObject * game_obj_array[], map &Map)
{
	//test:
	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		sf::Sprite sprite_temp;
		sprite_temp = game_obj_array[0]->get_sprite();
		sprite_temp.move(-game_obj_array[0]->get_speed() * time, 0);
		game_obj_array[0]->set_sprite(sprite_temp);
	}*/
}
void PhysicObj::update_phys(float time, GameObject * game_obj_array[], map &Map)
{
	update_phys_gen(time, game_obj_array, Map);
	update_phys_spec(time, game_obj_array, Map);
}

//Для графики:
void GraphObj::update_graph_gen(float time, GameObject * game_obj_array[], map &Map)
{}
void GraphObj::update_graph_spec(float time, GameObject * game_obj_array[], map &Map)
{}
void GraphObj::update_graph(float time, GameObject * game_obj_array[], map &Map)
{
	update_graph_gen(time, game_obj_array, Map);
	update_graph_spec(time, game_obj_array, Map);
}

//Для игровой логики:
void GameLogicObj::update_game_logic_spec(float time, GameObject * game_obj_array[], map &Map)
{}
void GameLogicObj::update_game_logic_gen(float time, GameObject * game_obj_array[], map &Map)
{}
void GameLogicObj::update_game_logic(float time, GameObject * game_obj_array[], map &Map)
{
	update_game_logic_gen(time, game_obj_array, Map);
	update_game_logic_spec(time, game_obj_array, Map);
}