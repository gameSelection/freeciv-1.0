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
#ifndef __PACKETS_H
#define __PACKETS_H

#include "player.h"

#define MAX_PACKET_SIZE   4096
#define NAME_SIZE           10
#define MSG_SIZE          1536
#define ADDR_LENGTH         32

enum packet_type {
  PACKET_REQUEST_JOIN_GAME,
  PACKET_REPLY_JOIN_GAME_ACCEPT,
  PACKET_REPLY_JOIN_GAME_REJECT,
  PACKET_SERVER_SHUTDOWN,
  PACKET_UNIT_INFO,
  PACKET_MOVE_UNIT,
  PACKET_TURN_DONE,
  PACKET_NEW_YEAR,
  PACKET_TILE_INFO,
  PACKET_SELECT_RACE,
  PACKET_ALLOC_RACE,
  PACKET_SHOW_MESSAGE,
  PACKET_PLAYER_INFO,
  PACKET_GAME_INFO,
  PACKET_MAP_INFO,
  PACKET_CHAT_MSG,
  PACKET_CITY_INFO,
  PACKET_CITY_SELL,
  PACKET_CITY_BUY,
  PACKET_CITY_CHANGE,
  PACKET_CITY_MAKE_SPECIALIST,
  PACKET_CITY_MAKE_WORKER,
  PACKET_CITY_CHANGE_SPECIALIST,
  PACKET_CITY_RENAME,
  PACKET_PLAYER_RATES,
  PACKET_PLAYER_REVOLUTION,
  PACKET_PLAYER_GOVERMENT,
  PACKET_PLAYER_RESEARCH,
  PACKET_UNIT_BUILD_CITY,
  PACKET_UNIT_DISBAND,
  PACKET_REMOVE_UNIT,
  PACKET_REMOVE_CITY,
  PACKET_UNIT_CHANGE_HOMECITY,
  PACKET_UNIT_COMBAT,
  PACKET_UNIT_ESTABLISH_TRADE,
  PACKET_UNIT_HELP_BUILD_WONDER,
  PACKET_UNIT_GOTO_TILE,
  PACKET_GAME_STATE,
  PACKET_NUKE_TILE,
  PACKET_DIPLOMAT_ACTION,
  PACKET_PAGE_MSG,
  PACKET_REPORT_REQUEST,
  PACKET_DIPLOMACY_INIT_MEETING,
  PACKET_DIPLOMACY_CREATE_CLAUSE,
  PACKET_DIPLOMACY_REMOVE_CLAUSE,
  PACKET_DIPLOMACY_CANCEL_MEETING,
  PACKET_DIPLOMACY_ACCEPT_TREATY,
  PACKET_DIPLOMACY_SIGN_TREATY
};

enum report_type {
  REPORT_WONDERS_OF_THE_WORLD,
  REPORT_TOP_5_CITIES,
  REPORT_DEMOGRAPHIC
};

/*********************************************************
  diplomat action!
*********************************************************/
struct packet_diplomacy_info {
  int plrno0, plrno1;
  int plrno_from;
  int clause_type;
  int value;
};


/*********************************************************
  diplomat action!
*********************************************************/
struct packet_diplomat_action
{
  int action_type;
  int diplomat_id;
  int target_id;    /* city_id or unit_id */
};



/*********************************************************
  unit request
*********************************************************/
struct packet_nuke_tile
{
  int x, y;
};



/*********************************************************
  unit request
*********************************************************/
struct packet_unit_combat
{
  int attacker_unit_id;
  int defender_unit_id;
  int attacker_hp;
  int defender_hp;
  int make_winner_veteran;
};


/*********************************************************
  unit request
*********************************************************/
struct packet_unit_request
{
  int unit_id;
  int city_id;
  int x, y;
  char name[MAX_LENGTH_NAME];
};



/*********************************************************
  player request
*********************************************************/
struct packet_player_request
{
  int tax, luxury, science;              /* rates */
  int goverment;                         /* goverment */
  int tech;                              /* research */
};



/*********************************************************
  city request
*********************************************************/
struct packet_city_request
{
  int city_id;                           /* all */
  int build_id;                          /* change, sell */
  int is_build_id_unit_id;               /* change */
  int worker_x, worker_y;                /* make_worker, make_specialist */
  int specialist_from, specialist_to;    /* change_specialist */
  char name[MAX_LENGTH_NAME];            /* rename */
};


/*********************************************************
  tile info
*********************************************************/
struct packet_tile_info {
  int x, y, type, special, known;
};



/*********************************************************
send to each client whenever the turn has ended.
*********************************************************/
struct packet_new_year {
  int year;
};


/*********************************************************
packet represents a request to the server, for moving the
units with the corresponding id's from the unids array,
to the position x,y
unids[] is a compressed array, containing garbage after
last 0 id.
*********************************************************/
struct packet_move_unit {
  int x, y, unid;
};


/*********************************************************

*********************************************************/
struct packet_unit_info {
  int id;
  int owner;
  int x, y;
  int veteran;
  int homecity;
  int type;
  int attacksleft;
  int movesleft;
  int hp;
  int activity;
  int activity_count;
  int unhappiness;
  int upkeep;
  int bribe_cost;
};



/*********************************************************
...
*********************************************************/
struct packet_city_info {
  int id;
  int owner;
  int x, y;
  char name[MAX_LENGTH_NAME];

  int size;
  int ppl_happy, ppl_content, ppl_unhappy;
  int ppl_elvis, ppl_scientist, ppl_taxman;
  int food_prod, food_surplus;
  int shield_prod, shield_surplus;
  int trade_prod, corruption;
  int trade[4];
  int luxury_total, tax_total, science_total;

  /* the physics */
  int food_stock;
  int shield_stock;
  int polution;
  int incite_revolt_cost;

  int is_building_unit;
  int currently_building;

  unsigned char improvements[B_LAST+1];
  unsigned char city_map[CITY_MAP_SIZE*CITY_MAP_SIZE+1];

  int did_buy, did_sell;
};



/*********************************************************
 this packet is the very first packet send by the client.
 the player hasn't been accepted yet.
*********************************************************/
struct packet_req_join_game {
  char name[NAME_SIZE];
};


/*********************************************************
...
*********************************************************/
struct packet_alloc_race {
  int race_no;
  char name[MAX_LENGTH_NAME];
};


/*********************************************************
 this structure is a generic packet, which is used by a great
 number of different packets. In general it's used by all
 packets, which only requires a message(apart from the type).
 blah blah..
*********************************************************/
struct packet_generic_message {
  char message[MSG_SIZE];
};


/*********************************************************
  like the packet above. 
*********************************************************/
struct packet_generic_integer {
  int value;
};


/*********************************************************
 and the servers replies.
*********************************************************/
struct server_reply_join_game {
  int you_can_join;             /* true/false */
  char msg[MSG_SIZE];
};


/*********************************************************
...
*********************************************************/
struct packet_player_info {
  int playerno;
  char name[MAX_LENGTH_NAME];
  int goverment;
  int embassy;
  int race;
  int turn_done, nturns_idle;
  int is_alive;
  int gold, tax, science, luxury;
  int researched;
  int researchpoints;
  int researching;
  unsigned char inventions[A_LAST+1];
  int is_connected;
  char addr[MAX_LENGTH_ADDRESS];
  int revolution;
};


/*********************************************************
...
*********************************************************/
struct packet_game_info {
  int gold;
  int tech;
  int techlevel;
  int skill_level;
  int timeout;
  int end_year;
  int year;
  int min_players, max_players, nplayers;
  int player_idx;
  int globalwarming;
  int heating;
  int global_advances[A_LAST];
  int global_wonders[B_LAST];
};

/*********************************************************
...
*********************************************************/
struct packet_map_info {
  int xsize, ysize;
  int is_earth;
};


/*********************************************************
this is where the data is first collected, whenever it
arrives to the client/server.
*********************************************************/
struct socket_packet_buffer {
  int ndata;
  int do_buffer_sends;
  unsigned char data[10*MAX_PACKET_SIZE];
};



struct connection {
  int sock, used;
  char *player; 
  struct socket_packet_buffer buffer;
  struct socket_packet_buffer send_buffer;
  char addr[ADDR_LENGTH];
};


int read_socket_data(int sock, struct socket_packet_buffer *buffer);
int send_connection_data(struct connection *pc, unsigned char *data, int len);

unsigned char *get_int16(unsigned char *buffer, int *val);
unsigned char *put_int16(unsigned char *buffer, int val);
unsigned char *get_int32(unsigned char *buffer, int *val);
unsigned char *put_int32(unsigned char *buffer, int val);
unsigned char *put_string(unsigned char *buffer, char *mystring);
unsigned char *get_string(unsigned char *buffer, char *mystring);

int send_packet_diplomacy_info(struct connection *pc, enum packet_type pt,
			       struct packet_diplomacy_info *packet);
struct packet_diplomacy_info *
recieve_packet_diplomacy_info(struct connection *pc);




int send_packet_diplomat_action(struct connection *pc, 
				struct packet_diplomat_action *packet);
struct packet_diplomat_action *
recieve_packet_diplomat_action(struct connection *pc);

int send_packet_nuke_tile(struct connection *pc, 
			  struct packet_nuke_tile *packet);
struct packet_nuke_tile *
recieve_packet_nuke_tile(struct connection *pc);


int send_packet_unit_combat(struct connection *pc, 
			    struct packet_unit_combat *packet);
struct packet_unit_combat *
recieve_packet_unit_combat(struct connection *pc);


int send_packet_tile_info(struct connection *pc, 
			 struct packet_tile_info *pinfo);
struct packet_tile_info *recieve_packet_tile_info(struct connection *pc);

int send_packet_map_info(struct connection *pc, 
			  struct packet_map_info *pinfo);
struct packet_map_info *recieve_packet_map_info(struct connection *pc);

int send_packet_game_info(struct connection *pc, 
			  struct packet_game_info *pinfo);
struct packet_game_info *recieve_packet_game_info(struct connection *pc);


struct packet_player_info *recieve_packet_player_info(struct connection *pc);
int send_packet_player_info(struct connection *pc, 
			    struct packet_player_info *pinfo);


int send_packet_new_year(struct connection *pc, 
			 struct packet_new_year *request);
struct packet_new_year *recieve_packet_new_year(struct connection *pc);

int send_packet_move_unit(struct connection *pc, 
			  struct packet_move_unit *request);
struct packet_move_unit *recieve_packet_move_unit(struct connection *pc);


int send_packet_unit_info(struct connection *pc,
			  struct packet_unit_info *req);
struct packet_unit_info *recieve_packet_unit_info(struct connection *pc);

int send_packet_req_join_game(struct connection *pc, 
			      struct packet_req_join_game *request);
struct packet_req_join_game *recieve_packet_req_join_game(struct 
							  connection *pc);

int send_packet_alloc_race(struct connection *pc, 
			   struct packet_alloc_race *packet);
struct packet_alloc_race *recieve_packet_alloc_race(struct connection *pc);






int send_packet_generic_message(struct connection *pc, int type,
				struct packet_generic_message *message);
struct packet_generic_message *recieve_packet_generic_message(struct 
							      connection *pc);

int send_packet_generic_integer(struct connection *pc, int type,
				struct packet_generic_integer *packet);
struct packet_generic_integer *recieve_packet_generic_integer(struct 
							      connection *pc);


int send_packet_city_info(struct connection *pc,struct packet_city_info *req);
struct packet_city_info *recieve_packet_city_info(struct connection *pc);

int send_packet_city_request(struct connection *pc, 
			     struct packet_city_request *packet, enum packet_type);
struct packet_city_request *
recieve_packet_city_request(struct connection *pc);


int send_packet_player_request(struct connection *pc, 
			       struct packet_player_request *packet,
			       enum packet_type req_type);
struct packet_player_request *
recieve_packet_player_request(struct connection *pc);

struct packet_unit_request *
recieve_packet_unit_request(struct connection *pc);
int send_packet_unit_request(struct connection *pc, 
			     struct packet_unit_request *packet,
			     enum packet_type req_type);

void *get_packet_from_connection(struct connection *pc, int *ptype);
void remove_packet_from_buffer(struct socket_packet_buffer *buffer);
void flush_connection_send_buffer(struct connection *pc);
void connection_do_buffer(struct connection *pc);
void connection_do_unbuffer(struct connection *pc);

#endif

