#ifndef __RANDOMIZER_H__
#define __RANDOMIZER_H__

typedef struct {
  unsigned short int x;
  unsigned short int y;
} coordinate_t;

coordinate_t rand_location(void);
unsigned short int rand_spawn(unsigned short int rate);
unsigned int rand_monster_lvl(unsigned int plevel);

#endif
