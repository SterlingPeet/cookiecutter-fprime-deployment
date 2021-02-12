#ifndef __{{cookiecutter.deployment_slug|upper}}_COMPONENTS_HEADER__
#define __{{cookiecutter.deployment_slug|upper}}_COMPONENTS_HEADER__

<COMPONENT_INCLUDES>

void constructApp(void);
void construct{{cookiecutter.deployment_slug}}Architecture(void);
void exitTasks(void);

<COMPONENT_INSTANCE_DECLARATIONS>
// extern Svc::ActiveRateGroupImpl rateGroup1HzComp;

#endif  // end __{{cookiecutter.deployment_slug|upper}}_COMPONENTS_HEADER__
