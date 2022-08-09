
// ============================================================================== //
// Project Name : Vehicle Control System - C - M.T. Diploma 65                    //
// File Name    : Source.c                                        //
// Author       : Hossam Nasr                                                     //
// Version      : Final Version (20 / 04 / 2022)                                  //
// ============================================================================== //


#include <stdio.h>
#include "Global_Variables_Function_Prototypes.h"


// ========================== Main Function ==================================== //

/* function main begins program execution */
int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	get_the_user_choice(); /* get the the user choice when needed */

	check_mainMENU_option(); /* check which option the user choose */
} /* end main function */



// ========================= Functions Definitions ============================= //

/* function definition: get the the user choice when needed */
void get_the_user_choice(void)
{
	/* represent the options to the user to choose from */
	printf("Choose what you want:\n");
	printf("=====================\n");
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n");

	/* prompt the user to enter a choice and read it from the console */
	printf("\nEnter a character indicating what you want: ");
	scanf(" %c", &choice);
} /* end get_the_user_choice function */



/* function definition: check which option at the beginning the user choose */
void check_mainMENU_option(void)
{
	/* use switch cases to choose the proper set of operations to apply */
	switch( choice )
	{
		case 'a':
		case 'A':
			engine_state = ON;
			printf("\n<<< The vehicle engine is ON >>>\n\n"); /* print the system current state */
			/* while the engine is ON, menu always displayed and waits for an answer */
			while( engine_state == ON )
			{
				sensors_set_menu(); /* print the sensor set menu and let the user decide what to do */
				check_sensorMENU_option(); /* check which option at the sensor menu the user choose */
				if( choice == 'A' || choice == 'a' )
				{
					print_state(); /* print the state of the vehicle to the console */
				}
			} /* end while */
			break;

		case 'b':
		case 'B':
			printf("\n<<< The vehicle engine is OFF >>>\n\n"); /* print the system current state */
			/* go back to the choice phase to let the user choose again */
			while( choice == 'b' || choice == 'B')
			{
				get_the_user_choice(); /* get the the user choice when needed */
				check_mainMENU_option(); /* check which option at the beginning the user choose, this function call itself */
			} /* end while */
			break;

		case 'c':
		case 'C':
			printf("\n<<< Quit System >>>\n"); /* print the system current state */
			return; /* quit the program by return any number to the main function of return type void */
			break; /* optional: not necessary as the program will end directly after return */

		default: /* user input undefined symbol */
			printf("\nInvalid Input. Try to input a valid one.\n\n"); /* inform the user that he/she has inputed an invalid input */
			/* prompt the user to input a valid choice */
			get_the_user_choice(); /* get the the user choice when needed */
			check_mainMENU_option(); /* check which option at the beginning the user choose, this function call itself */
			break; /* optional: will exit switch anyway */
	} /* end switch */
} /* end check_which_option function */




/* function definition: print the sensor set menu and let the user decide what to do */
void sensors_set_menu(void)
{
	/* represent the options to the user to choose from */
	printf("Choose the right option:\n");
	printf("========================\n");
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature\n");
	printf("d. Set the engine temperature\n\n");

	/* prompt the user to enter a choice and read it from the console */
	printf("Enter a character indicating what you want: ");
	scanf(" %c", &sensor_choice);
} /* end sensors_set_menu function */




/* function definition: check which option at the sensor menu the user choose */
void check_sensorMENU_option(void)
{
	/* use switch cases to choose the proper set of operations to apply */
	switch( sensor_choice )
	{
		case 'a':
		case 'A':
			engine_state = OFF; /* make the engine state OFF */
			choice = 'b'; /* manipulate the choice variable to be (b) to loop again on the main menu */
			/* go back to the choice phase to let the user choose again */
			printf("\n");
			get_the_user_choice();
			check_mainMENU_option();
			break;

		case 'b':
		case 'B':
			traffic_light(); /* get the traffic light data and decide what to do */
			/* check the special case of the speed of 30 to set the proper values */
			if( vehicle_speed == 30 )
			{
				speed_30_case(); /* put proper values for the special case of the speed of 30 */
				return;
			}
			break;

		case 'c':
		case 'C':
			/* check the special case of the speed of 30 to set the proper values */
			if( vehicle_speed == 30 )
			{
				speed_30_case(); /* put proper values for the special case of the speed of 30 */
				/* do not call the function of room temperature as it is already set at the special case of the speed 30 */
				return; /* return blank as it is a void function */
			}
			room_temperature();
			break;

		case 'd':
		case 'D':
			/* check the special case of the speed of 30 to set the proper values */
			if( vehicle_speed == 30 )
			{
				speed_30_case(); /* put proper values for the special case of the speed of 30 */
				/* do not call the function of engine temperature as it is already set at the special case of the speed 30 */
				return; /* return blank as it is a void function */
			}
			engine_temperature();
			break;


		default:
			/* inform the user that his input is invalid and make him choose again */
			printf("\nInvalid Input. Try to input a valid one.\n\n");
			sensors_set_menu();
			check_sensorMENU_option();
			break; /* optional: will exit switch anyway */
	} /* end switch */
} /* end check_sensor_option function */




/* function definition: get the traffic light data and decide what to do */
void traffic_light(void)
{
	char traffic_light_data; /* variable to store the data of the traffic light */

	/* represent the options of the traffic light to the user to choose from */
	printf("\nChoose from the traffic light options:\n");
	printf("======================================\n");
	printf("G. Green\n");
	printf("O. Yellow\n");
	printf("R. Red\n\n");

	/* prompt the user to enter the traffic light data from the console */
	printf("Enter the current traffic light color: ");
	scanf(" %c", &traffic_light_data);

	/* use switch cases to choose the proper set of operations to apply */
	switch( traffic_light_data )
	{
		/* check if the traffic light is green */
		case 'g':
		case 'G':
			vehicle_speed = 100; /* set the vehicle speed to 100 km/hr */
			break;

		/* check if the traffic light is yellow */
		case 'o':
		case 'O':
			vehicle_speed = 30; /* set the vehicle speed to 30 km/hr */
			break;

		/* check if the traffic light is red */
		case 'r':
		case 'R':
			vehicle_speed = 0; /* set the vehicle speed to 0 km/hr */
			break;

		default: /* user input undefined symbol */
			printf("\nInvalid Input.\n"); /* inform the user that he/she has inputed an invalid input */
			break; /* optional: will exit switch anyway */
	} /* end switch */
} /* end traffic_light function */




/* function definition: get the room temperature data and decide what to do */
void room_temperature(void)
{
	/* prompt the user to enter the room temperature data from the console */
	printf("\nEnter the current room temperature: ");
	scanf("%f", &curr_room_temperature);

	if( curr_room_temperature < 10 ) /* check if the room temperature is less than 10 */
	{
		/* turn the AC state to ON, and set the room temperature to 20 */
		ac_state = ON;
		room_temp = 20;
	}
	else if( curr_room_temperature > 30 ) /* check if the room temperature is greater than 30 */
	{
		/* turn the AC state to ON, and set the room temperature to 20 */
		ac_state = ON;
		room_temp = 20;
	}
	else /* otherwise */
	{
		/* turn the AC state to OFF */
		ac_state = OFF;
	}
} /* end room_temperature function */




/* function definition: get the engine_temperature data and decide what to do */
void engine_temperature(void)
{
	/* prompt the user to enter the engine temperature data from the console */
	printf("\nEnter the current engine temperature: ");
	scanf("%f", &curr_engine_temperature);

	if( curr_engine_temperature < 100 ) /* check if the engine temperature is less than 10 */
	{
		/* turn the Engine Temperature Controller state to ON, and set the engine temperature to 20 */
		etc_state = ON;
		engine_temp = 125;
	}
	else if( curr_engine_temperature > 150 ) /* check if the room temperature is greater than 30 */
	{
		/* turn the Engine Temperature Controller state to ON, and set the engine temperature to 20 */
		etc_state = ON;
		engine_temp = 125;
	}
	else /* otherwise */
	{
		/* turn the Engine Temperature Controller state to OFF */
		etc_state = OFF;
	}
} /* end room_temperature function */


/* function definition: put proper values for the special case of the speed of 30 */
void speed_30_case(void)
{
	/* inform the user that he entered a special case so it will need to provide some additional data */
	printf("\nThe speed is 30 Km/Hr and this is special case\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

	/* set the values of the system by calling special functions */
	adjust_AC(); /* do the special case needed operations for AC */
	adjust_ETC(); /* do the special case needed operations for ETC */
} /* end speed_30_case function */




/* function definition: do the special case needed operations for AC */
void adjust_AC(void)
{
	/* prompt the user to enter the room temperature data from the console */
	printf("\nEnter the current room temperature: ");
	scanf("%f", &curr_room_temperature);

	ac_state = ON; /* turn the AC state to ON */
	room_temp = ( curr_room_temperature * 5/4 ) + 1; /* set the room temperature */

	printf("\n"); /* print double of new line for readability */
} /* end adjust_AC */




/* function definition: do the special case needed operations for ETC */
void adjust_ETC(void)
{
	/* prompt the user to enter the engine temperature data from the console */
	printf("Enter the current engine temperature: ");
	scanf("%f", &curr_engine_temperature);

	etc_state = ON; /* turn the Engine Temperature Controller state to ON */
	engine_temp = ( curr_engine_temperature * 5/4 ) + 1; /* set the engine temperature  */
} /* end adjust_ETC */




/* function definition: print the state of the vehicle to the console */
void print_state(void)
{
	/* print a header for the state print */
	printf("\nCurrent vehicle state\n");
	printf("*********************\n");

	/* print the engine state */
	printf("Engine State: ");
	engine_state == ON ? printf("ON\n"): printf("OFF\n");

	/* print the AC state */
	printf("AC State: ");
	ac_state == ON ? printf("ON\n"): printf("OFF\n");

	printf("Vehicle Speed: %d Km/Hr\n", vehicle_speed); /* print the vehicle state */

	printf("Room Temperature: %.3f C\n", room_temp); /* print the room temperature */

	/* print the Engine Temperature Controller state */
	printf("Engine Temperature Controller: ");
	etc_state == ON ? printf("ON\n"): printf("OFF\n");

	printf("Engine Temperature: %.3f C\n\n", engine_temp); /* print the engine temperature */
} 
/* end print_state function */
