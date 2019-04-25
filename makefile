CFLAGS = `pkg-config --cflags glib-2.0 atk atk-bridge-2.0`
LIBS = `pkg-config --libs glib-2.0 atk atk-bridge-2.0`

all: Demo	

Demo: demo.a
	gcc $(CFLAGS) -o demo demo.c demo.a $(LIBS) -Wall -g3 -O0 -ggdb3

demo.a: demo_actor.o demo_component.o demo_root.o demo_window.o demo_frame.o demo_root_pane.o demo_layered_pane.o demo_panel.o
	ar rvs demo.a demo_actor.o demo_component.o demo_root.o demo_window.o demo_frame.o demo_root_pane.o demo_layered_pane.o demo_panel.o

demo_actor.o: demo_actor.h demo_actor.c
	gcc $(CFLAGS) -c demo_actor.c $(LIBS) -Wall -g3 -O0 -ggdb3

demo_component.o: demo_component.h demo_component.c
	gcc $(CFLAGS) -c demo_component.c $(LIBS) -Wall -g3 -O0 -ggdb3

demo_root.o: demo_root.h demo_root.c
	gcc $(CFLAGS) -c demo_root.c $(LIBS) -Wall -g3 -O0 -ggdb3
	
demo_root_pane.o: demo_root_pane.h demo_root_pane.c
	gcc $(CFLAGS) -c demo_root_pane.c $(LIBS) -Wall -g3 -O0 -ggdb3
	
demo_frame.o: demo_frame.h demo_frame.c
	gcc $(CFLAGS) -c demo_frame.c $(LIBS) -Wall -g3 -O0 -ggdb3

demo_layered_pane.o: demo_layered_pane.h demo_layered_pane.c
	gcc $(CFLAGS) -c demo_layered_pane.c $(LIBS) -Wall -g3 -O0 -ggdb3

demo_panel.o: demo_panel.h demo_panel.c
	gcc $(CFLAGS) -c demo_panel.c $(LIBS) -Wall -g3 -O0 -ggdb3
	
demo_window.o: demo_window.h demo_window.c
	gcc $(CFLAGS) -c demo_window.c $(LIBS) -Wall -g3 -O0 -ggdb3	
	
clean:
	rm -fr demo *.o *.a
	
