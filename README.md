# esp8266-ping
ESP-01s code for generating ICMP/Ping normal and malicious traffic, along with detection of said traffic using Machine Learning.

### Traffic type
Both scenarios have a packet header like Microsoft Windows OS.<br />
Normal : Normal ping packet traffic, meaning 1 second delay for each request sent.<br />
Malicious: continuous ping flood traffic with spoofed IP, no delay set.

The code found in folders "1-ESP_01s_Scenarios_C++_Code_Spoofed_IP" and "2-Flask_Server_Code" has generated a dataset that can be found here: [![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.8111635.svg)](https://doi.org/10.5281/zenodo.8111635)

Folder "3-Feature_Extraction_Shell_Script" is where shell script uses the Zeek tool and other Linux utilities to extract **flow information** from the pcap files (pcap found in the dataset).

Folder "4-Machine_Learning_Code" is where the Machine Learning process happens, the code is in Jupyter Notebook, python.

The publication reference for this work is [here](https://doi.org/10.1109/ACCESS.2023.3327061). 

### Branch
The flood branch has a code where the ESP just bombards the target IP address.

The master branch uses a server for logging the traffic, it created the dataset mentioned above, which is dedicated for an Intrusion Detection framework research "pending publication"

# Credit
[bluemurder/esp8266-ping](https://github.com/bluemurder/esp8266-ping#readme)
