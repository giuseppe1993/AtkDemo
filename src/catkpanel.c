/*
 * demo_panel.c
 *
 *  Created on: Apr 16, 2019
 *      Author: giuseppe
 */
#include <gmodule.h>
#include "catkpanel.h"

#define C_ATK_PANEL_GET_PRIVATE(o) (c_atk_panel_get_istance_private (o))

typedef struct
{
	gint pad1;

} CAtkPanelPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (CAtkPanel, c_atk_panel, C_TYPE_ATK_ACTOR)

CAtkPanel *
c_atk_panel_new (void)
{
   CAtkPanel *panel = g_object_new (C_TYPE_ATK_PANEL, NULL);

   atk_object_initialize(ATK_OBJECT(panel), NULL);

   return panel;
}

static const char*
c_atk_panel_get_name (AtkObject *obj)
{
   return "Atk Panel";
}

static const char*
c_atk_panel_get_description()
{
	return "this is the description of the panel component";
}

static void
c_atk_panel_initialize (AtkObject *self, gpointer null)
{
}

static void
c_atk_panel_finalize (GObject *object)
{
	g_return_if_fail (C_IS_ATK_PANEL(object));

	G_OBJECT_CLASS (c_atk_panel_parent_class)->finalize (object);
}

static void
c_atk_panel_class_init (CAtkPanelClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  AtkObjectClass *atk_class = ATK_OBJECT_CLASS (klass);

  atk_class->initialize = c_atk_panel_initialize;
  atk_class->get_name = c_atk_panel_get_name;
  atk_class->get_description = c_atk_panel_get_description;

  object_class->finalize = c_atk_panel_finalize;
}

static void
c_atk_panel_init (CAtkPanel *self)
{
   atk_object_set_role(ATK_OBJECT(self),ATK_ROLE_PANEL);

	atk_object_set_parent(ATK_OBJECT(self),NULL);
}
