// ======================================================================
// \title  {{cookiecutter.deployment_assembly}}SchedContexts.hpp
// \author {{cookiecutter.full_name}} <{{cookiecutter.email}}>
// \brief  {{cookiecutter.dep_short_description}}
// ======================================================================


#ifndef {{cookiecutter.deployment_dir_name|upper}}_TOP_{{cookiecutter.deployment_assembly|upper}}SCHEDCONTEXTS_HPP_
#define {{cookiecutter.deployment_dir_name|upper}}_TOP_{{cookiecutter.deployment_assembly|upper}}SCHEDCONTEXTS_HPP_

namespace {{cookiecutter.deployment_assembly}} {
    // A list of contexts for the rate groups
    enum {
        // CONTEXT_{{cookiecutter.deployment_assembly|upper}}_1Hz = 10, // 10Hz cycle
        CONTEXT_{{cookiecutter.deployment_assembly|upper}}_10Hz = 11 // 1 Hz cycle
    };
}  // end {{cookiecutter.deployment_assembly}}

#endif /* {{cookiecutter.deployment_dir_name|upper}}_TOP_{{cookiecutter.deployment_assembly|upper}}SCHEDCONTEXTS_HPP_ */
