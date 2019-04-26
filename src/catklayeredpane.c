/*
 * demo_layered_pane.c
 *
 *  Created on: Apr 16, 2019
 *      Author: giuseppe
 */
#include <gmodule.h>
#include "catklayeredpane.h"

#define C_ATK_LAYERED_PANE_GET_PRIVATE(o) (c_atk_layered_pane_get_istance_private (o))

typedef struct
{
	gint pad1;

} CAtkLayeredPanePrivate;

G_DEFINE_TYPE_WITH_PRIVATE (CAtkLayeredPane, c_atk_layered_pane, C_TYPE_ATK_ACTOR)

CAtkLayeredPane *
c_atk_layered_pane_new (void)
{
   CAtkLayeredPane *layered_pane = g_object_new (C_TYPE_ATK_LAYERED_PANE, NULL);

   atk_object_initialize(ATK_OBJECT(layered_pane), NULL);

   return layered_pane;
}

static const char*
c_atk_layered_pane_get_name (AtkObject *obj)
{
   return "Atk Layered Pane";
}

static const char*
c_atk_layered_pane_get_description()
{
	return "this is the description of the layered pane component";
}

static void
c_atk_layered_pane_initialize (AtkObject *self, gpointer null)
{
}

static void
c_atk_layered_pane_finalize (GObject *object)
{
	g_return_if_fail (C_IS_ATK_LAYERED_PANE(object));

	G_OBJECT_CLASS (c_atk_layered_pane_parent_class)->finalize (object);
}

static void
c_atk_layered_pane_class_init (CAtkLayeredPaneClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  AtkObjectClass *atk_class = ATK_OBJECT_CLASS (klass);

  atk_class->initialize = c_atk_layered_pane_initialize;
  atk_class->get_name = c_atk_layered_pane_get_name;
  atk_class->get_description = c_atk_layered_pane_get_description;

  object_class->finalize = c_atk_layered_pane_finalize;
}

static void
c_atk_layered_pane_init (CAtkLayeredPane *self)
{
   atk_object_set_role(ATK_OBJECT(self),ATK_ROLE_LAYERED_PANE);

	atk_object_set_parent(ATK_OBJECT(self),NULL);
}
