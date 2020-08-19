// ======================================================================
// \title  {{cookiecutter.component_name}}Component{{cookiecutter.component_explicit_common}}{{cookiecutter.component_suffix}}.cpp
// \author {{cookiecutter.full_name}} <{{cookiecutter.email}}>
// \brief  {{cookiecutter.component_short_description}}
// ======================================================================


#include <{{cookiecutter.deployment_path}}/{{cookiecutter.deployment_dir_name}}/{{cookiecutter.component_dir_name}}/{{cookiecutter.component_name}}Component{{cookiecutter.component_suffix}}.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace {{cookiecutter.component_namespace}} {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  {{cookiecutter.component_name}}Component{{cookiecutter.component_explicit_common}}{{cookiecutter.component_suffix}} ::
#if FW_OBJECT_NAMES == 1
    {{cookiecutter.component_name}}Component{{cookiecutter.component_explicit_common}}{{cookiecutter.component_suffix}}(
        const char *const compName
    ) :
      {{cookiecutter.component_name}}Component{{cookiecutter.component_explicit_common}}Base(compName),
#else
    {{cookiecutter.component_name}}Component{{cookiecutter.component_explicit_common}}Base(void),
#endif
    m_state(false)
  {}

  {{cookiecutter.component_name}}Component{{cookiecutter.component_explicit_common}}{{cookiecutter.component_suffix}} ::
    ~{{cookiecutter.component_name}}Component{{cookiecutter.component_explicit_common}}{{cookiecutter.component_suffix}}(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void {{cookiecutter.component_name}}Component{{cookiecutter.component_explicit_common}}{{cookiecutter.component_suffix}} ::
    schedIn_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
      blink();
      m_state = !m_state;
  }

} // end namespace {{cookiecutter.component_namespace}}
