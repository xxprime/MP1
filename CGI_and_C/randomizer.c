#include <stdlib.h>
#include <time.h>
#include "randomizer.h"

coordinate_t rand_location(void)
{
  coordinate_t loc;

  srand(time(NULL));
  loc.x = rand() % 9 + 1;
  loc.y = rand() % 9 + 1;

  return loc;
}

unsigned short int rand_spawn(unsigned short int rate)
{
  unsigned short int spawn;

  if (rate > 100 || rate < 0) return -1;

  srand(time(NULL));
  spawn = rand() % 100 + 1;

  if (spawn > rate) return 0;
  else if (spawn <= rate) return 1;
  else return -1;
}

unsigned int rand_monster_lvl(unsigned int plevel)
{
  unsigned int mlevel;
  unsigned short int pivot;

  srand(time(NULL));

  if (plevel > 1) pivot = rand() % 3;
  else if (plevel == 1) pivot = rand() % 2;
  else return -1;

  if (pivot == 0) mlevel = plevel;
  else if (pivot == 1) mlevel = plevel + 1;
  else if (pivot == 2) mlevel = plevel - 1;
  else mlevel = -1; //Something is wrong with the universe if this happens

  return mlevel;
}
