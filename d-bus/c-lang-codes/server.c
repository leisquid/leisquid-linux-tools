/**
 * @file        server.c
 * @brief       the code for server of D-Bus tests
 * @author      leisquid_tianyi_li
 * @date        '25.10.15
 * @licensing   AGPLv3+ license
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <polkit/polkit.h>

#define SOCKET_PATH "/var/run/dbus/system_bus_socket"
#define SERVICE_NAME "com.example.Sample"
#define OBJECT_PATH "/com/example/Sample"
#define INTERFACE_NAME "com.example.Sample.Interface"

int main(void) {
    int sockFd = socket(AF_UNIX, SOCK_STREAM,0);
    struct sockaddr_un addr =  {
        .sun_family = AF_UNIX
    };
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    if ( connect(sockFd, (struct sockaddr *) &addr, sizeof(addr)) < 0 ) {
        perror("D-Bus connection failed");
        exit(EXIT_FAILURE);
    }

    // service registration method (D-Bus binary procotol process needed actually)
    printf("Service registered on %s\n", SERVICE_NAME);

    while (TRUE) {
        // monitoring query (simplified example)
        sleep(5);
        printf("Service is alive...\n");
    }

    close(sockFd);
    return EXIT_SUCCESS;
}
