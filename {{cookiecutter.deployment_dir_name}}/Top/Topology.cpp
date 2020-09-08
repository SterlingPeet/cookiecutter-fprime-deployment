#include <Fw/Types/Assert.hpp>
#include <Os/Task.hpp>
#include <Os/Log.hpp>
#include <Os/File.hpp>
#include <Os/Baremetal/TaskRunner/TaskRunner.hpp>
#include <Fw/Types/MallocAllocator.hpp>
#include <Drv/ATmegaGpioDriver/ATmegaGpioDriverComponentImpl.hpp>
#include "{{cookiecutter.deployment_slug}}SchedContexts.hpp"
#include "Components.hpp"
#ifdef ARDUINO
    #include <avr/io.h>
#else
    volatile uint8_t DDRB = 2;
    volatile uint8_t PORTB = 2;
    #define PB0 0
    #define PB1 1
    #define PB2 2
    #define PB3 3
    #define PB4 4
    #define PB5 5
    #define PB6 6
    #define PB7 7
#endif

// Setup the rate group driver used to drive all the ActiveRateGroups connected to it.
// For each active rate group, there is a rate divisor that represents how often it is run.
static NATIVE_INT_TYPE rate_divisors[] = {1, 10};
Svc::RateGroupDriverImpl rateGroupDriverComp("RGDRV", rate_divisors, FW_NUM_ARRAY_ELEMENTS(rate_divisors));

// Context array variables are passed to rate group members if needed to distinguish one call from another
// These context must match the rate group members connected in ArduinoTopologyAi.xml
static NATIVE_UINT_TYPE rg10HzContext[] = { {{cookiecutter.deployment_slug}}::CONTEXT_{{cookiecutter.deployment_slug|upper}}_10Hz, 0, 0, 0};
Svc::ActiveRateGroupImpl rateGroup10HzComp("RG10Hz",rg10HzContext,FW_NUM_ARRAY_ELEMENTS(rg10HzContext));
// static NATIVE_UINT_TYPE rg1HzContext[] = {0, 0, {{cookiecutter.deployment_slug}}::CONTEXT_{{cookiecutter.deployment_slug|upper}}_1Hz, 0};
// Svc::ActiveRateGroupImpl rateGroup1HzComp("RG1Hz",rg1HzContext,FW_NUM_ARRAY_ELEMENTS(rg1HzContext));

// Standard system components

// Arduino specific components
{{cookiecutter.component_namespace}}::{{cookiecutter.component_slug}}{{cookiecutter.component_explicit_component_suffix}}{{cookiecutter.component_impl_suffix}} {{cookiecutter.component_instance_name}}("{{cookiecutter.component_instance_name}}");
Arduino::HardwareRateDriver hardwareRateDriver("RateDr", 100);
Drv::ATmegaGpioDriverComponentImpl ledGpio("ledGpio");

// Baremetal setup for the task runner
Os::TaskRunner taskRunner;
/**
 * Construct App:
 *
 * Constructs the App. It initialize components, call for command registration and
 * starts tasks. This is the initialization of the application, so new tasks and
 * memory can be acquired here, but should not be created at a later point.
 */
void constructApp() {
    // Initialize rate group driver
    rateGroupDriverComp.init();

    // Initialize the rate groups
    rateGroup10HzComp.init(10, 0);
    // rateGroup1HzComp.init(10, 1);

    // Initialize the core data handling components
    {{cookiecutter.component_instance_name}}.init(0);

    ledGpio.init(0);

#ifndef ARDUINO
    printf("Constructing Architecture.\n");
#endif
    // Callback to initialize architecture, connect ports, etc.
    // The contents of the function are autocoded from the
    // {{cookiecutter.deployment_slug}}TopologyAppAi.xml, and
    // incorporates the assembly name.
    construct{{cookiecutter.deployment_slug}}Architecture();

    // configure things
    ledGpio.setup(DDRB, PORTB, PB5, Drv::ATmegaGpioDriverComponentImpl::GPIO_OUT);

    hardwareRateDriver.start();

    // Start all active components' tasks thus finishing the setup portion of this code
    rateGroup10HzComp.start(0, 120, 10 * 1024);
    // rateGroup1HzComp.start(0, 119, 10 * 1024);

    // Start the task for the rate group
#ifndef ARDUINO
    printf("Starting TaskRunner.\n");
#endif
    while(1){taskRunner.run();}
}
/**
 * Exit Tasks:
 *
 * Exits the tasks in preparation for stopping the software. This is likely
 * not needed for Arduino projects, as they run forever, however; it is here
 * for completeness.
 */
void exitTasks(void) {
    // rateGroup1HzComp.exit();
    rateGroup10HzComp.exit();
}
