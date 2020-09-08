from __future__ import print_function

import datetime
import os
# import shutil
# import subprocess
# import sys
from os.path import join

try:
    from click.termui import secho
except ImportError:
    warn = print
else:
    def warn(text):
        for line in text.splitlines():
            secho(line, fg="white", bg="red", bold=True)


def replace_contents(filename, what, replacement):
    with open(filename) as fh:
        changelog = fh.read()
    with open(filename, 'w') as fh:
        fh.write(changelog.replace(what, replacement))

if __name__ == "__main__":
    today = datetime.date.today()
    # replace_contents('CHANGELOG.rst', '<TODAY>', today.strftime("%Y-%m-%d"))
    replace_contents(join('{{ cookiecutter.component_dir_name }}', 'docs', 'sdd.md'), '<TODAY>', today.strftime("%m/%d/%Y"))
    replace_contents('README.md', '<TODAY>', today.strftime("%m/%d/%Y"))

{% if cookiecutter.component_multiplatform_support == "no" %}
    mp_str = '{{cookiecutter.component_dir_name}}/{{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{}{{cookiecutter.component_impl_suffix}}.cpp'
    rm_list = ['Arduino', 'AVR', 'Linux']
    for i in rm_list:
        os.unlink(mp_str.format(i))
{% endif %}

# /{/% if cookiecutter.sphinx_docs == "no" %}
#     shutil.rmtree('docs')
# /{/% endif %}

# /{/%- if cookiecutter.command_line_interface == 'no' %}
#     os.unlink(join('src', '/{/{ cookiecutter.package_name }}', '__main__.py'))
#     os.unlink(join('src', '/{/{ cookiecutter.package_name }}', 'cli.py'))
# /{/% endif %}

    print("""
################################################################################
################################################################################

    You have succesfully created the `{{ cookiecutter.component_name }}` component.

################################################################################

    You've used these cookiecutter parameters:
{% for key, value in cookiecutter.items()|sort %}
        {{ "{0:26}".format(key + ":") }} {{ "{0!r}".format(value).strip("u") }}
{%- endfor %}

################################################################################

    You should now have a basic deployment that can be compiled and run.

    If you want to add components to the deployment, you can do that
    next.  This can be done by adding a line like this, near the bottom
    of the deployment's CMakeLists.txt file:

        add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../{{ cookiecutter.deployment_path }}/{{ cookiecutter.component_dir_name }}")

    Then you need to (possibly purge) and generate the new cmake config
    in the deployment:

        fprime-util generate
        fprime-util build

    Now you should be able to run the executable from the build folder.

""")

