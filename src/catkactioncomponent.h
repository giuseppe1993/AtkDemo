/*
 * catkactioncomponent.h
 *
 *  Created on: May 3, 2019
 *      Author: giuseppe
 */
 #ifndef DEMO_ACTION_COMPONENT_H_
 #define DEMO_ACTION_COMPONENT_H_

 #include <atk/atk.h>
 #include "catkaction.h"

 G_BEGIN_DECLS

 #define C_TYPE_ATK_ACTION_COMPONENT            (c_atk_action_component_get_type ())

 G_DECLARE_DERIVABLE_TYPE(CAtkActionComponent, c_atk_action_component, C, ATK_ACTION_COMPONENT, CAtkAction)

 struct _CAtkActionComponentClass
 {
   CAtkActionClass parent_class;
 };

 //protected
 void c_atk_component_set_layer (CAtkActionComponent *self, AtkLayer layer);
 void c_atk_component_set_coord_type (CAtkActionComponent *self, AtkCoordType coord_type);

 G_END_DECLS

 #endif
