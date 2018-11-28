===================================================================================
FogLAMP "expression" C++ South plugin
===================================================================================

Simulates a sensor using an arbitrary expression that can be supplied
via a configuration option., The plugin uses the C++ Mathematical Expression Toolkit Library
by Arash Partow and is used under the MIT licence granted on that toolkit.

See http://www.partow.net/programming/exprtk/index.html

The plugin only allows single variable expression, with a controlling variable
called x that is set between defined minimum and maximum values using a step
value. All of these are configured via configuratin parameters.

The ExprTk library has the following capabilities:

- Mathematical operators (+, -, \*, /, %, ^)

- Functions (min, max, avg, sum, abs, ceil, floor, round, roundn, exp, log, log10, logn, pow, root, sqrt, clamp, inrange, swap)

- Trigonometry (sin, cos, tan, acos, asin, atan, atan2, cosh, cot, csc, sec, sinh, tanh, d2r, r2d, d2g, g2d, hyp)

Build
-----
To build FogLAMP Expression C++ South plugin:

.. code-block:: console

  $ mkdir build
  $ cd build
  $ cmake ..

- By default the FogLAMP develop package header files and libraries
  are expected to be located in /usr/include/foglamp and /usr/lib/foglamp
- If **FOGLAMP_ROOT** env var is set and no -D options are set,
  the header files and libraries paths are pulled from the ones under the
  FOGLAMP_ROOT directory.
  Please note that you must first run 'make' in the FOGLAMP_ROOT directory.

You may also pass one or more of the following options to cmake to override
this default behaviour:

- **FOGLAMP_SRC** sets the path of a FogLAMP source tree
- **FOGLAMP_INCLUDE** sets the path to FogLAMP header files
- **FOGLAMP_LIB sets** the path to FogLAMP libraries
- **FOGLAMP_INSTALL** sets the installation path of Expression plugin

NOTE:
 - The **FOGLAMP_INCLUDE** option should point to a location where all the FogLAMP
   header files have been installed in a single directory.
 - The **FOGLAMP_LIB** option should point to a location where all the FogLAMP
   libraries have been installed in a single directory.
 - 'make install' target is defined only when **FOGLAMP_INSTALL** is set

Examples:

- no options

  $ cmake ..

- no options and FOGLAMP_ROOT set

  $ export FOGLAMP_ROOT=/some_foglamp_setup

  $ cmake ..

- set FOGLAMP_SRC

  $ cmake -DFOGLAMP_SRC=/home/source/develop/FogLAMP  ..

- set FOGLAMP_INCLUDE

  $ cmake -DFOGLAMP_INCLUDE=/dev-package/include ..
- set FOGLAMP_LIB

  $ cmake -DFOGLAMP_LIB=/home/dev/package/lib ..
- set FOGLAMP_INSTALL

  $ cmake -DFOGLAMP_INSTALL=/home/source/develop/FogLAMP ..

  $ cmake -DFOGLAMP_INSTALL=/usr/local/foglamp ..

********************************
Packaging for 'Expression' south
********************************

This repo contains the scripts used to create a foglamp-south-expression Debian package.

The make_deb script
===================

Run the make_deb command after compiling the plugin:

.. code-block:: console

  $ ./make_deb help
  make_deb {x86|arm} [help|clean|cleanall]
  This script is used to create the Debian package of FoglAMP C++ 'expression' south plugin
  Arguments:
   help     - Display this help text
   x86      - Build an x86_64 package
   arm      - Build an armv7l package
   clean    - Remove all the old versions saved in format .XXXX
   cleanall - Remove all the versions, including the last one
  $

Building a Package
==================

Finally, run the ``make_deb`` command:

.. code-block:: console

   $ ./make_deb
   The package root directory is   : /home/ubuntu/source/foglamp-south-expression
   The FogLAMP required version    : >=1.4
   The package will be built in    : /home/ubuntu/source/foglamp-south-expression/packages/build
   The architecture is set as      : x86_64
   The package name is             : foglamp-south-expression-1.0.0-x86_64

   Populating the package and updating version file...Done.
   Building the new package...
   dpkg-deb: building package 'foglamp-south-expression' in 'foglamp-south-expression-1.0.0-x86_64.deb'.
   Building Complete.
   $

Cleaning the Package Folder
===========================

Use the ``clean`` option to remove all the old packages and the files used to make the package.

Use the ``cleanall`` option to remove all the packages and the files used to make the package.
