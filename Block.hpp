#pragma once

#include "GraphObj.hpp"

class Block : public GraphObj
{
public:
	//Constructor:
	Block(std::string file_name_, std::string file_name_attack_, float X_, float Y_, float wight_, float height_, float wight_attack_, float height_attack_, int number_of_image_, int number_of_attack_image_, double coeff_, double coeff_attack_);
	Block();

	void stand_still(float time);
	virtual void update_graph(float time, GraphObj *graph_obj_array[], map &Map) override;
};