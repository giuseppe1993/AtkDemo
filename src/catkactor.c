/*
 * demo_actor.c
 *
 *  Created on: Apr 14, 2019
 *      Author: giuseppe
 */
#include <stdio.h>
#include <gmodule.h>
#include "catkactor.h"

#define C_ATK_ACTOR_GET_PRIVATE(o) (c_atk_actor_get_istance_private (o))

typedef struct
{
	GList *accessibleObjects;
	const char *name;
	const char *description;
	AtkStateSet *states;
	AtkRelationSet *relations;
	AtkAttributeSet *attributes;
} CAtkActorPrivate;

G_DEFINE_ABSTRACT_TYPE_WITH_PRIVATE (CAtkActor, c_atk_actor, ATK_TYPE_OBJECT)

void
c_atk_actor_add_child(CAtkActor *actor, AtkObject *obj)
{
	CAtkActorPrivate *priv = c_atk_actor_get_instance_private(actor);
	gint index = -1;

	atk_object_set_parent (obj, ATK_OBJECT (actor));
	priv->accessibleObjects = g_list_append (priv->accessibleObjects, obj);
	index = g_list_index (priv->accessibleObjects, obj);
	g_signal_emit_by_name (actor, "children-changed::add", index, obj, NULL);
}

void
c_atk_actor_remove_child(CAtkActor *actor, AtkObject *obj)
{
	CAtkActorPrivate *priv = c_atk_actor_get_instance_private(actor);
	gint index = -1;

	index = g_list_index (priv->accessibleObjects, obj);
	priv->accessibleObjects = g_list_remove (priv->accessibleObjects, obj);
	if (index != -1)
		g_signal_emit_by_name (actor, "children-changed::remove", index, obj, NULL);
}

void
c_atk_actor_add_state(CAtkActor *actor, AtkStateType state)
{
	CAtkActorPrivate *priv = c_atk_actor_get_instance_private (actor);
	atk_state_set_add_state(priv->states, state);
	atk_object_notify_state_change( ATK_OBJECT(actor), state, TRUE);
}

void c_atk_actor_remove_state(CAtkActor *actor, AtkStateType state)
{
	CAtkActorPrivate *priv = c_atk_actor_get_instance_private (actor);
	atk_state_set_remove_state(priv->states, state);

	atk_object_notify_state_change( ATK_OBJECT(actor), state, FALSE);
}

static AtkRelationSet*
c_atk_actor_ref_relation_set(AtkObject *obj)
{
	CAtkActorPrivate *priv = c_atk_actor_get_instance_private(C_ATK_ACTOR(obj));
	return g_object_ref(priv->relations);
}

static AtkStateSet*
c_atk_actor_ref_state_set(AtkObject *obj)
{
	CAtkActorPrivate *priv = c_atk_actor_get_instance_private(C_ATK_ACTOR(obj));
	return g_object_ref(priv->states);
}

static gint
c_atk_actor_get_n_children (AtkObject *obj)
{
  CAtkActorPrivate *priv = c_atk_actor_get_instance_private(C_ATK_ACTOR(obj));
  return g_list_length (priv->accessibleObjects);
}

static AtkObject*
c_atk_actor_ref_child (AtkObject *obj, gint i)
{
  GList *obj_list = NULL;
  gint num = 0;
  AtkObject *item = NULL;

  CAtkActorPrivate *priv = c_atk_actor_get_instance_private(C_ATK_ACTOR(obj));

  obj_list = priv->accessibleObjects;

  num = g_list_length (obj_list);

  g_return_val_if_fail ((i < num)&&(i >= 0), NULL);

  item = g_list_nth_data (obj_list, i);
  if (!item)
      return NULL;

  g_object_ref (item);

  return item;
}

void c_atk_actor_set_name(CAtkActor *actor, const char *name)
{
	CAtkActorPrivate *priv = c_atk_actor_get_instance_private(actor);
	AtkPropertyValues *signalstuff = g_new0(AtkPropertyValues, 1);
	GValue *old_value = g_new0 (GValue, 1);
	GValue *new_value = g_new0 (GValue, 1);
	g_value_init (old_value, G_TYPE_STRING);
	g_value_init (new_value, G_TYPE_STRING);
	g_value_set_string (old_value, priv->name);
	g_value_set_string (new_value, name);
	signalstuff->property_name = "accessible-name";
	signalstuff->old_value = *old_value;
	signalstuff->new_value = *new_value;
	priv->name = name;
	g_signal_emit_by_name (actor, "property-change", signalstuff, NULL);
}

static const char*
c_atk_actor_get_name(AtkObject *obj)
{
	g_return_val_if_fail (C_IS_ATK_ACTOR(obj), NULL);
	CAtkActorPrivate *priv = c_atk_actor_get_instance_private(C_ATK_ACTOR(obj));
	return strdup(priv->name);
}

void c_atk_actor_set_description(CAtkActor *actor, const char *description)
{
	CAtkActorPrivate *priv = c_atk_actor_get_instance_private(actor);
	AtkPropertyValues *signalstuff = g_new0(AtkPropertyValues, 1);
	GValue *old_value = g_new0 (GValue, 1);
	GValue *new_value = g_new0 (GValue, 1);
	g_value_init (old_value, G_TYPE_STRING);
	g_value_init (new_value, G_TYPE_STRING);
	g_value_set_string (old_value, priv->name);
	g_value_set_string (new_value, description);
	signalstuff->property_name = "accessible-name";
	signalstuff->old_value = *old_value;
	signalstuff->new_value = *new_value;
	priv->description = description;
	g_signal_emit_by_name (actor, "property-change", signalstuff, NULL);
}

static const char*
c_atk_actor_get_description(AtkObject *obj)
{
	g_return_val_if_fail (C_IS_ATK_ACTOR(obj), NULL);
	CAtkActorPrivate *priv = c_atk_actor_get_instance_private(C_ATK_ACTOR(obj));
	return strdup(priv->description);
}

static void*
copy_attribute(const void *origin, gpointer null)
{
	AtkAttribute *attribute = (AtkAttribute *) origin;
	AtkAttribute *copy = g_new0 ( AtkAttribute, 1 );

	copy->name = g_strdup (attribute->name);
	copy->value = g_strdup (attribute -> value);

	return copy;
}

static AtkAttributeSet*
c_atk_actor_get_attributes(AtkObject *obj)
{
	AtkAttributeSet *atr_list = NULL;
	int num = 0;

	CAtkActorPrivate *priv = c_atk_actor_get_instance_private(C_ATK_ACTOR(obj));
	num = g_slist_length (priv->attributes);

	if (!num)
	  return NULL;

	atr_list = (AtkAttributeSet *) g_list_copy_deep( (GList *) priv->attributes, copy_attribute, NULL);

	return atr_list;
}

void c_atk_actor_add_attribute (CAtkActor *actor, gchar *name, gchar *value)
{
	AtkAttribute *attribute = g_new0(AtkAttribute,1);
	attribute->name = name;
	attribute->value = value;
	CAtkActorPrivate *priv = c_atk_actor_get_instance_private(C_ATK_ACTOR(actor));
	if(!g_slist_find(priv->attributes, attribute))
		priv->attributes = g_slist_append(priv->attributes, attribute);

}

void c_atk_actor_remove_attribute (CAtkActor *actor, gchar *name, gchar *value)
{
	AtkAttribute *attribute = g_new0(AtkAttribute,1);
	attribute->name = name;
	attribute->value = value;
	CAtkActorPrivate *priv = c_atk_actor_get_instance_private(C_ATK_ACTOR(actor));
	if(!g_slist_find(priv->attributes, attribute))
		priv->attributes = g_slist_remove(priv->attributes, attribute);

}

AtkRelationSet* c_atk_actor_get_relation_set(CAtkActor *actor)
{
	CAtkActorPrivate *priv = c_atk_actor_get_instance_private(actor);
	return priv->relations;
}

void c_atk_actor_set_relation_set(CAtkActor *actor, AtkRelationSet* relations)
{
	CAtkActorPrivate *priv = c_atk_actor_get_instance_private(actor);
	g_free(priv->relations);
	priv->relations = relations;
}

static void
c_atk_actor_finalize (GObject *object)
{
	CAtkActor *actor = C_ATK_ACTOR(object);

	g_return_if_fail (C_IS_ATK_ACTOR(object));

	CAtkActorPrivate *priv = c_atk_actor_get_instance_private(actor);

	if (priv->accessibleObjects)
	{
	  g_list_free (priv->accessibleObjects);
	  priv->accessibleObjects = NULL;
	}

	atk_attribute_set_free(priv->attributes);
	g_free(priv->relations);

	g_clear_object(&priv->states);

	G_OBJECT_CLASS (c_atk_actor_parent_class)->finalize (object);
}


static void
c_atk_actor_class_init (CAtkActorClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  AtkObjectClass *atk_class = ATK_OBJECT_CLASS (klass);

  atk_class->get_n_children = c_atk_actor_get_n_children;
  atk_class->ref_child = c_atk_actor_ref_child;
	atk_class->get_name = c_atk_actor_get_name;
  atk_class->get_description = c_atk_actor_get_description;
  atk_class->ref_state_set = c_atk_actor_ref_state_set;
	atk_class->ref_relation_set = c_atk_actor_ref_relation_set;
  atk_class->get_attributes = c_atk_actor_get_attributes;

  object_class->finalize = c_atk_actor_finalize;
}

static void
c_atk_actor_init (CAtkActor *self)
{
	CAtkActorPrivate *priv = c_atk_actor_get_instance_private(self);
	priv->accessibleObjects = NULL;
	priv->states = atk_state_set_new();
	priv->relations = atk_relation_set_new();
	priv->attributes = NULL;
}
