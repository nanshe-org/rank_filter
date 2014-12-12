#Rank Filter

##Motivation

This package is designed to provide an efficient linear rank order filter written in C++ with Python bindings. It can take single or double precision floats as input. It was needed as the equivalent percentile filter in SciPy was found to be too slow and unnecessarily general. There was no equivalent in VIGRA.

##Requirements

In order to build this package, the following requirements are needed.

1. Python (only tested on 2.7.6)
2. Boost (requires 1.56 or later)
3. NumPy (only tested with 1.7.0)
4. VIGRA (only tested with a revision after release 1.10.0, commit [05cf09388e28ab9db49fda3763500f128445897d](https://github.com/ukoethe/vigra/commit/05cf09388e28ab9db49fda3763500f128445897d) )

##Building

Building is done using CMake. This makes it flexible and easy to use on different OSes. Also, it makes it easier to integrate with BuildEM ( <https://github.com/janelia-flyem/buildem> ), which also uses CMake.

###Getting Started

To start simply clone the repo and change directory to the repo.

	git clone https://github.com/jakirkham/rank_filter
	cd rank_filter

###Configuring

To configure the following variables must be set `BOOST_ROOT` and `VIGRA_ROOT`. In order to find Boost includes and libraries, the directory Boost was installed to must be set as `BOOST_ROOT`. Similarly, in order to find VIGRA includes and libraries, the directory VIGRA was installed to must be set as `VIGRA_ROOT`.

The first way to set the variables is to set them in the environment. This can be done as shown below. The benefit of using this technique is that this is the standard technique used by `make`. Thus, it can work nicely with systems using `make`. The downside is it is easy to forget what is in your environment and it is difficult to know how other programs will respond to them.

	export BOOST_ROOT=<path-to-Boost-root>
	export VIGRA_ROOT=<path-to-VIGRA-root>
	cmake .

The second way the variables can be set is by invoking `cmake` with them, which can be seen below. Variables set by `cmake` arguments like those shown below will always take precedence. As a result, if there are environment variables, they will be ignored if they have been passed to `cmake` directly.

	cmake -DBOOST_ROOT=<path-to-Boost-root> -DVIGRA_ROOT=<path-to-VIGRA-root> .
	
Additionally, the preferred python interpreter can be set by using the `PYTHON_EXECUTABLE` variable. If `PYTHON_EXECUTABLE` is not specified at all, the first python interpreter found on the path will be used.
	
###Building

Building is done easily using `make`. This will create a shared object in the slib directory, which can be imported by Python as a module.

	make

###Installing

Installing is also done easily using `make`. This will install the shared object in the identified Python's site-package folder allowing for importing this module using that Python.

	make install

###Cleaning

There are a few additional options regarding cleaning. It is possible to clean all build intermediates (including CMake generated files) leaving only the final build products. This is done by calling as below.

	make distclean

If it is desirable to eliminate the build products as well as all intermediates, then the call below can be used.

	make reset

##Notes

At present, the import order of rank_filter and vigra is not invariant. The causes of this is somewhat complicated ( <https://github.com/jakirkham/rank_filter/issues/3> ). It does not seem that this can be easily resolved at this point. However, as long as one is aware of this issue, it can be easily avoided. Simply follow the import order seen below.

	import rank_filter
	import vigra
