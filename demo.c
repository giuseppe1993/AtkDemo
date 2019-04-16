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
		c_atk_actor_add_state(frame, ATK_STATE_ENABLED);
		c_atk_actor_add_state(frame, ATK_STATE_FOCUSABLE);
		c_atk_actor_add_state(frame, ATK_STATE_VISIBLE);
		c_atk_actor_add_state(frame, ATK_STATE_SHOWING);
		c_atk_actor_add_state(frame, ATK_STATE_RESIZABLE);

		AtkAttribute *demo = g_new0(AtkAttribute,1);
		demo->name = "name";
		demo->value = "demo";
		c_atk_actor_add_attribute(frame, demo);
	}
}

static void
add_atk_child(CAtkActor *father, CAtkActor *child, AtkRole role){
	if (father && !child)
	{
		switch (role)
		{
		case ATK_ROLE_ROOT_PANE:
			printf("Ruolo root pane\n");
			child = C_ATK_ACTOR(c_atk_root_pane_new());
			printf("indirizzo di child = %p\n", child);
			printf("indirizzo di root_pane = %p\n", root_pane);
			break;
		case ATK_ROLE_PANEL:
			printf("Ruolo panel\n");
			child = C_ATK_ACTOR(c_atk_panel_new());
			break;
		case ATK_ROLE_LAYERED_PANE:
			printf("Ruolo layered pane\n");
			child = C_ATK_ACTOR(c_atk_layered_pane_new());
			break;		
		
		default:
			printf("Ruolo non riconosciuto\n");
		}
		if(child)
			c_atk_actor_add_child(father, ATK_OBJECT(child));
	}
	if(!father)
		printf("Padre non inizializzato\n");
}

int main(int argc, char **argv) {

	setup_atk_util();

	int init_outcome = atk_bridge_adaptor_init (&argc, &argv);

	if(init_outcome == 0){
		printf ("Initialized\n");
		add_atk_frame();
		add_atk_child(frame, root_pane, ATK_ROLE_ROOT_PANE);
		add_atk_child(root_pane, panel, ATK_ROLE_PANEL);
		add_atk_child(root_pane, layered_pane, ATK_ROLE_LAYERED_PANE);
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
