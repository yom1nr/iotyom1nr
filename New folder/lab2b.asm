; =======================================================
; Lab 2B: Serial Shift Input 16 Bit (Set 1 Style)
; Code structure based on Source 240 (Page 9)
; =======================================================

$MOD51

; --- Configuration ---
kDelay  EQU     1       ; if Simulation >> kDelay EQU 1

; --- Pin Definitions (ตามเอกสารหน้า 9) ---
LF_SEG  BIT     P1.4    ; Left Digit Control
RG_SEG  BIT     P1.5    ; Right Digit Control
PT_SEG  EQU     P0      ; Segment Data Port

pLED_R  BIT     P3.6    ; (Defined in sheet but not used)
pLED_G  BIT     P3.7    ; (Defined in sheet but not used)

pLoad   BIT     P2.2    ; Pin 1 of 74165
pClock  BIT     P2.1    ; Pin 2 of 74165
pData   BIT     P2.0    ; Pin 9 of 74165

; --- Variables ---
Data_H  EQU     20H     ; High Byte
Data_L  EQU     21H     ; Low Byte

; --- Main Program ---
ORG     0000H
        LJMP    Start

ORG     0100H
Start:
        MOV     SP, #30H
        SETB    pData       ; Init Input
        
        ; Init Displays (OFF)
        SETB    LF_SEG
        SETB    RG_SEG

LOOP:   
        CALL    GET_16BitData   ; อ่านข้อมูล
        CALL    Display_DATA    ; แสดงผล
        
        LJMP    LOOP

; =======================================================
; GET 16BitData Routine (ตามเอกสาร)
; =======================================================
GET_16BitData:
        CLR     pLoad       ; Latch Data
        SETB    pLoad
        
        CALL    Get8B       ; Read 1st Byte (S1 -> Data_L)
        MOV     Data_L, A
        
        CALL    Get8B       ; Read 2nd Byte (S6 -> Data_H)
        MOV     Data_H, A
        RET

Get8B:
        MOV     R0, #8
L_Shift:
        MOV     C, pData    ; Read Bit
        RRC     A           ; Shift into A
        CLR     pClock      ; Clock Low
        SETB    pClock      ; Clock High
        DJNZ    R0, L_Shift
        RET

; =======================================================
; Display Routine (โครงสร้างตามเอกสารหน้า 9)
; =======================================================
Display_DATA:
        ; ใน Sheet สั่งให้แสดง Data_L (หรือ Data_H ตามต้องการ)
        MOV     A, Data_L   
        CALL    Send2HEX
        RET

Send2HEX:
        PUSH    ACC
        SWAP    A
        
        ; [เพิ่ม] เลือกจอซ้าย (High Nibble)
        CLR     LF_SEG      
        SETB    RG_SEG
        
        CALL    Send1HEX    ; แสดงผลหลักซ้าย
        
        POP     ACC
        
        ; [เพิ่ม] เลือกจอขวา (Low Nibble)
        SETB    LF_SEG      
        CLR     RG_SEG
        
        ; Fall through to Send1HEX for Low Nibble
        
Send1HEX:
        ANL     A, #0FH     ; Mask เอาแค่ 4 บิตล่าง
        
Send1Seg:
        MOV     DPTR, #T_SEG
        MOVC    A, @A+DPTR  ; แปลงเป็นรหัสไฟ
        CPL     A           ; กลับบิต (สำหรับ Common Anode)
        MOV     PT_SEG, A   ; ส่งออก Port 0
        
        CALL    DELAY       ; หน่วงเวลา
        
        MOV     PT_SEG, #0FFH ; เคลียร์จอ (Ghosting Fix)
        RET

; =======================================================
; Delay & Table
; =======================================================
DELAY:
        MOV     R7, #kDelay
Wait2:  
        MOV     R6, #250    ; ปรับเลขนี้ถ้าจอกระพริบ (20-50 กำลังดี)
Wait1:  
        DJNZ    R6, Wait1
        DJNZ    R7, Wait2
        RET

T_SEG:
        ; 0-7
        DB      77H, 11H, 6DH, 5DH, 18H, 5EH, 7EH, 15H
        ; 8-F
        DB      7FH, 5FH, 3FH, 7AH, 66H, 79H, 6EH, 2EH

END