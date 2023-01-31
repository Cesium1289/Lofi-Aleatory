# Project Planning Assignment
## Features List
* UI - SMFL
* User options to adjust 
  * Root key 
  * Beats per measure
  * Beats per minute 
  * Envelope
  * Accent
  * Volume 
  * Sound wave type
  * Gain
* Let user create and pick preset audio values
* Runtime sound generation
* Allow user to randomize audio values



## MVP List
* Let user adjust values through command line
  * Root key 
  * Beats per measure
  * Beats per minute 
  * Envelope
  * Accent
  * Volume 
  * Sound wave type
  * Gain
* Command line argument validation
* Random sound option

## User Stories
* As a user, I want to know that each value I enter is valid so that each time I run the program it yields the same results. - Carson
* As a new user to our Lofi-Aleatory application I don’t know how to make my own sound. I want to have a button that will make a sound for me so that each time I click it, a unique sound is played each time. - Kyle
* As a music student, I want to generate different sounds so that I can learn about sound engineering theory. -Tien 

## Program Structure
The program will be broken down into serveral files, where the wave generation, audio values, and user interface will be defined. Main will then use these files as needed. The wave generation class will use the user defined audio values to generate each sound wave, and the ui will reflect those change.
