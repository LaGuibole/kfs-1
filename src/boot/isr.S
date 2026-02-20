.code32

.extern keyboard_handler
.extern default_handler

.global isr_default
isr_default:
    pusha
    call default_handler
    popa
    iret

.global isr_keyboard
isr_keyboard:
    pusha
    subl $12, %esp      # align stack [test debug]
    call keyboard_handler
    addl $12, %esp      # restore [debug tjrs on teste hein]
    popa
    iret
