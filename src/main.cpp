/*
 * Parth Sarthi Sharma (pss242@cornell.edu)
 * Code based on examples from Raspberry Pi Foundation.
 * This code is an implementation of the famous snake game.
 * It uses 4 GPIO pins to control the snake which has to eat the food
 * in order to grow in length.
 */

//Include necessary libraries
#include "pico/stdlib.h"
#include "pico/time.h"
#include <stdio.h>
#include <math.h>

//Picopad specific libraries
#include "picopad_fonts.h"
#include "picopad_init.h"
#include "picopad_key.h"

//Graphics and display libraries
#include "lib_drawtft.h"
#include "st7789.h"

#define HEIGHT 240
#define WIDHT 320

//Structure to hold the node (each point) of the snake.
//The snake is constructed using a linked list type data structure.
typedef struct Node{ //Node structure
short x; //The x coordinate and the y coordinate of the node
short y; 
struct Node *next; //The next node of the snake
}Node;

Node *head = NULL; //The head of the snake

short food[2]; //The array to hold x-coordinate and the y-coordinate of the food
volatile char direction = KEY_RIGHT; //The current direction of the snake
char alive = 1; //The flag that determines if the snake is alive
volatile char reset = 1; //The reset flag

inline int randomRange(int min, int max){ //Function to generate a random number between min and max
    return (rand() % (max - min)) + min;
}

void setPixel(short x, short y, uint16_t color) {
    DispDirtyPoint(x, y);
    DispUpdate();
}

void drawRect(short x, short y, short width, short height, uint16_t color) {
    for (short i = y; i < y + height; i++) {
        for (short j = x; j < x + width; j++) {
            setPixel(j, i, color);
        }
    }
    DispUpdate();
}

void swap(short *x, short *y){ //Function to swap two shorts
    if(*x != *y){
        *x = *x ^ *y;
        *y = *x ^ *y;
        *x = *x ^ *y;
    }
}

void genFood(){ //The function to generate the food
genAgain:
    food[0] = randomRange(0, HEIGHT); //Get a random x coordinate
    food[1] = randomRange(0, HEIGHT); //Get a random y coordinate
    Node *current = head; //Create a new current node
    current = current->next; //Make the current node point to the next node
    while(current != NULL){ //Iterate to the end of the list
        if(food[0] == current->x && food[1] == current->y){ //If at any point the food lies on the body of the snake
            goto genAgain; //Generate new coordinates for the food
        }
        current = current->next; //Else point to the next node
    }
    drawRect(food[0] << 2, food[1] << 2, 4, 4, COL_YELLOW); //Draw a yellow rectangle for food
    DispUpdate();
}

void addNode(short x, short y){ //Function to add a new node for the snake
    if(head == NULL){ //If the linked list is empty
        head = (Node *)malloc(sizeof(Node)); //Allocate memory for the head
        head->x = x; //Set x-coordinate for the head
        head->y = y; //Set y-coordinate for the head
        head->next = NULL; //Make the next of head as NULL
        drawRect(x << 2, y << 2, 4, 4, COL_RED); //Draw a red rectangle for head
    }
    else{ //Else
        Node *current = head; //Create a new pointer pointing to the head
        while(current->next != NULL){ //Iterate to the last element of the list
            current = current->next;
        }
        current->next = (Node *)malloc(sizeof(Node)); //Allocate new memory for the next node
        current->next->x = x; //Set x-coordinate for the new node
        current->next->y = y; //Set y-coordinate for the new node
        current->next->next = NULL; //Set the next node as NULL
        drawRect(x << 2, y << 2, 4, 4, COL_GREEN); //Draw a green rectangle for the list
    }
    DispUpdate();
}

void move(short x, short y){ //Function to move the snake such that the new coordinates of the head are x, y
    drawRect(x << 2, y << 2, 4, 4, COL_RED); //Draw the new head
    Node *current = head; //Create a new pointer pointing to the head
    while(current != NULL){ //For all the elements of the snake's body
        drawRect(current->x << 2, current->y << 2, 4, 4, COL_GREEN); //Draw the new snake body
        //Swap the coordinates and the current node coordinates
        swap(&(current->x), &x);
        swap(&(current->y), &y);
        current = current->next; //Go over to the next node
        if(current != NULL){ //If the current node is not null
            if(current->x == head->x && current->y == head->y){ //If the snake eats itself
                alive = 0; //Kill it
                drawRect(head->x << 2, head->y << 2, 4, 4, COL_RED); //Draw the head one last time
                pDrawFont = FontBoldB8x14;
                DrawFontHeight = 12; //Set the text size as 4
                DrawText2("Had je mrtev", 100, 200, COL_WHITE); //Print the message
                break;
            }
        }
    }
    DispUpdate();

    drawRect(x << 2, y << 2, 4, 4, COL_BLACK); //Clear the oldest element
    DispUpdate();
}

void eatAndMove(short x, short y){ //Function to eat the food and still move by increasing the length of the snake
    drawRect(x << 2, y << 2, 4, 4, COL_RED); //Draw the new head
    Node *current = head; //Create a new pointer pointing to the head
    while(current->next != NULL){ //For all the elements until the second last element of the snake's body
        //Store the old values of x and y coordinates in the temporary placeholders
        drawRect(current->x << 2, current->y << 2, 4, 4, COL_GREEN); //Draw the new snake body
        //Swap the coordinates and the current node coordinates
        swap(&(current->x), &x);
        swap(&(current->y), &y);
        current = current->next; //Go over to the next node
    }
    DispUpdate();

    current->next = (Node *)malloc(sizeof(Node)); //Allocate new memory for the next node
    //Update the new coordinates of the body
    drawRect(current->x << 2, current->y << 2, 4, 4, COL_GREEN); //Draw the new snake body
    //Swap the coordinates and the current node coordinates
    swap(&(current->x), &x);
    swap(&(current->y), &y);
    current = current->next;  //Go over to the next node
    //Update the last element of the body
    current->x = x;
    current->y = y;
    current->next = NULL; //Make the last element point to NULL
    DispUpdate();
}

void moveUp(){ //The function to move UP
    if(head->x == food[0] && head->y == food[1]){ //If the head is on the food
        if(head->y == 0){ //If the head is on the top edge of the screen
            eatAndMove(head->x, HEIGHT - 1); //Eat the food and move to the bottom edge of the screen
        }
        else{ //Else
            eatAndMove(head->x, head->y - 1); //Eat the food and move UP
        }
        genFood(); //Generate new food
    }
    else{ //Else
        if(head->y == 0){ //If the head is on the top edge of the screen
            move(head->x, HEIGHT - 1); //Move to the bottom edge of the screen
        }
        else{ //Else
            move(head->x, head->y - 1); //Move UP
        }
    }
}

void moveDown(){ //The function to move DOWN
    if(head->x == food[0] && head->y == food[1]){ //If the head is on the food
        if(head->y == HEIGHT - 1){ //If the head is on the bottom edge of the screen
            eatAndMove(head->x, 0); //Eat the food and move to the top edge of the screen
        }
        else{ //Else
            eatAndMove(head->x, head->y + 1); //Eat the food and move DOWN
        }
        genFood(); //Generate new food
    }
    else{ //Else
        if(head->y == HEIGHT - 1){ //If the head is on the bottom edge of the screen
            move(head->x, 0); //Move to the top edge of the screen
        }
        else{ //Else
            move(head->x, head->y + 1); //Move DOWN
        }
    }
}

void moveLeft(){ //The function to move LEFT
    if(head->x == food[0] && head->y == food[1]){ //If the head is on the food
        if(head->x == 0){ //If the head is on the left edge of the screen
            eatAndMove(WIDTH - 1, head->y); //Eat the food and move to the right edge of the screen
        }
        else{ //Else
            eatAndMove(head->x - 1, head->y); //Eat the food and move LEFT
        }
        genFood(); //Generate new food
    }
    else{ //Else
        if(head->x == 0){ //If the head is on the left edge of the screen
            move(WIDTH - 1, head->y); //Move to the right edge of the screen
        }
        else{ //Else
            move(head->x - 1, head->y); //Move LEFT
        }
    }
}

void moveRight(){ //The function to move RIGHT
    if(head->x == food[0] && head->y == food[1]){ //If the head is on the food
        if(head->x == WIDTH - 1){ //If the head is on the right edge of the screen
            eatAndMove(0, head->y); //Eat the food and move to the left edge of the screen
        }
        else{ //Else
            eatAndMove(head->x + 1, head->y); //Eat the food and move RIGHT
        }
        genFood(); //Generate new food
    }
    else{ //Else
        if(head->x == WIDTH - 1){ //If the head is on the right edge of the screen
            move(0, head->y); //Move to the left edge of the screen
        }
        else{ //Else
            move(head->x + 1, head->y); //Move RIGHT
        }
    }
}

void changeDir(uint gpio, uint32_t events) { //The change direction interrupt handler
    if(alive){ //If the snake is alive
        switch(gpio){ //Switch based on the GPIO
            case BTN_UP_PIN: direction = (direction == KEY_DOWN ? KEY_DOWN : KEY_UP); //If the command is to go UP and the snake isn't going DOWN, go UP
                         break;
            case BTN_DOWN_PIN: direction = (direction == KEY_UP ? KEY_UP : KEY_DOWN); //If the command is to go DOWN and the snake isn't going UP, go DOWN
                           break;
            case BTN_LEFT_PIN: direction = (direction == KEY_RIGHT ? KEY_RIGHT : KEY_LEFT); //If the command is to go LEFT and the snake isn't going RIGHT, go LEFT
                           break;
            case BTN_RIGHT_PIN: direction = (direction == KEY_LEFT ? KEY_LEFT : KEY_RIGHT); //If the command is to go RIGHT and the snake isn't going LEFT, go RIGHT
                            break;
            default: break;
        }
    }
    else{ //If the snake is dead
        reset = 1; //Set the reset flag
    }
}

int main()
{
    DeviceInit();
    
    //stdio_init_all();//Initialize all of the present standard stdi
    
    short i; //An interator
    srand(1); //Random seed

/*  gpio_set_irq_enabled_with_callback(BTN_UP_PIN, GPIO_IRQ_EDGE_FALL, true, &changeDir); //Attach the callback to the specified GPIO
    gpio_set_irq_enabled_with_callback(BTN_DOWN_PIN, GPIO_IRQ_EDGE_FALL, true, &changeDir); //Attach the callback to the specified GPIO
    gpio_set_irq_enabled_with_callback(BTN_LEFT_PIN, GPIO_IRQ_EDGE_FALL, true, &changeDir); //Attach the callback to the specified GPIO
    gpio_set_irq_enabled_with_callback(BTN_RIGHT_PIN, GPIO_IRQ_EDGE_FALL, true, &changeDir); //Attach the callback to the specified GPIO */

    while(True){ //While eternity
        if(reset){ //If the reset flag has been set
            drawRect(0, 0, WIDTH, HEIGHT, COL_BLACK); //Clear the screen
            alive = 1; //Resurrect the snake

            //Clear the linked list
            Node *tmp; //Create a temporary node
            while(head != NULL){ //While head exists
                tmp = head; //Make the temp as head
                head = head->next; //Head is the next of itself
                free(tmp); //Free the temp
            }
            //Create the snake
            for(i = 0; i < 8; i++){
                addNode((WIDTH / 2) - i, HEIGHT / 2);
            }
            direction = KEY_RIGHT; //Set default direction to be RIGHT
            genFood(); //Generate food
            reset = 0; //Clear the reset flag
        }
        while(alive){ //While the snake is alive
            //unsigned long begin_time = (unsigned long)(get_absolute_time() / 1000); //Save the start time of the loop
            absolute_time_t current_time = get_absolute_time();
            uint64_t current_time_ms = to_us_since_boot(current_time) / 1000;
            unsigned long begin_time = (unsigned long)current_time_ms;

            switch(direction){ //Switch based on the direction the snake is moving in
                case KEY_UP: moveUp(); //If the direction is UP, move UP
                            break;
                case KEY_DOWN: moveDown(); //If the direction is DOWN, move DOWN
                            break;
                case KEY_LEFT: moveLeft(); //If the direction is LEFT, move LEFT
                            break;
                case KEY_RIGHT: moveRight(); //If the direction is RIGHT, move RIGHT
                            break;
                default: break;
            }

            sleep_ms(33 - ((unsigned long)current_time_ms - begin_time));
        }
    }

}