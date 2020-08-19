// ======================================================================
// \title  {{cookiecutter.component_name}}ComponentAVR{{cookiecutter.component_suffix}}.cpp
// \author {{cookiecutter.full_name}} <{{cookiecutter.email}}>
// \brief  {{cookiecutter.component_short_description}}
// ======================================================================

#include <{{cookiecutter.deployment_path}}/{{cookiecutter.deployment_dir_name}}/{{cookiecutter.component_dir_name}}/{{cookiecutter.component_name}}Component{{cookiecutter.component_suffix}}.hpp>
#include "Fw/Types/BasicTypes.hpp"

// #include <Arduino.h>
namespace {{cookiecutter.component_namespace}} {

  void {{cookiecutter.component_name}}Component{{cookiecutter.component_explicit_common}}{{cookiecutter.component_suffix}} ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    {{cookiecutter.component_name}}Component{{cookiecutter.component_explicit_common}}Base::init(instance);
  }

  void {{cookiecutter.component_name}}Component{{cookiecutter.component_explicit_common}}{{cookiecutter.component_suffix}} ::
    blink()
  {
      this->gpio_out(0, m_state);
  }

} // end namespace {{cookiecutter.component_namespace}}
