.extern keyboard_handler
.extern default_handler

# generic handler as we only manage IRQ1(keyboard)
.global isr_default
isr_default:
    pusha
    call default_handler
    popa
    iret

# keyboard hadnler
.global isr_keyboard
isr_keyboard:
    pusha
    call keyboard_handler
    popa
    iret
