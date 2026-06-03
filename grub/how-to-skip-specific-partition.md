# 如何在 GRUB 中屏蔽指定特定分区的操作系统

以 CC BY-NC-SA 4.0 许可证授权

1. **查询并记录要屏蔽的分区 UUID 和设备路径**

    执行以下命令：

    ```bash
    sudo blkid
    ```

    或

    ```bash
    lsblk -f
    ```

    获取目标分区的 UUID（如 `0123-cdef`）和设备路径（如 `/dev/sda2`）。

2. **编辑 GRUB 配置文件 `/etc/default/grub`**

    添加下面一行，打开 `os-prober` 以检测其他操作系统（已经启用 os-prober 就不用再添加了）：

    ```grub
    GRUB_DISABLE_OS_PROBER=false
    ```

    添加下面一行，指定想要屏蔽的分区：

    ```grub
    GRUB_OS_PROBER_SKIP_LIST="0123-cdef@/dev/sda2"
    ```

    可以用空格或逗号分隔多个值：

    ```grub
    GRUB_OS_PROBER_SKIP_LIST="0123-cdef@/dev/sda2 4567-89ab@/dev/sda3"
    ```

    或

    ```grub
    GRUB_OS_PROBER_SKIP_LIST="0123-cdef@/dev/sda2,4567-89ab@/dev/sda3"
    ```

3. **更新 GRUB 配置**

    保存文件后，执行：

    ```bash
    sudo update-grub
    ```

    或

    ```bash
    sudo grub-mkconfig --output=/boot/grub/grub.cfg
    ```

---

Leisquid Tianyi Li
