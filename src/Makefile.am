EXTRA_DIST = GameWorld.h GameAssetManager.h GameAsset.h CubeAsset.h PyramidAsset.h Camera.h BoundingBox.h PythonBindings.h GameLoop.h

bin_PROGRAMS = 3dplatformer
3dplatformer_SOURCES = main.cc
3dplatformer_LDADD = ./.libs/lib3dplatformer.so

#Code to compile the game engine as a library along with the python bindings code.
lib_LTLIBRARIES = lib3dplatformer.la
lib3dplatformer_la_SOURCES = PythonBindings.cc CubeAsset.cc GameAsset.cc BoundingBox.cc GameAssetManager.cc PyramidAsset.cc Camera.cc GameWorld.cc GameLoop.cc

AM_CPPFLAGS = -DGL_GLEXT_PROTOTYPES -DGL3_PROTOTYPES
AM_CPPFLAGS += -std=c++11 -I/usr/include/python2.7
AM_CPPFLAGS += $(gl_CFLAGS) $(glew_CFLAGS) $(sdl2_CFLAGS) $(BOOST_CPPFLAGS)

#new open GL flags added based off discussion found at http://nuclear.mutantstargoat.com/articles/make/#a-makefile-for-99-of-your-programs for osx builds
LDFLAGS = -framework OpenGL -framework GLUT -lSDL2 -lboost_system -lboost_python -lpython2.7 -Wl,-rpath,'$$ORIGIN/.libs'

LIBS += $(gl_LIBS) $(glew_LIBS) $(sdl2_LIBS) $(BOOST_THREAD_LIBS) $(BOOST_PROGRAM_OPTIONS_LIBS)
