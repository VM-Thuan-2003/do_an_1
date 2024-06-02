//! library depedences
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

char payload[] = "hello esp";

#define UART_BUFFER_SIZE 32

typedef struct {
    uint8_t buffer[UART_BUFFER_SIZE];
    volatile uint16_t head;
    volatile uint16_t tail;
} UART_Buffer;

UART_Buffer uart_tx_buffer, uart_rx_buffer;

bool UART_BufferEmpty(UART_Buffer *buffer) {
    return buffer->head == buffer->tail;
}

bool UART_BufferFull(UART_Buffer *buffer) {
    return ((buffer->head + 1) % UART_BUFFER_SIZE) == buffer->tail;
}

void UART_SendByte(uint8_t data) {
    if (!UART_BufferFull(&uart_tx_buffer)) {
        uart_tx_buffer.buffer[uart_tx_buffer.head] = data;
        uart_tx_buffer.head = (uart_tx_buffer.head + 1) % UART_BUFFER_SIZE;
        enable_interrupts(INT_TBE); // Enable UART transmit interrupt
    }
}

void UART_SendString(char *str) {
    while (*str) {
        UART_SendByte(*str++);
    }
}

bool UART_ReadByte(uint8_t *data) {
    if (!UART_BufferEmpty(&uart_rx_buffer)) {
        *data = uart_rx_buffer.buffer[uart_rx_buffer.tail];
        uart_rx_buffer.tail = (uart_rx_buffer.tail + 1) % UART_BUFFER_SIZE;
        return true;
    }
    return false;
}


void UART_ReadString(char *buffer, uint16_t maxLength) {
    uint16_t i = 0;
    uint8_t received_data;

    while (i < maxLength - 1) {
        if (UART_ReadByte(&received_data)) {
            if (received_data == '\n' || received_data == '\r') {
                break; // Stop reading on newline or carriage return
            }
            buffer[i++] = received_data;
        }
    }
    buffer[i] = '\0'; // Null-terminate the string
}

#INT_TBE
void UART_TxHandler() {
    if (!UART_BufferEmpty(&uart_tx_buffer)) {
        putc(uart_tx_buffer.buffer[uart_tx_buffer.tail]);
        uart_tx_buffer.tail = (uart_tx_buffer.tail + 1) % UART_BUFFER_SIZE;
    } else {
        disable_interrupts(INT_TBE); // Disable UART transmit interrupt
    }
}

#INT_RDA
void UART_RxHandler() {
    uint8_t received_data = getc();
    uint16_t next_head = (uart_rx_buffer.head + 1) % UART_BUFFER_SIZE;

    if (next_head != uart_rx_buffer.tail) { // Ensure there is space in the buffer
        uart_rx_buffer.buffer[uart_rx_buffer.head] = received_data;
        uart_rx_buffer.head = next_head;
    } else {
        // Handle buffer overflow if necessary
    }
}

