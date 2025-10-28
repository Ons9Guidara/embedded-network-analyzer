#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

int tcp_count = 0;
int udp_count = 0;
long total_bytes = 0;

// Packet processing callback
void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    struct ip *ip_hdr = (struct ip*)(packet + 14); // skip Ethernet header
    total_bytes += header->len;

    if(ip_hdr->ip_p == IPPROTO_TCP) tcp_count++;
    else if(ip_hdr->ip_p == IPPROTO_UDP) udp_count++;

    printf("Packet: %s -> %s, length %d\n",
           inet_ntoa(ip_hdr->ip_src), inet_ntoa(ip_hdr->ip_dst), header->len);
}

int main() {
    char *dev = "eth0"; 
    char errbuf[PCAP_ERRBUF_SIZE];
    
    pcap_t *handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Could not open device %s: %s\n", dev, errbuf);
        return 2;
    }

    // Apply TCP/UDP filter
    struct bpf_program fp;
    char filter_exp[] = "tcp or udp";
    if (pcap_compile(handle, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == -1) {
        fprintf(stderr, "Error compiling filter\n");
        return 2;
    }
    pcap_setfilter(handle, &fp);

    printf("Capturing packets on %s...\n", dev);
    pcap_loop(handle, 50, packet_handler, NULL); // capture 50 packets

    printf("\nSummary:\nTCP packets: %d\nUDP packets: %d\nTotal bytes: %ld\n",
           tcp_count, udp_count, total_bytes);

    pcap_close(handle);
    return 0;
}

