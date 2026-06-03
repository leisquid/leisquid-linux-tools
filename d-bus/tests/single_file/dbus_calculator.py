#!/usr/bin/env python3

"""
    @file       dbus_calculator.py
    @brief      an example for D-Bus server, providing a calculator service with
                plus and times function
    @author     leisquid_tianyi_li
    @date       '25.10. 9
    @licensing  AGPLv3+ license

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
from dbus.mainloop.glib import DBusGMainLoop
from dbus.service import Object, method
from gi.repository import GLib

BUS_NAME: str = "name.leisquid.Calculator"
OBJECT_PATH: str = "/name/leisquid/Calculator"
# INTERFACE_NAME: str = "com.example.Calculator"
INTERFACE_NAME: str = BUS_NAME

class CalculatorService(Object):
    def __init__(self):
        ## 注册 D-Bus 服务名
        bus_name: dbus.service.BusName = dbus.service.BusName(BUS_NAME, bus=dbus.SessionBus())
        ## 初始化 D-Bus 对象路径
        super().__init__(bus_name, OBJECT_PATH)

    @method(dbus_interface=INTERFACE_NAME,
            in_signature='ii',  ## 输入参数类型：两个整数
            out_signature='i')  ## 输出结果类型：一个整数
    def Add(self, a: int, b: int) -> int:
        """两个整数相加"""
        return a + b

    @method(dbus_interface=INTERFACE_NAME,
            in_signature='ii',
            out_signature='i')
    def Multiply(self, a: int, b: int) -> int:
        """两个整数相乘"""
        return a * b

def main():
    ## 设置 D-Bus 主循环为 GLib
    DBusGMainLoop(set_as_default=True)
    
    ## 创建服务实例
    service: CalculatorService = CalculatorService()
    
    ## 运行GLib主循环
    loop: GLib = GLib.MainLoop()
    print("D-Bus 服务已启动，按 Control+C 退出...")
    loop.run()

if (__name__ == "__main__"):
    main()
