Here is my list of tweaks which in the end provided (relatively slightly and noticeable only after removal of B2 card from DS DAC) improved SQ in comparison to Bridge2 (also connected to network via galvanic isolation).


* **Power RPI with appropriate LPS** (e.g. ideally 3A +)
    * Basically you do not want to have any switching power supply on audio power line
* **Do have Galvanically isolated Ethernet**
    * Either PinkFaun ethernet isolator
    * Or Optical transceivers with LPSs (Linear Power Supplies)
    * not just to RPi, but to any device galvanically connected to your audio chain (like PowerPlant to ethernet)
* **Use Matrix Audio SPDIF2 or similar quality USB isolator + reclocker**
    * Matrix Output module Powered by SuperCapacitor, which is powered by LPS (to make sure you have cleanest power on the most critical part)
    * USB needs Y-split cable - data from RPI , power from LPS (preferably filtered and ideally also on SuperCapacitor)
* **Use properly shielded USB and HDMI cables**
    * eg. shield is connected only one one side
    * basically applies to any shielded cable
* **Use RAM-loaded OS - like piCore linux**
    * You can further optimize inside the OS, like:
        * Reduce RPI Voltages and Clocks, to reduce RFI you don't have properly shielded RPI case
        * Update schedulers to FIFO + few other parameters and vm tweaks 
        * Bind critical processes to separate CPU cores and all other processes to one "common" core, for example:
            * Roon Bridge processes on Core1
            * Roon RAAT process on Core2
            * UpNP process on Core2
            * All other processes (and eventually interrupts) on core3
                * And of course make sure only essential processes are running after boot
            * Set highest priority for audio-related processes, lower for supporting processes and default for all the rest
            * Set audio-processes attributes to real-time
        * Set network interface to static IP address
* **Remove all unnecessary galvanic connections from your audio system**
    * Tip: if you have multiple digital sources (like TV, console etc) connected to audio chain, try to have them all connected via optical TOSLINK only (there are even manual optical switches available which doesn't need power - best solution for me as i don't mind SQ on such inputs much - although it actually doesn't sound bad, it will inherently have some imperfections in optical interconnections)
    
