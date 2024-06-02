#include <SoftwareSerial.h>

SoftwareSerial espSerial(14, 12); //13-15 // tx-rx

#define UART_BUFFER_SIZE 32

typedef struct {
    uint8_t buffer[UART_BUFFER_SIZE];
    volatile uint16_t head;
    volatile uint16_t tail;
} UART_Buffer;

UART_Buffer uart_tx_buffer;

bool UART_BufferEmpty(UART_Buffer *buffer) {
    return buffer->head == buffer->tail;
}

bool UART_BufferFull(UART_Buffer *buffer) {
    return ((buffer->head + 1) % UART_BUFFER_SIZE) == buffer->tail;
}

bool UART_SendByte(uint8_t data) {
    if (!UART_BufferFull(&uart_tx_buffer)) {
        uart_tx_buffer.buffer[uart_tx_buffer.head] = data;
        uart_tx_buffer.head = (uart_tx_buffer.head + 1) % UART_BUFFER_SIZE;
        return true;
    }
    return false;
}

void UART_SendString(const char *str) {
    while (*str) {
        if (!UART_SendByte(*str++)) {
            // Buffer is full, handle error or wait for buffer space
        }
    }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  espSerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(espSerial.available()){
    String input = espSerial.readString() + "\n";
    Serial.println(input);
    // UART_SendString(input.c_str());
  }

  if(Serial.available()){
    String inputss = Serial.readString();
    Serial.print(inputss);
    espSerial.print("heeelo\n\r");
    // UART_SendString("hello");
  }
}
