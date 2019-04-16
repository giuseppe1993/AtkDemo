/*
 * demo_panel.h
 *
 *  Created on: Apr 16, 2019
 *      Author: giuseppe
 */

#ifndef DEMO_PANEL_H_
#define DEMO_PANEL_H_

#include <atk/atk.h>
#include "demo_actor.h"

G_BEGIN_DECLS

#define C_TYPE_ATK_PANEL            (c_atk_panel_get_type ())

G_DECLARE_DERIVABLE_TYPE(CAtkPanel, c_atk_panel, C, ATK_PANEL, CAtkActor)

struct _CAtkPanelClass
{
  CAtkActorClass parent_class;
};

CAtkPanel *c_atk_panel_new (void);

G_END_DECLS

#endif /* DEMO_PANEL_H_ */
