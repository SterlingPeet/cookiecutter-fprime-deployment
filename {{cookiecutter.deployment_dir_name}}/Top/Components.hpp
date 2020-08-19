#ifndef __{{cookiecutter.deployment_assembly|upper}}_COMPONENTS_HEADER__
#define __{{cookiecutter.deployment_assembly|upper}}_COMPONENTS_HEADER__

#define COMM_SERIAL

void construct{{cookiecutter.deployment_assembly}}Architecture(void);
void exitTasks(void);
void constructApp();

#include <Drv/ATmegaGpioDriver/ATmegaGpioDriverComponentImpl.hpp>

#include <Svc/ActiveRateGroup/ActiveRateGroupImpl.hpp>
#include <Svc/RateGroupDriver/RateGroupDriverImpl.hpp>

#include <ATmega/HardwareRateDriver/HardwareRateDriver.hpp>
#include <{{cookiecutter.deployment_path}}/{{cookiecutter.deployment_dir_name}}/{{cookiecutter.component_dir_name}}/{{cookiecutter.component_name}}Component{{cookiecutter.component_suffix}}.hpp>

// Core components
extern Drv::ATmegaGpioDriverComponentImpl ledGpio;
extern Svc::RateGroupDriverImpl rateGroupDriverComp;
extern Svc::ActiveRateGroupImpl rateGroup10HzComp;
extern Arduino::HardwareRateDriver hardwareRateDriver;
extern {{cookiecutter.component_namespace}}::{{cookiecutter.component_name}}Component{{cookiecutter.component_suffix}} {{cookiecutter.component_instance_name}};

// #ifdef COMM_SERIAL
//   extern Arduino::SerialDriverComponentImpl comm;
// #endif

#endif  // end __{{cookiecutter.deployment_assembly|upper}}_COMPONENTS_HEADER__
