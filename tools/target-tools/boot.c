#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include "elf.h"

#define MAX_FILE_SIZE 0x1000000
#define DRAM_SIZE 0x40000000 //16MB (1024*1024*16) //0x40000000
#define SRAM_SIZE (1024*64) //64KB
#define BBL_LOAD_OFFSET     0x0
#define VMLINUX_LOAD_OFFSET 0xA000000
#define BOOMCONFIG_LOAD_OFFSET 0x900FC00

//#include <asm/arch/map.h>
//#include <asm/io.h>
#define BOOM_reset_handle 0x0
#define start_point (BOOM_reset_handle/(sizeof(*DRAM)))

unsigned int* BOOM_nRESET;
unsigned char* DRAM;
unsigned char* SRAM;
unsigned int* UARTLITE;
unsigned int* BBL;

static int load_file_to_mem(unsigned char* MEM_ADDR, const char* filename);
static void validate_check(char* msg, unsigned char* base, unsigned int offset, unsigned int vsize);
//static int boom_BIN_LOAD(unsigned char*);

int main(void)
{
	struct stat sb;
	int fd;
	int fd_dram;
        printf("*I [NX_LOG] Start MMAP\n");

	if((fd = open("/sys/bus/pci/devices/0000:01:00.0/resource0", O_RDWR)) < 0)
	{
		printf("*E [NX_LOG] SRAM fopen fail\n");
		return 1;
	}
	if((fd_dram = open("/sys/bus/pci/devices/0000:01:00.0/resource1", O_RDWR)) < 0)
	{
		printf("*E [NX_LOG] DRAM fopen fail\n");
		return 1;
	}
	if(fstat(fd, &sb) < 0)
	{
		printf("*E [NX_LOG] fstat fail\n");
		return 1;
	}
        if((SRAM = (unsigned char*)mmap(0, SRAM_SIZE, (PROT_WRITE | PROT_READ), MAP_SHARED,
                fd, 0x80000)) == -1)
        {
            printf("*E [NX_LOG] SRAM MMAP fail\n");
            return 1;
        }

	if((DRAM = (unsigned char*)mmap(0, DRAM_SIZE, (PROT_WRITE | PROT_READ), MAP_SHARED, 
		fd_dram, 0x0)) == -1)
	{
		printf("*E [NX_LOG] DRAM MMAP fail\n");
		return 1;
	}
	if((BOOM_nRESET = (unsigned int*)mmap(0, 10, (PROT_WRITE | PROT_READ), MAP_SHARED, 
		fd, 0x220000)) == -1)
	{
		printf("*E [NX_LOG] BOOM_nRESET MMAP fail\n");
		return 1;
	}
	/* if((UARTLITE = (unsigned int*)mmap(0, 4, (PROT_WRITE | PROT_READ), MAP_SHARED, */
	/* 	fd, 0x30000)) == -1) */
	/* { */
	/* 	printf("*E [NX_LOG] UARTLITE fail\n"); */
	/* 	return 1; */
	/* } */

	printf("*I [NX_LOG] Enter the reset\n");
	BOOM_nRESET[2] = 0;
	usleep(1000*1000);

	printf("*I [NX_LOG] Now reset...\n");
        memset(DRAM + BOOMCONFIG_LOAD_OFFSET, 0, 0x10000);
        memset(DRAM + BBL_LOAD_OFFSET, 0, 8012648);
//        load_file_to_mem(DRAM + VMLINUX_LOAD_OFFSET, "vmlinux");
        load_file_to_mem(DRAM + BOOMCONFIG_LOAD_OFFSET, "BOOMConfig.cfg");
        load_file_to_mem(DRAM + BBL_LOAD_OFFSET, "bbl.bin");

	printf("*I [NX_LOG] Release the reset\n");
	usleep(1000*1000);
	BOOM_nRESET[2] = 1;
	usleep(2000*1000);

        //validate_check("bbl.bin  0x60080000 32byte", SRAM,0,32);
        //validate_check("vmlinux  0x80A00000 32byte", DRAM+VMLINUX_LOAD_OFFSET,0,32);
        //validate_check("phy addr 0x7fffffff 32byte", DRAM,0,32);
        validate_check("phy addr 0x80200000 32byte", DRAM+0x00200000,0,32);

	printf("*I [NX_LOG] SRAM End of test\n");

	munmap(BOOM_nRESET, 10);
        munmap(DRAM, DRAM_SIZE);
        munmap(SRAM, SRAM_SIZE);
        //        munmap(UARTLITE, 4);
        close(fd);
	close(fd_dram);
	return 0;
}


static int load_file_to_mem(unsigned char* MEM_ADDR, const char* filename)
{
  int fd;
  fd = open(filename, O_RDWR);
  struct stat st_bbl;
  fstat(fd, &st_bbl);
  size_t sz_bbl = st_bbl.st_size;
  unsigned char *hFd;
  if((hFd = (unsigned char*)mmap(0, sz_bbl, PROT_READ, MAP_SHARED, fd, 0)) == -1)
  {
      printf("*E [NX_LOG] mmap fail for load file\n");
      return 1;
  }
  printf("[SUKER] %s loaded...\n",filename);
  memset(MEM_ADDR, 0, sz_bbl);
  memcpy(MEM_ADDR, hFd, sz_bbl);

  /* //-----------------bbl validate---------------------- */
  /* validate_check("bbl_head 32byte", bbl_bin,0,32); */
  /* validate_check("DRAM_head 32byte", MEM_ADDR,0,32); */
  /* //-----------------bbl validate---------------------- */

  munmap(hFd, sz_bbl);
  close(fd);

  return 0;
}

static void validate_check(char* msg, unsigned char* base, unsigned int offset, unsigned int vsize)
{
  printf("[SUKER] %s\n",msg);
  for (unsigned int i=0; i< vsize; i++)
  {
    printf("%x ",(unsigned char)(*(base+offset+i)));
  } 
  printf("\n\n");
}
