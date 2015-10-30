#include <stdlib.h>
#include <time.h>
#include "stats.h"

int cur_health(unsigned int s_health, unsigned int dmg, unsigned int def)
{
  int final_dmg = dmg - def;
  int current_health;

  if (final_dmg < 0) final_dmg = 0;

  current_health = s_health - final_dmg;

  if (current_health < 0) current_health = 0;

  return current_health;
}

unsigned int dmg_attack(unsigned int s_strength, unsigned int t_level)
{
  unsigned int damage = s_strength + t_level;

  return damage;
}

unsigned int dmg_skill(unsigned int s_intelligence, unsigned int t_level)
{
  unsigned int damage = s_intelligence + (t_level * 2);

  return damage;
}

unsigned int dmg_reduction(unsigned int s_vitality, unsigned int s_level)
{
  unsigned int defense = (s_vitality / 2) + s_level;

  return defense;
}

unsigned short int flee_success(unsigned int s_agility, unsigned int s_level, unsigned int t_level)
{
  unsigned short int success;
  unsigned int flee = (s_agility / 5) + s_level;
  unsigned int bonus;

  srand(time(NULL));

  bonus = rand() % s_level + 1;
  flee = flee + bonus;
  if (flee >= (t_level * 2)) success = 1;
  else success = 0;

  return success;
}

unsigned short int hit_success(unsigned int s_dexterity, unsigned int t_agility)
{
  unsigned short int success;
  unsigned int hit, dodge;

  srand(time(NULL));

  hit = rand() % s_dexterity;
  dodge = rand() % t_agility;

  if (hit >= dodge) success = 1;
  else success = 0;

  return success;
}
