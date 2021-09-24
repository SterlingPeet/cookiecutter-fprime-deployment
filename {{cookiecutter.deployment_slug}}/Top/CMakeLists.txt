####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
# Note: using PROJECT_NAME as EXECUTABLE_NAME
####
set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/{{cookiecutter.deployment_slug}}TopologyAppAi.xml"
    "${CMAKE_CURRENT_LIST_DIR}/Main.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Topology.cpp"
)
# Note: supply non-explicit dependencies here
set(MOD_DEPS
    Fw/Logger
{%- if cookiecutter.deployment_target_platform_support != 'Arduino' %}
    Svc/LinuxTime
{% else %}
    ATmega/Svc/ATmegaTime
{%- endif %}
{%- if cookiecutter.deployment_baremetal_scheduler == 'yes' %}
    Os/Baremetal/TaskRunner
{%- endif %}
{%- if cookiecutter.deployment_target_platform_support != 'Arduino' %}
    # Communication Implementations
    Drv/Udp
    Drv/TcpClient
{%- endif %}
)

register_fprime_executable()

{%- if cookiecutter.deployment_target_platform_support == 'Arduino' %}
if(${CMAKE_SYSTEM_NAME} STREQUAL "Arduino")
    set(ARDUINO_DEPENDENCY_TARGET_TOP "${PROJECT_NAME}")
    add_arduino_dependency("${PROJECT_NAME}_exe")
    unset(ARDUINO_DEPENDENCY_TARGET_TOP)
endif()
{%- endif %}
