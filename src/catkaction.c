/*
 * catkaction.c
 *
 *  Created on: May 3, 2019
 *      Author: giuseppe
 */
 #include <gmodule.h>
 #include "catkaction.h"

 #define C_ATK_ACTION_GET_PRIVATE(o) (c_atk_action_get_istance_private (o))

 typedef struct
 {
     GList *accessibleActions;
 } CAtkActionPrivate;

struct _RealAction {
   gchar* description;
   gchar* name;
   gchar* keybinding;
   gchar* localizedname;
 };

 static void c_atk_action_atk_action_init (AtkActionIface *iface);

 G_DEFINE_ABSTRACT_TYPE_WITH_CODE (CAtkAction, c_atk_action, C_TYPE_ATK_ACTOR, { G_ADD_PRIVATE (CAtkAction); G_IMPLEMENT_INTERFACE (atk_action_get_type(), c_atk_action_atk_action_init); })

static gint
c_atk_action_get_n_actions(AtkAction *action)
{
  g_return_val_if_fail (C_IS_ATK_ACTION(action), -1);
  CAtkActionPrivate *priv = c_atk_action_get_instance_private(C_ATK_ACTION(action));
  return g_list_length(priv->accessibleActions);
}

static const gchar*
c_atk_action_get_description(AtkAction *action, gint i)
{
  g_return_val_if_fail (C_IS_ATK_ACTION(action), NULL);
  CAtkActionPrivate *priv = c_atk_action_get_instance_private(C_ATK_ACTION(action));
  RealAction *data = g_list_nth_data (priv->accessibleActions, i);
  g_return_val_if_fail (data, NULL);
  return strdup(data->description);
}

static const gchar*
c_atk_action_get_name(AtkAction *action, gint i)
{
  g_return_val_if_fail (C_IS_ATK_ACTION(action), NULL);
  CAtkActionPrivate *priv = c_atk_action_get_instance_private(C_ATK_ACTION(action));
  RealAction *data = g_list_nth_data (priv->accessibleActions, i);
  g_return_val_if_fail (data, NULL);
  return data->name;
}

static const gchar*
c_atk_action_get_keybinding(AtkAction *action, gint i)
{
  g_return_val_if_fail (C_IS_ATK_ACTION(action), NULL);
  CAtkActionPrivate *priv = c_atk_action_get_instance_private(C_ATK_ACTION(action));
  RealAction *data = g_list_nth_data (priv->accessibleActions, i);
  g_return_val_if_fail (data, NULL);
  return data->keybinding;
}

static const gchar*
c_atk_action_get_localized_name(AtkAction *action, gint i)
{
  g_return_val_if_fail (C_IS_ATK_ACTION(action), NULL);
  CAtkActionPrivate *priv = c_atk_action_get_instance_private(C_ATK_ACTION(action));
  RealAction *data = g_list_nth_data (priv->accessibleActions, i);
  g_return_val_if_fail (data, NULL);
  return data->localizedname;
}

 static void
 c_atk_action_atk_action_init (AtkActionIface *iface)
 {
     iface->get_n_actions = c_atk_action_get_n_actions;
     iface->get_description = c_atk_action_get_description;
     iface->get_name = c_atk_action_get_name;
     iface->get_keybinding = c_atk_action_get_keybinding;
     iface->get_localized_name = c_atk_action_get_localized_name;
 }

 static void
 c_atk_action_finalize (GObject *object)
 {
 	g_return_if_fail (C_IS_ATK_ACTION(object));
  CAtkActionPrivate *priv = c_atk_action_get_instance_private(C_ATK_ACTION(object));
  if (priv->accessibleActions)
	{
	  g_list_free (priv->accessibleActions);
	  priv->accessibleActions = NULL;
	}

 	G_OBJECT_CLASS (c_atk_action_parent_class)->finalize (object);
 }

 static void
 c_atk_action_class_init (CAtkActionClass *klass)
 {
   GObjectClass *object_class = G_OBJECT_CLASS (klass);
   object_class->finalize = c_atk_action_finalize;
 }

 void c_atk_action_add_action(CAtkAction *self, RealAction *action)
 {
   CAtkActionPrivate *priv = c_atk_action_get_instance_private(self);
   priv->accessibleActions = g_list_append (priv->accessibleActions, action);
 }

 void c_atk_action_remove_action(CAtkAction *self, RealAction *action)
 {
   CAtkActionPrivate *priv = c_atk_action_get_instance_private(self);
   priv->accessibleActions = g_list_remove (priv->accessibleActions, action);
 }

 void c_atk_action_set_name(CAtkAction *self, RealAction *action, gchar *name)
 {
   CAtkActionPrivate *priv = c_atk_action_get_instance_private(self);
   GList *data = g_list_find(priv->accessibleActions, action);
   RealAction *realaction = (RealAction*) data->data;
   g_return_if_fail (realaction);
   g_free((void*)realaction->name);
   realaction->name = name;
 }
 void c_atk_action_set_keybinding(CAtkAction *self, RealAction *action, gchar *keybinding)
 {
   CAtkActionPrivate *priv = c_atk_action_get_instance_private(self);
   GList *data = g_list_find(priv->accessibleActions, action);
   RealAction *realaction = (RealAction*) data->data;
   g_return_if_fail (realaction);
   g_free((void*)realaction->keybinding);
   realaction->keybinding = keybinding;
 }

 void c_atk_action_set_localized_name(CAtkAction *self, RealAction *action, gchar *localizedname)
 {
   CAtkActionPrivate *priv = c_atk_action_get_instance_private(self);
   GList *data = g_list_find(priv->accessibleActions, action);
   RealAction *realaction = (RealAction*) data->data;
   g_return_if_fail (realaction);
   g_free((void*)realaction->localizedname);
   realaction->localizedname = localizedname;
 }

 static void
 c_atk_action_init (CAtkAction *self)
 {
     CAtkActionPrivate *priv = c_atk_action_get_instance_private(self);
     priv->accessibleActions = NULL;
 }
