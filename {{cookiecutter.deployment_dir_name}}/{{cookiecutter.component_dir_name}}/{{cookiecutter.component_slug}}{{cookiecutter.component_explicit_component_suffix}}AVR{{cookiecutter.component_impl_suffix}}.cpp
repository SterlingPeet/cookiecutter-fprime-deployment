// ======================================================================
// \title  {{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}AVR{{cookiecutter.component_impl_suffix}}
// \author {{cookiecutter.full_name}} <{{cookiecutter.email}}>
// \brief  {{cookiecutter.component_short_description}}
// ======================================================================

#include <{{cookiecutter.deployment_path}}/{{cookiecutter.deployment_dir_name}}/{{cookiecutter.component_dir_name}}/{{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_impl_suffix}}.hpp>
#include "Fw/Types/BasicTypes.hpp"

// #include <Arduino.h>
namespace {{cookiecutter.component_namespace}} {

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

} // end namespace {{cookiecutter.component_namespace}}
