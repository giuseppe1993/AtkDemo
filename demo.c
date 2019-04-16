/*
 * AtkDemo.c
 *
 *  Created on: Mar 21, 2019
 *      Author: giuseppe
 */
#include <stdio.h>
#include <stdlib.h>
#include <atk/atk.h>
#include <atk-bridge.h>
#include "myAtk.h"

static CAtkActor *root = NULL;
static CAtkActor *frame = NULL;
static CAtkActor *root_pane = NULL;
static CAtkActor *layered_pane = NULL;
static CAtkActor *panel = NULL;
//static CAtkWindow *window = NULL;
static GMainLoop *mainloop;

static AtkObject *
get_root (void)
{
	if (!root)
		root = C_ATK_ACTOR(c_atk_root_new ());

	return ATK_OBJECT(root);
}

const gchar *
get_toolkit_name (void)
{
  return strdup ("Atk Util Demo");
}

static void
setup_atk_util (void)
{
  AtkUtilClass *klass;

  klass = g_type_class_ref (ATK_TYPE_UTIL);
  klass->get_root = get_root;
  klass->get_toolkit_name = get_toolkit_name;
  g_type_class_unref (klass);
}

static void
add_atk_frame(void){
	if (root && !frame)
	{
		frame = C_ATK_ACTOR(c_atk_frame_new());
		c_atk_actor_add_child(root, ATK_OBJECT(frame));
		//interrogation of java object
		c_atk_actor_add_state ( frame, ATK_STATE_ENABLED);
		c_atk_actor_add_state ( frame, ATK_STATE_FOCUSABLE);
		c_atk_actor_add_state ( frame, ATK_STATE_VISIBLE);
		c_atk_actor_add_state ( frame, ATK_STATE_SHOWING);
		c_atk_actor_add_state ( frame, ATK_STATE_RESIZABLE);

		c_atk_actor_add_attribute( frame, "name", "demo" );
	}
}

static CAtkActor*
create_atk_child_for_role(AtkRole role)
{
	switch (role)
	{
	case ATK_ROLE_ROOT_PANE:
		return C_ATK_ACTOR(c_atk_root_pane_new());		
	case ATK_ROLE_PANEL:
		return C_ATK_ACTOR(c_atk_panel_new());
	case ATK_ROLE_LAYERED_PANE:
		return C_ATK_ACTOR(c_atk_layered_pane_new());
	
	default:
		g_assert_not_reached();
		return NULL;
	}
}

int main(int argc, char **argv) {

	setup_atk_util();

	int init_outcome = atk_bridge_adaptor_init (&argc, &argv);

	if(init_outcome == 0){
		printf ("Initialized\n");
		add_atk_frame();
		root_pane = create_atk_child_for_role(ATK_ROLE_ROOT_PANE);
		atk_object_set_parent(ATK_OBJECT(root_pane),ATK_OBJECT(frame));
		panel = create_atk_child_for_role(ATK_ROLE_PANEL);
		atk_object_set_parent(ATK_OBJECT(panel),ATK_OBJECT(root_pane));
		layered_pane = create_atk_child_for_role(ATK_ROLE_LAYERED_PANE);
		atk_object_set_parent(ATK_OBJECT(layered_pane),ATK_OBJECT(root_pane));
	}
	else
		printf ("Not Initialized\n");

	mainloop = g_main_loop_new (NULL, FALSE);
	g_main_loop_run (mainloop);

	atk_bridge_adaptor_cleanup();
	//g_object_unref(window);
	g_object_unref(panel);
	g_object_unref(layered_pane);
	g_object_unref(root_pane);
	g_object_unref(frame);
	g_object_unref(root);

	return 0;

}
