|Build Status|

--------------

Rank Filter
===========

Motivation
----------

This package is designed to provide an efficient linear rank order
filter written in C++ with Python bindings. It can take single or double
precision floats as input. It was needed as the equivalent percentile
filter in SciPy was found to be too slow and unnecessarily general.
There was no equivalent in VIGRA.

Requirements
------------

In order to build this package, the following requirements are needed.

1. Python (only tested on 2.7.6)
2. Boost (requires 1.56 or later)
3. NumPy (only tested with 1.7.0)
4. VIGRA (only tested with a revision after release 1.10.0, commit
   `05cf09388e28ab9db49fda3763500f128445897d <https://github.com/ukoethe/vigra/commit/05cf09388e28ab9db49fda3763500f128445897d>`__
   )
5. Nose (optional for running test, tested with 1.2.1)

Building
--------

Building is done using CMake. This makes it flexible and easy to use on
different OSes. Also, it makes it easier to integrate with BuildEM (
https://github.com/janelia-flyem/buildem ), which also uses CMake.

Getting Started
~~~~~~~~~~~~~~~

To start simply clone the repo and change directory to the repo.

::

    git clone https://github.com/nanshe-org/rank_filter
    cd rank_filter

Configuring
~~~~~~~~~~~

To configure the following variables must be set ``BOOST_ROOT`` and
``VIGRA_ROOT``. In order to find Boost includes and libraries, the
directory Boost was installed to must be set as ``BOOST_ROOT``.
Similarly, in order to find VIGRA includes and libraries, the directory
VIGRA was installed to must be set as ``VIGRA_ROOT``.

The first way to set the variables is to set them in the environment.
This can be done as shown below. The benefit of using this technique is
that this is the standard technique used by ``make``. Thus, it can work
nicely with systems using ``make``. The downside is it is easy to forget
what is in your environment and it is difficult to know how other
programs will respond to them.

::

    export BOOST_ROOT=<path-to-Boost-root>
    export VIGRA_ROOT=<path-to-VIGRA-root>
    cmake .

The second way the variables can be set is by invoking ``cmake`` with
them, which can be seen below. Variables set by ``cmake`` arguments like
those shown below will always take precedence. As a result, if there are
environment variables, they will be ignored if they have been passed to
``cmake`` directly.

::

    cmake -DBOOST_ROOT=<path-to-Boost-root> -DVIGRA_ROOT=<path-to-VIGRA-root> .

Additionally, the preferred python interpreter can be set by using the
``PYTHON_EXECUTABLE`` variable. If ``PYTHON_EXECUTABLE`` is not
specified at all, the first python interpreter found on the path will be
used.

Checking
~~~~~~~~

Before building the Python bindings it is worth checking if the C++ code
passes its own test suite. This can be done using ``make`` with the
command below. It is not required to run this stage, but it will be run
every time when building. These test are no guarantee that the Python
module will work. All they verify is that the C++ code works.

::

    make check

Building
~~~~~~~~

Building is done easily using ``make``. This will create a shared object
in the slib directory, which can be imported by Python as a module. As
mentioned in the Checking section, the C++ tests will be run first. If
they fail, the Python module will not be built. They do not guarantee
that the Python module will work. Instead the testing stage can be used
to validate the module.

::

    make

Testing
~~~~~~~

Once the Python module is built, it is worth testing whether it works.
This can be done with ``make`` using the command below. Unlike the C++
tests, these are Python tests that use nose to run the tests. The tests
are the Python analogues of the ones used in C++ tests. They not only
verify that basic command run, but that they pass with correct results
only.

::

    make test

Installing
~~~~~~~~~~

After building and testing, it is time to install. Using ``make``, the
command below will install the module in the identified Python's
site-package folder allowing for importing this module using that
Python.

::

    make install

Cleaning
~~~~~~~~

There are a few additional options regarding cleaning. It is possible to
clean all build intermediates (including CMake generated files) leaving
only the final build products. This is done by calling as below.

::

    make distclean

If it is desirable to eliminate the build products as well as all
intermediates, then the call below can be used.

::

    make reset

.. |Build Status| image:: https://travis-ci.org/nanshe-org/rank_filter.svg?branch=master
   :target: https://travis-ci.org/nanshe-org/rank_filter
