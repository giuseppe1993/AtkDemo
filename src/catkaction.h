/*
 * catkaction.h
 *
 *  Created on: May 3, 2019
 *      Author: giuseppe
 */
 #ifndef DEMO_ACTION_H_
 #define DEMO_ACTION_H_

 #include <atk/atk.h>
 #include "catkactor.h"

 G_BEGIN_DECLS

 #define C_TYPE_ATK_ACTION            (c_atk_action_get_type ())

 G_DECLARE_DERIVABLE_TYPE(CAtkAction, c_atk_action, C, ATK_ACTION, CAtkActor)

 struct _CAtkActionClass
 {
   CAtkActorClass parent_class;
 };

 typedef struct
 {
   const gchar* description;
   const gchar* name;
   const gchar* keybinding;
   const gchar* localizedname;
 } RealAction;

 void c_atk_action_add_action(CAtkAction *self, RealAction *action);
 void c_atk_action_remove_action(CAtkAction *self, RealAction *action);
 void c_atk_action_set_name(CAtkAction *self, RealAction *action, gchar *name);
 void c_atk_action_set_keybinding(CAtkAction *self, RealAction *action, gchar *keybinding);
 void c_atk_action_set_localized_name(CAtkAction *self, RealAction *action, gchar *localizedname);


 G_END_DECLS

 #endif
