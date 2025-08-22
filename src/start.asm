;
; NobleLib - Minimal C standard library
;
; Copyright (C) 2025 NobleNomadic
;
; This program is free software; you can redistribute it and/or
; modify it under the terms of the GNU General Public License
; as published by the Free Software Foundation; either version 2
; of the License, or (at your option) any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program; if not, see <http://www.gnu.org/licenses/>.
;
; start.asm - minimal ELF entrypoint for Linux x86-64
; Provides argc, argv, envp and calls main(argc, argv, envp).

    global _start
    extern main          ; main() is in your C code

section .text
_start:
    ; Stack layout at process entry:
    ;   rsp -> argc
    ;          argv[0]
    ;          argv[1]
    ;          ...
    ;          argv[argc] = NULL
    ;          envp[0]
    ;          ...
    ;          envp[n] = NULL
    ;
    ; SysV ABI argument registers for function calls:
    ;   rdi = 1st arg, rsi = 2nd, rdx = 3rd, rcx = 4th, r8 = 5th, r9 = 6th

    mov rdi, [rsp]          ; argc -> rdi
    lea rsi, [rsp+8]        ; argv -> rsi
    lea rdx, [rsi + rdi*8 + 8] ; envp -> rdx (skip argv[argc] NULL)

    call main               ; int main(int argc, char **argv, char **envp)

    ; return value from main is in eax
    mov edi, eax            ; status code -> first arg to exit
    mov eax, 60             ; syscall: exit (60 on x86-64)
    syscall

