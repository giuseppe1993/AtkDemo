/*
 * demo_component.c
 *
 *  Created on: Apr 14, 2019
 *      Author: giuseppe
 */
#include <stdio.h>
#include <gmodule.h>
#include "demo_component.h"

#define C_ATK_COMPONENT_GET_PRIVATE(o) (c_atk_component_get_istance_private (o))

typedef struct
{
    gint *x,
    gint *y,
    gint *width,
    gint *height,
    AtkCoordType coord_type,
    AtkLayer layer

} CAtkComponentPrivate;


G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE (CAtkComponent, c_atk_component, ATK_TYPE_OBJECT)

static void 
c_atk_component_get_extents (AtkComponent *component, gint *x, gint *y, gint *width, gint *height, AtkCoordType coord_type)
{
    CAtkComponentPrivate *priv = c_atk_component_get_instance_private(component);
    x = priv->x;
    y = priv->y;
    width = priv->width;
    height = priv->height;
    coord_type = priv->coord_type;
}

AtkLayer 
c_atk_component_get_layer(AtkComponent *component)
{
    CAtkComponentPrivate *priv = c_atk_component_get_instance_private(component);
    return priv->layer;
}

static void
c_atk_component_finalize (GObject *object)
{
	CAtkComponent *component = C_ATK_COMPONENT(object);

	g_return_if_fail (C_IS_ATK_COMPONENT(object));

	G_OBJECT_CLASS (c_atk_component_parent_class)->finalize (object);
}

static void
c_atk_component_class_init (CAtkComponentClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  AtkObjectClass *atk_class = ATK_OBJECT_CLASS (klass);

  atk_class->get_extents = c_atk_component_get_extents;
  atk_class->get_layer = c_atk_component_get_layer;

  object_class->finalize = c_atk_component_finalize;
}

static void
c_atk_component_init (CAtkComponent *self)
{
    priv->x = 0;
    priv->y = 0;
    priv->width = 0;
    priv->height = 0;
    priv->coord_type = ATK_XY_SCREEN;
    priv->layer = ATK_LAYER_INVALID;
}
