#!/usr/bin/env python3

"""
    @file       dbus_server.py
    @brief      an example for D-Bus server, providing a calculator service with
                plus and times function
    @author     leisquid_tianyi_li
    @date       '25.10. 9
    @licensing  AGPLv3+ license

    Copyright (c) 2023-26 Leisquid Tianyi Li.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
"""

import dbus
import dbus.server
from dbus.mainloop.glib import DBusGMainLoop
from gi.repository import GLib
import signal

## D-Bus service configuration
BUS_NAME: str = "name.leisquid.Calculator"
OBJECT_PATH: str = "/name/leisquid/Calculator"
INTERNAL_NAME: str = BUS_NAME

## D-Bus Calculator service class
class CalculatorService(dbus.service.Object):

    ## init D-Bus session bus
    def __init__(self):
        DBusGMainLoop(set_as_default=True)
        bus: dbus.SessionBus = dbus.SessionBus()

        ## require bus name
        busName: dbus.service.BusName = dbus.service.BusName(BUS_NAME, bus=bus)

        ## init object
        super().__init__(busName, OBJECT_PATH)
        print(f"D-Bus service has launched with name: {BUS_NAME}")
        print(f"object path: {OBJECT_PATH}")
        print(f"the service is running...")

        ## plus method
        @dbus.service.method(INTERFACE_NAME,
                             in_signature='dd',
                             out_signature='d',
                             sender_keyword='sender')
        def Add(self, a: int, b: int, sender=None):
            result: int = a + b
            print(f"received Add request from {sender}: {a} + {b} = {result}")
            self.OperationCompleted('add', a, b, result)
            return result

        ## multiply method
        @dbus.service.method(INTERFACE_NAME,
                            in_signature='dd',
                            out_signature='d')
        def Multiply(self, a: int, b: int, sender=None):
            result: int = a * b
            print(f"received Multiply request from {sender}: {a} * {b} = {result}")
            self.OperationCompleted('multiply', a, b, result)
            return result

    ## displayback method
    @dbus.service.method(INTERFACE_NAME,
                        in_signature='dd',
                        out_signature='d')
    def Echo(self, message):
        responce: str = f"server responds: {message}"
        print(f"received displayback request: {message}")
        return responce

