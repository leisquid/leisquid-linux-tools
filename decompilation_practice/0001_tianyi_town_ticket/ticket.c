/**
 * @file        ticket.c
 * @brief       the code for decompilation practice.
 * @author      leisquid_tianyi_li
 * @date        '26.6.18
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

typedef struct {
    unsigned int    price;
    char            *ticket_content;
} MyTicket;

MyTicket *init_ticket(void) {
    MyTicket *tic = (MyTicket *) malloc(sizeof(MyTicket));
    if ( tic ) {
        *tic = (MyTicket) {
            10,
            "+-----------------------------+\n"
            "| Metro Ticket to Tianyi Town |\n"
            "|   Price: 10 steamed buns    |\n"
            "+-----------------------------+"
        };
    }
    return tic;
}

void close_ticket(MyTicket **ticket_ptr) {
    if (ticket_ptr && *ticket_ptr) {
        free(*ticket_ptr);
        *ticket_ptr = NULL;
    }
}

int main(void) {
    unsigned int    steamed_buns = 0;
    unsigned int    feeded_steamed_buns = 0;
    unsigned int    change = 0;
    MyTicket        *ticket = init_ticket();

    if ( ! ticket ) {
        puts("Failed to Initiate ticket!");
        return EXIT_FAILURE;
    }

    do {
        printf("Please feed me steamed buns: ");
        scanf("%u", &steamed_buns);
        feeded_steamed_buns += steamed_buns;
    } while (feeded_steamed_buns < ticket->price);

    change = feeded_steamed_buns - ticket->price;

    puts("\nOutputting ticket...\n");
    puts(ticket->ticket_content);
    printf("Change: %u\n", change);

    close_ticket(&ticket);

    return EXIT_SUCCESS;
}
