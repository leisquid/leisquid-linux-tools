/**
 * @file        ticket_optimized.c
 * @brief       the optimized code for ticket.c.
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
#include <stdbool.h>

typedef struct {
    unsigned int    price;
    char            *ticket_content;
} MyTicket;

bool init_ticket(MyTicket *tic) {
    if ( ! tic ) {
        return false;
    }

    tic->price = 10;
    tic->ticket_content =
        "+-----------------------------+\n"
        "| Metro Ticket to Tianyi Town |\n"
        "|   Price: 10 steamed buns    |\n"
        "+-----------------------------+"
    ;

    return true;
}

int main(void) {
    unsigned int steamed_buns = 0;
    unsigned int feeded = 0;
    unsigned int change = 0;
    MyTicket ticket;    /* allocated on stack */

    if ( ! init_ticket(&ticket) ) {
        puts("Failed to initiate ticket!");
        return EXIT_FAILURE;
    }

    do {
        printf("Please feed me steamed buns: ");
        scanf("%u", &steamed_buns);
        feeded += steamed_buns;
    } while (feeded < ticket.price);

    change = feeded - ticket.price;

    puts("\nOutputting ticket...\n");
    puts(ticket.ticket_content);
    printf("Change: %u\n", change);

    return EXIT_SUCCESS;
}
