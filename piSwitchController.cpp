#include "RF24Mesh/RF24Mesh.h"
#include <RF24/RF24.h>
#include <RF24Network/RF24Network.h>

RF24 radio(24,0);
RF24Network network(radio);
RF24Mesh mesh(radio,network);

int main(int argc, char** argv) {
    mesh.setNodeID(0);
    printf("start\n");
    mesh.begin();

    while(1)
    {        
        mesh.update();
        mesh.DHCP();
        
        while(network.available()){
            RF24NetworkHeader header;
            network.peek(header);
            
            uint32_t dat=0;
            switch(header.type){
                case 'M': 
                    network.read(header, &dat, sizeof(dat)); 
                    printf("Rcv %u from 0%o\n",dat,header.from_node);
                    break;
                default: 
                    network.read(header,0,0); 
                    printf("Rcv bad type %d from 0%o\n",header.type,header.from_node); 
                    break;
            }
        }
        delay(2);
    }
    return 0;
}

            
            
            
