#include "PhysicCount.hpp"

#define RADIUS_ARGUE 100
#define BULLET_LOCATION_INTO_ARRAY 4

PhysicCount::PhysicCount()
{
    number_of_player_in_array = -1;
}

void PhysicCount::physic_count(float time, map &Map)
{
	float old_X, old_Y, speed_x, speed_y;
	for (int i = 0; i < PHYS_OBJ_ARRAY_CAPACITY; i++)
	{
		old_X = phys_obj_array[i]->get_X();
		old_Y = phys_obj_array[i]->get_Y();
		speed_x = phys_obj_array[i]->get_speed_x();
		speed_y = phys_obj_array[i]->get_speed_y();
		phys_obj_array[i]->set_X(old_X + speed_x * time );
		phys_obj_array[i]->set_Y(old_Y + speed_y * time );

		for (int j = i + 1; j < PHYS_OBJ_ARRAY_CAPACITY; j++)
		{
			if ((phys_obj_array[i]->get_HP() > 0) && (phys_obj_array[j]->get_HP() > 0))
			{
				bool coll_flag = collision(phys_obj_array[i], phys_obj_array[j]);
				if (!coll_flag)
				{
					phys_obj_array[j]->set_is_staying(0);
					/*if (i == 1)
					{
						printf("time = %lf\n", time);
						printf("speed_x = %lf\n", speed_x);
						printf("speed_y = %lf\n", speed_y);
						printf("old_X = %lf\n", old_X);
						printf("old_Y = %lf\n", old_Y);
						printf("set_X(%lf)\n", old_X + speed_x * time);
						printf("set_Y(%lf)\n\n\n", old_Y + speed_y * time);
					}*/
				}
			}
		}
		//printf("gib = %i\n", phys_obj_array[i]->get_is_block());
		//printf("wight = %lf\n", phys_obj_array[i]->get_wight());
	}
	//printf("\n\n\n\n");
}

bool PhysicCount::collision(PhysicObj *first, PhysicObj *second)
{
	bool collided = 0;
	float centre_x1 = first->get_X() + first->get_wight() /2;
	float centre_x2 = second->get_X() + second->get_wight()/ 2;
	float centre_y1 = first->get_Y() + first->get_height()/ 2;
	float centre_y2 = second->get_Y() + second->get_height()/ 2;
	float hit_radius_sum_sqr = (first->get_hit_radius() + second->get_hit_radius()) * (first->get_hit_radius() + second->get_hit_radius());
	float centre_distance_sqr = (centre_x1 - centre_x2)*(centre_x1 - centre_x2) + (centre_y1 - centre_y2) * (centre_y1 - centre_y2);

	bool is_bullet_first = first->get_is_bullet();
	bool is_bullet_second = second->get_is_bullet();
	bool is_player_first = first->get_is_player();
	bool is_player_second = second->get_is_player();


	if  ((centre_distance_sqr <= hit_radius_sum_sqr) &&
		(centre_distance_sqr >= hit_radius_sum_sqr/1.2) && ((!is_bullet_first) || (!is_player_second)) && ((!is_bullet_second) || (!is_player_first)))
	{
		collided = 1;
		// Count of impulses
		//printf("collision ");
		float m1 = first->get_mass(), m2 = second->get_mass(), v1x = first->get_speed_x(),
		v1y = first->get_speed_y(), v2x = second->get_speed_x(), v2y = second->get_speed_y();
		first->set_speed_x((m2 * v2x + v1x * (m1 - m2)) / (m1 + m2));
		first->set_speed_y((m2 * v2y + v1y * (m1 - m2)) / (m1 + m2));
		second->set_speed_x((m1 * v1x + v2x * (m1 - m2)) / (m1 + m2));
		second->set_speed_y((m1 * v1y + v2y * (m1 - m2)) / (m1 + m2));

		//////////////////////////Warning. here is KOSTIL
		if (first->get_is_bullet() && second->get_is_first_enemy())
		{
			first->set_HP(-10);
			second->set_HP(second->get_HP() - 30);
		}
		if (second->get_is_bullet() && first->get_is_first_enemy())
		{
			second->set_HP(-10);
			first->set_HP(first->get_HP() - 30);
		}

		// If PhysicObj intersects another we need to make them not to superimose
		/*float tgB = abs(second->get_speed_y() / second->get_speed_x());
		float cosB = 1 / sqrt(1 + tgB*tgB);
		float sinB = tgB / sqrt(1 + tgB * tgB);
		float speed_x2 = second->get_speed_x();
		float speed_y2 = second->get_speed_y();
		float x2 = second->get_X();
		float y2 = second->get_Y();
		if ((speed_x2 >= 0) && (speed_y2 < 0))
		{
			printf("second_X = %lf\n", x2);
			second->set_X(abs(x2 - COLLIS_CORRECTION * cosB/2));
			second->set_Y(abs(y2 + COLLIS_CORRECTION * sinB / 2));
			printf("second_X = %lf\n\n\n\n", second->get_X());
		}
		if ((speed_x2 < 0) && (speed_y2 < 0))
		{
			printf("second_X = %lf\n", x2);
			second->set_X(abs(x2 + COLLIS_CORRECTION * cosB / 2));
			second->set_Y(abs(y2 + COLLIS_CORRECTION * sinB / 2));
			printf("second_X = %lf\n\n\n\n", second->get_X());
		}
		if ((speed_x2 < 0) && (speed_y2 >= 0))
		{
			printf("second_X = %lf\n", x2);
			second->set_X(abs(x2 + COLLIS_CORRECTION * cosB / 2));
			second->set_Y(abs(y2 - COLLIS_CORRECTION * sinB / 2));
			printf("second_X = %lf\n\n\n\n", second->get_X());
		}
		if ((speed_x2 >= 0) && (speed_y2 >= 0))
		{
			printf("second_X = %lf\n", x2);
			second->set_X(abs(x2 - COLLIS_CORRECTION * cosB / 2));
			second->set_Y(abs(y2 - COLLIS_CORRECTION * sinB / 2));
			printf("second_X = %lf\n\n\n\n", second->get_X());
		}*/
		//if (centre_distance_sqr <= hit_radius_sum_sqr + COLLIS_CORRECTION)
		//	second->set_is_staying(1);
		//second->set_speed_x(0);
		//second->set_speed_y(0);
	}
	return collided;
}

//arguments should be changed
void PhysicCount::logic_realisation()
{
    players_in_radius();
    bullet_hit();
	//no_way_rock();
    //other functions
}

void PhysicCount::bullet_hit()
{
    for (int i = 0; i<PHYS_OBJ_ARRAY_CAPACITY; i++)
        if (phys_obj_array[i]->get_is_bullet())
            bullet_damage(i);
}

void PhysicCount::bullet_damage(int number_in_array)
{
    if (!phys_obj_array[number_in_array]->get_intersect_bullet_event())
    {
        int bullet_centre_x = phys_obj_array[number_in_array]->get_X() + (phys_obj_array[number_in_array]->get_wight())/2;
        int bullet_centre_y = phys_obj_array[number_in_array]->get_Y() + (phys_obj_array[number_in_array]->get_height())/2;
        
        int player_centre_x = phys_obj_array[number_of_player_in_array]->get_X() + (phys_obj_array[number_of_player_in_array]->get_wight())/2;
        int player_centre_y = phys_obj_array[number_of_player_in_array]->get_Y() + (phys_obj_array[number_of_player_in_array]->get_height())/2;
        
        int local_radius = phys_obj_array[number_of_player_in_array]->get_wight();
        
        if (((bullet_centre_x + local_radius) < player_centre_x) && ((bullet_centre_y + local_radius) < player_centre_y))
            phys_obj_array[number_in_array]->set_intersect_bullet_event(true);
    }
}

void PhysicCount::players_in_radius()
{
    number_of_player_in_array = 0;
    
    for (int i = 0; i < PHYS_OBJ_ARRAY_CAPACITY; i++)
    {
        
        if (phys_obj_array[i]->get_is_ghost() || phys_obj_array[i]->get_is_first_enemy())
            hero_interrapted(i);
    }
}

void PhysicCount::hero_interrapted(int number_in_array)
{
        int centre_x = phys_obj_array[number_in_array]->get_X() + (phys_obj_array[number_in_array]->get_wight())/2;
        
        int centre_y = phys_obj_array[number_in_array]->get_Y() + (phys_obj_array[number_in_array]->get_height())/2;
        
        int player_centre_x = phys_obj_array[number_of_player_in_array]->get_X() + (phys_obj_array[number_of_player_in_array]->get_wight())/2;
        
        int player_centre_y = phys_obj_array[number_of_player_in_array]->get_Y() + (phys_obj_array[number_of_player_in_array]->get_height())/2;
            
    if (((centre_x - player_centre_x) * (centre_x - player_centre_x) + ((centre_y - player_centre_y)*(centre_y - player_centre_y))) <= 10000)
            phys_obj_array[number_in_array]->set_player_in_radius_event(true);
    else
        phys_obj_array[number_in_array]->set_player_in_radius_event(false);
}

void PhysicCount::no_way_rock()
{
	for (int i = 0; i < PHYS_OBJ_ARRAY_CAPACITY; i++)
	{
		//printf("gib = %i\n", phys_obj_array[i]->get_is_block());
		if (phys_obj_array[i]->get_is_block())
		{
			//printf("eto ya\n");
			float player_X = phys_obj_array[0]->get_X();
			float player_Y = phys_obj_array[0]->get_Y();
			float obj_X = phys_obj_array[i]->get_X();
			float obj_Y = phys_obj_array[i]->get_Y();
			float obj_wight = phys_obj_array[i]->get_wight();
			float obj_height = phys_obj_array[i]->get_height();

			/*printf("player_X = %lf\n", player_X);
			printf("player_Y = %lf\n", player_Y);
			printf("obj_X = %lf\n", obj_X);
			printf("obj_Y = %lf\n", obj_Y);
			printf("obj_wight = %lf\n", obj_wight);
			printf("obj_height = %lf\n\n\n", obj_height);*/

			printf("player_speed_x = %lf\n", phys_obj_array[0]->get_speed_x());
			printf("player_speed_y = %lf\n", phys_obj_array[0]->get_speed_y());
			if ((player_X >= obj_X) && (player_X <= obj_X + obj_wight) && (player_Y >= obj_Y) && (player_Y <= obj_Y + obj_height))
			{
				printf("!");
				phys_obj_array[0]->set_speed_x(-phys_obj_array[0]->get_speed_x());
				phys_obj_array[0]->set_speed_y(-phys_obj_array[0]->get_speed_y());
				printf("player_speed_x = %lf\n", phys_obj_array[0]->get_speed_x());
				printf("player_speed_y = %lf\n\n\n\n", phys_obj_array[0]->get_speed_y());
			}
		}
	}
	printf("\n\n\n\n");
}

