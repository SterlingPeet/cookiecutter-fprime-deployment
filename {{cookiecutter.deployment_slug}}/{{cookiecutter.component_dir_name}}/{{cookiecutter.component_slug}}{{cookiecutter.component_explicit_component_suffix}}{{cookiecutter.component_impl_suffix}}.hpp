{%- if (cookiecutter.deployment_path == '.') or (cookiecutter.deployment_path == '') %}
    {%- set __deployment_path = '' -%}
{% else %}
    {%- set __deployment_path = [cookiecutter.deployment_path, '/']|join() -%}
{%- endif -%}
// ======================================================================
// \title  {{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_impl_suffix}}.hpp
// \author {{cookiecutter.full_name}} <{{cookiecutter.email}}>
// \brief  {{cookiecutter.component_short_description}}
// ======================================================================

#ifndef {{cookiecutter.component_slug}}Component_HPP
#define {{cookiecutter.component_slug}}Component_HPP

#include "{{__deployment_path}}{{cookiecutter.deployment_slug}}/{{cookiecutter.component_dir_name}}/{{cookiecutter.component_slug}}ComponentAc.hpp"

{% set namespaces = cookiecutter.component_namespace.split('::') -%}
{% for name in namespaces -%}
namespace {{ name }} {
{% endfor %}
  class {{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_impl_suffix}} :
    public {{cookiecutter.component_slug}}ComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object {{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_impl_suffix}}
      //!
      {{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_impl_suffix}}(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object {{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_impl_suffix}}
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object {{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_impl_suffix}}
      //!
      ~{{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_impl_suffix}}(void);

    PRIVATE:
{%- if cookiecutter.deployment_parameter_support == "yes" %}
      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for downlinkParams command handler
      //! Command to telemeter the current parameter values in use.
      void downlinkParams_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );
{% endif %}
      //! Blink a given pin
      void blink();
      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for schedIn
      //!
      void schedIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );

{%- if cookiecutter.component_kind == 'active' %}
      //!  \brief Input ping port handler
      //!
      //!  This port is called by the health task to verify task aliveness
      //!
      //!  \param portNum incoming port call. For this class, should always be zero
      //!  \param key value returned to health task to verify round trip

      void pingIn_handler(NATIVE_INT_TYPE portNum, U32 key);
{%- endif %}

{%- if cookiecutter.deployment_parameter_support == "yes" %}
      //! parameter update notification
      //!
      void parameterUpdated(FwPrmIdType id);
{% endif %}
      bool m_state;
      U32 m_blinks;
{%- if cookiecutter.deployment_parameter_support == "yes" %}
      U32 m_blinkDecimateCntrl;
{%- endif %}
    };

{% for name in namespaces|reverse -%}
} // end namespace {{ name }}
{% endfor %}
#endif // end {{cookiecutter.component_slug}}Component_HPP
