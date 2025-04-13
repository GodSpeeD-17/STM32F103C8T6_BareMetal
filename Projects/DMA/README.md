# 📦 STM32F103C8T6 DMA Driver (Bare Metal)

This project provides a lightweight, bare-metal DMA (Direct Memory Access) driver implementation for the STM32F103C8T6 microcontroller. The driver supports basic DMA configuration, data transfer between memory and peripherals, and interrupt handling.

---

## 🚀 Features

- ✅ Memory-to-Memory (MEM2MEM) transfers
- ✅ Peripheral-to-Memory (PER2MEM) / Memory-to-Peripheral transfers (MEM2PER)
- ✅ Configurable data width (8, 16, 32 bits)
- ✅ Circular buffer support
- ✅ Transfer complete, half-transfer, and error interrupts
- ✅ Minimal footprint and clean abstraction

---

## 📚 Theory – How STM32F1 DMA Works

STM32F103C8T6 DMA is channel-based. Each channel is fixed to specific peripherals.

### 🧠 Key Registers Per Channel

| Register     | Description                                 |
|--------------|---------------------------------------------|
| `CCR`        | Control Register (direction, mode, size)    |
| `CNDTR`      | Number of data items to transfer            |
| `CPAR`       | Peripheral address                          |
| `CMAR`       | Memory address                              |

---

### 🔁 DMA Transfer Modes

| Mode                  | `MEM2MEM` | `DIR` | Description                      |
|-----------------------|-----------|-------|----------------------------------|
| Peripheral → Memory   | 0         | 0     | Receive from peripheral (e.g., UART RX) |
| Memory → Peripheral   | 0         | 1     | Transmit to peripheral (e.g., SPI TX)   |
| Memory → Memory       | 1         | **0** | Copy data in RAM (⚠️ DIR must be 0)     |

> In `MEM2MEM` mode, the DMA treats **CPAR as source** and **CMAR as destination**, but `DIR` **must still be set to 0** (read from "peripheral").
> Conclusion:
    - Within Memory: `DIR` = `DMAx_DIR_MEM2MEM` (0)
    - Outside Memory: `DIR` = `DMAx_DIR_PER2MEM` (1)

---

## 🛠️ Usage

---

### 📌 Memory-to-Memory Transfer

```c
// Define DMA Channel Configuration Structure
dma_channel_config_t mem2mem_config = {
    .direction = DMAx_DIR_MEM2MEM,         // MUST be 0 for MEM2MEM
    .mem2mem = DMAx_MEM2MEM_ENABLE,        // Enable MEM2MEM
    .circular_mode = DMAx_CIRC_DISABLE,    // Disable Circular Mode
    .priority = DMAx_PRIORITY_HIGH         // Keep it at high priority
};
// DMA Channel Data Configuration Structure
dma_channel_data_t mem2mem_data_config = {
    .srcDataSize = DMAx_DATA_SIZE_BIT_8,   // Data Size for Source
    .dstDataSize = DMAx_DATA_SIZE_BIT_8,   // Data Size for Destination
    .srcInc = DMAx_INC_ENABLE,             // Increment Source Address
    .dstInc = DMAx_INC_ENABLE              // Increment Destination Address
};
// DMA Channel Interrupt Configuration Structure
dma_channel_intr_t mem2mem_irq_config = {
    .TCIE = DMAx_IRQ_ENABLE,                // Complete Transfer Interrupt Enable
    .HTIE = DMAx_IRQ_DISABLE,               // Half Transfer Interrupt Enable
    .TEIE = DMAx_IRQ_ENABLE                 // Transfer Error Interrupt Enable
};
```

---

### 📌 Peripheral-to-Memory Transfer

The **Peripheral-to-Memory (PER2MEM)** transfer mode is used to receive data from a peripheral (e.g., UART RX, SPI RX, ADC) into memory. The DMA controller will transfer data from a peripheral to a specified memory location.

```c
// Define DMA Channel Configuration Structure for Peripheral to Memory (e.g., UART RX)
dma_channel_config_t rx_dma_config = {
    .direction = DMAx_DIR_PER2MEM,        // Direction: Peripheral to Memory
    .mem2mem = DMAx_MEM2MEM_DISABLE,      // Disable MEM2MEM mode
    .circular_mode = DMAx_CIRC_ENABLE,    // Enable Circular Mode (for continuous RX)
    .priority = DMAx_PRIORITY_HIGH        // Set High Priority for the DMA transfer
};

// DMA Channel Data Configuration Structure
dma_channel_data_t rx_dma_data_config = {
    .srcDataSize = DMAx_DATA_SIZE_BIT_8,  // Data Size for Source (Peripheral)
    .dstDataSize = DMAx_DATA_SIZE_BIT_8,  // Data Size for Destination (Memory)
    .srcInc = DMAx_INC_DISABLE,           // Source Address doesn't increment (fixed peripheral address)
    .dstInc = DMAx_INC_ENABLE             // Destination Address increments (memory)
};

// DMA Channel Interrupt Configuration Structure (optional)
dma_channel_intr_t rx_dma_irq_config = {
    .TCIE = DMAx_IRQ_ENABLE,             // Enable Transfer Complete Interrupt
    .HTIE = DMAx_IRQ_DISABLE,            // Disable Half Transfer Interrupt
    .TEIE = DMAx_IRQ_ENABLE              // Enable Transfer Error Interrupt
};
```

---

### 📌 Memory-to-Peripheral Transfer

```c
// Define DMA Channel Configuration Structure for Memory to Peripheral (e.g., UART TX)
dma_channel_config_t tx_dma_config = {
    .direction = DMAx_DIR_PER2MEM,        // Direction: Memory to Peripheral
    .mem2mem = DMAx_MEM2MEM_DISABLE,      // Disable MEM2MEM mode
    .circular_mode = DMAx_CIRC_DISABLE,   // Disable Circular Mode (used for single-shot transfer)
    .priority = DMAx_PRIORITY_HIGH        // Set High Priority for the DMA transfer
};

// DMA Channel Data Configuration Structure
dma_channel_data_t tx_dma_data_config = {
    .srcDataSize = DMAx_DATA_SIZE_BIT_8,  // Data Size for Source (Memory)
    .dstDataSize = DMAx_DATA_SIZE_BIT_8,  // Data Size for Destination (Peripheral)
    .srcInc = DMAx_INC_ENABLE,            // Source Address increments (memory)
    .dstInc = DMAx_INC_DISABLE            // Destination Address doesn't increment (fixed peripheral address)
};

// DMA Channel Interrupt Configuration Structure (optional)
dma_channel_intr_t tx_dma_irq_config = {
    .TCIE = DMAx_IRQ_ENABLE,             // Enable Transfer Complete Interrupt
    .HTIE = DMAx_IRQ_DISABLE,            // Disable Half Transfer Interrupt
    .TEIE = DMAx_IRQ_ENABLE              // Enable Transfer Error Interrupt
};
```

---
