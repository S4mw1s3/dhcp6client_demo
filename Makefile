PICOTCP=../picotcp
CFLAGS=-g -ggdb -I./build/include
LDFLAGS=-L./build/lib ./build/lib/libpicotcp.a -lvdeplug -lpicotcp

all: picotcp
	gcc $(CFLAGS) pico_dev_vde.c main.c -o app $(LDFLAGS)

picotcp:
	$(MAKE) -C $(PICOTCP) PING=1 TUN=0 TAP=0 MCAST=1 SNTP_CLIENT=0 NAT=0 ICMP4=1 MDNS=0 CRC=0 OLSR=0 SLAACV4=0 DHCP_CLIENT=0 DHCP_SERVER=0 TFTP=0 DNS_CLIENT=0

clean:
	@rm -rfv build
	@rm -f app
