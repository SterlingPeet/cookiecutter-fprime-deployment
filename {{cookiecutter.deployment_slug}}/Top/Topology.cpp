{%- if cookiecutter.deployment_target_platform_support != 'Arduino' %}
    {%- set __deployment_cli = 'yes' %}
{%- else %}
    {%- set __deployment_cli = 'no' %}
{%- endif -%}
{%- set __dep_cmdseq_comp = cookiecutter.deployment_command_sequence_support -%}
{%- set __dep_health_comp = cookiecutter.deployment_health_support -%}
{%- if cookiecutter.deployment_target_platform_support != 'Arduino' %}
    {%- set __dep_time_comp = 'linuxTime' %}
{%- else %}
    {%- set __dep_time_comp = 'arduinoTime' %}
{%- endif -%}
#include <Components.hpp>
#include <Fw/Types/Assert.hpp>
{%- if cookiecutter.deployment_baremetal_scheduler == 'yes' %}
#include <Os/Baremetal/TaskRunner/TaskRunner.hpp>
{%- endif %}
#include <Os/Task.hpp>
#include <Fw/Logger/Logger.hpp>
#include <Os/Log.hpp>
#include <Fw/Types/MallocAllocator.hpp>
{% if __deployment_cli == 'yes' -%}
#include <Fw/Types/EightyCharString.hpp>
{%- endif %}
{%- if cookiecutter.deployment_rg_sched_contexts_hpp == "yes" %}
#include <{{cookiecutter.deployment_slug}}SchedContexts.hpp>
{%- endif %}
{% if cookiecutter.deployment_target_platform_support != 'Arduino' -%}
#include <Svc/FramingProtocol/FprimeProtocol.hpp>
{%- endif %}
{% if cookiecutter.deployment_target_platform_support == 'Arduino' -%}
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
{%- endif %}

#if defined TGT_OS_TYPE_LINUX || TGT_OS_TYPE_DARWIN
#include <getopt.h>
#include <stdlib.h>
#include <ctype.h>
#endif

// List of context IDs
enum {
    UPLINK_BUFFER_STORE_SIZE = 3000,
    UPLINK_BUFFER_QUEUE_SIZE = 30,
    UPLINK_BUFFER_MGR_ID = 200
};

Os::Log osLogger;
{% if cookiecutter.deployment_target_platform_support != 'Arduino' -%}
Svc::FprimeDeframing deframing;
Svc::FprimeFraming framing;
{%- endif %}
{%- if (__dep_cmdseq_comp == "yes") or (cookiecutter.deployment_file_xfer_support == 'yes') %}
Fw::MallocAllocator mallocator;
{%- endif %}

// Registry
#if FW_OBJECT_REGISTRATION == 1
static Fw::SimpleObjRegistry simpleReg;
#endif

// Component instance pointers

// Setup the rate group driver used to drive all the ActiveRateGroups connected to it.
// For each active rate group, there is a rate divisor that represents how often it is run.
static NATIVE_INT_TYPE rgDivs[] = {% if cookiecutter.deployment_rg_sched_contexts_hpp == "yes" %}{1, 10};{% else %}{1, 2, 4};{% endif %}
Svc::RateGroupDriverImpl rateGroupDriverComp(FW_OPTIONAL_NAME("RGDvr"),rgDivs,FW_NUM_ARRAY_ELEMENTS(rgDivs));

// Context array variables are passed to rate group members if needed to distinguish one call from another
// These context must match the rate group members connected in {{cookiecutter.deployment_slug}}TopologyAi.xml
static NATIVE_UINT_TYPE rg1Context[] = {{ '{' }}{% if cookiecutter.deployment_rg_sched_contexts_hpp == "yes" %}{{cookiecutter.deployment_slug}}::CONTEXT_{{cookiecutter.deployment_slug|upper}}_10Hz{% else %}0{% endif %},0,0,0,0,0,0,0,0,0{{ '}' }};
Svc::ActiveRateGroupImpl rateGroup1Comp(FW_OPTIONAL_NAME("RG1"),rg1Context,FW_NUM_ARRAY_ELEMENTS(rg1Context));

// static NATIVE_UINT_TYPE rg2Context[] = {{ '{' }}{% if cookiecutter.deployment_rg_sched_contexts_hpp == "yes" %}{{cookiecutter.deployment_slug}}::CONTEXT_{{cookiecutter.deployment_slug|upper}}_5Hz{% else %}0{% endif %},0,0,0,0,0,0,0,0,0{{ '}' }};
// Svc::ActiveRateGroupImpl rateGroup2Comp(FW_OPTIONAL_NAME("RG2"),rg2Context,FW_NUM_ARRAY_ELEMENTS(rg2Context));

// static NATIVE_UINT_TYPE rg3Context[] = {{ '{' }}{% if cookiecutter.deployment_rg_sched_contexts_hpp == "yes" %}{{cookiecutter.deployment_slug}}::CONTEXT_{{cookiecutter.deployment_slug|upper}}_1Hz{% else %}0{% endif %},0,0,0,0,0,0,0,0,0{{ '}' }};
// Svc::ActiveRateGroupImpl rateGroup3Comp(FW_OPTIONAL_NAME("RG3"),rg3Context,FW_NUM_ARRAY_ELEMENTS(rg3Context));
{% for component in cookiecutter.internal_use.components -%}
    {%- if (component.use == 'yes') and (component.group != 'rg') %}
        {%- if component.instance == "textLogger" %}
#if FW_ENABLE_TEXT_LOGGING
{{ component.namespace }}::{{ component.class }} {{ component.instance }}(FW_OPTIONAL_NAME("{{ component.instance }}"){{ component.args.instance }});
#endif
        {%- else %}
{{ component.namespace }}::{{ component.class }} {{ component.instance }}(FW_OPTIONAL_NAME("{{ component.instance }}"){{ component.args.instance }});
        {%- endif -%}
    {%- endif -%}
{%- endfor %}
{% if cookiecutter.deployment_baremetal_scheduler == 'yes' %}
// Baremetal setup for the task runner
Os::TaskRunner taskRunner;
{%- endif %}
{% if cookiecutter.deployment_health_support == "yes" %}
const char* getHealthName(Fw::ObjBase& comp) {
   #if FW_OBJECT_NAMES == 1
       return comp.getObjName();
   #else
      return "[no object name]"
   #endif
}
{%- endif %}

/**
 * Construct App:
 *
 * Constructs the App. It initialize components, call for command registration and
 * starts tasks. This is the initialization of the application, so new tasks and
 * memory can be acquired here, but should not be created at a later point.
 */
{%- if __deployment_cli == 'yes' %}
bool constructApp(bool dump, U32 port_number, char* hostname) {
{% else %}
void constructApp(void) {
{%- endif %}

#if FW_PORT_TRACING
    Fw::PortBase::setTrace(false);
#endif

    // Initialize each component instance in memory
{%- for component in cookiecutter.internal_use.components %}
    {%- if component.use == 'yes' %}
        {%- if component.instance == "textLogger" %}
#if FW_ENABLE_TEXT_LOGGING
    {{ component.instance }}.init({{ component.args.init }});
#endif
        {%- else %}
    {{ component.instance }}.init({{ component.args.init }});
        {%- endif -%}
    {%- endif -%}
{%- endfor %}

    Fw::Logger::logMsg("Constructing Architecture.\n");

    // Callback to initialize architecture, connect ports, etc.
    // The contents of the function are autocoded from the
    // {{cookiecutter.deployment_slug}}TopologyAppAi.xml, and
    // incorporates the assembly name.
    construct{{cookiecutter.deployment_slug}}Architecture();

{%- if __deployment_cli == 'yes' %}
    // dump topology if requested
    if (dump) {
#if FW_OBJECT_REGISTRATION == 1
        simpleReg.dump();
#endif
        return true;
    }
{%- endif %}

    /* Register commands */
{%- for component in cookiecutter.internal_use.components %}
    {%- if (component.use == 'yes') and (component.kind == 'active') and (component.cmds.connect != 'no') %}
    {{ component.instance }}.regCommands();
    {%- endif -%}
{%- endfor %}
{%- if cookiecutter.deployment_parameter_support == "yes" %}

    // read parameters
{%- if cookiecutter.deployment_target_platform_support != "Arduino" %}
    prmDb.readParamFile();
{%- endif %}
    {{cookiecutter.component_instance_name}}.loadParameters();
{% endif %}
{% if cookiecutter.deployment_file_xfer_support == "yes" %}
    // set up BufferManager instances
    Svc::BufferManagerComponentImpl::BufferBins upBuffMgrBins;
    memset(&upBuffMgrBins,0,sizeof(upBuffMgrBins));
    upBuffMgrBins.bins[0].bufferSize = UPLINK_BUFFER_STORE_SIZE;
    upBuffMgrBins.bins[0].numBuffers = UPLINK_BUFFER_QUEUE_SIZE;
    fileUplinkBufferManager.setup(UPLINK_BUFFER_MGR_ID,0,mallocator,upBuffMgrBins);
{%- endif %}

{%- if cookiecutter.deployment_health_support == "yes" %}
    // set health ping entries
    Svc::HealthImpl::PingEntry pingEntries[] = {
{%- set health_count = [] -%}{#- Counting list length is needed to defeat jinja scoping rules -#}
{%- for component in cookiecutter.internal_use.components %}
    {%- if (component.use == 'yes') and (component.health.connect == 'yes') %}
        {3,5,getHealthName({{ component.instance }})},  // {{ health_count|length }}
        {%- set __ = health_count.append(1) -%}
    {%- endif -%}
{%- endfor %}
    };

    // register ping table
    health.setPingEntries(pingEntries,FW_NUM_ARRAY_ELEMENTS(pingEntries),0x123);
{%- endif %}

{%- if cookiecutter.deployment_target_platform_support == "Arduino" %}
    // Configure hardware
    uartDriver.open(Drv::ATmegaSerialDriverComponentImpl::DEVICE::USART0,
                    Drv::ATmegaSerialDriverComponentImpl::BAUD_RATE::BAUD_115K,
                    Drv::ATmegaSerialDriverComponentImpl::PARITY::PARITY_NONE);
    ledGpio.setup(DDRB, PORTB, PB5, Drv::ATmegaGpioDriverComponentImpl::GPIO_OUT);
{%- endif %}

    // Active component startup
    //   The .start() function has the following arguments:
    //    1. Thread ID, unique value for each thread, not used for Linux or Baremetal
    //    2. Thread Priority, passed to underlying OS
    //    3. Thread Stack Size, passed to underlying OS, not used for Baremetal
{%- set priority_count = [] -%}{#- Counting list length is needed to defeat jinja scoping rules -#}
{%- for component in cookiecutter.internal_use.components %}
    {%- if (component.use == 'yes') and (component.kind == 'active') %}
    {{ component.instance }}.start({{ priority_count|length }}, {{ 100 - priority_count|length }}, {{ cookiecutter.internal_use.thread_stack_size }});
        {%- set __ = priority_count.append(1) -%}
    {%- endif -%}
{%- endfor %}
{% if __deployment_cli == 'yes' %}
    // Initialize socket server if and only if there is a valid specification
    if (hostname != NULL && port_number != 0) {
        Fw::EightyCharString name("ReceiveTask");
        // Uplink is configured for receive so a socket task is started
        comm.configure(hostname, port_number);
        comm.startSocketTask(name, 100, 10 * 1024);
    }
    return false;
{%- endif %}
}

/**
 * Exit Tasks:
 *
 * Exits the tasks in preparation for stopping the software.{% if cookiecutter.deployment_target_platform_support == 'Arduino' %} This is likely
 * not needed for Arduino projects, as they run forever, however; it is here
 * for completeness.{% endif %}
 */
void exitTasks(void) {
{%- for component in cookiecutter.internal_use.components %}
    {%- if (component.use == 'yes') and (component.kind == 'active') %}
    {{ component.instance }}.exit();
    {%- endif -%}
{%- endfor %}
{%- if cookiecutter.deployment_baremetal_scheduler == "no" %}
    // join the component threads with NULL pointers to free them
{%- for component in cookiecutter.internal_use.components %}
    {%- if (component.use == 'yes') and (component.kind == 'active') %}
    (void) {{ component.instance }}.ActiveComponentBase::join(NULL);
    {%- endif -%}
{%- endfor %}
{%- endif %}
{% if cookiecutter.deployment_target_platform_support != "Arduino" %}
    comm.stopSocketTask();
    (void) comm.joinSocketTask(NULL);
{%- endif %}
{%- if __dep_cmdseq_comp == "yes" %}
    cmdSeq.deallocateBuffer(mallocator);
{%- endif %}
{%- if cookiecutter.deployment_file_xfer_support == "yes" %}
    fileUplinkBufferManager.cleanup();
{%- endif %}
}
