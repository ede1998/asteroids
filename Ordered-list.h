/*                                                   *
 * file: Ordered-list.h                              *
 * author: Erik Hennig                               *
 * date: 25.12.2016                                  *
 * abstract: implementation of ordered_list class,   *
 *          simple, single-linked list to store date */


struct element {
  element * pnext;
  void * data;
};

class ordered_list
{
  public:
    ordered_list();
    virtual ~ordered_list();
    int append(void * newdata);
    bool del(int index);
    void * getElement(int index);
    int getlength();
  private:
    element * _pfirst;
    element * _plast;
    bool iterate(element * * p);
    element* getElPointer(int index);
};
