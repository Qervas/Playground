org 0x7c00
bits 16

%define ENDL 0x0D, 0x0A

;
; FAT12 header
;
jmp short start
nop

bdb_oem: 					db 'MSWIN4.1'  	;8bytes
bdb_bytes_per_sector:		dw 512	
bdb_sector_per_cluster:		db 1
bdb_reserved_sectors:		dw 1
bdb_fat_count:				db 2
bdb_dir_entries:			dw 0E0h
bdb_total_sectors:			dw 2880	; 2880*512=1.44MB
bdb_media_descriptor_type:	db 0F0h ; F0=3.5" floppy, F8=hard disk
bdb_sectors_per_fat:		dw 9 	; 9 sectors/fat
bdb_sectors_per_track:		dw 18   ; 18 sectors/track
bdb_heads:  				dw 2	; 2 heads
bdb_hidden_sectors:			dd 0	; 0 hidden sectors
bdb_large_sector_count:		dd 0	; 0 large sectors

; extended boot record
ebr_drive_number:			db 0	; 0x00 = floppy, 0x80 = hard disk
							db 0	; reserved
ebr_boot_signature:			db 0x29	; 0x29 = next 3 fields are valid
ebr_volume_id:				db 12h, 34h, 56h, 78h ; serial number, value doesn't matter
ebr_volume_label:			db 'FrankYin OS'	; 11 bytes
ebr_system_id:				db 'FAT12   '	; 8 bytes

; boot code starts here
	

start:
    jmp main

; prints a string to the screen
; Params:
;   -ds: si points to string

puts:
    ; save register we will modify
    push si
    push ax

.loop:
    lodsb       ;loads next character in al
    or al, al   ;verify if next character is null?
    jz .done
    
    mov ah, 0x0e;call bios interrupt
    mov bh, 0
    int 0x10

    jmp .loop

.done:
    pop ax
    pop si
    ret

main:
    ; setup data segments
    mov ax, 0
    mov ds, ax
    mov es, ax

    ; setup stack
    mov ss, ax
    mov sp, 0x7c00  ; stack grows downwards from where it is loaded in memory

    ; read something from floppy disk
    ; BIOS should set DL to drive number
    mov [ebr_drive_number], dl

    mov ax, 1   ;LBA=1, second sector from disk
    mov cl, 1   ;1 sector to read
    mov bx, 0x7E00 ;data should be after the bootloader
    call disk_read

    mov si, msg_hello
    call puts

    cli
    hlt             ; no immediate work to be done, putting the processor into an idle state.

;Error handlers
floppy_error:
    mov si, msg_read_failed
    call puts
    jmp wait_key_and_reboot

wait_key_and_reboot:
    mov ah, 0
    int 16h         ; wait for keypress
    jmp 0FFFFh:0    ;jump to beginning of BIOS, should reboot


.halt:
    cli             ;disable interrupts, this way CPU can't get out of "halt" state
    jmp .halt

;Disk routines

;Converts an LBA address to a CHS addresss(LBA: Logic Block Address)
;Parameters
;   -ax: LBA address
;Returns
;   -cx [bits 0-5]: sector number
;   -cx [bits 6-15]: cylinder
;   -dh: head number

lba_to_chs:
    push ax
    push dx
    
    xor dx, dx                              ;dx=0
    div word [bdb_sectors_per_track]        ;ax=LBA / SectorsPerTrack
    inc dx                                  ;dx = (LBA % SectorsPerTrack + 1 )= sector
    xor dx, dx                              ;dx = 0
    div word [bdb_heads]                    ;ax = (LBA / SectorsPerTrack) / Heads = cylinder
                                            ;dx = (LBA / SectorsPerTrack) % Heads = head
    mov dh, dl                              ;dh = head
    mov ch, al                              ;ch = cylinder ( lower 8 bits )
    or cl, ah                               ;put upper 2 bits of cylinder in cl

    pop ax
    mov dl, al
    pop ax
    ret


; Reads sectors from a disk
; Parameters:
;   - ax: LBA address
;   - cl: number of sectors to read (up to 128)
;   - dl: drive number
;   - es:bx : memory address where to store reading data
disk_read:
    push ax                                 ;save registers will be modified
    push bx
    push cx
    push dx
    push di

    push cx                                 ;temporarily save CL(number of sectors to read)
    call lba_to_chs                         ;compute CHS
    pop ax                                  ;AL = number of sectors


    mov ah, 02h
    mov di, 3                               ;retry count
.retry:
    pusha                                   ;save all register, don't know what bios modifies
    stc                                     ;set carry flag, some BIOS'es, don't set it
    int 13h                                 ;carry flag cleared = success
    jnc .done                               ;jump if carry not set

    ;read failed
    popa
    call disk_reset

    dec di
    test di, di
    jnz .retry

.fail:
    ;all attempts are exhausted
    jmp floppy_error
.done:
    popa

    pop di
    pop dx
    pop cx
    pop bx
    pop ax                                 ;restore registers modified

;Resets disk controller
;Parameters:
;   dl: drive number
disk_reset: pusha
mov ah, 0
stc
int 13h
jc floppy_error
popa
ret

msg_hello:              db 'Hello world!', ENDL, 0
msg_read_failed:        db 'Read from disk failed!', ENDL, 0

times 510-($-$$) db 0
dw 0AA55h


