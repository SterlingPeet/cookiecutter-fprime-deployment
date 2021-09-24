{%- if (cookiecutter.deployment_path == '.') or (cookiecutter.deployment_path == '') %}
    {%- set __deployment_path = '' -%}
{% else %}
    {%- set __deployment_path = [cookiecutter.deployment_path, '/']|join() -%}
{%- endif -%}
// ======================================================================
// \title  {{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}Linux{{cookiecutter.component_impl_suffix}}.cpp
// \author {{cookiecutter.full_name}} <{{cookiecutter.email}}>
// \brief  {{cookiecutter.component_short_description}}
// ======================================================================

#include <{{__deployment_path}}{{cookiecutter.deployment_slug}}/{{cookiecutter.component_dir_name}}/{{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_impl_suffix}}.hpp>
#include "Fw/Types/BasicTypes.hpp"

// #include <Arduino.h>
{% set namespaces = cookiecutter.component_namespace.split('::') -%}
{% for name in namespaces -%}
namespace {{ name }} {
{% endfor %}
  void {{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_impl_suffix}} ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    {{cookiecutter.component_slug}}ComponentBase::init(instance);
  }

  void {{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_impl_suffix}} ::
    blink()
  {
      this->gpio_out(0, m_state);
  }

{% for name in namespaces|reverse -%}
} // end namespace {{ name }}
{% endfor %}
