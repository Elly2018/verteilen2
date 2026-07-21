/**
    MIT License

    Copyright (c) 2026 ZhuElly

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
 */
#include <verteilen2/network.h>
#include <iostream>

#if defined(_WIN32)
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <iphlpapi.h>
    #pragma comment(lib, "iphlpapi.lib")
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/types.h>
    #include <ifaddrs.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

namespace verteilen2 {

    static bool is_port_fine(int32_t port) {
#ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) return false;
        SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == INVALID_SOCKET) { WSACleanup(); return false; }
#else
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) return false;
#endif

        // Allow quick reuse of the port so we don't lock it ourselves during the test
        int opt = 1;
#ifdef _WIN32
        setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));
#else
        setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
#endif

        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

        // Try to bind to the port
        bool available = (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) == 0);

        // Clean up the socket immediately
#ifdef _WIN32
        closesocket(sock);
        WSACleanup();
#else
        close(sock);
#endif
        return available;
    }

    std::vector<std::string> network_get_all_ipv4() {
        std::vector<std::string> ips;
#if !defined(_WIN32)
        // --- Linux / macOS Implementation (getifaddrs) ---
        struct ifaddrs* ifAddrStruct = nullptr;
        struct ifaddrs* ifa = nullptr;

        if (getifaddrs(&ifAddrStruct) == -1) {
            std::cerr << "Failed to get network interfaces\n";
            return ips;
        }

        for (ifa = ifAddrStruct; ifa != nullptr; ifa = ifa->ifa_next) {
            // Check if it is a valid IPv4 address structure
            if (!ifa->ifa_addr || ifa->ifa_addr->sa_family != AF_INET) {
                continue;
            }

            // Get the raw IPv4 string pointer
            void* tmpAddrPtr = &((struct sockaddr_in*)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            
            std::string ip_str(addressBuffer);
            
            // Optional: Skip loopback interface if you don't want 127.0.0.1
            if (ip_str == "127.0.0.1") continue; 

            ips.push_back(ip_str);
        }

        if (ifAddrStruct != nullptr) {
            freeifaddrs(ifAddrStruct);
        }

#else
        // --- Windows Implementation (GetAdaptersAddresses) ---
        ULONG bufLen = 15000;
        PIP_ADAPTER_ADDRESSES adapters = (IP_ADAPTER_ADDRESSES*)malloc(bufLen);

        if (GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_PREFIX, NULL, adapters, &bufLen) == NO_ERROR) {
            for (PIP_ADAPTER_ADDRESSES curr = adapters; curr != NULL; curr = curr->Next) {
                // Skip down/inactive interfaces
                if (curr->OperStatus != IfOperStatusUp) continue;

                for (PIP_ADAPTER_UNICAST_ADDRESS unicast = curr->FirstUnicastAddress; unicast != NULL; unicast = unicast->Next) {
                    sockaddr_in* sockaddr = (sockaddr_in*)unicast->Address.lpSockaddr;
                    char buf[INET_ADDRSTRLEN];
                    getnameinfo((struct sockaddr*)sockaddr, sizeof(sockaddr_in), buf, sizeof(buf), NULL, 0, NI_NUMERICHOST);
                    
                    std::string ip_str(buf);
                    if (ip_str == "127.0.0.1") continue;

                    ips.push_back(ip_str);
                }
            }
        }
        free(adapters);
#endif

        return ips;
    }

    std::vector<std::string> network_get_all_ipv6() {
        std::vector<std::string> ips;

#if !defined(_WIN32)
        // --- Linux / macOS Implementation ---
        struct ifaddrs* ifAddrStruct = nullptr;
        struct ifaddrs* ifa = nullptr;

        if (getifaddrs(&ifAddrStruct) == -1) {
            std::cerr << "Failed to get network interfaces\n";
            return ips;
        }

        for (ifa = ifAddrStruct; ifa != nullptr; ifa = ifa->ifa_next) {
            // Look strictly for IPv6 address structures (AF_INET6)
            if (!ifa->ifa_addr || ifa->ifa_addr->sa_family != AF_INET6) {
                continue;
            }

            void* tmpAddrPtr = &((struct sockaddr_in6*)ifa->ifa_addr)->sin6_addr;
            char addressBuffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
            
            std::string ip_str(addressBuffer);
            
            // Optional Filters:
            if (ip_str == "::1") continue; // Skip loopback
            // if (ip_str.rfind("fe80", 0) == 0) continue; // Uncomment to skip link-local addresses

            ips.push_back(ip_str);
        }

        if (ifAddrStruct != nullptr) {
            freeifaddrs(ifAddrStruct);
        }

#else
        // --- Windows Implementation ---
        ULONG bufLen = 15000;
        PIP_ADAPTER_ADDRESSES adapters = (IP_ADAPTER_ADDRESSES*)malloc(bufLen);

        // Request AF_INET6 specifically here
        if (GetAdaptersAddresses(AF_INET6, GAA_FLAG_INCLUDE_PREFIX, NULL, adapters, &bufLen) == NO_ERROR) {
            for (PIP_ADAPTER_ADDRESSES curr = adapters; curr != NULL; curr = curr->Next) {
                if (curr->OperStatus != IfOperStatusUp) continue;

                for (PIP_ADAPTER_UNICAST_ADDRESS unicast = curr->FirstUnicastAddress; unicast != NULL; unicast = unicast->Next) {
                    sockaddr_in6* sockaddr = (sockaddr_in6*)unicast->Address.lpSockaddr;
                    char buf[INET6_ADDRSTRLEN];
                    getnameinfo((struct sockaddr*)sockaddr, sizeof(sockaddr_in6), buf, sizeof(buf), NULL, 0, NI_NUMERICHOST);
                    
                    std::string ip_str(buf);
                    
                    if (ip_str == "::1") continue; // Skip loopback
                    
                    ips.push_back(ip_str);
                }
            }
        }
        free(adapters);
#endif

        return ips;
    }

    int32_t network_get_port_available(int32_t start) {
        while(start <= 65535) {
            if(is_port_fine(start)){
                return start;
            }
            start++;
        }
        return -1;
    }

}

