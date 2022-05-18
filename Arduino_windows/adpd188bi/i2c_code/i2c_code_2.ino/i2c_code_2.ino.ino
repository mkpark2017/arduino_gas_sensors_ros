#include<Wire.h>
const int ADPD_ADDR=0x64;  // I2C slave address
const int RESET_ADDR=0x0f;
const int SAMPLING_MODE_ADDR=0x10;

const byte FIFO_CFG_ADDR          = 0x11;
const byte SAMPLING_RATE_ADDR     = 0x12;
const byte LED_SLOT_ADDR          = 0x14;
const byte SLOTB_NUM_AVG_ADDR     = 0x15;
const byte INTEG_ORDER_A_ADDR     = 0x17;
const byte SLOTA_CH1_OFFSET_ADDR  = 0x18;
const byte SLOTA_CH2_OFFSET_ADDR  = 0x19;
const byte SLOTA_CH3_OFFSET_ADDR  = 0x1A;
const byte SLOTA_CH4_OFFSET_ADDR  = 0x1B;
const byte INTEG_ORDER_B_ADDR     = 0x1D;
const byte SLOTB_CH1_OFFSET_ADDR  = 0x1E;
const byte SLOTB_CH2_OFFSET_ADDR  = 0x1F;
const byte SLOTB_CH3_OFFSET_ADDR  = 0x20;
const byte SLOTB_CH4_OFFSET_ADDR  = 0x21;
const byte ILED3_COARSE_ADDR      = 0x22;
const byte ILED1_COARSE_ADDR      = 0x23;
const byte ILED2_COARSE_ADDR      = 0x24;
const byte ILED_FINE_ADDR         = 0x25;
const byte SLOTA_LED_PULSE_ADDR   = 0x30;
const byte SLOTA_NUMPULSES_ADDR   = 0x31;
const byte SLOTB_LED_PULSE_ADDR   = 0x35;
const byte SLOTB_NUMPULSES_ADDR   = 0x36;
const byte SLOTA_AFE_WINDOW_ADDR  = 0x39;
const byte SLOTB_AFE_WINDOW_ADDR  = 0x3B;
const byte AFE_PWR_CFG1_ADDR      = 0x3C;
const byte SLOTA_TIA_CFG_ADDR     = 0x42;
const byte SLOTA_AFE_CFG_ADDR     = 0x43;
const byte SLOTB_TIA_CFG_ADDR     = 0x44;
const byte SLOTB_AFE_CFG_ADDR     = 0x45;
const byte MATH_ADDR              = 0x58;
const byte PD_REVERSE_ADDR        = 0x54;

const byte FIFO_ACCESS_ADDR=0x60;

/* Maximum size of hardware FIFO buffer. */
#define ADPD188BI_FIFO_BUF_MAX_SIZE     128

typedef struct {
    //SeI2c_t             *m_hi2c;
    //uint8_t             m_address;      /* I2C address. */
    uint8_t             m_buffer[ADPD188BI_FIFO_BUF_MAX_SIZE];
} ADPD188BI_t;
/* Local objects */
static ADPD188BI_t Adpd188BI;
static ADPD188BI_t * Driver = &Adpd188BI;

static void Smoke_sendData(ADPD188BI_t *handle)
{

    uint8_t l_buff[7] = {0};
    uint32_t l_size = 0;

    // We read values as words
    uint32_t l_fifoBuff[ADPD188BI_FIFO_BUF_MAX_SIZE/2];

    // FIFO is configured to store one sample of sum of the 4 channels in a 32-bit format.
    // Thus, there will be 2 data words in the FIFO. One for each slot.
    uint32_t l_fifoSamples = 2;

    uint32_t l_pBuff[l_fifoSamples];


}


void set_config(byte reg_addr, uint16_t setting){
  byte buffer[2];
  
  Wire.beginTransmission(ADPD_ADDR);
  Wire.write(reg_addr);
  buffer[0] = setting >> 8;
  buffer[1] = (byte) setting;
  Serial.print("Buffer1: ");
  Serial.print(buffer[0], BIN);
  Serial.print("  |  Buffer2: ");
  Serial.println(buffer[1], BIN);
  Wire.write( buffer, 2);
  Wire.endTransmission();
}

void init_ADPD(){
  
  set_config(RESET_ADDR, 0x01); //Software Reset
  set_config(SAMPLING_MODE_ADDR, 0x01); // Program mode (Fully powered + no Sampling)

  //---------------Recommended Cofiguration----------------
  set_config(FIFO_CFG_ADDR, 0x30A9); //Writes a 32-bit sum to the FIFO for Time Slot A and Time Slot B
  set_config(SAMPLING_RATE_ADDR, 0x0200); //16 Hz sampling rate
  set_config(LED_SLOT_ADDR, 0x011D); // Blue Slot A, IR Slot B, combine PDs
  set_config(SLOTB_NUM_AVG_ADDR, 0x0000); // No decimation
  set_config(INTEG_ORDER_A_ADDR, 0x0009); // Time Slot A chop mode, inverted, noninverted, noninverted, inverted (see the Improving SNR Using Integrator Chopping section for more information)
  set_config(SLOTA_CH1_OFFSET_ADDR, 0x0000); //No ADC offset
  set_config(SLOTA_CH2_OFFSET_ADDR, 0x3FFF); //Unused channel
  set_config(SLOTA_CH3_OFFSET_ADDR, 0x3FFF); //Unused channel
  set_config(SLOTA_CH4_OFFSET_ADDR, 0x3FFF); //Unused channel
  set_config(INTEG_ORDER_B_ADDR, 0x0009); //Time Slot B chop mode (inverted, noninverted, noninverted, inverted)
  set_config(SLOTB_CH1_OFFSET_ADDR, 0x0000); //No ADC offset
  set_config(SLOTB_CH2_OFFSET_ADDR, 0x3FFF); //Unused channel
  set_config(SLOTB_CH3_OFFSET_ADDR, 0x3FFF); //Unused channel 
  set_config(SLOTB_CH4_OFFSET_ADDR, 0x3FFF); //Unused channel
  set_config(ILED3_COARSE_ADDR, 0x3539); //LED3 IR
  set_config(ILED1_COARSE_ADDR, 0x3536); //LED1 blue
  set_config(ILED2_COARSE_ADDR, 0x1530); //LED2 unused
  set_config(ILED_FINE_ADDR, 0x630C); //Default LED drive trim
  set_config(SLOTA_LED_PULSE_ADDR, 0x0320); //3 μs LED pulse
  set_config(SLOTA_NUMPULSES_ADDR, 0x040E); //Four pulses, 15 μs LED offset
  set_config(SLOTB_LED_PULSE_ADDR, 0x0320); //3 μs LED pulse
  set_config(SLOTB_NUMPULSES_ADDR, 0x040E); //Four pulses, 15 μs LED offset
  set_config(SLOTA_AFE_WINDOW_ADDR, 0x22F0); //Integrator timing
  set_config(SLOTB_AFE_WINDOW_ADDR, 0x22F0); //Integrator timing
  set_config(AFE_PWR_CFG1_ADDR, 0x31C6); //Power down Channel 2, Channel 3, and Channel 4
  set_config(SLOTA_TIA_CFG_ADDR, 0x1C34); //200k TIA gain
  set_config(SLOTA_AFE_CFG_ADDR, 0xADA5); //Signal path configuration
  set_config(SLOTB_TIA_CFG_ADDR, 0x1C34); //200k TIA gain
  set_config(SLOTB_AFE_CFG_ADDR, 0xADA5); //Signal path configuration
  set_config(MATH_ADDR, 0x0544); //Math for chop mode inverted, noninverted, noninverted, inverted LED
  set_config(PD_REVERSE_ADDR, 0x0AA0); //PD reverse bias, approximately 250 mV

  //---------------Change to Normal mode------------------
  set_config(SAMPLING_MODE_ADDR, 0x02);

}

void setup(){
  Wire.begin();
  Serial.begin(9600);
  init_ADPD();
}
void loop(){
  
  Smoke_sendData(Driver);
  delay(100);
}
