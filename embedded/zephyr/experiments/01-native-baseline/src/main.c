#include<zephyr/kernel.h>
#include<zephyr/sys/printk.h>

int main(void)
{
	printk("experiment:native baseline\n");
	printk("extend main at %lld ms\n",(long long)(k_uptime_get()));

	
	// for(int i=0;i<=3;i++)
	// {
	// 	k_sleep(K_MSEC(500));
	// 	printk("heartbeat %d at%lld\n",i,k_uptime_get());
	// }
	int requested_ms[]={1,10,100,500};
	for(int i=0;i<4;i++)
	{
		int64_t before=k_uptime_get();
		k_msleep(requested_ms[i]);
		int64_t after=k_uptime_get();
		printk("requested=%d ms,observed=%lld ms \n",requested_ms[i],(after-before));
	}
	printk("main is returning now \n");
return 0;
}
