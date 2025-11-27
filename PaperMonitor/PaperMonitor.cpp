#include <iostream>
#include "CPU.h"
#include "GPU.h"

int main(array<System::String^>^ args)
{
    CPUSensor cpuSensor;
    GPUSensor gpuSensor;

    while (true)
    {
        float cpuTemp = cpuSensor.GetTemperature();
        float gpuTemp = gpuSensor.GetTemperature();

        // Now using pre-calculated manufacturer
        System::String^ cpuManufacturer = cpuSensor.GetManufacturer();
        System::String^ cpuModel = cpuSensor.GetModel();
        System::String^ gpuManufacturer = gpuSensor.GetManufacturer();
        System::String^ gpuModel = gpuSensor.GetModel();

        if (cpuTemp >= 0)
        {
            System::Console::WriteLine("{0} {1} Temperature: {2} °C", cpuManufacturer, cpuModel, cpuTemp);
        }
        else 
        {
            System::Console::WriteLine("CPU Temperature sensor not found.");
        }

        if (gpuTemp >= 0)
        {
            System::Console::WriteLine("{0} {1} Temperature: {2} °C", 
                gpuManufacturer, gpuModel, gpuTemp);
        }
        else 
        {
            System::Console::WriteLine("GPU Temperature sensor not found.");
        }

        // Wait for 1 second
        System::Threading::Thread::Sleep(1000);
    }

    return 0;
}
