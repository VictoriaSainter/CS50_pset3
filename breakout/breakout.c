//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// height and width of paddle in pixels
#define PADDLEHEIGHT 20
#define PADDLEWIDTH 50

// height and width of circle in pixels
#define CIRCLEHEIGHT 20
#define CIRCLEWIDTH 20

// height and width of Bricks in pixels
#define BRICKHEIGHT 15
#define BRICKWIDTH 35

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3


// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    //velocity of ball
    double xVelocity = drand48() + 1.5;
    double yVelocity = 3 ;
    
    //start on mouse click
    waitForClick();
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // TODO 
        
        //1) PADDLE MOVES WITH MOUSE
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        
        if (event != NULL)
        {
            if ( getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - getWidth(paddle) / 2;
                double y = getY(paddle);// - getWidth(paddle);
                
                if (x < 0)
                {
                    x = 0;
                }
                
                if (x > 350)
                {
                    x = 350;
                }
                setLocation(paddle, x, y);
            }
            
            
        }
        //2) Ball moves/bounces

        
        move(ball, xVelocity, yVelocity);
        //ball bounces off bottom of window
        if (getY(ball) + getWidth(ball) >= HEIGHT )
        {
            pause(20);
            lives--;
            setLocation(ball, (WIDTH/2) - (CIRCLEWIDTH / 2 ), ((HEIGHT/2) - (CIRCLEHEIGHT * 2)));
            setLocation(paddle, (WIDTH/2) - (PADDLEWIDTH / 2 ), (HEIGHT - (PADDLEHEIGHT * 2)));
            waitForClick();
        }
            

            
        //ball bounces off top of window
        else if (getY(ball) <= 0)
        {
            yVelocity = -yVelocity;
        }
        
        
        //ball bounces off RHS
        if (getX(ball) + getWidth(ball) >= WIDTH)
        {
            xVelocity = -xVelocity;
        }
        
        //ball bounces off LHS
        else if (getX(ball) <= 0)
        {
            xVelocity = -xVelocity;
        }
        
        //ball bounces off paddle, and bricks. If a brick, brick disappears
        GObject collidedObject = detectCollision(window, ball);
        
        if (collidedObject != NULL) 
        {
            if ( collidedObject == paddle)
            {
                yVelocity = -yVelocity;
            }
            else if (strcmp(getType(collidedObject), "GRect") == 0 && collidedObject != paddle) 
            {
                yVelocity = -yVelocity;
                removeGWindow(window, collidedObject);
                bricks--;
                points++;
                char pointsChar[2];
                sprintf(pointsChar, "%i", points);                     
                setLabel(label, pointsChar);
            }
        }

        pause(10);
        
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
 
void initBricks(GWindow window)
{
    // DONE!!!
    
    int newX = BRICKHEIGHT/2;
    int newY = BRICKHEIGHT;
    
    char *colors[] = { "YELLOW", "RED", "GREEN", "BLUE", "ORANGE" };
    
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            GRect newBrick = newGRect(newX, newY, BRICKWIDTH, BRICKHEIGHT);
            setFilled(newBrick, true);
            setColor(newBrick, colors[i]);
            newX += (BRICKWIDTH + 4);
            add(window, newBrick);
        }
    
    newY += BRICKHEIGHT + 5;
    newX = BRICKHEIGHT/2;
        
    }
}
   

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // DONE!!!!
    
    GOval circle = newGOval((WIDTH/2) - (CIRCLEWIDTH / 2 ), ((HEIGHT/2) - (CIRCLEHEIGHT * 2)), CIRCLEWIDTH, CIRCLEHEIGHT);
    setColor(circle, "BLACK");
    setFilled(circle, true);
    add(window, circle);
    return circle;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // DONE!!!!
    GRect newPaddle = newGRect ((WIDTH/2) - (PADDLEWIDTH / 2 ), (HEIGHT - (PADDLEHEIGHT * 2)) , PADDLEWIDTH, PADDLEHEIGHT);
    setFilled(newPaddle, true);
    setColor(newPaddle, "PINK");
    add(window, newPaddle);
    
    return newPaddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    
    GLabel scoreboard = newGLabel("0");
    setFont(scoreboard, "SansSerif-50");
    setColor(scoreboard, "d0d0d0");
    add(window, scoreboard);
    double x = (WIDTH - getWidth(scoreboard)) / 2;
    double y = (HEIGHT - getHeight(scoreboard)) / 2 + 50;
    setLocation(scoreboard, x, y);
    
    return scoreboard;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
