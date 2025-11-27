#include "CPU.h"

CPUSensor::CPUSensor() {
    manufacturer = "Unknown";
    model = "Unknown";

    computer = gcnew Computer();
    computer->IsCpuEnabled = true;
    computer->IsGpuEnabled = false;
    computer->IsMemoryEnabled = false;
    computer->IsMotherboardEnabled = false;
    computer->IsControllerEnabled = false;
    computer->IsNetworkEnabled = false;
    computer->IsStorageEnabled = false;
    computer->Open();

    try {
        for each (IHardware ^ hardware in computer->Hardware)
        {
            if (hardware->HardwareType == HardwareType::Cpu)
            {
                hardware->Update();
                
                // Set manufacturer
                manufacturer = hardware->Name->StartsWith("Intel") ? "Intel" : "AMD";
                
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

float CPUSensor::GetTotalCpuUsage() {
    computer->Open();

    try {
        for each (IHardware ^ hardware in computer->Hardware)
        {
            if (hardware->HardwareType == HardwareType::Cpu)
            {
                hardware->Update();

                for each (ISensor ^ sensor in hardware->Sensors)
                {
                    if (sensor->SensorType == SensorType::Load)
                    {
                        // Look for the "CPU Total" sensor which represents overall CPU usage
                        if (sensor->Name == "CPU Total")
                        {
                            return float(sensor->Value);
                        }
                    }
                }

                // Fallback: if "CPU Total" not found, look for any CPU load sensor
                for each (ISensor ^ sensor in hardware->Sensors)
                {
                    if (sensor->SensorType == SensorType::Load)
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

    return -1.0; // Indicate no usage found
}

float CPUSensor::GetTemperature() {
    computer->Open();

    try {
        for each (IHardware ^ hardware in computer->Hardware)
        {
            if (hardware->HardwareType == HardwareType::Cpu)
            {
                hardware->Update();
                
                for each (ISensor ^ sensor in hardware->Sensors)
                {
                    if (sensor->SensorType == SensorType::Temperature)
                    {
                        if (manufacturer == "Intel" && sensor->Name == "CPU Package")
                        {
                            return float(sensor->Value);
                        }
                        else if (manufacturer == "AMD")
                        {
                            if (sensor->Name == "Core (Tctl/Tdie)")
                            {
                                return float(sensor->Value);
                            }
                        }
                    }
                }

                // Fallback to first temperature sensor
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

String^ CPUSensor::GetManufacturer() {
    return manufacturer;
}

String^ CPUSensor::GetModel() {
    return model;
}