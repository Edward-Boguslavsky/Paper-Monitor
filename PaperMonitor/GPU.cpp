#include "GPU.h"

GPUSensor::GPUSensor() {
    manufacturer = "Unknown";
    model = "Unknown";

    computer = gcnew Computer();
    computer->IsCpuEnabled = false;
    computer->IsGpuEnabled = true;
    computer->IsMemoryEnabled = false;
    computer->IsMotherboardEnabled = false;
    computer->IsControllerEnabled = false;
    computer->IsNetworkEnabled = false;
    computer->IsStorageEnabled = false;
    computer->Open();

    try {
        for each (IHardware ^ hardware in computer->Hardware)
        {
            if (hardware->HardwareType == HardwareType::GpuNvidia || 
                hardware->HardwareType == HardwareType::GpuAmd || 
                hardware->HardwareType == HardwareType::GpuIntel)
            {
                hardware->Update();
                
                // Set manufacturer
                if (hardware->Name->StartsWith("NVIDIA"))
                {
                    manufacturer = "NVIDIA";
                }
                else if (hardware->Name->StartsWith("AMD"))
                {
                    manufacturer = "AMD";
                }
                
                // Set full model name
                model = hardware->Name;
                break;
            }
        }
    }
    finally 
    {
        computer->Close();
    }
}

float GPUSensor::GetTemperature() {
    computer->Open();

    try {
        for each (IHardware ^ hardware in computer->Hardware)
        {
            if (hardware->HardwareType == HardwareType::GpuNvidia ||
                hardware->HardwareType == HardwareType::GpuAmd ||
                hardware->HardwareType == HardwareType::GpuIntel)
            {
                hardware->Update();

                for each (ISensor ^ sensor in hardware->Sensors)
                {
                    if (sensor->SensorType == SensorType::Temperature)
                    {
                        return float(sensor->Value);
                    }
                }
            }
        }
    }
    finally 
    {
        computer->Close();
    }

    return -1.0; // Indicate no temperature found
}

String^ GPUSensor::GetManufacturer() {
    return manufacturer;
}

String^ GPUSensor::GetModel() {
    return model;
}