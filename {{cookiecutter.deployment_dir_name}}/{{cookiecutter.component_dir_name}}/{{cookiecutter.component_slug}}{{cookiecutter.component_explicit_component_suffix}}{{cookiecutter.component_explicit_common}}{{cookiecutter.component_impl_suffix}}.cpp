// ======================================================================
// \title  {{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_explicit_common}}{{cookiecutter.component_impl_suffix}}.cpp
// \author {{cookiecutter.full_name}} <{{cookiecutter.email}}>
// \brief  {{cookiecutter.component_short_description}}
// ======================================================================


#include <{{cookiecutter.deployment_path}}/{{cookiecutter.deployment_dir_name}}/{{cookiecutter.component_dir_name}}/{{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_impl_suffix}}.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace {{cookiecutter.component_namespace}} {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  {{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_impl_suffix}} ::
#if FW_OBJECT_NAMES == 1
    {{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_impl_suffix}}(
        const char *const compName
    ) :
      {{cookiecutter.component_slug}}ComponentBase(compName),
#else
    {{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_impl_suffix}}(void) :
#endif
    m_state(false){% if cookiecutter.deployment_parameter_support == "yes" %},
    m_blinks(0),
    m_blinkDecimateCntrl(0){% endif %}
  {}
{% if cookiecutter.component_multiplatform_support != 'yes' %}
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
{% endif %}
  {{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_impl_suffix}} ::
    ~{{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_impl_suffix}}(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void {{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_impl_suffix}} ::
    schedIn_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
{%- if cookiecutter.deployment_parameter_support == "yes" %}
    Fw::ParamValid valid;
    m_blinkDecimateCntrl++;

    if(m_blinkDecimateCntrl >= this->paramGet_blinkDecimate(valid))
    {
{%- endif %}
      blink();
      m_state = !m_state;
      m_blinkDecimateCntrl = 0;

      if(m_state)
      {
        m_blinks++;
        tlmWrite_numBlinks(m_blinks);
      }
{%- if cookiecutter.deployment_parameter_support == "yes" %}
    }
{%- endif %}
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------
{% if cookiecutter.deployment_parameter_support == "yes" %}
  void {{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_impl_suffix}} ::
    downlinkParams_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    Fw::ParamValid valid;
    U8 val1 = this->paramGet_blinkDecimate(valid);
    this->tlmWrite_blinkDecimate(val1);
    this->cmdResponse_out(opCode,cmdSeq,Fw::COMMAND_OK);
  }

  void {{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_impl_suffix}} ::
    parameterUpdated(
        FwPrmIdType id
    )
  {
    this->log_ACTIVITY_LO_{{cookiecutter.component_slug}}ParameterUpdated(id);
    Fw::ParamValid valid;
    switch(id) {
      case PARAMID_BLINKDECIMATE: {
        U8 val = this->paramGet_blinkDecimate(valid);
        this->tlmWrite_blinkDecimate(val);
        break;
      }
      default:
        FW_ASSERT(0,id);
        break;
    }
  }
{% endif %}
} // end namespace {{cookiecutter.component_namespace}}
