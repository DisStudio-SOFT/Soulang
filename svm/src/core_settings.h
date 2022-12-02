#ifndef CORE_SETTINGS
    #define CORE_SETTINGS

    #define STACK_INITSIZE 32

    enum INSTRUCTIONS{
        STACK_PUSH =         0x10,// spush <value>
        STACK_CLEAR =        0x12,// sclear
        STACK_PRINT =        0x20 // print <FFFF address>
    };
#endif