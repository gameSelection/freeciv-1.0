/********************************************************************** 
 Freeciv - Copyright (C) 1996 - A Kjeldberg, L Gregersen, P Unold
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
***********************************************************************/
#ifndef __TECH_H
#define __TECH_H
struct player;

enum tech_type_id {  
  A_NONE, A_ADVANCED, A_ALPHABET, A_ASTRONOMY, A_ATOMIC,
  A_AUTOMOBILE, A_BANKING, A_BRIDGE, A_BRONZE, A_CEREMONIAL,
  A_CHEMISTRY, A_CHIVALRY, A_CODE, A_COMBUSTION, A_COMMUNISM,
  A_COMPUTERS, A_CONSCRIPTION, A_CONSTRUCTION, A_CURRENCY,
  A_DEMOCRACY, A_ELECTRICITY, A_ELECTRONICS, A_ENGINEERING,
  A_EXPLOSIVES, A_FEUDALISM, A_FLIGHT, A_FUSION, A_GENETIC,
  A_GUNPOWDER, A_HORSEBACK, A_INDUSTRIALIZATION, A_INVENTION,
  A_IRON, A_LABOR, A_LITERACY, A_MAGNETISM, A_MAPMAKING, A_MASONRY,
  A_MASS, A_MATHEMATICS, A_MEDICINE, A_METALLURGY, A_MONARCHY,
  A_MYSTICISM, A_NAVIGATION, A_FISSION, A_POWER, A_PHILOSOPHY,
  A_PHYSICS, A_PLASTICS, A_POTTERY, A_RAILROAD, A_RECYCLING,
  A_REFINING, A_RELIGION, A_ROBOTICS, A_ROCKETRY, A_SPACEFLIGHT,
  A_STEAM, A_STEEL, A_SUPERCONDUCTOR, A_CORPORATION, A_REPUBLIC,
  A_WHEEL, A_THEORY, A_TRADE, A_UNIVERSITY, A_WRITING, A_LAST
};

#define TECH_UNKNOWN 0
#define TECH_KNOWN 1
#define TECH_REACHABLE 2

struct advance {
  char *name;
  int req[2];
};

int get_invention(struct player *plr, int tech);
void set_invention(struct player *plr, int tech, int value);
void update_research(struct player *plr);


extern struct advance advances[];

#endif
