// ======================================================================
// \title  {{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_impl_suffix}}.hpp
// \author {{cookiecutter.full_name}} <{{cookiecutter.email}}>
// \brief  {{cookiecutter.component_short_description}}
// ======================================================================

#ifndef {{cookiecutter.component_slug}}Component_HPP
#define {{cookiecutter.component_slug}}Component_HPP

#include "{{cookiecutter.deployment_path}}/{{cookiecutter.deployment_dir_name}}/{{cookiecutter.component_dir_name}}/{{cookiecutter.component_slug}}ComponentAc.hpp"

namespace {{cookiecutter.component_namespace}} {

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
      bool m_state;
    };

} // end namespace {{cookiecutter.component_namespace}}

#endif // end {{cookiecutter.component_slug}}Component_HPP
