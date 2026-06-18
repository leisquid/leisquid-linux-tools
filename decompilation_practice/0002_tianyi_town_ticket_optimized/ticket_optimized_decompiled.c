/**
 * @file        ticket_optimized.c
 * @brief       the code decompiled from ticket_optimized.c compilation by
 *              Ghidra.
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
#include <stdbool.h>

typedef struct {
    unsigned int    price;
    char            *ticket_content;
} MyTicket;

bool init_ticket(MyTicket *tic)

{
  if (tic != (MyTicket *)0x0) {
    tic->price = 10;
    tic->ticket_content =
         "+-----------------------------+\n| Metro Ticket to Tianyi Town |\n|   Price: 10 steamed buns    |\n+-----------------------------+"
    ;
  }
  return tic != (MyTicket *)0x0;
}

int main(void)

{
  bool bVar1;
  int returned_value;
  MyTicket ticket;
  int steamed_buns;
  uint change;
  uint feeded;
  
  steamed_buns = 0;
  feeded = 0;
  change = 0;
  bVar1 = init_ticket(&ticket);
  if (bVar1) {
    do {
      printf("Please feed me steamed buns: ");
      scanf("%u",&steamed_buns);
      feeded = feeded + steamed_buns;
    } while (feeded < ticket.price);
    change = feeded - ticket.price;
    puts("\nOutputting ticket...\n");
    puts(ticket.ticket_content);
    printf("Change: %u\n",(ulong)change);
    returned_value = 0;
  }
  else {
    puts("Failed to initiate ticket!");
    returned_value = 1;
  }
  return returned_value;
}
