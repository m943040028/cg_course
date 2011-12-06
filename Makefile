# Simple Makefile for 6.837 raycasting assignment
# for g++ on linux platforms

# ===============================================================

SRCS 	 	= main.C \
		  matrix.C \
		  image.C \
		  scene_parser.C \
		  sphere.C \
		  triangle.C \
		  plane.C \
		  transform.C \
		  raytracer.C \
		  camera.C \
		  group.C \
		  diffuse.C \
		  normal.C

# ===============================================================

LIBS            = -lm -L/usr/X11R6/lib
CC		= g++
EXE	  	= raytracer
OBJS =  $(SRCS:.C=.o)

# ===============================================================
# targets

.PHONY: all depend clean

all: depend $(EXE)

depend:
	$(CC) -E -M $(SRCS) > Makefile.depend

clean: 
	-rm -f *~ *bak *.o  core.* Makefile.depend $(EXE) 

# ===============================================================
# compilation rules

$(EXE): $(OBJS)
	$(CC) -g -o $@ $(OBJS) $(LIBS)

.C.o:
	$(CC) $< -g -c -o $@

.cpp.o:
	$(CC) $< -g -c -o $@

# ===============================================================

-include Makefile.depend

