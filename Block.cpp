#include "Block.hpp"

Block::Block(std::string file_name_, std::string file_name_attack_, float X_, float Y_, float wight_, float height_, float wight_attack_, float height_attack_, int number_of_image_, int number_of_attack_image_, double coeff_, double coeff_attack_) :
	GraphObj(file_name_, file_name_attack_, X_, Y_, wight_, height_, wight_attack_, height_attack_, number_of_image_, number_of_attack_image_, coeff_, coeff_attack_)
{
	phys->set_is_block(true);
	phys->set_mass(1000000000);
	phys->set_hit_radius(10);
}

Block::Block() :
	GraphObj()
{}

void Block::stand_still(float time)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, wight, height));
	sprite.setPosition(phys->get_X(), phys->get_Y());
	float speed_x = phys->get_speed_x();
	float speed_y = phys->get_speed_y();
}

void Block::update_graph(float time, GraphObj *graph_obj_array[], map &Map)
{
	stand_still(time);
}