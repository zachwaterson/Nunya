/*
Copyright (C) 2015 The University of Notre Dame
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#include "console.h"
#include "memory.h"
#include "memory_raw.h"     // memory_init
#include "process.h"
#include "interrupt.h"
#include "keyboard.h"
#include "clock.h"
#include "ata.h"
#include "string.h"
#include "graphics.h"
#include "ascii.h"
#include "syscall.h"
#include "rtc.h"
#include "kernelcore.h"
#include "cmd_line.h"
#include "disk.h"
#include "iso.h"

/*
This is the C initialization point of the kernel.
By the time we reach this point, we are in protected mode,
with interrupts disabled, a valid C stack, but no malloc heap.
Now we initialize each subsystem in the proper order:
*/

int kernel_main() {
    graphics_init();
    console_init();

    console_printf("video: %d x %d\n", video_xres, video_yres, video_xbytes);
    console_printf("kernel: %d bytes\n", kernel_size);

    memory_init();
    interrupt_init();
    rtc_init();
    clock_init();
    keyboard_init();

    /*
    process_init() is a big step.  This initializes the process table, but also gives us our own process structure, private stack, and enables paging.  Now we can do complex things like wait upon events.
    */
    process_init();

    ata_init();

    console_printf("\nBASEKERNEL READY:\n");

    //change text color to white after bootup
    console_set_fgcolor(255, 255, 255);
    //test ISO filesystem
    struct iso_dir *test_directory = iso_dopen("/", 3);
    console_printf("The directory is at %x\n", test_directory);


    struct directory_record *test_record = iso_dread(test_directory);
    // while (test_record) {
    //     console_printf("The test record is at %x\n", test_record);
    //     console_printf("Directory file identifier is %s\n", test_record->file_identifier);
    //     test_record = iso_dread(test_directory);
    // }



    // struct iso_file *file_test = iso_fopen("/INNER_TE/NO_EXIST.TXT", test->ata_unit);
    // console_printf("Value of file_test pointer is: %x\n", file_test);


    // struct iso_file *file_test = iso_fopen("/U_P_TEST", test->ata_unit);
    // struct iso_file *inner_file_test = iso_fopen("/INNER_TE/INNER_TE.TXT", test->ata_unit);

    // console_printf("The process pointer is %x\n", file_test);
    // console_printf("The inner text file pointer is %x\n", inner_file_test);

    // uint8_t *process_data = kmalloc(file_test->data_length);

    struct iso_file *text_file_test = iso_fopen("/TEXT.TXT", test_directory->ata_unit);
    console_printf("The text file pointer is %x\n", text_file_test);
    char file_read[text_file_test->data_length];
    int num_read = iso_fread(file_read, 1, text_file_test->data_length, text_file_test);
    console_printf("File read says: %s\n", file_read);

    // console_printf("[sl] data_length: %d\n", file_test->data_length);
    // int num_read = iso_fread(process_data, 1, file_test->data_length, file_test);

    // struct process *p = process_create(file_test->data_length, PAGE_SIZE);


    // uint32_t real_addr;
    // if (!pagetable_getmap(p->pagetable, 0x80000000, &real_addr)) {
    //     console_printf("[sl] Unable to get map\n");
    //     halt();
    // }

    // memcpy((void *)real_addr, (void *)process_data, file_test->data_length);

    // console_printf("i was wondering\n");

    // process_yield();


    while(1) {
        cmd_line_attempt(keyboard_read_str());
    }

    return 0;
}
