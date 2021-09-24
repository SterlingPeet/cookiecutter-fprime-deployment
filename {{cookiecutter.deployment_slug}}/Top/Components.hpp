{%- if cookiecutter.deployment_target_platform_support != 'Arduino' -%}
    {%- set __deployment_cli = 'yes' -%}
{% else %}
    {%- set __deployment_cli = 'no' -%}
{%- endif -%}
#ifndef __{{cookiecutter.deployment_slug|upper}}_COMPONENTS_HEADER__
#define __{{cookiecutter.deployment_slug|upper}}_COMPONENTS_HEADER__

#include <Fw/Obj/SimpleObjRegistry.hpp>
{%- for component in cookiecutter.internal_use.components|sort(attribute='hpp') %}
    {%- if component.use == 'yes' %}
#include <{{ component.hpp }}>
    {%- endif -%}
{%- endfor %}
{% if cookiecutter.deployment_baremetal_scheduler == 'yes' -%}
#include <Os/Baremetal/TaskRunner/TaskRunner.hpp>
{%- endif %}

{% if __deployment_cli == 'yes' -%}
bool constructApp(bool dump, U32 port_number, char* hostname);
{%- else %}
void constructApp(void);
{%- endif %}
void construct{{cookiecutter.deployment_slug}}Architecture(void);
void exitTasks(void);

{% for component in cookiecutter.internal_use.components|sort(attribute='type')|sort(attribute='namespace') %}
    {%- if component.use == 'yes' %}
extern {{ component.namespace }}::{{ component.class }} {{ component.instance }};
    {%- endif -%}
{%- endfor %}
// extern Svc::ActiveRateGroupImpl rg2Context;
// extern Svc::ActiveRateGroupImpl rg3Context;
{% if cookiecutter.deployment_baremetal_scheduler == 'yes' -%}
// Scheduler definition
extern Os::TaskRunner taskRunner;
{%- endif %}
#endif  // end __{{cookiecutter.deployment_slug|upper}}_COMPONENTS_HEADER__
