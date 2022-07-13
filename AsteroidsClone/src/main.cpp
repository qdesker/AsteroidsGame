#include <fstream>
#include <iostream>
#include <string>
#include "Constants.h"
#include "Framework.h"
#include "Game.h"

using namespace std;

int main()
{
	std::ifstream ConfigFile ("settings//settings.ini");
	if (ConfigFile.is_open())
	{
		std::string line;
		while(getline(ConfigFile, line))
		{
			line.erase(std::remove_if(line.begin(), line.end(), isspace),
								 line.end());
			if( line.empty() || line[0] == '#' )
			{
				continue;
			}
			const std::size_t delimiter = line.find("=");
			std::string name = line.substr(0, delimiter);
			std::string value = line.substr(delimiter + 1);
			if(name == "window_width")
			{
				WINDOW_WIDTH = std::stoi(value);
			}
			else if ( name == "window_height")
			{
				WINDOW_HEIGHT = std::stoi(value);
			}
			else if ( name == "map_width")
			{
				MAP_WIDTH = std::stoi(value);
			}
			else if ( name == "map_height")
			{
				MAP_HEIGHT = std::stoi(value);
			}
			else if ( name == "fullscreen")
			{
				FULLSCREEN = value != "0";
			}
			else if ( name == "num_asteroids")
			{
				NUM_ASTEROIDS = std::stoi(value);
			}
			else if ( name == "num_ammo")
			{
				NUM_AMMO = std::stoi(value);
			}
			else if ( name == "ability_probability")
			{
				ABILITY_PROBABILITY = std::stof(value);
			}
			else if ( name == "big_asteroid_mass")
			{
				BIG_ASTEROID_MASS = std::stof(value);
			}
			else if ( name == "small_asteroid_mass")
			{
				SMALL_ASTEROID_MASS = std::stof(value);
			}
			else if ( name == "big_asteroid_partition_time")
			{
				BIG_ASTEROID_PARTITION_TIME = std::stoi(value);
			}
			else if ( name == "player_speed")
			{
				PLAYER_SPEED = std::stof(value);
			}
			else if ( name == "asteroids_down_limit_speed")
			{
				ASTEROIDS_DOWN_LIMIT_SPEED = std::stof(value);
			}
			else if ( name == "asteroids_upper_limit_speed")
			{
				ASTEROIDS_UPPER_LIMIT_SPEED = std::stof(value);
			}
			else if ( name == "bullet_speed")
			{
				BULLET_SPEED = std::stof(value);
			}
			else if ( name == "friction_force")
			{
				FRICTION_FORCE = std::stof(value);
			}
			else if ( name == "no_spawn_zone_radius")
			{
				NO_SPAWN_ZONE_RADIUS = std::stoi(value);
			}
			else if ( name == "shoot_cooldown")
			{
				SHOOT_COOLDOWN = std::stof(value);
			}
			else if (name == "shield_duration")
			{
				SHIELD_DURATION = std::stof(value);
			}
			else if (name == "homing_missile_speed")
			{
				HOMING_MISSILE_SPEED = std::stof(value);
			}
		}
		ConfigFile.close();
	}
	else
	{
		std::cerr << "Couldn't open config file for reading.\n";
	}
	return run(new Game);
}
