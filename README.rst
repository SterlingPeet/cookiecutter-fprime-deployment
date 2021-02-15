===============================
Cookiecutter: F Prime Component
===============================

**WARNING:** The template is currently intended to support ATmega specific deployments, so if that is not your goal, the results may be somewhat unexpected.

Cookiecutter_ template for a `F Prime`_ deployment, to help with reducing the copy-pasta effect while creating new deployments.
There are just enough pieces to remember to change/fix, that it is rather challenging to do without a template.
So here is a template to fill in all the major adjustments, so you can spend time develping a deployment or writing a component instead of scratching your head over why you get weird errors.

.. contents:: Table of Contents

Features
--------

* Choice of various licenses. (maybe, eventually)

Requirements
------------

Projects using this template have these minimal dependencies:

* Cookiecutter_ - just for creating the project

To get quickly started on a new system, just install Cookiecutter_. You
should do this in your ``fprime-venv``.  To install it, just run this
in your shell or command prompt, within the ``venv`` environment::

  pip install cookiecutter

Usage and options
-----------------

This template is intended to make it easy to generate all the boilerplate required for a `F Prime`_ deployment and a single component internal to that deployment.
A collection of components along with a mission/project configuration [deployment] completes the framework to fill out a robotic software project; e.g.: a balloon payload, an wheeled rover, or maybe a satellite.

First navigate to the directory where you want to add your deployment.
The template is going to create the folder containing your component in the current directory (you should *not* try to create the folder ahead of the template).
Next, generate the deployment's boilerplate::

  cookiecutter gh:SterlingPeet/cookiecutter-fprime-deployment

You will be asked for these fields:

.. list-table::
    :header-rows: 1

    * - Template variable
      - Default
      - Description

    * - ``full_name``
      - .. code:: python

            "Sterling Peet"
      - Main author of this component.

        Can be set in your ``~/.cookiecutterrc`` config file.

    * - ``email``
      - .. code:: python

            "noreply@nospam.com"
      - Contact email of the author.

        Can be set in your ``~/.cookiecutterrc`` config file.

    * - ``deployment_display_name``
      - .. code:: python

            "My Example"
      - The printed name of this deployment for documentation and strings.  It should be concise and convey the purpose of the deployment.

    * - ``deployment_short_description``
      - .. code:: python

            "An example deployment [...]"
      - One line description of the deployment's purpose (used in headers and comments).

    * - ``deployment_slug``
      - .. code:: python

            "MyExample"
      - A slug_ is a simplified version of the ``deployment_name``, which will be used for the topology assembly name and file names within the deployment folder structure.  It should be ``TitleCase`` with no spaces or special characters.

    * - ``deployment_dir_name``
      - .. code:: python

            "MyExample"
      - This is the name of the deployment's main directory.  The obvious choice is to use your ``deployment_slug`` for this field.

    * - ``deployment_path``
      - .. code:: python

            "example/path"
      - This is the path from the F Prime root to the current directory, not including the deployment's folder.  Do not add a ``/`` to the front or back of the path.

    * - ``deployment_path_to_fprime_root``
      - .. code:: python

            "../.."
      - This is the path from the current directory to the F Prime root, not including the deployment's folder.  Do not add a ``/`` to the front or back of the path.

    * - ``deployment_parameter_support``
      - .. code:: python

            "yes"
      - Include components and connections to support persistent parameter storage using the F Prime parameter subsystem.

    * - ``component_name``
      - .. code:: python

            "Led Blinker"
      - The printed name of this exerciser component for documentation and strings.  It should be concise and convey the purpose of the component.

    * - ``component_short_description``
      - .. code:: python

            "An example component [...]"
      - One line description of the project (used in headers and comments).  This should describe the purpose of the component in the Imperetive Voice, not the context where the component is used.

    * - ``component_slug``
      - .. code:: python

            "LedBlinker"
      - A slug_ is a simplified version of the ``component_name``, which will be used for the class name and file names within the component folder structure.  It should be ``TitleCase`` with no spaces or special characters.

    * - ``component_dir_name``
      - .. code:: python

            "LedBlinker"
      - This is the name of the component's main directory.  The obvious choice is to use your ``deployment_slug`` for this field.

    * - ``component_explicit_component_suffix``
      - .. code:: python

            "Component"
      - The general convention is for F Prime components to have the ``Component`` suffix for file names and class names.  While it is not required, the Autocoder will assume this format, and Autocoder provided templates may be more difficult to adapt if this is not selected.

    * - ``component_explicit_common``
      - .. code:: python

            ""
      - If preferred, the cpp file with the common implementation code can be appended with the suffix ``Common``.

    * - ``component_impl_suffix``
      - .. code:: python

            "Impl"
      - The general convention is for F Prime components to have the ``Impl`` suffix for file names and class names.  While it is not required, the Autocoder will assume this format, and Autocoder provided templates may be more difficult to adapt if this is not selected.

    * - ``component_path_to_fprime_root``
      - .. code:: python

            "../../.."
      - This is the path from the current directory to the F Prime root, not including the components's folder.  Do not add a ``/`` to the front or back of the path (this should auto-populate from the deployment path).

    * - ``component_namespace``
      - .. code:: python

            "Prjct::Grp"
      - This is the namespace where your component's implementation class resides.  It is usually the same but can be different from the path.

    * - ``component_kind``
      - .. code:: python

            "passive"
      - You can choose and active or passive component type.  If you change your mind, is it set in the Autocoder input file (and some of the component's port kinds may also affected).

    * - ``component_multiplatform_support``
      - .. code:: python

            "no"
      - If you need different implementations of your component based on the target platform, choose ``yes`` to get additional support file templates.

    * - ``component_instance_name``
      - .. code:: python

            "ledblinker"
      - This is the variable name given to the instantiation of your component in the topology.

    * - ``startup_arduino_delay_msec``
      - .. code:: python

            "2000"
      - Startup delay during the deployment startup, so you can tell if you got the deployment into a boot loop.  This is only available on the ``Arduino`` platform.

    * - ``startup_arduino_log_stream``
      - .. code:: python

            "Serial"
      - This is the ``Arduino`` stream where the debug statements for the main deployment will print.

    * - ``license``
      - .. code:: python

            "None"
      - License to use. Available options:

        * None (no license text, assume project level license)
        * BSD license
        * MIT license

        What license to pick? https://choosealicense.com/

You should now have a basic deployment that can be compiled and run.

If you want to add components to the deployment, you can do that next.
This can be done by adding a line like this, near the bottom of the deployment's ``CMakeLists.txt`` file::

  add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../Prjct/Grp/MyExample")

Then you need to (possibly purge) and generate the new cmake config in that deployment::

  fprime-util generate
  fprime-util build

Now you should be able to run the executable from the build folder.


Changelog
---------

See `CHANGELOG.rst <https://github.com/SterlingPeet/cookiecutter-fprime-component/tree/master/CHANGELOG.rst>`_.

.. _Cookiecutter: https://github.gatech.edu/audreyr/cookiecutter
.. _F Prime: https://github.com/nasa/fprime/
