/*
 * demo_layered_pane.h
 *
 *  Created on: Apr 16, 2019
 *      Author: giuseppe
 */

#ifndef DEMO_LAYERED_PANE_H_
#define DEMO_LAYERED_PANE_H_

#include <atk/atk.h>
#include "demo_actor.h"

G_BEGIN_DECLS

#define C_TYPE_ATK_LAYERED_PANE            (c_atk_layered_pane_get_type ())

G_DECLARE_DERIVABLE_TYPE(CAtkLayeredPane, c_atk_layered_pane, C, ATK_LAYERED_PANE, CAtkActor)

struct _CAtkLayeredPaneClass
{
  CAtkActorClass parent_class;
};

CAtkLayeredPane *c_atk_layered_pane_new (void);

G_END_DECLS

#endif /* DEMO_LAYERED_PANE_H_ */
