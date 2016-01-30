#!/bin/bash
vde_switch -s /var/run/vde.ctl -m 777 -M /var/run/pico.mgmt -d -hub -t vde0
ifconfig vde0 10.40.0.1 netmask 255.255.0.0

sudo ip addr add 2001:db8:0:1::1000/64 dev vde0
sudo cp ./pico-dhcpd6.conf /etc/dhcp/pico-dhcpd6.conf
sudo dhcpd -6 -cf /etc/dhcp/pico-dhcpd6.conf
