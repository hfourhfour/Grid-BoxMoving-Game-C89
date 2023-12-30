import java.util.*;

/**
* This piece of software takes input for shark sightings and performs various operations on them using menu selection.
* To start please input the sightings per day, per shark species as prompted.
* After sighting information is gathered, a menu will appear with various options.
*
* @Author Jet Ng 21209121
* @Version 1st September 2022
*/

public class TaskTwo
{
	public static void main(String[] args)
	{
        System.out.println("----------------------------------------------------------------------------------------------");
        System.out.println("Welcome to the Shark Sightings program.");
        int [] GreatWhite = new int[5]; // Initialise arrays for the 4 shark species and sightings variable used to store user input as prompted per day.
        int [] Tiger = new int[5];
        int [] GreyNurse = new int [5];
        int [] Mako = new int [5];
        int sightings = 0;
        System.out.println("Please start by typing in the following: ");

// GREAT WHITE INPUT LOOP
        System.out.println("Sightings per day for the following shark type: GREAT WHITE");      
        for (int i = 0; i < 5; i++)
        {
		    try
		    {   
                Scanner input = new Scanner(System.in);
                System.out.print("Day " + (i+1) + ": ");
                sightings  = input.nextInt();
                if (sightings >= 0)
                    {        
                        GreatWhite[i] = sightings;
                    	input.reset();        
                	}               
                else
                	{
                    	System.out.println("Please try again, if there were no sightings, please type in 0 for that day.");
                    	i = i - 1;
                	}
            }
        	catch (InputMismatchException e)
        	{
			    System.out.println("Your input was invalid (not an integer) please try again.");
                i = i - 1;
        	}
        }// END GREAT WHITE LOOP

// TIGER SHARK INPUT LOOP
    	System.out.println("Sightings per day for the following shark type: TIGER");      
        for (int i = 0; i < 5; i++)
        {
		    try
		    {   
                Scanner input = new Scanner(System.in);
                System.out.print("Day " + (i+1) + ": ");
                sightings  = input.nextInt();
                if (sightings >= 0)
                    {        
                        Tiger[i] = sightings;
                    	input.reset();        
                	}               
                else
                	{
                    	System.out.println("Please try again, if there were no sightings, please type in 0 for that day.");
                    	i = i - 1;
                	}
            }
        	catch (InputMismatchException e)
        	{
			    System.out.println("Your input was invalid (not an integer) please try again.");
                i = i - 1;
        	}
	    }//END TIGER LOOP

// GREY NURSE SHARK INPUT LOOP
    	System.out.println("Sightings per day for the following shark type: GREY NURSE");      
        for (int i = 0; i < 5; i++)
        {
		    try
		    {   
                Scanner input = new Scanner(System.in);
                System.out.print("Day " + (i+1) + ": ");
                sightings  = input.nextInt();
                if (sightings >= 0)
                    {        
                        GreyNurse[i] = sightings;
                    	input.reset();        
                	}               
                else
                	{
                    	System.out.println("Please try again, if there were no sightings, please type in 0 for that day.");
                    	i = i - 1;
                	}
            }
        	catch (InputMismatchException e)
        	{
			    System.out.println("Your input was invalid (not an integer) please try again.");
                i = i - 1;
        	}
	    }// END GREYNURSE LOOP

// MAKO SHARK INPUT LOOP
    	System.out.println("Sightings per day for the following shark type: MAKO");      
        for (int i = 0; i < 5; i++)
        {
		    try
		    {   
                Scanner input = new Scanner(System.in);
                System.out.print("Day " + (i+1) + ": ");
                sightings  = input.nextInt();
                if (sightings >= 0)
                    {        
                        Mako[i] = sightings;
                    	input.reset();        
                	}               
                else
                	{
                    	System.out.println("Please try again, if there were no sightings, please type in 0 for that day.");
                    	i = i - 1;
                	}
            }
        	catch (InputMismatchException e)
        	{
			    System.out.println("Your input was invalid (not an integer) please try again.");
                i = i - 1;
        	}
	    }//END MAKO LOOP

// START OF MENU
        int menu = 0;
        int choice = 0;
        Scanner input = new Scanner(System.in);
        do
        {        
		    try // START MENU TRY CATCH
        	{
                System.out.println();
                System.out.println("----------------------------------------------------------------------------------------------------------");
                System.out.println("Menu for Shark Sighting Information:");
                System.out.println("1. Display the average number of sightings for each shark species over the 5 days.");
                System.out.println("2. Display the shark species with the highest number of sightings on any of the 5 days.");
                System.out.println("3. Display the shark species with the lowest number of sightings on any of the 5 days.");
                System.out.println("4. Display percentage breakdown of total sightings over the 5 days by shark species.");
                System.out.println("5. Display the day that had the largest number of total shark sightings regardless of species.");
                System.out.println("0. Exit program.");
                System.out.println("----------------------------------------------------------------------------------------------------------");
	            System.out.println();
                System.out.print("Please select your menu option: ");
                input.reset();
                choice = input.nextInt();
                if (choice < 0 || choice > 5) // Check for invalid integer input
                {
                    System.out.println("Your input was not one of the menu options (1,2,3,4,5,0). Please try again using one of those.");
                    input.reset();
                }
                else if (choice == 1) // Menu Option 1, two loops to sum each array per shark and display average of summed array elements.
                {   
                    for (int j = 0; j < 4; j++)
                    {
                        int sum = 0;
                        int avg = 0;
                        if (j == 0)
                        {
                            for (int k = 0; k < 5; k++)
                            {
                                sum += GreatWhite[k];
                            } 
                            avg = (sum / 5);
                            System.out.println();
                            System.out.println("GREAT WHITE SHARK - Average sightings = " + avg); 
                        }
                        if (j == 1)
                        {
                            for (int k = 0; k < 5; k++)
                            {
                                sum += Tiger[k];
                            } 
                            avg = (sum / 5);
                            System.out.println("TIGER SHARK - Average sightings = " + avg); 
                        }
            			if (j == 2)
                        {
                            for (int k = 0; k < 5; k++)
                            {
                                sum += GreyNurse[k];
                            } 
                            avg = (sum / 5);
                            System.out.println("GREY NURSE SHARK - Average sightings = " + avg); 
                        }
		            	if (j == 3)
                        {
                            for (int k = 0; k < 5; k++)
                            {
                                sum += Mako[k];
                            } 
                            avg = (sum / 5);
                            System.out.println("MAKO SHARK - Average sightings = " + avg); 
                            System.out.println();
                        }
                    }
                input.reset();
                }
                else if (choice == 2) // Menu Option 2, sorting each array to get max value at end of array (at index 4). Then check index 4 of each array and print depending on largest value.
                {
                    Arrays.sort(GreatWhite);
		            Arrays.sort(Tiger);
		            Arrays.sort(GreyNurse);
		            Arrays.sort(Mako);
		            int a = GreatWhite[4];
		            int b = Tiger[4];	
		            int c = GreyNurse[4];
		            int d = Mako[4];
		            System.out.println();
		            if (Math.max(Math.max(a,b),Math.max(c,d)) == a)
		            {
		                System.out.println("The GREAT WHITE SHARK had the most amount of sightings over the 5 days at " + a + " sightings.");
		            }   
		            else if (Math.max(Math.max(a,b),Math.max(c,d)) == b)
		            {
		                System.out.println("The TIGER SHARK had the most amount of sightings over the 5 days at " + b + " sightings.");
		            }
		            else if (Math.max(Math.max(a,b),Math.max(c,d)) == c)
		            {
		                System.out.println("The GREY NURSE SHARK had the most amount of sightings over the 5 days at " + c + " sightings.");
		            }
		            else if (Math.max(Math.max(a,b),Math.max(c,d)) == d)
		            {
		                System.out.println("The MAKO SHARK had the most amount of sightings over the 5 days at " + d + " sightings.");
		            }
                input.reset();    
                }
        		else if (choice == 3) // Menu Option 3, Same process as for Menu Option 2, but pulling minimum value from index 0.
                {
                    Arrays.sort(GreatWhite);
		            Arrays.sort(Tiger);
		            Arrays.sort(GreyNurse);
		            Arrays.sort(Mako);
		            int a = GreatWhite[0];
		            int b = Tiger[0];	
		            int c = GreyNurse[0];
		            int d = Mako[0];
		            System.out.println();
		            if (Math.min(Math.min(a,b),Math.min(c,d)) == a)
		            {
		                System.out.println("The GREAT WHITE SHARK had the least amount of sightings over the 5 days at " + a + " sightings.");
		            }   
		            else if (Math.min(Math.min(a,b),Math.min(c,d)) == b)
		            {
		                System.out.println("The TIGER SHARK had the least amount of sightings over the 5 days at " + b + " sightings.");
		            }
		            else if (Math.min(Math.min(a,b),Math.min(c,d)) == c)
		            {
		                System.out.println("The GREY NURSE SHARK had the least amount of sightings over the 5 days at " + c + " sightings.");
		            }
		            else if (Math.min(Math.min(a,b),Math.min(c,d)) == d)
		            {
		                System.out.println("The MAKO SHARK had the least amount of sightings over the 5 days at " + d + " sightings.");
                    }
                input.reset();    
                }
		        else if (choice == 4) // Menu Option 4, two loops for summing each array per shark similar to Menu Option 2, then summing all arrays and finding percentage for each shark type.
                {
		            double greatW = 0;
		            double tiger = 0;
		            double greyN = 0;
		            double mako = 0;   
                    for (int j = 0; j < 4; j++)
                    {
                        int sum = 0;
                        if (j == 0)
                        {
                            for (int k = 0; k < 5; k++)
                            {
                                sum += GreatWhite[k];
                            } 
                            greatW = sum;
                        }
                        if (j == 1)
                        {
                            for (int k = 0; k < 5; k++)
                            {
                                sum += Tiger[k];
                            } 
                            tiger = sum;
                        }
            		    if (j == 2)
                        {
                            for (int k = 0; k < 5; k++)
                            {
                                sum += GreyNurse[k];
                            } 
                            greyN = sum;
                        }
		                if (j == 3)
                        {
                            for (int k = 0; k < 5; k++)
                            {
                                sum += Mako[k];
                            } 
                            mako = sum;
                        }
                    }
		            double percentTotal = (greatW + tiger + greyN + mako);
		            greatW = Math.round(greatW/percentTotal*100);
		            tiger = Math.round(tiger/percentTotal*100);
		            greyN = Math.round(greyN/percentTotal*100);
		            mako = Math.round(mako/percentTotal*100);
                    System.out.println();
		            System.out.println("Percentage breakdown of shark sightings over the 5 days: ");
		            System.out.println("GREAT WHITE SHARKS - " + greatW + "%");
		            System.out.println("TIGER SHARKS - " + tiger + "%");
		            System.out.println("GREY NURSE SHARKS - " + greyN + "%");
		            System.out.println("MAKO SHARKS - " + mako + "%");
                    input.reset();
                }
		        else if (choice == 5) // Menu Option 5, summing each day's index per shark then finding highest total day.
		        {
                    int d1 = 0;
                    int d2 = 0;
                    int d3 = 0;
                    int d4 = 0;
                    int d5 = 0;
                    System.out.println();
		            for (int j = 0; j < 5; j++) //for loop to sum index j of every shark, and assign to a day variable.
		            {
			            int sum = 0; 
			            sum += GreatWhite[j];
			            sum += Tiger[j];
			            sum += GreyNurse[j];
			            sum += Mako[j];
			            if (j == 0)
                        {
                            d1 = sum;
                        }	
			            if (j == 1)
                        {
                            d2 = sum;
                        }	
			            if (j == 2)
                        {
                            d3 = sum;
                        }	
			            if (j == 3)
                        {
                            d4 = sum;
                        }
			            if (j == 4)
                        {
                            d5 = sum;
                        }		
		            }
                    if (Math.max(Math.max(d2,d3),Math.max(d4,d5)) <= d1) // Maximum value checks for Days 1-5 from for loop above, to display based on which day has the highest sightings.
                    {
                        System.out.println("DAY 1 had the largest total number of shark sightings at " + d1 + ", regardless of species.");
                    }
                    else if (Math.max(Math.max(d1,d3),Math.max(d4,d5)) <= d2)
                    {
                        System.out.println("DAY 2 had the largest total number of shark sightings at " + d2 + ", regardless of species.");
                    }
                    else if (Math.max(Math.max(d1,d2),Math.max(d4,d5)) <= d3)
                    {
                        System.out.println("DAY 3 had the largest total number of shark sightings at " + d3 + ", regardless of species.");
                    }
                    else if (Math.max(Math.max(d1,d2),Math.max(d4,d5)) <= d4)
                    {
                        System.out.println("DAY 4 had the largest total number of shark sightings at " + d4 + ", regardless of species.");
                    }
                    else if (Math.max(Math.max(d1,d2),Math.max(d3,d4)) <= d5)
                    {
                        System.out.println("DAY 5 had the largest total number of shark sightings at " + d5 + ", regardless of species.");
                    } 
                }
                else if (choice == 0)
                {
                    menu = 1;
                    input.close();
                    System.out.println("Exiting...");
                }
        }// END OF MENU TRY
        catch (InputMismatchException e) // Check for input exceptions that aren't integers, similar error message and loop back to menu.
        {
            System.out.println("Your input was not an integer corresponding to a menu option. Please try again.");
			input.next();
        }// END MENU CATCH
            } while (menu == 0); // END OF MENU WHILE LOOP

    } // END MAIN
}// END CLASS
