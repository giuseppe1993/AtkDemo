/*
 * demo_frame.c
 *
 *  Created on: Apr 10, 2019
 *      Author: giuseppe
 */
#include <gmodule.h>
#include "catkframe.h"

#define C_ATK_FRAME_GET_PRIVATE(o) (c_atk_frame_get_istance_private (o))

typedef struct
{
	gint pad1;

} CAtkFramePrivate;

G_DEFINE_TYPE_WITH_PRIVATE (CAtkFrame, c_atk_frame, C_TYPE_ATK_COMPONENT)

CAtkFrame *
c_atk_frame_new (void)
{
   CAtkFrame *frame = g_object_new (C_TYPE_ATK_FRAME, NULL);

   atk_object_initialize(ATK_OBJECT(frame), NULL);

   return frame;
}

static void
c_atk_frame_initialize (AtkObject *self, gpointer null)
{
}

static void
c_atk_frame_finalize (GObject *object)
{
	g_return_if_fail (C_IS_ATK_FRAME(object));

	G_OBJECT_CLASS (c_atk_frame_parent_class)->finalize (object);
}

static void
c_atk_frame_class_init (CAtkFrameClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  AtkObjectClass *atk_class = ATK_OBJECT_CLASS (klass);

  atk_class->initialize = c_atk_frame_initialize;

  object_class->finalize = c_atk_frame_finalize;
}

static void
c_atk_frame_init (CAtkFrame *self)
{
	atk_object_set_role (ATK_OBJECT(self), ATK_ROLE_FRAME);
	atk_object_set_parent (ATK_OBJECT(self), NULL);
	c_atk_actor_set_name(C_ATK_ACTOR(self),"Atk Frame");
  c_atk_actor_set_description(C_ATK_ACTOR(self),"this is the description of the frame component");
	c_atk_component_set_layer (C_ATK_COMPONENT(self), ATK_LAYER_WINDOW);
	c_atk_component_set_coord_type (C_ATK_COMPONENT(self), ATK_XY_SCREEN);
}
