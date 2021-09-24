{%- if (cookiecutter.deployment_path == '.') or (cookiecutter.deployment_path == '') %}
    {%- set __deployment_path = '' -%}
{% else %}
    {%- set __deployment_path = [cookiecutter.deployment_path, '/']|join() -%}
{%- endif -%}
{%- if cookiecutter.deployment_target_platform_support != 'Arduino' %}
    {%- set __deployment_cli = 'yes' %}
{% else %}
    {%- set __deployment_cli = 'no' %}
{%- endif -%}
{%- if __deployment_cli == 'yes' %}
#include <getopt.h>
#include <stdlib.h>
#include <ctype.h>
#include <signal.h>
#include <stdio.h>

{% endif -%}
#include <{{__deployment_path}}{{cookiecutter.deployment_slug}}/Top/Components.hpp>
#include <Fw/Logger/Logger.hpp>
#include <Os/Log.hpp>
{%- if cookiecutter.deployment_target_platform_support == 'Arduino' %}
#ifdef ARDUINO
    #include <ATmega/ATmegaOs/Arduino/StreamLog.hpp>
    #include <Arduino.h>
    #include <ATmega/ATmegaOs/AVR/XMem.hpp>
#endif

#define STARTUP_DELAY_MS {{cookiecutter.startup_delay_msec}}

#if defined (DEBUG_TOP_FREE_RAM) || defined (DEBUG_TOP_SETUP)
    #ifdef ARDUINO
        // #include <Arduino.h>
        #include <ATmega/vendor/libraries/MemoryFree/MemoryFree.h>
    #endif
    #ifndef DEBUG_Serial
        #define DEBUG_Serial {{cookiecutter.arduino_log_stream}}
    #endif
#endif
{%- endif %}

/**
 * In a production deployment, the following version definitions should
 * be kept in a component that can telemeter the values on-demand, and
 * those definitions can be used directly in the logMsg call rather than
 * being re-defined below.
 */
#define {{cookiecutter.deployment_slug|upper}}_VERSION_MAJOR 0
#define {{cookiecutter.deployment_slug|upper}}_VERSION_MINOR 0
#define {{cookiecutter.deployment_slug|upper}}_VERSION_PATCH 1

{%- if __deployment_cli == 'yes' %}
void print_usage(const char* app) {
    (void) printf("Usage: ./%s [options]\n-p\tport_number\n-a\thostname/IP address\n",app);
}


volatile sig_atomic_t terminate = 0;

static void sighandler(int signum) {
    exitTasks();
    terminate = 1;
}

void run1cycle(void) {
    // call interrupt to emulate a clock
    blockDrv.callIsr();
    Os::Task::delay(1000); //10Hz
}

void runcycles(NATIVE_INT_TYPE cycles) {
    if (cycles == -1) {
        while (true) {
            run1cycle();
        }
    }

    for (NATIVE_INT_TYPE cycle = 0; cycle < cycles; cycle++) {
        run1cycle();
    }
}
{%- endif %}

/**
 * Main function for {{cookiecutter.deployment_display_name}} Deployment executable.
 */
int main(int argc, char* argv[]) {
{%- if __deployment_cli == 'yes' %}
    U32 port_number;
    I32 option;
    char *hostname;
    port_number = 0;  // Invalid port number forced
    option = 0;
    hostname = NULL;
    bool dump = false;

    while ((option = getopt(argc, argv, "hdp:a:")) != -1){
        switch(option) {
            case 'h':
                print_usage(argv[0]);
                return 0;
                break;
            case 'p':
                port_number = atoi(optarg);
                break;
            case 'a':
                hostname = optarg;
                break;
            case '?':
                return 1;
            case 'd':
                dump = true;
                break;
            default:
                print_usage(argv[0]);
                return 1;
        }
    }

    (void) printf("Hit Ctrl-C to quit\n");
{%- endif %}

{%- if cookiecutter.deployment_target_platform_support == 'Arduino' %}
#ifdef ARDUINO
    init();
#endif

#ifdef ARDUINO
    #ifndef LOG_Serial
        #ifndef DEBUG_Serial
            #define LOG_Serial {{cookiecutter.arduino_log_stream}}
        #else
            #define LOG_Serial DEBUG_Serial
        #endif
    #endif

    LOG_Serial.begin(115200);
    Os::setArduinoStreamLogHandler(&LOG_Serial);
#endif
{%- endif %}
    Os::Log logger;

#ifndef RELEASE_BUILD
    Fw::Logger::logMsg("\r\n{{cookiecutter.deployment_slug}} Version %d.%d.%d-devel\r\n",
                       {{cookiecutter.deployment_slug|upper}}_VERSION_MAJOR,
                       {{cookiecutter.deployment_slug|upper}}_VERSION_MINOR,
                       {{cookiecutter.deployment_slug|upper}}_VERSION_PATCH);
#else
    Fw::Logger::logMsg("\r\n{{cookiecutter.deployment_slug}} Version %d.%d.%d\r\n",
                       {{cookiecutter.deployment_slug|upper}}_VERSION_MAJOR,
                       {{cookiecutter.deployment_slug|upper}}_VERSION_MINOR,
                       {{cookiecutter.deployment_slug|upper}}_VERSION_PATCH);
#endif

{%- if cookiecutter.deployment_target_platform_support == 'Arduino' %}
    delay({{cookiecutter.startup_delay_msec}});

#ifdef ARDUINO
{%- if cookiecutter.startup_arduino_led_flash == 'yes' %}
    // Two quick flashes for viz indication
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(600);
{%- else %}
    // // Two quick flashes for viz indication
    // pinMode(13, OUTPUT);
    // digitalWrite(13, HIGH);
    // delay(100);
    // digitalWrite(13, LOW);
    // delay(100);
    // digitalWrite(13, HIGH);
    // delay(100);
    // digitalWrite(13, LOW);
    // delay(600);
{%- endif %}
#endif

#ifdef DEBUG_TOP_FREE_RAM
    #ifdef ARDUINO
    DEBUG_Serial.print("\nFree RAM: ");
    DEBUG_Serial.println(freeMemory());
    #endif
#endif

    constructApp();
{%- endif %}
{%- if __deployment_cli == 'yes' %}
    bool quit = constructApp(dump, port_number, hostname);
    if (quit) {
        return 0;
    }

    // register signal handlers to exit program
    signal(SIGINT,sighandler);
    signal(SIGTERM,sighandler);

    int cycle = 0;

    // Alternate option from RPI example:
    //linuxTimer.startTimer(100); //!< 10Hz
    while (!terminate) {
        // (void) printf("Cycle %d\n",cycle);
        runcycles(1);
        cycle++;
    }

    // Give time for threads to exit
    (void) printf("Waiting for threads...\n");
    Os::Task::delay(1000);

    (void) printf("Exiting...\n");
{% else %}
{# Maybe this should be done differently? #}
#ifndef ARDUINO
    (void) printf("Starting TaskRunner.\n");
#endif
    while(1){taskRunner.run();}
{%- endif %}

    return 0;
}
