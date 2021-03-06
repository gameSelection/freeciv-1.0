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
#include <stdlib.h>
#include "genlist.h"


/************************************************************************
  ...
************************************************************************/
void genlist_init(struct genlist *pgenlist)
{
  pgenlist->nelements=0;
  pgenlist->head_link=&pgenlist->null_link;
  pgenlist->tail_link=&pgenlist->null_link;
  pgenlist->null_link.next=&pgenlist->null_link;
  pgenlist->null_link.prev=&pgenlist->null_link;
  pgenlist->null_link.dataptr=0;
}


/************************************************************************
  ...
************************************************************************/
int genlist_size(struct genlist *pgenlist)
{
  return pgenlist->nelements;
}

/************************************************************************
  ...
************************************************************************/
void *genlist_get(struct genlist *pgenlist, int idx)
{
  struct genlist_link *link=find_genlist_position(pgenlist, idx);

  return link->dataptr;
}



/************************************************************************
  ...
************************************************************************/
void genlist_unlink_all(struct genlist *pgenlist)
{
  if(pgenlist->nelements) {
    struct genlist_link *plink=pgenlist->head_link, *plink2;

    do {
      plink2=plink->next;
      free(plink);
    } while((plink=plink2)!=&pgenlist->null_link);

    pgenlist->head_link=&pgenlist->null_link;
    pgenlist->tail_link=&pgenlist->null_link;

    pgenlist->nelements=0;
  }

}



/************************************************************************
  ...
************************************************************************/
void genlist_unlink(struct genlist *pgenlist, void *punlink)
{
  if(pgenlist->nelements) {
    struct genlist_link *plink=pgenlist->head_link;
    
    while(plink!=&pgenlist->null_link && plink->dataptr!=punlink)
       plink=plink->next;
    
    if(plink->dataptr==punlink) {
      if(pgenlist->head_link==plink)
	 pgenlist->head_link=plink->next;
      else
	 plink->prev->next=plink->next;

      if(pgenlist->tail_link==plink)
	 pgenlist->tail_link=plink->prev;
      else
	 plink->next->prev=plink->prev;
      
      pgenlist->nelements--;
    }
  }

}




/************************************************************************
  ...
************************************************************************/
void genlist_insert(struct genlist *pgenlist, void *data, int pos)
{
  if(!pgenlist->nelements) { /*list is empty, ignore pos */
    
    struct genlist_link *plink=(struct genlist_link *)
      malloc(sizeof(struct genlist_link));

    plink->dataptr=data;
    plink->next=&pgenlist->null_link;
    plink->prev=&pgenlist->null_link;

    pgenlist->head_link=plink;
    pgenlist->tail_link=plink;

  }
  else {
    struct genlist_link *plink=(struct genlist_link *)
      malloc(sizeof(struct genlist_link));
    plink->dataptr=data;


    if(pos==0) {
      plink->next=pgenlist->head_link;
      plink->prev=&pgenlist->null_link;
      pgenlist->head_link->prev=plink;
      pgenlist->head_link=plink;
    }
    else if(pos==-1) {
      plink->next=&pgenlist->null_link;
      plink->prev=pgenlist->tail_link;
      pgenlist->tail_link->next=plink;
      pgenlist->tail_link=plink;
    }
    else {
      struct genlist_link *pre_insert_link; 
      pre_insert_link=find_genlist_position(pgenlist, pos);
      pre_insert_link->next->prev=plink;
    }
  }

  pgenlist->nelements++;
}

/************************************************************************
  ...
************************************************************************/
void genlist_iterator_init(struct genlist_iterator *iter,
				struct genlist *pgenlist, int pos)
{
  iter->list=pgenlist;
  iter->link=find_genlist_position(pgenlist, pos);
}





/************************************************************************
  ...
************************************************************************/
struct genlist_link *
find_genlist_position(struct genlist *pgenlist, int pos)
{
  struct genlist_link *plink;


  if(pos==0)
    return pgenlist->head_link;
  else if(pos==-1)
    return pgenlist->tail_link;
  else if(pos>=pgenlist->nelements)
    return &pgenlist->null_link;

  if(pos<pgenlist->nelements/2)   /* fastest to do forward search */
    for(plink=pgenlist->head_link; pos; pos--)
      plink=plink->next;
 
  else                           /* fastest to do backward search */
    for(plink=pgenlist->tail_link,pos=pgenlist->nelements-pos-1; pos; pos--)
      plink=plink->prev;
 
  return plink;
}







