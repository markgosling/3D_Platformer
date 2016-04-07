EXTRA_DIST = GameWorld.h GameAssetManager.h GameAsset.h CubeAsset.h PyramidAsset.h Camera.h BoundingBox.h

bin_PROGRAMS = shaderexample
shaderexample_SOURCES = main.cc GameWorld.cc GameAssetManager.cc CubeAsset.cc PyramidAsset.cc Camera.cc GameAsset.cc BoundingBox.cc

AM_CPPFLAGS = -DGL_GLEXT_PROTOTYPES -DGL3_PROTOTYPES
AM_CPPFLAGS += -std=c++11
AM_CPPFLAGS += $(gl_CFLAGS) $(glew_CFLAGS) $(sdl2_CFLAGS) $(BOOST_CPPFLAGS)

#new code adapted from example at http://nuclear.mutantstargoat.com/articles/make/#a-makefile-for-99-of-your-programs
LDFLAGS = -framework OpenGL -framework GLUT
####end of new code

LIBS += $(gl_LIBS) $(glew_LIBS) $(sdl2_LIBS) $(BOOST_THREAD_LIBS) $(BOOST_PROGRAM_OPTIONS_LIBS)
