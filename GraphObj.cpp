#include "GraphObj.hpp"

GraphObj::GraphObj(std::string file_name_, std::string file_name_attack_, float X_, float Y_, float wight_, float height_, float wight_attack_, float height_attack_, int number_of_image_, int number_of_attack_image_, double coeff_, double coeff_attack_)
{
    phys = new PhysicObj();
	phys->set_HP(100);
    phys->set_wight(wight_);
    phys->set_height(height_);

	//printf("wight_ = %lf\n", wight_);
	//printf("height_ = %lf\n", height_);
	//printf("wight = %lf\n", phys->get_wight());
	//printf("height = %lf\n", phys->get_height());

	if (wight_ > height_) phys->set_hit_radius(height_/4);
	else phys->set_hit_radius(wight_/4);
    phys->set_X(X_);
    phys->set_Y(Y_);

	speed = 0;
    coeff_attack = coeff_attack_;//gr
    current_frame_attack = 0;//gr
    
	speed = 0;
    hero_direction = 3;//gr
    coeff = coeff_;//gr
    current_frame = 0;//gr
	//here
    
    life = 1;
    
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
    if (image_attack.loadFromFile(/*resourcePath() +*/file_name_attack_) == false)
        assert(!"Class Character is crashed(loadFromFile image_attack)");
    
    if (texture_attack.loadFromImage(image_attack) == false)
        assert(!"Class Character is crashed(loadFromImage texture_attack)");
    
    if (image.loadFromFile(/*resourcePath() +*/file_name_) == false)
        assert(!"Class ObjectStatic is crashed(loadFromFile image)");
    
    if (texture.loadFromImage(image) == false)
        assert(!"Class ObjectStatic is crashed(loadFromImage texture)");
    
    sprite.setPosition(X_, Y_);
    sprite.setTextureRect(sf::IntRect(0, 0, wight_, height_));
    
    sprite_attack.setPosition(X_, Y_);
    sprite_attack.setTextureRect(sf::IntRect(0, 0, wight_, height_));
}

GraphObj::GraphObj()
{}

void GraphObj::update_graph(float time, GraphObj *graph_obj_array[], map &Map)
{}

/*void GraphObj::move_if_button_pressed(bool condition, int direct, int str_num, float time)
{
	if (condition) 
	{
		hero_direction = direct;
		current_frame += coeff * time;
		if (current_frame > number_of_image) current_frame -= number_of_image;
		sprite.setTextureRect(sf::IntRect(int(current_frame) * wight, str_num * height, wight, height));

		float speed_x = phys->get_speed_x();
		float speed_y = phys->get_speed_y();
		switch(direct)
		{
		case LEFT:
			if (speed_x > -CHAR_SPEED)
				phys->set_speed_x(speed_x - ACCELERATION *time);
			phys->set_speed_y(0);
			break;
		case RIGHT:
			if (speed_x <= CHAR_SPEED)
				phys->set_speed_x(speed_x + ACCELERATION * time);
			phys->set_speed_y(0);
			break;
		case UP:
			phys->set_speed_x(0);
			if (speed_y > -CHAR_SPEED)
				phys->set_speed_y(speed_y - ACCELERATION * time);
			break;
		case DOWN:
			phys->set_speed_x(0);
			if (speed_y <= CHAR_SPEED)
				phys->set_speed_y(speed_y + ACCELERATION * time);
			break;
		}
		sprite.move( phys->get_speed_x()* time, phys->get_speed_y() *time);
	}
}*/

PhysicObj* GraphObj::get_phys()
{
    return phys;
}

void GraphObj::set_phys(PhysicObj *phys_)
{
    phys = phys_;
}

double GraphObj::get_coeff()
{
    return coeff;
}

double GraphObj::get_coeff_attack()
{
    return coeff_attack;
}

int GraphObj::get_hero_direction()
{
    return hero_direction;
}

void GraphObj::set_hero_direction(int hero_direction_)
{
    hero_direction = hero_direction_;
}

bool GraphObj::is_alive()
{
    if (phys->get_HP() <= 0)
        return false;
    else return true;
}

float GraphObj::get_wight()
{
    return wight;
}

float GraphObj::get_height()
{
    return height;
}

sf::Sprite GraphObj::get_sprite()
{
    return sprite;
}

int GraphObj::get_number_of_image()
{
    return number_of_image;
}

void GraphObj::set_image(sf::Image image_)
{
    image = image_;
}

void GraphObj::set_texture(sf::Texture texture_)
{
    texture = texture_;
}

void GraphObj::set_sprite(sf::Sprite sprite_)
{
    sprite = sprite_;
}

float GraphObj::get_wight_attack()
{
    return wight_attack;
}

float GraphObj::get_height_attack()
{
    return height_attack;
}

sf::Sprite GraphObj::get_sprite_attack()
{
    return sprite_attack;
}

int GraphObj::get_number_of_attack_image()
{
    return number_of_attack_image;
}

void GraphObj::set_image_attack(sf::Image image_attack_)
{
    image_attack = image_attack_;
}

void GraphObj::set_texture_attack(sf::Texture texture_attack_)
{
    texture_attack = texture_attack_;
}
/*float PhysicObj::get_speed()
{
	return speed;
}

void PhysicObj::set_speed_x(float speed_)
{
	speed = speed_;
}*/
