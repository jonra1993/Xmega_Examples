/**
 * The example will configure the Timer D0 (TCD0) in waveform generator mode.
 * AWex is used to output PWM signals from Compare modules CCA and CCB.
 * These complementary signals are output on Port D0 and D1. Deadtimes are
 * inserted. This example is dimming the duty-cycle of the two signals in an
 * opposite way.
  * In addition the example configures the CCA and CCB interrupts to update the
  * duty-cycle
  
   * Summary of Timer Counter configuration:
   *  - TCE0 : Timer
   *  - Compare/Capture modules A/B : Compare and waveform generation in Dual
   *  slope mode
   *  - AXexE : Deadtime Low and High insertion and override of Port E0/E1
   *
   
 **/

#include <asf.h>
#include <string.h>
#include <asf.h>

#define timer_a_usar TCC0
#define	timer_a_usar_PERIOD 0x0100

uint16_t cca_pwm_index;
uint16_t ccb_pwm_index;

static void example_cca_interrupt_callback(void)
{
	cca_pwm_index += 0x01;
	if (cca_pwm_index >= 0xFE) cca_pwm_index=0;
	tc_write_cc_buffer(&timer_a_usar, TC_CCA, cca_pwm_index);
}
static void example_ccb_interrupt_callback(void)
{
	ccb_pwm_index -= 0x01;
	if (ccb_pwm_index <= 0x01) ccb_pwm_index=0xFF;
	tc_write_cc_buffer(&timer_a_usar, TC_CCB, ccb_pwm_index);
}

static void conf_timer(void)
{
	tc_enable(&timer_a_usar);
	
	tc_set_cca_interrupt_level(&timer_a_usar, TC_INT_LVL_LO);
	tc_set_ccb_interrupt_level(&timer_a_usar, TC_INT_LVL_LO);	
	
	tc_set_wgm(&timer_a_usar,TC_WG_NORMAL);
	
	tc_set_cca_interrupt_callback(&timer_a_usar,example_cca_interrupt_callback);
	tc_set_ccb_interrupt_callback(&timer_a_usar,example_ccb_interrupt_callback);	
	
	/* Configures the Timer period*/
	tc_write_period(&timer_a_usar, timer_a_usar_PERIOD);	
	
	/* Configures the CCA and CCB levels*/
    tc_write_cc(&timer_a_usar, TC_CCA, timer_a_usar_PERIOD/2);
    tc_write_cc(&timer_a_usar, TC_CCB, timer_a_usar_PERIOD/2);

	/* Enables the CCA and CCB channels*/
	tc_enable_cc_channels(&timer_a_usar,TC_CCAEN);
	tc_enable_cc_channels(&timer_a_usar,TC_CCAEN);
	
	/* Configures the waveform genertaor in Dual Slope mode and Top*/
	tc_set_wgm(&timer_a_usar,TC_WG_DS_T);	
	
	/* Enables and configures the deadtime of CCA and CCB outputs*/
	tc_awex_enable_cca_deadtime(&AWEXC);
	tc_awex_enable_ccb_deadtime(&AWEXC);
	//This register holds the number of peripheral clock cycles for the dead-time high side.
	tc_awex_set_dti_high(&AWEXC, timer_a_usar_PERIOD/6);
	tc_awex_set_dti_low(&AWEXC, timer_a_usar_PERIOD/6);

	/* Outputs CCA and CCB on Port C0 and C1*/
	tc_awex_set_output_override(&AWEXC, 0B00000011);
	tc_set_resolution(&timer_a_usar, 10000);	
}
int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).
	pmic_init();
	board_init();
	sysclk_init();
	conf_timer();
	sleepmgr_init();
	sei();

	while (1)
	{
		/* Go to sleep, everything is handled by interrupts. */
	 // sleepmgr_enter_sleep(); si se pone no funciona
	}
}
