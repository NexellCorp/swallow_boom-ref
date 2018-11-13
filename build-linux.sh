cd work/linux
make clean
cd ../../
make -j12
sshpass -pfpga123 scp -r work/bbl.bin fpga@192.168.1.182:/home/fpga/test/BOOM/uartlite/suker/
