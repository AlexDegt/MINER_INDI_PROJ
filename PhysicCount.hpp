#include "PhysicObj.hpp"
#include "Map.hpp"

class PhysicCount
{
public:
    PhysicObj* phys_obj_array[PHYS_OBJ_ARRAY_CAPACITY];
    PhysicCount();
    
    //Counting Physics:
    void physic_count(float time, map &Map);
	bool collision(PhysicObj * first, PhysicObj * second);
    void logic_realisation();
    
    //Functions realisated in logic_realisation
    int number_of_player_in_array;
    void players_in_radius();
    void bullet_hit();
    void bullet_damage(int number_in_array);
	void no_way_rock();

    void hero_interrapted(int number_in_array);
};
