/*
 * demo_component.h
 *
 *  Created on: Apr 25, 2019
 *      Author: giuseppe
 */

#ifndef DEMO_COMPONENT_H_
#define DEMO_COMPONENT_H_

#include <atk/atk.h>
#include "fixAtk.h"

G_BEGIN_DECLS

#define C_TYPE_ATK_COMPONENT            (c_atk_component_get_type ())

G_DECLARE_DERIVABLE_TYPE(CAtkComponent, c_atk_component, C, ATK_COMPONENT, CAtkActor)

struct _CAtkComponentClass
{
  CAtkActorClass parent_class;
};

void c_atk_component_get_extents (AtkComponent *component, gint *x, gint *y, gint *width, gint *height, AtkCoordType coord_type);

AtkLayer c_atk_component_get_layer(AtkComponent *component);

G_END_DECLS

#endif /* DEMO_COMPONENT_H_ */
