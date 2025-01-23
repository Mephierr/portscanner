#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>

void scanPort(const std::string& host, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Ошибка при создании сокета" << std::endl;
        return;
    }

    sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    inet_pton(AF_INET, host.c_str(), &sa.sin_addr);

    // Попытка соединения с целевым хостом и портом
    int result = connect(sock, (struct sockaddr*)&sa, sizeof(sa));
    if (result == -1) {
        std::cout << "Порт " << port << " закрыт" << std::endl;
    } else {
        std::cout << "Порт " << port << " открыт" << std::endl;
    }

    // Закрытие сокета
    close(sock);
}

int main() {
    std::string host = "127.0.0.1";  // Локальный хост
    int startPort = 1;  // Начальный порт
    int endPort = 1024; // Конечный порт

    for (int port = startPort; port <= endPort; ++port) {
        scanPort(host, port);
    }

    return 0;
}