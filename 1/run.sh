#!/bin/bash
chmod 777 -R .
docker run -ti --rm -v "$PWD/linux":/home/student/src/linux --name fase2 -v  "$PWD/initramfs":/home/student/src/initramfs tiagoshibata/pcs3746
