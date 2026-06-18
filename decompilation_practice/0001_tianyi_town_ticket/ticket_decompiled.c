/**
 * @file        ticket_decompiled.c
 * @brief       the code decompiled from ticket.c compilation by Ghidra.
 *              Caution: this decompiled code is just for reference and may not
 *                       pass the compilation.
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

MyTicket * init_ticket(void)

{
  MyTicket *tic;
  
  tic = malloc(0x10);
  if (tic != (MyTicket *)0x0) {
    tic->price = 10;
    tic->ticket_content =
         "+-----------------------------+\n| Metro Ticket to Tianyi Town |\n|   Price: 10 steamed buns    |\n+-----------------------------+"
    ;
  }
  return tic;
}

void close_ticket(MyTicket **ticket_ptr)

{
  if ((ticket_ptr != (MyTicket **)0x0) && (*ticket_ptr != (MyTicket *)0x0)) {
    free(*ticket_ptr);
    *ticket_ptr = (MyTicket *)0x0;
  }
  return;
}

int main(void)

{
  int returned_value;
  MyTicket *ticket;
  int steamed_buns;
  uint change;
  uint feeded_steamed_buns;
  
  steamed_buns = 0;
  feeded_steamed_buns = 0;
  change = 0;
  ticket = init_ticket();
  if (ticket == (MyTicket *)0x0) {
    puts("Failed to Initiate ticket!");
    returned_value = 1;
  }
  else {
    do {
      printf("Please feed me steamed buns: ");
      scanf(&DAT_001020c1,&steamed_buns);   // DAT_001020c1 指向地址处的内容为：0x25, 0x75, 0x00
      feeded_steamed_buns = feeded_steamed_buns + steamed_buns;
    } while (feeded_steamed_buns < ticket->price);
    change = feeded_steamed_buns - ticket->price;
    puts("\nOutputting ticket...\n");
    puts(ticket->ticket_content);
    printf("Change: %u\n",(ulong)change);
    close_ticket(&ticket);
    returned_value = 0;
  }
  return returned_value;
}
