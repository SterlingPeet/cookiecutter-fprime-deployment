===============================
Cookiecutter: F Prime Component
===============================

**WARNING:** The template is currently intended to support ATmega specific deployments, so if that is not your goal, the results may be somewhat unexpected.

**WARNING:** Beta version, the documentation is not up to date yet (working on it, but needed to crank out some test deployments internally. Sorry!).

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

    * - ``component_name``
      - .. code:: python

            "My Example"
      - The printed name of this component for documentation and strings.  It should be concise and convey the purpose of the component.

    * - ``short_description``
      - .. code:: python

            "An example component [...]"
      - One line description of the project (used in headers and comments).

    * - ``component_class_name``
      - .. code:: python

            "MyExampleComponent"
      - The name of this component's class in the code.  It should be ``CamelCase``.  The autocoder requires the suffix ``Component`` to function properly.

    * - ``component_explicit_common``
      - .. code:: python

            ""
      - If preferred, the cpp file with the common implementation code can be appended with the suffix ``Common``.

    * - ``component_suffix``
      - .. code:: python

            ""
      - If preferred, the files and classes can be appended with the suffix ``Impl``.

    * - ``component_path``
      - .. code:: python

            "Prjct/Grp"
      - This is the path from the F Prime root to the current directory, not including the component's folder.

    * - ``component_namespace``
      - .. code:: python

            "Prjct::Grp"
      - This is the namespace where your component's implementation class resides.  It is usually the same but can be different from the path.

    * - ``component_kind``
      - .. code:: python

            "active"
      - You can choose and active or passive component type.  If you change your mind, is it set in the Autocoder input file.

    * - ``license``
      - .. code:: python

            "None"
      - License to use. Available options:

        * None (no license text, assume project level license)
        * BSD license
        * MIT license

        What license to pick? https://choosealicense.com/

You will still need to run ``fprime-util`` to generate the templates from your autocoder input file.

This requires your component to be included in a deployment.
This can be done by adding a line like this, near the bottom of the deployment's ``CMakeLists.txt`` file::

  add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../Prjct/Grp/MyExample")

Then you need to (possibly purge) and generate the new cmake config in that deployment::

  fprime-util generate

Now you can edit your ``MyExampleComponentAi.xml`` file define the component to your liking, and generate the implementation boilerplate::

  cd MyExample
  fprime-util impl -b {path/to/your/deployment}

Next, copy the ``-template`` code contents into your ``.hpp`` and ``.cpp`` files.
Try not to overwrite the freshly generated comments at the top!


Changelog
---------

See `CHANGELOG.rst <https://github.com/SterlingPeet/cookiecutter-fprime-component/tree/master/CHANGELOG.rst>`_.

.. _Cookiecutter: https://github.gatech.edu/audreyr/cookiecutter
.. _F Prime: https://github.com/nasa/fprime/
