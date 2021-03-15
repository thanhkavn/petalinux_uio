# petalinux_uio
1. petalinux-create --type project --template zynqMP --name led
2. petalinux-config --get-hw-description=../test_myip.sdk  --> DTG Settings → (zcu104-revc) MACHINE_NAME
3. petelinux-config -c kernel --> Device Drivers -> Userspace I/O drivers
<*> Userspace I/O platform driver with generic IRQ handling
<*> Userspace platform driver with generic irq and dynamic memory
4. change system-user.dtsi in linux-images\project-spec\meta-user\recipes-bsp\device-tree\files --> 

/include/ "system-conf.dtsi"
/ {
    chosen {
        bootargs = "earlycon clk_ignore_unused   uio_pdrv_genirq.of_id=generic-uio";
        stdout-path = "serial0:115200n8";
    };
};
  
&axi_gpio_0 {
    compatible = "generic-uio";
};
