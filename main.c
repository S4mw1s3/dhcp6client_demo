#include <stdlib.h>
#include <stdint.h>
#include "pico_defines.h"
#include "pico_stack.h"
#include "pico_socket.h"
#include "pico_dev_vde.h"
#include "pico_ipv6.h"
#include "pico_icmp6.h"
#include "pico_dhcp6_client.h"

void dhcp_cb(void* cli, int code)
{
    if(code == PICO_DHCP6_SUCCESS)
        printf("DHCP6 success!\n");
    else
        printf("DHCP6 failed: %i\n", code);
}

int main(void)
{
    uint8_t mac[6] = {0x00,0x00,0x00,0x12,0x34,0x56};
    struct pico_device *pico_dev_eth;
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
