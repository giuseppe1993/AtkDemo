/*
 * catkroot.c
 *
 *  Created on: Mar 29, 2019
 *      Author: giuseppe
 */

#include <gmodule.h>
#include "catkroot.h"

#define C_ATK_ROOT_GET_PRIVATE(o) (c_atk_root_get_istance_private (o))

typedef struct
{
  gint pad1;

} CAtkRootPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (CAtkRoot, c_atk_root, C_TYPE_ATK_ACTOR)

CAtkRoot *
c_atk_root_new (void)
{
   CAtkRoot *root = g_object_new (C_TYPE_ATK_ROOT, NULL);
   atk_object_initialize (ATK_OBJECT(root), NULL);
   return root;
}

static void
c_atk_root_initialize (AtkObject *self, gpointer null)
{
}

static void
c_atk_root_finalize (GObject *object)
{
	g_return_if_fail (C_IS_ATK_ROOT(object));
  G_OBJECT_CLASS (c_atk_root_parent_class)->finalize (object);
}

static void
c_atk_root_class_init (CAtkRootClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  AtkObjectClass *atk_class=ATK_OBJECT_CLASS(klass);

  atk_class->initialize = c_atk_root_initialize;

  object_class->finalize = c_atk_root_finalize;
}

static void
c_atk_root_init (CAtkRoot *self)
{
  atk_object_set_role(ATK_OBJECT(self), ATK_ROLE_APPLICATION);
	atk_object_set_parent(ATK_OBJECT(self), NULL);
  c_atk_actor_set_name(C_ATK_ACTOR(self),"Atk Root");
  c_atk_actor_set_description(C_ATK_ACTOR(self),"this is the description of the root component");
}
