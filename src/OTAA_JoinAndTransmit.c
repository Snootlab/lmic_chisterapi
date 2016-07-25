/*
 * Snootlab SAS
 *-----------------------------------------------------------------------------------------
 * Example of Joining a LoraWAN network and uplink some data.
 * This example is using "Over The Air" mode of LoraWAN specifications.
 * You have to get or to generate APPEUI, DEVEUI and DEVKEY.
 * You need to register these identifiers into the backend of your operator.
 * 
 * Nicolas Gonzalez <ngonzalez@snootlab.com>
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include <wiringPi.h>

#include <lmic.h>
#include <hal.h>
#include <local_hal.h>

/*
 *  APPEUI : Global Application ID that uniquely identifies the application provider
 *  DEVEUI : Global End-device ID that uniquely identifies the end-device
 *  DEVKEY : Application AES-128 key, could be different for every device
 *
 *  cf doc/LoraWAN_specification.pdf @6.2 Over-the-Air Activation
 */
static const u1_t APPEUI[8]  = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const u1_t DEVEUI[8]  = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const u1_t DEVKEY[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

/*
 * These three functions are accessor for
 * the LMIC library, do not modify.
 */
void os_getArtEui (u1_t* buf) 
{
    memcpy(buf, APPEUI, 8);
}

void os_getDevEui (u1_t* buf) 
{
    memcpy(buf, DEVEUI, 8);
}

void os_getDevKey (u1_t* buf) 
{
    memcpy(buf, DEVKEY, 16);
}

/*
 * Pinout for the LMIC library.
 * This is the pinout of the RFM95 on
 * the ChisteraPi.
 */
lmic_pinmap pins = {
  .nss = 10,
  .rxtx = UNUSED_PIN,
  .rst = 0,
  .dio = {7,4,5}
};

/*
 * Callback for all the events of the LMIC library.
 * There is much more events than three.
 *
 * cf doc/LMIC-v1.5.pdf @2.3 Application callbacks
 */
void onEvent (ev_t ev)
{
    switch(ev) 
    {
        case EV_JOINING:
	        fprintf(stdout, "Joining .........................................\n");
	        break;
        case EV_JOINED:
            fprintf(stdout, "Joined ..........................................\n");
            
            /* Send a buffer to the LoraWAN network 
             * The transmission of a byte (42) whithout acknowledgement.
             * If you want acknowledgment turn the '0' into a '1'.
             */
            LMIC.frame[0] = 42;
            LMIC_setTxData2(1, LMIC.frame, 1, 0);
	        break;
        case EV_TXCOMPLETE:
            fprintf(stdout, "TX complete .....................................\n");
            break;
        default:
            break;
    }
}

/*
 *  Example of a job function.
 *  LMIC library offer a job scheduler.
 *  You can use it on a linux environment 
 *  if you want to keep your software portable
 *  to another platform.
 *
 *  hellofunc is call every second and show
 *  the seconds since the start of the scheduler.
 */
static osjob_t periodicjob;
static void hellofunc(osjob_t* j)
{
    static unsigned long sec_counter = 0;
    printf("%d seconds\n", sec_counter++);
    os_setTimedCallback(j, os_getTime()+sec2osticks(1), hellofunc);
}

/*
 *  This is the main function.
 *  You can split it into two functions:
 *  setup() and loop() to keep the portability
 *  whith the Arduino environment.
 */
int main() 
{
  os_init();
  os_setCallback(&periodicjob, hellofunc);

  LMIC_reset();
  LMIC_startJoining();

  while (1) 
  {
      os_runloop();
      
      /*
       * LMIC is a microcontroller library so into
       * a linux environment you can add a tempo to
       * avoid 100% cpu ...
       */
      //usleep(1);      
  }

  return 0;
}
