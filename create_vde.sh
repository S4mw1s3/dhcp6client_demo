#!/bin/bash
vde_switch -s /tmp/pic0.ctl -m 777 -M /tmp/pico.mgmt -d -hub -t vde0
vde_switch -s /tmp/pic1.ctl -m 777 -M /tmp/pici.mgmt -d -hub
ifconfig vde0 10.40.0.1 netmask 255.255.0.0



ip addr add 2001:db8:0:1::1000/64 dev vde0
dhcpd -6 -cf ./dhcpd6.conf
