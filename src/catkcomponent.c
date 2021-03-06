/*
 * demo_component.c
 *
 *  Created on: Apr 25, 2019
 *      Author: giuseppe
 */
#include <stdio.h>
#include <gmodule.h>
#include "catkcomponent.h"

#define C_ATK_COMPONENT_GET_PRIVATE(o) (c_atk_component_get_istance_private (o))

typedef struct
{
    AtkRectangle *rectangle;
    AtkCoordType coord_type;
    AtkLayer layer;
} CAtkComponentPrivate;

static void c_atk_component_atk_component_init (AtkComponentIface *iface);

G_DEFINE_ABSTRACT_TYPE_WITH_CODE (CAtkComponent, c_atk_component, C_TYPE_ATK_ACTOR, { G_ADD_PRIVATE (CAtkComponent); G_IMPLEMENT_INTERFACE (atk_component_get_type(), c_atk_component_atk_component_init); })

static void
c_atk_component_get_extents (AtkComponent *component, gint *x, gint *y, gint *width, gint *height, AtkCoordType coord_type)
{
    CAtkComponentPrivate *priv = c_atk_component_get_instance_private(C_ATK_COMPONENT(component));
    *x = priv->rectangle->x;
    *y = priv->rectangle->y;
    *width = priv->rectangle->width;
    *height = priv->rectangle->height;
    coord_type = priv->coord_type;
}

static AtkLayer
c_atk_component_get_layer(AtkComponent *component)
{
    CAtkComponentPrivate *priv = c_atk_component_get_instance_private(C_ATK_COMPONENT(component));
    return priv->layer;
}

static void
c_atk_component_atk_component_init (AtkComponentIface *iface)
{
    iface->get_extents = c_atk_component_get_extents;
    iface->get_layer = c_atk_component_get_layer;
}

void
c_atk_component_set_layer (CAtkComponent *self, AtkLayer layer)
{
    CAtkComponentPrivate *priv = c_atk_component_get_instance_private(self);
    priv->layer = layer;
}

void
c_atk_component_set_bound (CAtkComponent *self, gint x, gint y, gint width, gint height)
{
  CAtkComponentPrivate *priv = c_atk_component_get_instance_private(self);
  priv->rectangle->x = x;
  priv->rectangle->y = y;
  priv->rectangle->width = width;
  priv->rectangle->height = height;
}

void
c_atk_component_set_coord_type(CAtkComponent *self, AtkCoordType coord_type)
{
    CAtkComponentPrivate *priv = c_atk_component_get_instance_private(self);
    priv->coord_type = coord_type;
}


static void
c_atk_component_finalize (GObject *object)
{
	g_return_if_fail (C_IS_ATK_COMPONENT(object));

	G_OBJECT_CLASS (c_atk_component_parent_class)->finalize (object);
}

static void
c_atk_component_class_init (CAtkComponentClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = c_atk_component_finalize;
}

static void
c_atk_component_init (CAtkComponent *self)
{
    CAtkComponentPrivate *priv = c_atk_component_get_instance_private(self);
    priv->rectangle = g_new0 ( AtkRectangle, 1 );
    priv->layer = ATK_LAYER_INVALID;
}
