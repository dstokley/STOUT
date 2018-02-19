#include <stdlib.h>
#include <stdio.h>
#include <common.h>
#include <exports.h>
#include <Watchdog.h>
#include <asm/arch/imx-regs.h>

#define WDT_GDIR_REG(x)				((x) + 0x4)
#define WDT_DR_REG(x)					((x))

#define WDT_DIR_OUT_GPIO(x,n)   writel(readl(WDT_GDIR_REG((x))) | (1 << (n)), WDT_GDIR_REG((x)))
#define WDT_DIR_IN_GPIO(x,n)    writel(readl(WDT_GDIR_REG((x))) & ~(1 << (n)), WDT_GDIR_REG((x)))
#define WDT_SET_H_GPIO(x,n)     writel(readl(WDT_DR_REG((x))) | (1 << (n)) , WDT_DR_REG((x)))
#define WDT_SET_L_GPIO(x,n)     writel(readl(WDT_DR_REG((x))) & ~(1 << (n)) , WDT_DR_REG((x)))

void enable_watchdog(void)
{
	WDT_DIR_OUT_GPIO(APX_WDT_TRIGGER_BASE, APX_WDT_TRIGGER_NUM);
	WDT_DIR_OUT_GPIO(APX_WDT_ENABLE_BASE, APX_WDT_ENABLE_NUM);
	WDT_SET_L_GPIO(APX_WDT_ENABLE_BASE, APX_WDT_ENABLE_NUM);
}

void disable_watchdog(void)
{
	/* reset the watchdog, first, since it may be close to timing out */
	/*     Set ENABLE to OUTPUT, LOW */
	WDT_DIR_OUT_GPIO(APX_WDT_ENABLE_BASE, APX_WDT_ENABLE_NUM);
	WDT_SET_L_GPIO(APX_WDT_ENABLE_BASE, APX_WDT_ENABLE_NUM);

	/*     Set TRIGGER to OUTPUT, then transition from LOW to HIGH */
	WDT_DIR_OUT_GPIO(APX_WDT_TRIGGER_BASE, APX_WDT_TRIGGER_NUM);
	WDT_SET_L_GPIO(APX_WDT_TRIGGER_BASE, APX_WDT_TRIGGER_NUM);
	WDT_SET_H_GPIO(APX_WDT_TRIGGER_BASE, APX_WDT_TRIGGER_NUM);

	/* Now, disable the watchdog */
	/*     This follows the sequence in uboot-imx/board/udoo/udoo_qd/udoo.c */
	/*        function: setup_iomux_wdog()  */
	/*     Set TRIGGER to OUTPUT, LOW */
   	WDT_DIR_OUT_GPIO(APX_WDT_TRIGGER_BASE, APX_WDT_TRIGGER_NUM);
	WDT_SET_L_GPIO(APX_WDT_TRIGGER_BASE, APX_WDT_TRIGGER_NUM);

	/* Set ENABLE to OUTPUT, HIGH */
	WDT_DIR_OUT_GPIO(APX_WDT_ENABLE_BASE, APX_WDT_ENABLE_NUM);
	WDT_SET_H_GPIO(APX_WDT_ENABLE_BASE, APX_WDT_ENABLE_NUM);

	/* Set TRIGGER to INPUT */
   	WDT_DIR_IN_GPIO(APX_WDT_TRIGGER_BASE, APX_WDT_TRIGGER_NUM);
}

void reset_watchdog(void)
{
	/* Any transition on the watchdog trigger will reset the watchdog.
	   Ensure that a transition occurs by setting a known state (LOW,
	   in this case) and then transitioning (to HIGH, in this case). */
	WDT_SET_L_GPIO(APX_WDT_TRIGGER_BASE, APX_WDT_TRIGGER_NUM);
	WDT_SET_H_GPIO(APX_WDT_TRIGGER_BASE, APX_WDT_TRIGGER_NUM);
}
int hello_world (int argc, char * const argv[])
{
	int i;

	// enable_watchdog();
	// reset_watchdog();

	disable_watchdog();

	/* Set GPIO40 as OUTPUT, LOW */
	WDT_DIR_OUT_GPIO(GPIO2_BASE_ADDR, LED_PIN);
	WDT_SET_L_GPIO(GPIO2_BASE_ADDR, LED_PIN);


	/* Print the ABI version */
	app_startup(argv);
	printf ("Example expects ABI version %d\n", XF_VERSION);
	printf ("Actual U-Boot ABI version %d\n", (int)get_version());

	printf ("Hello World\n");

	printf ("argc = %d\n", argc);

	for (i=0; i<=argc; ++i) {
		printf ("argv[%d] = \"%s\"\n",
			i,
			argv[i] ? argv[i] : "<NULL>");
	}

	printf ("Hit any key to exit ... ");
	while (!tstc())
	{
		for(timer_value = 0; timer_value < 4000000; timer_value++)
		{
			for(timer_value_1 = 0; timer_value_1 < 5; timer_value_1++)
			{
			}
		}
		WDT_SET_H_GPIO(GPIO2_BASE_ADDR, LED_PIN);  /* LED ON */
		// reset_watchdog();

		for(timer_value = 0; timer_value < 4000000; timer_value++)
		{
			for(timer_value_1 = 0; timer_value_1 < 5; timer_value_1++)
			{
			}
		}
		WDT_SET_L_GPIO(GPIO2_BASE_ADDR, LED_PIN);  /* LED OFF */
	}

	/* consume input */
	(void) getc();

	printf ("\n\n");
	return (0);
}
