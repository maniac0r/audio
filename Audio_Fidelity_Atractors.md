Grafana Dashboard trying to display all "audio reproduction relevant" metrics i was able to gather up till now.

Datasources:
* [PowerPlant stats](https://github.com/maniac0r/powerplant-stats) bash script collecting data from P10 and sending those to influxdb
* [haas.io](https://www.home-assistant.io) based influxdb where metrics from Z-Wave devices are collected
* [soundmeter](https://github.com/shichao-an/soundmeter) with bash wrapper to send averaged, min and max measured data periodicaly to influxdb + bash script to play waring when sound level is over threshold.
* [netdata](https://github.com/netdata/netdata) for collecting idle-jitter data from server runnig Roon&UpNP servers
* [bettercap](https://github.com/bettercap/bettercap) with bash wrapper for collection of Bluetooth data and sending them to elasticsearch
* [kismet](https://github.com/kismetwireless/kismet) feeding data to tshark 
* [tshark](https://gitlab.com/wireshark/wireshark) with bash wrapper to parse output and feed elastiscearch

Features:
* current temperature & humidity in listening room
* current PowerPlant internal temperatures and output power
* current PowerPlant input/output voltage, it's difference and Standard Deviation per last 10 miutes
* current status of Z-Wave power sockets (we want them all off during critical listening)
* historical overview of PowerPlant "undervoltage" - e.g. Output voltage is higher than Input voltage
* historical iddle-jitter of media server
* historical view of neighborhood Bluetooth and Wifi busyness
* min,max and average sound level in listening room ("raw value from microphone", not in dB)

The idea:
Check if we don't have undervoltage, output/input voltage stdev not high, limited number of Z-Wave wake-ups, min noise level below desired threshold and finally no unnecessary wifi/bt devices closely around.

![Dashboard](https://raw.githubusercontent.com/maniac0r/audio/master/Audio%20Fidelity%20Attractors%20-%2024h.png "Grafana Dashboard")
