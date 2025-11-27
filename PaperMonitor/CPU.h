#pragma once
#include <vcclr.h>
#include <iostream>

using namespace System;
using namespace LibreHardwareMonitor::Hardware;

public ref class CPUSensor {
public:
    CPUSensor();
    float GetTotalCpuUsage();
    float GetTemperature();
    String^ GetManufacturer();
    String^ GetModel();

private:
    String^ manufacturer;
    String^ model;
    Computer^ computer;
};