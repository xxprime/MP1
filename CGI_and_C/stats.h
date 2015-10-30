#ifndef __STATS_H__
#define __STATS_H__

typedef struct {
  unsigned int strength;
  unsigned int agility;
  unsigned int dexterity;
  unsigned int vitality;
  unsigned int intelligence;
  unsigned int health;
  unsigned int maxhealth;
  unsigned int level;
} stats_t;

int cur_health(unsigned int s_health, unsigned int dmg, unsigned int def);
unsigned int dmg_attack(unsigned int s_strength, unsigned int t_level);
unsigned int dmg_skill(unsigned int s_intelligence, unsigned int t_level);
unsigned int dmg_reduction(unsigned int s_vitality, unsigned int s_level);
unsigned short int flee_success(unsigned int s_agility, unsigned int s_level, unsigned int t_level);
unsigned short int hit_success(unsigned int s_dexterity, unsigned int t_agility);


#endif
