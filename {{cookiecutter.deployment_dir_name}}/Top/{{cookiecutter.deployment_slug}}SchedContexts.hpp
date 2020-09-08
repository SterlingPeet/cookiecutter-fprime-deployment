// ======================================================================
// \title  {{cookiecutter.deployment_slug}}SchedContexts.hpp
// \author {{cookiecutter.full_name}} <{{cookiecutter.email}}>
// \brief  {{cookiecutter.dep_short_description}}
// ======================================================================


#ifndef {{cookiecutter.deployment_dir_name|upper}}_TOP_{{cookiecutter.deployment_slug|upper}}SCHEDCONTEXTS_HPP_
#define {{cookiecutter.deployment_dir_name|upper}}_TOP_{{cookiecutter.deployment_slug|upper}}SCHEDCONTEXTS_HPP_

namespace {{cookiecutter.deployment_slug}} {
    // A list of contexts for the rate groups
    enum {
        // CONTEXT_{{cookiecutter.deployment_slug|upper}}_1Hz = 10, // 1 Hz cycle
        CONTEXT_{{cookiecutter.deployment_slug|upper}}_10Hz = 11 // 10 Hz cycle
    };
}  // end {{cookiecutter.deployment_slug}}

#endif /* {{cookiecutter.deployment_dir_name|upper}}_TOP_{{cookiecutter.deployment_slug|upper}}SCHEDCONTEXTS_HPP_ */
