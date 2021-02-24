#include "em_device.h"
#include "em_chip.h"
#include "em_msc.h"

/* by weiguo lu */
// please review 
#define APPLICATION_START_ADDR (0x00000000)
MSC_RAMFUNC_DECLARATOR void BOOT_jump(uint32_t sp, uint32_t pc);

// Switch to bank 1
MSC_RAMFUNC_DEFINITION_BEGIN
void MSC_BankSwitch(void)
{
  volatile uint32_t pc, sp, word0Before, word0After;
  volatile bool switchedBefore, switchedAfter;

  MSC_Init();

  // The CLW1 is the 123th word of the Lockbits Page
  uint32_t *CLW1_ADDR = (((uint32_t *)LOCKBITS_BASE) + 123);

  // Clear the Bankswitch Disable bit to enable bank switching
  uint32_t bankswitchEnable = 0xFFFFFFFE;
  MSC_WriteWord(CLW1_ADDR, &bankswitchEnable, 4);

  // Check status
  switchedBefore = MSC->STATUS & MSC_STATUS_BANKSWITCHED ? true : false;
  word0Before = *(uint32_t*)0x00000000;

  // Switch to bank 1
  MSC->BANKSWITCHLOCK = MSC_BANKSWITCHLOCK_BANKSWITCHLOCKKEY_UNLOCK;
  while(MSC->BANKSWITCHLOCK);

  MSC->CMD = MSC_CMD_SWITCHINGBANK;

  switchedAfter = MSC->STATUS & MSC_STATUS_BANKSWITCHED ? true : false;
  word0After = *(uint32_t*)0x00000000;

  //jump to 0x00000000
  /* Set new vector table */
  SCB->VTOR = (uint32_t)APPLICATION_START_ADDR;

  /* Read new SP and PC from vector table */
  sp = *((uint32_t *)APPLICATION_START_ADDR);
  pc = *((uint32_t *)APPLICATION_START_ADDR + 1);

#if defined(_SILICON_LABS_32B_SERIES_1)
  /* Invalidate I-cache before executing from main flash. */
  MSC->CACHECMD = MSC_CACHECMD_INVCACHE;
#endif

  MSC_Deinit();

  BOOT_jump(sp, pc);
}
MSC_RAMFUNC_DEFINITION_END

/**************************************************************************//**
 * @brief This function sets up the Cortex M-3 with a new SP and PC.
 *****************************************************************************/
MSC_RAMFUNC_DEFINITION_BEGIN void BOOT_jump(uint32_t sp, uint32_t pc)
{
  (void) sp;
  (void) pc;
  /* Set new MSP, PSP based on SP (r0)*/
  __asm("msr msp, r0");
  __asm("msr psp, r0");

  /* Jump to PC (r1)*/
  __asm("mov pc, r1");
}
MSC_RAMFUNC_DEFINITION_END

int main(void)
{
  /* Chip errata */
  CHIP_Init();

  MSC_BankSwitch();

  /* Infinite loop */
  while (1) {
  }
}
