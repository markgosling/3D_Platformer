EXTRA_DIST = GameWorld.h GameAssetManager.h GameAsset.h CubeAsset.h PyramidAsset.h Camera.h BoundingBox.h

bin_PROGRAMS = 3dplatformer
3dplatformer_SOURCES = main.cc
3dplatformer_LDADD = lib3dplatformer.la

lib_LTLIBRARIES = lib3dplatformer.la
lib3dplatformer_la_SOURCES = GameWorld.cc GameAssetManager.cc CubeAsset.cc PyramidAsset.cc Camera.cc GameAsset.cc BoundingBox.cc
lib3dplatformer_la_LDFLAGS = -version-info 0:1

AM_CPPFLAGS = -DGL_GLEXT_PROTOTYPES -DGL3_PROTOTYPES
AM_CPPFLAGS += -std=c++11
AM_CPPFLAGS += $(gl_CFLAGS) $(glew_CFLAGS) $(sdl2_CFLAGS) $(BOOST_CPPFLAGS)
AM_CPPFLAGS += -I /usr/include/python2.7

#new code adapted from example at http://nuclear.mutantstargoat.com/articles/make/#a-makefile-for-99-of-your-programs for osx builds
LDFLAGS = -framework OpenGL -framework GLUT -lpython2.7 -lboost_python
####end of new code

LIBS += $(gl_LIBS) $(glew_LIBS) $(sdl2_LIBS) $(BOOST_THREAD_LIBS) $(BOOST_PROGRAM_OPTIONS_LIBS)
