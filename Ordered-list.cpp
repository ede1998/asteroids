/*                                                   *
 * file: Ordered-list.cpp                            *
 * author: Erik Hennig                               *
 * date: 25.12.2016                                  *
 * abstract: implementation of ordered_list class,   *
 *          simple, single-linked list to store date */

#include <cstddef>
#include "Ordered-list.h"
#include <iostream>

ordered_list::ordered_list() :
        _pfirst ( NULL ),
        _plast  ( NULL )
{

}

ordered_list::~ordered_list()
{
  element * pdel, * ptmp = _pfirst;
  do
  {
    pdel = ptmp;
    iterate(&ptmp);
    delete(pdel);
  }
  while (ptmp);
}

int ordered_list::append(void * newdata)
{
  element * ptmp, * ppos;
  ptmp = new element;
  ptmp->data = newdata;
  ptmp->pnext = NULL;
  if (!_pfirst)
  {
    _pfirst = ptmp;
    return 0;
  }
  else
  {
    int i = 1;
    ppos = _pfirst;
    while (ppos->pnext)
    {
      iterate(&ppos);
      i++;
    }
    ppos->pnext = ptmp;
    return i;
  }
}

bool ordered_list::del(int index)
{
  element * pdel_pre = getElPointer(index - 1), * pdel = getElPointer(index);
  if (pdel_pre && pdel)
  {
    pdel_pre->pnext = pdel->pnext;
    delete(pdel);
    return true;
  }
  if (!pdel_pre && pdel)
  {
    _pfirst = pdel->pnext;
    delete(pdel);
    return true;
  }
  return false;
}

void * ordered_list::getElement(int index)
{
  element * ptmp = getElPointer(index);
  if (!ptmp) return NULL;
  return ptmp->data;
}

int ordered_list::getlength()
{
  element * p = _pfirst;
  int len = 0;
  while (iterate(&p))
    len++;
  return len;
}

bool ordered_list::iterate(element * * p)
{
  if (*p)
  {
    
    *p = (*p)->pnext;
    return true;
  }
  return false;
}

element* ordered_list::getElPointer(int index)
{
  element * ppos = _pfirst;
  if (index < 0) return NULL;
  
  for (int i = 0; (ppos->pnext) && (i < index); i++)
  {
    iterate(&ppos);
    //Abort 1)if next i not last i  AND   2) next element = NULL 
    //Abort if end of list reached
    if ((!ppos->pnext) && !(i + 1 == index)) return NULL;
  }
  
  return ppos;
}


