#ifndef __WINDOW_GROUP_FACTORY_H__
#define __WINDOW_GROUP_FACTORY_H__

#include "../../models/window_group/window_group.h"

window_group_t* create_window_group();

void free_window_group(window_group_t* window_group);

#endif // __WINDOW_GROUP_FACTORY_H__
