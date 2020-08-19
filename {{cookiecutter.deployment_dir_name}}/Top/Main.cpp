#include <{{cookiecutter.deployment_path}}/{{cookiecutter.deployment_dir_name}}/Top/Components.hpp>
#ifdef ARDUINO
    #include <Os/Arduino/StreamLog.hpp>
    #include <Arduino.h>
    #include <Os/AVR/XMem.hpp>
#endif

#define STARTUP_DELAY_MS {{cookiecutter.startup_delay_msec}}

/**
 * Main function.
 */
int main(int argc, char* argv[]) {
#ifdef ARDUINO
    init();
    // initVariant();  // Seems to cause main() duplicate to show up...

    {{cookiecutter.arduino_log_stream}}.begin(115200);
    Os::setArduinoStreamLogHandler(&{{cookiecutter.arduino_log_stream}});
    Serial.println("Started!");

    delay({{cookiecutter.startup_delay_msec}});
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
    constructApp();
    return 0;
}
