#include <stdlib.h>
#include <stdint.h>
#include "pico_defines.h"
#include "pico_stack.h"
#include "pico_socket.h"
#include "pico_dev_vde.h"
#include "pico_ipv6.h"
#include "pico_icmp6.h"
#include "pico_dhcp6_client.h"

struct pico_device *pico_dev_eth;

void dhcp_cb(void* cli, int code)
{
    if(code == PICO_DHCP6_SUCCESS) {
        char buff[50];
        struct pico_ipv6_link *address;
        address = pico_ipv6_global_get(pico_dev_eth);
        pico_ipv6_to_string(buff, (uint8_t *)&address->address);
        printf("DHCP6 success!\n");
        printf("Address: %s\n", buff);
    }
    else
        printf("DHCP6 failed: %i\n", code);
}

int main(void)
{
    uint8_t mac[6] = {0x00,0x00,0x00,0x12,0x34,0x56};
    struct pico_ip6 dst, nm;
    int i;

    pico_stack_init();

    pico_dev_eth = pico_vde_create("/tmp/pic0.ctl", "pic0", mac);

    if (!pico_dev_eth)
        while (1);

    /* Wait for DAD to end */
    for(i=0; i<400; i++)
    {
        pico_stack_tick();
        PICO_IDLE();
    }
    
    pico_dhcp6_initiate_negotiation(pico_dev_eth, &dhcp_cb, 0);

    for (;;) {
        pico_stack_tick();
        PICO_IDLE();
    }
}
